#pragma once

#include "CoreMath.h"
#include "Component.h"

class Transform : public Component
{
    private:
    public:
        glm::mat4 translate;
        glm::mat4 rotate;
        glm::mat4 scale;
        glm::mat4 matrix;
};