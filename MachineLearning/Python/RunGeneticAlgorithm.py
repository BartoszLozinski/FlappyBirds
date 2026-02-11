import torch
from pathlib import Path
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
save_path = Path("TrainedModel/genetic_algorithm_flappy.pt")
save_path.parent.mkdir(parents=True, exist_ok=True)
torch.save(best_model.state_dict(), save_path)
