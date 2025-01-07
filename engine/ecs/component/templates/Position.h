#pragma once

#include "Component.h"
#include "Vector2.h"
namespace ECS
{
class Position : public Component
{
    private:
    public:
        float x;
        float y;

};
}