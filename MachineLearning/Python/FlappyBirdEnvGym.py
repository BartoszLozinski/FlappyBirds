import flappy_env
import gymnasium as gym
import numpy as np
import torch
import torch.nn as nn
import torch.nn.functional as F
import random

# run it from build/MachineLearning
# python3 -m venv venv
# source venv/bin/activate
# run this from the main directory (FlappyBirds)
# PYTHONPATH=build/MachineLearning python3 MachineLearning/Python/FlappyBirdEnvGym.py

WINDOW_WIDTH = 800
WINDOW_HEIGHT = 600

class FlappyBirdEnvGym(gym.Env):
    def __init__(self):
        self.env = flappy_env.Environment()
        self.action_space = gym.spaces.Discrete(2)
        self.observation_space = gym.spaces.Box(
            low=np.array([-1.0, -1.0, -1.0, -1.0], dtype=np.float32),
            high=np.array([1.0, 1.0, 1.0, 1.0,], dtype=np.float32),
            shape=(4,),
            dtype=np.float32
        )

    def reset(self, seed=None, options=None):
        super().reset(seed=seed)
        
        if seed is not None:
            self.env.seed(seed)

        self.env.reset()
        state = self.env.get_state()
        return self._obs(state), {}
    
    def step(self, action):
        action_enum = (
            flappy_env.ControlOption.Jump if action == 1 else flappy_env.ControlOption.NoOp
        )

        result = self.env.step(action_enum)
        obs = self._obs(result.state)
        return obs, result.reward, result.done, False, {}

    def _obs(self, state):
        return np.array([
            state.bird_y / WINDOW_HEIGHT,
            np.clip(state.bird_vy / 30.0, -1.0, 1.0),
            (state.next_pipe_x - state.bird_x) / WINDOW_WIDTH,
            ((state.top_pipe_y + state.bottom_pipe_y) * 0.5  - state.bird_y) / WINDOW_HEIGHT
        ], dtype=np.float32)


# -------------- Neural Network --------------

class BirdNet(nn.Module):
    def __init__(self, input_dim=4, hidden_dim=8):
        super().__init__()
        self.fc1 = nn.Linear(input_dim, hidden_dim)  # input layer and hidden layer
        self.fc2 = nn.Linear(hidden_dim, 1)  # hidden layer and jump probability (output layer)
        self.sigmoid = nn.Sigmoid()

    def forward(self, x):
        x = F.relu(self.fc1(x))
        x = self.sigmoid(self.fc2(x))
        return x
    
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


def evaluate(model, env, max_steps=1500):
    """Run single episode and return total reward"""
    state, _ = env.reset()
    total_reward = 0
    steps = 0

    while steps < max_steps:
        state_tensor = torch.tensor(state, dtype=torch.float32).unsqueeze(0)
        jump_probability = model(state_tensor).item()
        action = 1 if jump_probability > 0.5 else 0
        next_state, reward, done, _, _ = env.step(action)
        total_reward += reward
        state = next_state
        steps += 1
        if done:
            break
    
    return total_reward


def mutate(weights, mutation_rate=0.1):
    """Random Gaussian mutation"""
    new_weights = weights.copy()
    
    for i in range(len(weights)):
        if np.random.rand() < mutation_rate:
            new_weights[i] += np.random.normal(0, 0.2)

    return new_weights


def crossover(w1, w2):
    mask = np.random.rand(len(w1)) > 0.5
    child = np.where(mask, w1, w2)
    return child


# Genetic algorithm

def run_genetic_algorithm(env, population_size=50, generations=50, elite_frac=0.2):
    #Initialize
    model = BirdNet()
    weight_shape = get_weights(model).shape[0]
    population = [np.random.randn(weight_shape) for _ in range(population_size)]

    for generation in range(generations):
        fitness = []
        
        for individual in population:
            set_weights(model, individual)
            score = evaluate(model, env)
            fitness.append(score)

        fitness = np.array(fitness)
        elite_count = int(population_size * elite_frac)
        elite_idx = fitness.argsort()[-elite_count:]
        elites = [population[i] for i in elite_idx]

        print(f"Generation {generation} | max reward: {fitness.max():.2f} | mean reward: {fitness.mean():.2f}")

        # Create next generation
        new_population = elites.copy()
        while len(new_population) < population_size:
            parent1, parent2 = random.sample(elites, 2)
            child = crossover(parent1, parent2)
            child = mutate(child)
            new_population.append(child)

        population = new_population

    # Return best model
    best_idx = fitness.argmax()
    set_weights(model, population[best_idx])
    return model

# ---------- Run ----------


env = FlappyBirdEnvGym()
best_model = run_genetic_algorithm(env)

# Save trained model
torch.save(best_model.state_dict(), "genetic_algorithm_flappy.pt")
