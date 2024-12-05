#ifndef RENDERER_H
#define RENDERER_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "EngineCore.h"
#include "MaterialComponent.h"
#include "Mesh.h"
#include "TextComponent.h"
class Renderer {
   public:
    Renderer();

    // Initialization and Cleanup
    void initialize();
    void cleanup();

    // Rendering Methods
    void clear(const glm::vec4& clearColor);
    void bindMaterial(const MaterialComponent& material);
    void renderMesh(const Mesh& mesh, const MaterialComponent& material, const glm::mat4& modelMatrix);
    void renderBatch(const std::vector<Mesh*>& meshes, const MaterialComponent& material,
                     const std::vector<glm::mat4>& transforms);
    void renderText(const TextComponent& textComponent);

   private:
    // Uniform and Texture Binding
    void bindUniforms(const MaterialComponent& material) const;
    void bindTextures(const MaterialComponent& material) const;

    // Helper Methods
    template <typename T>
    void setUniform(GLuint program, const std::string& name, const T& value) const;

    void addQuadVertices(std::vector<float>& vertices, float x, float y, float w, float h) const;
    void uploadAndDrawText(const std::vector<float>& vertices) const;
};

#endif  // RENDERER_H
