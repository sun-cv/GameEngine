#pragma once

#include "CoreUtility.h"

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
