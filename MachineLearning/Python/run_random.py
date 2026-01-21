import flappy_env
import random

#run it from build/MachineLearning
#PYTHONPATH=. python3 ../../MachineLearning/Python/run_random.py

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
        result = env.step(random.choice(ACTIONS))

        total_reward += result.reward
        state = result.state
        done = result.done
        step += 1

    print(
        f"Episode {episode} finished "
        f"in {step} steps, total_reward={total_reward:.2f}"
    )