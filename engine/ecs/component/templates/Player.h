#pragma once

#include "Component.h"
namespace ECS
{
class Player : public Component
{
    private:
    public:
        bool state                               = true;
};
}