import flappy_env

#TODO get or create CoreLogic instance and pass to environment

env = flappy_env.Environment()

state = env.reset()
print(state.bird_x, state.bird_y)

result = env.step(flappy_env.ControlOption.Jump)
print(result.state.bird_y, result.reward, result.done)
