#ifndef INDEX_BUFFER_H
#define INDEX_BUFFER_H

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include "Log.h"

class IndexBuffer
{
    private:
        unsigned int rendererID;
        unsigned int count;
    public:
        IndexBuffer(const unsigned int* data, unsigned int count);
        ~IndexBuffer();

    void bind() const;
    void unbind() const;

    inline unsigned int getCount() const { return count; };
};

#endif