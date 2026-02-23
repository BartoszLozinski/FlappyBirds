#include <pybind11/pybind11.h>
#include "Environment.hpp"

namespace py = pybind11;

/*

"Exports" C++ API to python, whereas LHS is python structure/architecture, and RHS is the C++ side
from build/MachineLearning dir simply run: PYTHONPATH=. python3 ../../MachineLearning/Python/script_name.py
to run your script with bindings

*/

PYBIND11_MODULE(flappy_env, m)
{
    py::enum_<ControlOption>(m, "ControlOption")
        .value("NoOp", ControlOption::None)//pythons None collides with pythons keyword
        .value("Jump", ControlOption::Jump)
        .export_values();

    py::class_<Gameplay::State>(m, "State")
        .def_readonly("bird_x", &Gameplay::State::birdX)
        .def_readonly("bird_y", &Gameplay::State::birdY)
        .def_readonly("bird_size", &Gameplay::State::birdSize)
        .def_readonly("bird_vy", &Gameplay::State::birdVy)
        .def_readonly("next_pipe_x", &Gameplay::State::nextPipeX)
        .def_readonly("gap_top_vertex_y", &Gameplay::State::gapTopVertexY)
        .def_readonly("gap_bottom_vertex_y", &Gameplay::State::gapBottomVertexY)
        .def_readonly("can_jump", &Gameplay::State::birdAbleToJump)
        .def_readonly("frames_since_last_jump", &Gameplay::State::framesSinceLastJump);

    py::class_<ReinforcementLearning::DataTransition>(m, "StepResult")
        .def_readonly("state", &ReinforcementLearning::DataTransition::stateAfterAction)
        .def_readonly("reward", &ReinforcementLearning::DataTransition::reward)
        .def_readonly("done", &ReinforcementLearning::DataTransition::done);

    py::class_<ReinforcementLearning::Environment>(m, "Environment")
        .def(py::init<>())
        .def("reset", &ReinforcementLearning::Environment::Reset)
        .def("get_state", &ReinforcementLearning::Environment::GetState)
        .def("step", &ReinforcementLearning::Environment::RunStep)
        .def("seed", &ReinforcementLearning::Environment::Seed);
};
