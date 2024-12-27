#include "VertexArray.h"


VertexArray::VertexArray()
{
    glGenVertexArrays(1, &rendererID);
}

VertexArray::~VertexArray()
{   
    glDeleteVertexArrays(1, &rendererID);
}

void VertexArray::addVBO(const VertexBuffer& VBO, const VertexBufferLayout& layout)
{
    bind();
    VBO.bind();

    const auto& elements = layout.getElements();

    uintptr_t offset = 0;

    for (unsigned int i = 0; i < elements.size(); i++)
    {
        const auto& element = elements[i];

        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.getStride(), (const void*)offset);
        offset += element.count * VertexBufferElement::getSizeOfType(element.type);
    } 
}

void VertexArray::addIBO(const IndexBuffer& IBO)
{
    indexCount = IBO.getCount();
}

void VertexArray::bind() const
{
    glBindVertexArray(rendererID);
}

void VertexArray::unbind() const
{
    glBindVertexArray(0);
}
