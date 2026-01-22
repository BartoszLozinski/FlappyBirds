import flappy_env
import gymnasium as gym
import numpy as np
from gymnasium.utils.env_checker import check_env

#import random

#run it from build/MachineLearning
#PYTHONPATH=. python3 ../../MachineLearning/Python/FlappyBirdEnvGym.py

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


env = FlappyBirdEnvGym()
check_env(env, warn=True)

"""

env = flappy_env.Environment()
NUM_EPISODES = 5
MAX_STEPS = 10_000

ACTIONS = [
    flappy_env.ControlOption.NoOp,
    flappy_env.ControlOption.Jump,
]

for episode in range(NUM_EPISODES):
    state = env.reset()
    done = False
    step = 0
    total_reward = 0.0

    while not done and step < MAX_STEPS:
        #Random action (0 - none, 1 - jump)
        action = np.random.choice(ACTIONS)
        result = env.step(action)
        total_reward += result.reward
        state = result.state
        done = result.done
        step += 1

    print(
        f"Episode {episode} finished "
        f"in {step} steps, total_reward={total_reward:.2f}"
    )
    
"""