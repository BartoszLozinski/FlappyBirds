#include "Environment.hpp"
/*
PYBIND11_MODULE(flappy_env, m)
{
    py::class_<Gameplay::State>(m, "State")
        .def_readonly("bird_x", &Gameplay::State::birdX)
        .def_readonly("bird_y", &Gameplay::State::birdY)
        .def_readonly("bird_vy", &Gameplay::State::birdVy)
        .def_readonly("next_pipe_x", &Gameplay::State::nextPipeX)
        .def_readonly("top_pipe_y", &Gameplay::State::topPipeY)
        .def_readonly("bottom_pipe_y", &Gameplay::State::bottomPipeY)
        .def_readonly("can_jump", &Gameplay::State::birdAbleToJump);

    py::class_<StepResult>(m, "StepResult")
        .def_readonly("state", &StepResult::next_state)
        .def_readonly("reward", &StepResult::reward)
        .def_readonly("done", &StepResult::done);

    py::class_<Environment>(m, "Environment")
        .def(py::init<>())
        .def("reset", &Environment::Reset)
        .def("step", &Environment::Step);
}
*/