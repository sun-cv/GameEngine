#pragma once

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

class RendererDep
{
    private:

    public:

        void draw(VertexArray &VAO, Shader &shader) const;
        void clear(glm::vec4 clearColor) const;
};
