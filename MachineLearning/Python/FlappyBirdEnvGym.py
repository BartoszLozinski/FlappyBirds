import flappy_env
import gymnasium as gym
import numpy as np


# run it from build/MachineLearning
# python3 -m venv venv
# source venv/bin/activate
# run this from the main directory (FlappyBirds)
# PYTHONPATH=build/MachineLearning python3 MachineLearning/Python/FlappyBirdEnvGym.py

# Lets import model and check it visually

WINDOW_WIDTH = 800
WINDOW_HEIGHT = 600

class FlappyBirdEnvGym(gym.Env):
    def __init__(self):
        self.env = flappy_env.Environment()
        self.action_space = gym.spaces.Discrete(2)
        self.observation_space = gym.spaces.Box(
            low=np.array([-1.0, -1.0, -1.0, -1.0, 0.0], dtype=np.float32),
            high=np.array([1.0, 1.0, 1.0, 1.0, 1.0], dtype=np.float32),
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
            flappy_env.ControlOption.Jump if action == 1 else flappy_env.ControlOption.NoOp
        )

        result = self.env.step(action_enum)
        obs = self._obs(result.state)
        return obs, result.reward, result.done, False, {}

    def _obs(self, state):
        return np.array([
            state.bird_y / WINDOW_HEIGHT,
            np.clip(state.bird_vy / 40.0, -1.0, 1.0),
            (state.next_pipe_x - state.bird_x) / WINDOW_WIDTH,
            ((state.top_pipe_y + state.bottom_pipe_y) * 0.5  - state.bird_y) / WINDOW_HEIGHT,
            np.clip(state.frames_since_last_jump / 500.0, 0.0, 1.0)
        ], dtype=np.float32)

