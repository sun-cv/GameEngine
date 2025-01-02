#pragma once

#include "CoreUtility.h"

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"


#include "Component.h"

class Mesh : public Component
{
    private:
        std::vector<float>                      vertices;
        std::vector<unsigned int>               indices;
        VertexBufferLayout                      layout;

        
    public:
        unsigned int                            ID = 0;
        
        float                                   width;
        float                                   height;

        std::unique_ptr<VertexArray>            VAO;
        std::unique_ptr<VertexBuffer>           VBO;
        std::unique_ptr<IndexBuffer>            IBO;
        std::unique_ptr<VertexBuffer>           xVBO;

    public:
        Mesh(const std::string& name, const std::vector<float>& vertices, const std::vector<unsigned int>& indices, VertexBufferLayout& layout);
        ~Mesh();

        void bind();
        void unbind();

        unsigned int getID() { return ID; };

              std::vector<float>&           getVertices() { return vertices; };
        const std::vector<unsigned int>&    getIndices () { return indices;  };

        void updateVertices(const std::vector<float> vertices);
        void updateVertices(const std::vector<float> vertices, VertexBufferLayout& layout);
        void instanceBuffer(const std::vector<glm::mat4>& instanceTransforms);
        
};