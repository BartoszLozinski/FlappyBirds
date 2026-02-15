#!/bin/bash

set -e #Stops at the first error

if [ ! -d "venv" ]; then
    python3 -m venv venv
fi

source venv/bin/activate

PYTHONPATH=build/MachineLearning python3 MachineLearning/Python/RunGeneticAlgorithm.py
PYTHONPATH=build/MachineLearning python3 MachineLearning/Python/ExportPtToJson.py

deactivate
