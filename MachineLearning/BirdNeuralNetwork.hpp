#pragma once

#include <vector>
#include <string>

namespace ReinforcementLearning
{
    class BirdNeuralNetwork
    {
    private:
        std::vector<std::vector<float>> fullyConnecterLayer1_weights; // from input to hidden layer
        std::vector<float> fullyConnecterLayer1_bias;
        std::vector<float> fullyConnecterLayer2_weights; // from hidden layer to output
        float fullyConnecterLayer2_bias;
        void Load(const std::string& filePath);

    public:
        BirdNeuralNetwork() = default;
        BirdNeuralNetwork(const std::string& filePath);
        float Forward(const std::vector<float>& input) const;
    };    
}

