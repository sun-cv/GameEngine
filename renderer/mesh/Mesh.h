#ifndef MESH_H
#define MESH_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "EngineCore.h"

class Mesh {
   public:
    Mesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices);
    ~Mesh();

    GLuint getVAO() const { return VAO; }

    const std::vector<float>& getVertices() const { return vertices; }
    const std::vector<unsigned int>& getIndices() const { return indices; }

    void updateVertices(const std::vector<float>& newVertices);
    void setupInstanceBuffer(const std::vector<glm::mat4>& instanceTransforms);

    GLuint VAO, VBO, EBO;
    std::string ID;

   private:
    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    void setupMesh();
};

#endif
