#include "Graphics/Pipes.hpp"

namespace Graphics
{
    Pipes::Pipes(const Game::Pipes& pipes_)
        : pipes(pipes_)
        , pipesRenderable( Rectangle{ pipes.GetPipes()[0] }
                         , Rectangle{ pipes.GetPipes()[1] })
        {}
};