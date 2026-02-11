import torch
import os
from FlappyBirdEnvGym import FlappyBirdEnvGym
from GeneticAlgorithm import run_genetic_algorithm

# run it from build/MachineLearning
# python3 -m venv venv
# source venv/bin/activate
# run this from the main directory (FlappyBirds)
# PYTHONPATH=build/MachineLearning python3 MachineLearning/Python/RunGeneticAlgorithm.py

env = FlappyBirdEnvGym()
best_model = run_genetic_algorithm(env)

# Save trained model
os.makedirs("TrainedModel", exist_ok=True)
torch.save(best_model.state_dict(), "TrainedModel/genetic_algorithm_flappy.pt")
