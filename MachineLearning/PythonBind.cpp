#include <pybind11/pybind11.h>
#include "Environment.hpp"

namespace py = pybind11;

PYBIND11_MODULE(flappy_env, m)
{
    py::class_<Gameplay::State>(m, "State")
        .def_readonly("bird_x", &Gameplay::State::birdX)
        .def_readonly("bird_y", &Gameplay::State::birdY)
        .def_readonly("bird_size", &Gameplay::State::birdSize)
        .def_readonly("bird_vy", &Gameplay::State::birdVy)
        .def_readonly("next_pipe_x", &Gameplay::State::nextPipeX)
        .def_readonly("top_pipe_y", &Gameplay::State::topPipeY)
        .def_readonly("bottom_pipe_y", &Gameplay::State::bottomPipeY)
        .def_readonly("pipe_size_x", &Gameplay::State::pipeSizeX)
        .def_readonly("pipe_size_y", &Gameplay::State::pipeSizeY)
        .def_readonly("pipes_gap_y", &Gameplay::State::pipesGapY)
        .def_readonly("can_jump", &Gameplay::State::birdAbleToJump)
        .def_readonly("frames_since_last_jump", &Gameplay::State::framesSinceLastJump);

    py::class_<ReinforcementLearning::DataTransition>(m, "StepResult")
        .def_readonly("state", &ReinforcementLearning::DataTransition::stateAfterAction)
        .def_readonly("reward", &ReinforcementLearning::DataTransition::reward)
        .def_readonly("done", &ReinforcementLearning::DataTransition::done);

    py::class_<ReinforcementLearning::Environment>(m, "Environment")
        .def(py::init<>())
        .def("reset", &ReinforcementLearning::Environment::Reset)
        .def("step", &ReinforcementLearning::Environment::RunStep);
}
