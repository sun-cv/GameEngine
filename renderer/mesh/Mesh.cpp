#include "Mesh.h"

Mesh::Mesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices)
    : vertices(vertices), indices(indices) {
    setupMesh();
}

Mesh::~Mesh() {
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteVertexArrays(1, &VAO);
}

void Mesh::setupMesh() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    // Upload vertex data
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    // Upload index data
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    // Define vertex layout (Position + UV)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);  // Position
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                          (void*)(3 * sizeof(float)));  // UV
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

void Mesh::updateVertices(const std::vector<float>& newVertices) {
    vertices = newVertices;

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
}

void Mesh::setupInstanceBuffer(const std::vector<glm::mat4>& instanceTransforms) {
    GLuint instanceVBO;
    glGenBuffers(1, &instanceVBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
    glBufferData(GL_ARRAY_BUFFER, instanceTransforms.size() * sizeof(glm::mat4), instanceTransforms.data(),
                 GL_STATIC_DRAW);

    for (int i = 0; i < 4; i++) {
        glVertexAttribPointer(3 + i, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4) * i));
        glEnableVertexAttribArray(3 + i);
        glVertexAttribDivisor(3 + i, 1);
    }

    glBindVertexArray(0);
}
