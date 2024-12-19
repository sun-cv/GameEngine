#ifndef VELOCITY_COMPONENT_H
#define VELOCITY_COMPONENT_H

#include "Component.h"
#include "Vector2.h"

class Velocity : public Component
{
    private:
    public:
        Vector2 velocity                        = {0, 0};
};

#endif