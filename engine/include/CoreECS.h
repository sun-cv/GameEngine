
#ifndef CORE_ECS_H
#define CORE_ECS_H

#include <vector>
#include <tuple>

#include "CoreComponent.h"

namespace ECS
{
    using size                                  = size_t;

    typedef std::tuple
    <
        std::vector<Enemy>,
        std::vector<Player>,
        std::vector<Lifespan>,
        std::vector<Position>,
        std::vector<Render>,
        std::vector<Velocity>
    >                                           VectorTuple;
}


namespace ECS
{
    const size ComponentCount                   = 6;
    const size MAX_ENTITIES                     = 100;
    const size INVALID_ENTITY                   = static_cast<size>(-1);
}

#include "Vector2.h"
#include "Entity.h"
#include "EntityMemoryPool.h"
#include "EntityManager.h"

namespace ECS
{
    class Vector2;
    class Entity;
    class EntityMemoryPool;
    class EntityManager;
}

#endif