#pragma once

#include "CoreUtility.h"
#include "CoreMath.h"

#include "ECSDefinition.h"

#include "ForwardRender.h"

class Renderer
{
    private:

    public:

        void draw(std::shared_ptr<Material> material, std::shared_ptr<Mesh> mesh) const;
        void drawInstance(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material, ECS::Entity instanceCount) const;
        void clear(glm::vec4 clearColor) const;
};
