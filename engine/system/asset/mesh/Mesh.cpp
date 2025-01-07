#include "Mesh.h"

Mesh::Mesh(const std::string& name, const std::vector<float>& vertices, const std::vector<unsigned int>& indices, VertexBufferLayout& layout) : name(name), vertices(vertices), indices(indices), layout(layout)
{
    VAO = std::make_unique<VertexArray>();

    VBO = std::make_unique<VertexBuffer>(vertices.data(), vertices.size() * sizeof(float));
    VAO->addVBO(*VBO, layout);

    IBO = std::make_unique<IndexBuffer>(indices.data(), static_cast<unsigned int>(indices.size()));
    VAO->addIBO(*IBO);

    VAO->unbind();
    VBO->unbind();
    IBO->unbind();

    float minX = std::numeric_limits<float>::max();
    float maxX = std::numeric_limits<float>::lowest();
    float minY = std::numeric_limits<float>::max();
    float maxY = std::numeric_limits<float>::lowest();

    for (size_t i = 0; i < vertices.size(); i += 2) {
        minX = std::min(minX, vertices[i]);
        maxX = std::max(maxX, vertices[i]);
        minY = std::min(minY, vertices[i + 1]);
        maxY = std::max(maxY, vertices[i + 1]);
    }

    width = maxX - minX;
    height = maxY - minY;
}

Mesh::~Mesh()
{
}

void Mesh::bind()
{
    VAO->bind();
}

void Mesh::unbind()
{
    VAO->unbind();
    VBO->unbind();
    IBO->unbind();
}

void Mesh::updateVertices(const std::vector<float> vertices)
{    
    VBO = std::make_unique<VertexBuffer>(vertices.data(), vertices.size());
    VAO->addVBO(*VBO, layout);
}

void Mesh::updateVertices(const std::vector<float> vertices, VertexBufferLayout& layout)
{    
    VBO = std::make_unique<VertexBuffer>(vertices.data(), vertices.size());
    VAO->addVBO(*VBO, layout);
}

void Mesh::instanceBuffer(const std::vector<glm::mat4>& instanceTransforms)
{
    VAO->bind();
    xVBO = std::make_unique<VertexBuffer>(instanceTransforms.data(), instanceTransforms.size() * sizeof(glm::mat4));


    for (int i = 0; i < 4; i++)
    {
        glEnableVertexAttribArray(2 + i);
        glVertexAttribPointer    (2 + i, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (const void*)(sizeof(glm::vec4) * i));
        glVertexAttribDivisor    (2 + i, 1);
    }
    
    VAO->unbind();
}
