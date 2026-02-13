#include "BirdNeuralNetwork.hpp"
#include <nlohmann/json.hpp>

#include <fstream>
#include <iostream>

using json = nlohmann::json;

namespace ReinforcementLearning
{
    void BirdNeuralNetwork::Load(const std::string& filePath)
    {
        std::cout << "Current path: " << std::filesystem::current_path() << '\n';
        std::filesystem::path modelPath = std::filesystem::current_path();
        modelPath /= filePath;
        std::ifstream file(modelPath.string());
        json j;
        file >> j;

        fc1_weights = j["fc1.weight"].get<std::vector<std::vector<float>>>();
        fc1_bias = j["fc1.bias"].get<std::vector<float>>();
        fc2_weights = j["fc2.weight"][0].get<std::vector<float>>();
        fc2_bias = j["fc2.bias"][0];
    }

    BirdNeuralNetwork::BirdNeuralNetwork(const std::string& filePath)
    {
        Load(filePath);
    }

    float BirdNeuralNetwork::Forward(const std::vector<float>& input) const
    {
        std::vector<float> hidden(fc1_weights.size(), 0.0f);

        for (std::size_t i = 0; i < fc1_weights.size(); i++)
        {
            for (std::size_t j = 0; j < input.size(); j++)
                hidden[i] += fc1_weights[i][j] * input[j];

            hidden[i] += fc1_bias[i];
            hidden[i] = std::max(0.0f, hidden[i]);
        }

        float output = 0.0;
        for (std::size_t i = 0; i < hidden.size(); i++)
            output += fc2_weights[i] * hidden[i];

        output += fc2_bias;
        return output;
    }
};
