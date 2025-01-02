#pragma once

#include "CoreUtility.h"
#include "ForwardRender.h"


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
