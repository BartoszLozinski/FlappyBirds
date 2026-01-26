import flappy_env
import gymnasium as gym
import numpy as np
from gymnasium.utils.env_checker import check_env

import torch
import torch.nn as nn
import torch.nn.functional as F

from collections import deque
import random

# run it from build/MachineLearning
# PYTHONPATH=. python3 ../../MachineLearning/Python/FlappyBirdEnvGym.py

class FlappyBirdEnvGym(gym.Env):
    def __init__(self):
        self.env = flappy_env.Environment()

        self.action_space = gym.spaces.Discrete(2)
        
        self.observation_space = gym.spaces.Box(
            low=-np.inf,
            high=np.inf,
            shape=(5,),
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
            flappy_env.ControlOption.Jump if action == 1
            else flappy_env.ControlOption.NoOp
        )

        result = self.env.step(action_enum)
        obs = self._obs(result.state)
        return obs, result.reward, result.done, False, {}

    def _obs(self, state):
        return np.array([
            state.bird_y,
            state.bird_vy,
            state.next_pipe_x - state.bird_x,
            state.top_pipe_y,
            state.bottom_pipe_y
        ], dtype=np.float32)


class DQN(nn.Module):
    def __init__(self, state_dim, action_dim):
        super().__init__()
        self.net = nn.Sequential(
            nn.Linear(state_dim, 128),
            nn.ReLU(),
            nn.Linear(128, 128),
            nn.ReLU(),
            nn.Linear(128, action_dim)
        )

    def forward(self, x):
        return self.net(x)
    

class ReplyBuffer:
    def __init__(self, capacity):
        self.buffer = deque(maxlen=capacity)

    def push(self, state, action, reward, next_state, done):
        self.buffer.append((state, action, reward, next_state, done))

    def sample(self, batch_size):
        batch = random.sample(self.buffer, batch_size)
        state, action, reward, next_state, done = map(np.array, zip(*batch))
        return (
            torch.tensor(state, dtype=torch.float32),
            torch.tensor(action, dtype=torch.int64),
            torch.tensor(reward, dtype=torch.float32),
            torch.tensor(next_state, dtype=torch.float32),
            torch.tensor(done, dtype=torch.float32),
        )
    
    def __len__(self):
        return len(self.buffer)
    

def select_epsilon_greedy(policy, state, epsilon=0.1):
    if random.random() < epsilon:
        return random.randint(0, 1)
    else:
        state_tensor = torch.tensor(state, dtype=torch.float32).unsqueeze(0)
        with torch.no_grad():
            q_values = policy(state_tensor)
        return int(torch.argmax(q_values, dim=1).item())


def train_step(policy, target, replay, optimizer, batch_size=64, gamma=0.99):
    if len(replay) < batch_size:
        return
    
    states, actions, rewards, next_states, dones = replay.sample(batch_size)

    q_values = policy(states).gather(1, actions.unsqueeze(1)).squeeze(1)
    with torch.no_grad():
        next_q_values = target(next_states).max(1)[0]
    target_q = rewards + gamma * next_q_values * (1 - dones)

    loss = F.mse_loss(q_values, target_q)

    optimizer.zero_grad()
    loss.backward()
    optimizer.step()


# Minimal Training loop


env = FlappyBirdEnvGym()
check_env(env, warn=True)
#env.seed(42)

state_dim = 5
action_dim = 2

policy = DQN(state_dim, action_dim)
target = DQN(state_dim, action_dim)
target.load_state_dict(policy.state_dict())

optimizer = torch.optim.Adam(policy.parameters(), lr=1e-3)
replay = ReplyBuffer(100_000)

NUM_EPISODES = 10
MAX_STEPS = 1000

for episode in range(NUM_EPISODES):
    state, _ = env.reset(seed=42)
    done = False
    total_reward = 0
    steps = 0
    
    while not done and steps < MAX_STEPS:
        action = select_epsilon_greedy(policy, state, epsilon=0.1)
        next_state, reward, done, _, _ = env.step(action)

        replay.push(state, action, reward, next_state, done)
        state = next_state
        total_reward += reward
        steps += 1

        train_step(policy, target, replay, optimizer)

    if episode % 2 == 0:
        target.load_state_dict(policy.state_dict())

    print(f"Episode {episode} finished in {steps} steps, total_reward={total_reward:.2f}")



"""




"""