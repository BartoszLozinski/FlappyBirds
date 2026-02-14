import flappy_env
import gymnasium as gym
import numpy as np
import torch
import torch.nn as nn
import torch.nn.functional as F
import random
from FlappyBirdEnvGym import FlappyBirdEnvGym

WINDOW_WIDTH = 800
WINDOW_HEIGHT = 600

MODEL_FILEPATH = "../../genetic_algorithm_flappy.pt"

# run it from build/MachineLearning
# python3 -m venv venv
# source venv/bin/activate
# run this from the main directory (FlappyBirds)
# PYTHONPATH=build/MachineLearning python3 MachineLearning/Python/GeneticAlgorithm.py


# -------------- Neural Network --------------


class BirdNet(nn.Module):
    def __init__(self, input_dim=5, hidden_dim=32):
        super().__init__()
        self.fc1 = nn.Linear(input_dim, hidden_dim)
        self.fc2 = nn.Linear(hidden_dim, 1)
        self.sigmoid = nn.Sigmoid()

    def forward(self, x):
        x = F.relu(self.fc1(x)) # Rectified Linear Unit (ReLU)
        return self.fc2(x)
    
# Genetic algorithm helper functions


def get_weights(model):
    """Flatten weights to 1D array"""
    return np.concatenate([param.data.cpu().numpy().flatten() for param in model.parameters()])


def set_weights(model, weights):
    """Set model weights from 1D array"""
    pointer = 0
    for parameter in model.parameters():
        shape = parameter.data.cpu().numpy().shape
        size = parameter.data.numel()
        new_weights = weights[pointer:pointer+size].reshape(shape)
        parameter.data = torch.tensor(new_weights, dtype=torch.float32)
        pointer += size


def evaluate(model, env, max_steps=3000):
    state, _ = env.reset(seed=1234)
    total_reward = 0
    steps = 0

    while steps < max_steps:
        state_tensor = torch.tensor(state, dtype=torch.float32).unsqueeze(0)
        action = 1 if model(state_tensor).item() > 0.0 else 0
        next_state, reward, done, _, _ = env.step(action)
        total_reward += reward
        state = next_state
        steps += 1
        if done:
            break
    
    return total_reward


def mutate(weights, mutation_rate=0.05):
    new_weights = weights.copy()

    for i in range(len(new_weights)):
        if np.random.rand() < mutation_rate:
            if np.random.rand() < 0.9:
                new_weights[i] += np.random.normal(0, 0.1)  # small tweak
            else:
                new_weights[i] += np.random.normal(0, 1.0)  # big jump

    return new_weights


def crossover(w1, w2):
    mask = np.random.rand(len(w1)) > 0.5
    child = np.where(mask, w1, w2)
    return child


# Genetic algorithm

def run_genetic_algorithm(env, population_size=150, generations=50, elite_frac=0.2):
    # Initialize
    model = BirdNet()
    weight_shape = get_weights(model).shape[0]
    population = [np.random.randn(weight_shape) for _ in range(population_size)]
    best_ever = None
    best_score = -np.inf

    for generation in range(generations):
        fitness = []
        
        for individual in population:
            set_weights(model, individual)
            score = evaluate(model, env, 50000)
            fitness.append(score)

        fitness = np.array(fitness)

        gen_best_idx = fitness.argmax()
        gen_best_score = fitness[gen_best_idx]

        if gen_best_score > best_score:
            best_score = gen_best_score
            best_ever = population[gen_best_idx].copy()

        elite_count = int(population_size * elite_frac)
        elite_idx = fitness.argsort()[-elite_count:]
        elites = [population[i] for i in elite_idx]

        print(f"Generation {generation} | max reward: {fitness.max():.2f} | mean reward: {fitness.mean():.2f}")

        # Create next generation
        new_population = []
        if best_ever is not None:
            new_population.append(best_ever.copy())

        new_population.extend(elites)

        while len(new_population) < population_size:
            parent1, parent2 = random.sample(elites, 2)
            child = crossover(parent1, parent2)
            child = mutate(child, 0.05)
            new_population.append(child)

        population = new_population
        
        if (best_score > 500) and (generation > 10):
            print("Early stopping - good enough solution found")
            set_weights(model, best_ever)
            return model

    # Return best model
    set_weights(model, best_ever)
    return model
