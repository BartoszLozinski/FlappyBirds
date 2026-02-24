This is learning project for integration of Python ML tools, C++ game engine and Computer Vision (OpenCV - to be done)

1. For game rendering SFML library was used, while simple UI for game style selection was done using Qt
Neural network was trained using pytorch, exported to *.pt and then to *.json file.
The model is imported to C++ controller (AIDrivenSessionFlappyBird - MLController class) to evaluate it,
and controll bird behavior.

Main goal of this project was to play with architectural design, keep SOLID principles,
and involve integration between two technologies (Python and C++),
while NN-model performance is not an main object to optimize right now.

2. Architectural structure:

FlappyBirds
|
|___Core
|       |_Game logic
|       |_Graphics (Rendering)
|       |_UI (Qt)
|       |_Unit tests
|
|_Machine learning
        |_AI driven session (with ML Controller)
        |_Python:
                |_Gym (gymnasium module)
                |_Genetic algorithm (Pytorch)
                |_Training/Running/ModelExporting scirpts

3. Neural network architecture

Input:
- normalized bird Y-position
- clipped vertical velocirty
- normalized next pipe distance
- normalized gap offset
- clipped frames since last jump

Hidden layer:
- 32 neurons
- ReLU activation

Output:
- single linear neuron
- jump if output value > 0

Reward function:
- Simply +1 point per pipe passed and -1 point for death

![Demo](Assets/GifCV.gif)
