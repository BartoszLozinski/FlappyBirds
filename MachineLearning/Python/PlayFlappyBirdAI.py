import torch
import numpy as np
import gymnasium as gym
import flappy_env
import FlappyBirdEnvGym
from GeneticAlgorithm import PolicyNet

WINDOW_WIDTH = 800
WINDOW_HEIGHT = 600

MODEL_FILEPATH = "genetic_algorithm_flappy.pt"

# PYTHONPATH=build/MachineLearning python3 MachineLearning/Python/PlayFlappyBirdAI.py
# Load trained model


model = PolicyNet()
model.load_state_dict(torch.load(MODEL_FILEPATH))
model.eval()

# Create environment

env = FlappyBirdEnvGym.FlappyBirdEnvGym()
state, _ = env.reset()
# add render flag to C++ engine or extend Session class


def select_action(model, state):
    state_t = torch.tensor(state, dtype=torch.float32).unsqueeze(0)
    with torch.no_grad():
        p_jump = model(state_t).item()

    return 1 if p_jump > 0.5 else 0

# Run game


done = False
total_reward = 0
while not done:
    action = select_action(model, state)
    state, reward, done, _, _ = env.step(action)
    total_reward += reward

print(f"Total reward: {total_reward}")
