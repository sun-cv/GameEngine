#pragma once

#include "CoreMath.h"
#include "Component.h"

namespace ECS
{
class Transform : public Component
{
    private:
        glm::mat4 getIdentityMatrix() const
        {
            return glm::mat4(1.0f);
        }

    public:
        glm::mat4 modelMatrix;

        void reset()
        {
            modelMatrix = getIdentityMatrix();
        }
};
}
