#pragma once

#include <vector>
#include <string>

namespace ReinforcementLearning
{
    using NNInput = std::vector<float>;
    using Weights = std::vector<std::vector<float>>;
    using Bias = std::vector<float>;
    using NNOutput = std::vector<float>;

    struct DenseLayer
    {
        Weights weights; //[outId][inId]
        Bias bias; //[outId]
        NNOutput Forward(const NNInput& input) const;
        DenseLayer(const Weights& weights_, const Bias& bias_);
        DenseLayer()  = default;
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

