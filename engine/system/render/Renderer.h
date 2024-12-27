#ifndef RENDERER_H
#define RENDERER_H

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

class Renderer
{
    private:
        glm::vec4 clearColor; 

    public:

    private:

    public:
        void draw(VertexArray &VAO, Shader &shader) const;
        void clear() const;
        glm::vec4& getClearColor() { return clearColor;}
};


#endif