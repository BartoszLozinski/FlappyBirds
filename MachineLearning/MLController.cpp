#include "MLController.hpp"
#include "Game/GameConfig.hpp"

#include <algorithm>

namespace ReinforcementLearning
{
    MLController::MLController(const std::string& filePath)
        : model(BirdNeuralNetwork{filePath})
    {};

    ControlOption MLController::Decide() const
    {
        return this->controlOption;
    }

    void MLController::DeduceControlOption(const float nnOutput)
    {
        controlOption = nnOutput > 0.0f ? ControlOption::Jump : ControlOption::None;
    }

    std::vector<float> MLController::Observe(const Gameplay::State& state) const
    {
        std::vector<float> observer(5);
        observer[0] = state.birdY / Game::Config::WINDOW_HEIGHT;
        observer[1] = std::clamp(state.birdVy / 40.0f, -1.0f, 1.0f);
        observer[2] = (state.nextPipeX - state.birdX) / Game::Config::WINDOW_WIDTH;
        observer[3] = ((state.gapTopVertexY + state.gapBottomVertexY) * 0.5f - state.birdY) / Game::Config::WINDOW_HEIGHT;
        observer[4] = std::clamp(state.framesSinceLastJump / 500.0f, 0.0f, 1.0f);

        return observer;
    }

    void MLController::UpdateStatus(const Gameplay::State& state)
    {
        const auto nnInput = Observe(state);
        const auto nnOutput = model.Forward(nnInput);
        DeduceControlOption(nnOutput);
    }

}
