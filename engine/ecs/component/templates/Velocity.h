#pragma once

#include "Component.h"
#include "Vector2.h"
namespace ECS
{
class Velocity : public Component
{
    private:
    public:
        float x;
        float y;
};
}