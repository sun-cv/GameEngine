#pragma once

#include "Component.h"
namespace ECS
{
class Enemy : public Component
{
    private:
    public:
        bool state                              = true;
};
}