#pragma once

#include <tuple>
#include <vector>

#include "Vector2.h"

#include "CoreComponent.h"

namespace ECS
{
    using size = size_t;

    typedef std::tuple<
        std::vector<Enemy>,
        std::vector<Lifespan>,
        std::vector<Player>,
        std::vector<Position>,
        std::vector<Render>,
        std::vector<Title>,
        std::vector<Transform>,
        std::vector<Velocity>
    > VectorTuple;
}
