#pragma once

#include "CoreUtility.h"
#include "ForwardRender.h"

#include "CoreMath.h"

class Renderer
{
    private:

    public:

        void draw(std::shared_ptr<Material> material, std::shared_ptr<Mesh> mesh) const;
        void drawInstance(std::shared_ptr<Material> material, std::shared_ptr<Mesh> mesh, unsigned int instanceCount) const;
        void clear(glm::vec4 clearColor) const;
};
