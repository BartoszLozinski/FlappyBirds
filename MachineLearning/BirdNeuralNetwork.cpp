#include "BirdNeuralNetwork.hpp"
#include <nlohmann/json.hpp>

#include <fstream>

using json = nlohmann::json;

namespace ReinforcementLearning
{
    DenseLayer::DenseLayer(const Weights& weights_, const Bias& bias_)
        : weights(weights_)
        , bias(bias_)
    {};

    NNOutput DenseLayer::Forward(const NNInput& input) const
    {
        NNOutput output(weights.size(), 0.0f);

        for (std::size_t i = 0; i < weights.size(); i++)
        {
            for (std::size_t j = 0; j < input.size(); j++)
                output[i] += weights[i][j] * input[j];

            output[i] += bias[i];
        }

        return output;
    }

    void BirdNeuralNetwork::Load(const std::string& filePath)
    {
        std::filesystem::path modelPath = std::filesystem::current_path();
        modelPath /= filePath;
        std::ifstream file{modelPath.string()};
        json j;
        file >> j;

        denseLayer1.weights = j["fc1.weight"].get<Weights>();
        denseLayer1.bias = j["fc1.bias"].get<Bias>();
        denseLayer2.weights = j["fc2.weight"].get<Weights>();
        denseLayer2.bias = j["fc2.bias"].get<Bias>();
    }

    BirdNeuralNetwork::BirdNeuralNetwork(const std::string& filePath)
    {
        Load(filePath);
    }

    float BirdNeuralNetwork::Forward(const std::vector<float>& input) const
    {
        auto hidden = denseLayer1.Forward(input);

        // ReLU (Rectified Linear Unit) activation
        for (auto& value : hidden)
            value = std::max(0.0f, value);

        auto output = denseLayer2.Forward(hidden);
        return output.at(0);
    }
};
