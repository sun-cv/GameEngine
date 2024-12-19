#ifndef ENTITY_CORE_H
#define ENTITY_CORE_H

#include <cmath>
#include <map>
#include <vector>

#include "ComponentCore.h"

namespace ECS
{
    using Type                                  = size_t;
    const Type INVALID_ENTITY                   = static_cast<Type>(-1);
    const Type ComponentCount                   = 6;

    typedef std::tuple<
        std::vector<Enemy>,
        std::vector<Player>,
        std::vector<Lifespan>,
        std::vector<Position>,
        std::vector<Render>,
        std::vector<Velocity>
>                                           EntityComponentVectorTuple;

}

#endif