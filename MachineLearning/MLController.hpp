#pragma once
#include "BirdNeuralNetwork.hpp"
#include <Game/IController.hpp>
#include "Gameplay/State.hpp"

#include <string>
#include <vector>

namespace ReinforcementLearning
{
    class MLController : public IController
    {
    private:
        BirdNeuralNetwork model;
        std::vector<float> Observe(const Gameplay::State& state) const;
        void DeduceControlOption(const float nnOutput);

    public:
        MLController() = delete;
        MLController(const std::string& filePath);
        [[nodiscard]] ControlOption Decide() const override;
        void UpdateStatus(const Gameplay::State& state);

    };

}
