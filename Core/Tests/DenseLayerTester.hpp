#pragma once

#include <gtest/gtest.h>
#include "../MachineLearning/BirdNeuralNetwork.hpp"


struct DenseLayerFixture : public testing::Test
{
    //assume 2 inputs and 3-neuron hidden layer
    ReinforcementLearning::DenseLayer denseLayerFixture{
        { {0.1f, 0.2f}, {0.3f, 0.4f}, {0.5f, 0.6f} },
        { 0.1f, 0.1f, 0.1f }
    };
};

TEST_F(DenseLayerFixture, ForwardCalculationTest)
{
    const ReinforcementLearning::NNInput input{ 1.0f, 2.0f };
    const ReinforcementLearning::NNOutput expectedOutput{ 0.6f, 1.2f, 1.8f };

    const auto output = denseLayerFixture.Forward(input);
   
    for (std::size_t i = 0; i < expectedOutput.size(); i++)
        ASSERT_NEAR(expectedOutput[i], output[i], 1e-6f);
}
