import json
import torch
from GeneticAlgorithm import BirdNet

# PYTHONPATH=build/MachineLearning python3 MachineLearning/Python/ExportPtToJson.py

MODEL_PATH = "TrainedModel/genetic_algorithm_flappy.pt"
OUTPUT_JSON = "TrainedModel/genetic_algorithm_flappy.json"

model = BirdNet()
model.load_state_dict(torch.load(MODEL_PATH, map_location="cpu"))
model.eval()

state = model.state_dict()

export_dict = {}
for key, value in state.items():
    export_dict[key] = value.detach().cpu().numpy().tolist()

with open(OUTPUT_JSON, "w") as f:
    json.dump(export_dict, f, indent=4)

print("Model exported to JSON successfully.")
