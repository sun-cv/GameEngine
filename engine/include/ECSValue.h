#pragma once

namespace ECS
{
    using size                                  = size_t;
    using Entity                                = size_t;
    
    const size ComponentCount                   = 8;
    const size MAX_ENTITIES                     = 10000;
    const size INVALID_ENTITY                   = static_cast<size>(-1);
}
