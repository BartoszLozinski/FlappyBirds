#pragma once

#include <vector>
#include <string>

namespace ReinforcementLearning
{
    class BirdNeuralNetwork
    {
    private:
        std::vector<std::vector<float>> fc1_weights; // from input to hidden layer
        std::vector<float> fc1_bias;
        std::vector<float> fc2_weights; // from hidden layer to output
        float fc2_bias;
        void Load(const std::string& filePath);

    public:
        BirdNeuralNetwork() = default;
        BirdNeuralNetwork(const std::string& filePath);
        float Forward(const std::vector<float>& input) const;
    };    
}
