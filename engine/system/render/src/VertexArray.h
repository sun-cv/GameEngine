#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"

#include "Log.h"

class VertexArray
{
    private:
        unsigned int rendererID;
        unsigned int indexCount;

    public:
        VertexArray();
        ~VertexArray();

        void addVBO(const VertexBuffer& VBO, const VertexBufferLayout& layout);
        void addIBO(const IndexBuffer&  IBO);

        void bind() const;
        void unbind() const;

        inline unsigned int getIndexCount() const { return indexCount; };

};


#endif