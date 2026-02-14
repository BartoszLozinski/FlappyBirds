#pragma once

#include <vector>
#include <string>

namespace ReinforcementLearning
{
    struct DenseLayer
    {
        std::vector<std::vector<float>> weights; //[outId][inId]
        std::vector<float> bias; //[outId]
        std::vector<float> Forward(const std::vector<float>& input) const;
    };

    class BirdNeuralNetwork
    {
    private:
        DenseLayer denseLayer1;
        DenseLayer denseLayer2;
        void Load(const std::string& filePath);

    public:
        BirdNeuralNetwork() = default;
        BirdNeuralNetwork(const std::string& filePath);
        float Forward(const std::vector<float>& input) const;
    };    
}

