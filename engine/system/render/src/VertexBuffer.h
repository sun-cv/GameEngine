#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include "Log.h"

class VertexBuffer
{
    private:
        unsigned int rendererID;
    public:
        VertexBuffer() {};
        VertexBuffer(const void* data, size_t size);
        ~VertexBuffer();

    void bind() const;
    void unbind() const;

};

#endif