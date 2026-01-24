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
