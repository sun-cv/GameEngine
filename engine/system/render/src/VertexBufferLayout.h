#ifndef VERTEX_BUFFER_LAYOUT_H
#define VERTEX_BUFFER_LAYOUT_H

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>

#include <vector>

struct VertexBufferElement
{
    unsigned int type;
    unsigned int count;
    unsigned char normalized;

    static unsigned int getSizeOfType(unsigned int type)
    {
        switch (type)
        {
            case GL_FLOAT:                      return 4;
            case GL_UNSIGNED_INT:               return 4;
            case GL_UNSIGNED_BYTE:              return 1;
        }
        return 0;
    }

};

class VertexBufferLayout
{
    private:
        std::vector<VertexBufferElement> elements;
        unsigned int stride;

    public:
    VertexBufferLayout(): stride(0) {};
    ~VertexBufferLayout() {};

    template<typename Type>
    void push(unsigned int count)
    {
        static_assert(false, "Type not supported");
    }

    template<>
    void push<float>(unsigned int count)
    {
        elements.push_back({GL_FLOAT, static_cast<unsigned int>(count), GL_FALSE});
        stride += count * VertexBufferElement::getSizeOfType(GL_FLOAT);
    }


    template<>
    void push<unsigned int>(unsigned int count)
    {
        elements.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
        stride += count * VertexBufferElement::getSizeOfType(GL_UNSIGNED_INT);
    }

    template<>
    void push<unsigned char>(unsigned int count)
    {
        elements.push_back({GL_UNSIGNED_BYTE, count, GL_TRUE});
        stride += count * VertexBufferElement::getSizeOfType(GL_UNSIGNED_BYTE);
    }

    inline const std::vector<VertexBufferElement> getElements() const& { return elements; }    

    inline unsigned int getStride() const& { return stride; };
};


#endif