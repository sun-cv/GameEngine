#include "Renderer.h"

Renderer::Renderer() { initialize(); }

void Renderer::initialize() {
    std::cout << "[SYSTEM]::[RENDERER] Starting renderer..." << std::endl;
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    std::cout << "[SYSTEM]::[RENDERER] Loaded successfully." << std::endl;
}

void Renderer::clear(const glm::vec4& clearColor) {
    glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::bindMaterial(const MaterialComponent& material) {
    glUseProgram(material.shader->ID);
    bindUniforms(material);
    bindTextures(material);
}

void Renderer::bindUniforms(const MaterialComponent& material) const {
    for (const auto& [name, value] : material.intUniforms) {
        setUniform(material.shader->ID, name, value);
    }
    for (const auto& [name, value] : material.floatUniforms) {
        setUniform(material.shader->ID, name, value);
    }
    for (const auto& [name, value] : material.vec3Uniforms) {
        setUniform(material.shader->ID, name, value);
    }
    for (const auto& [name, value] : material.mat4Uniforms) {
        setUniform(material.shader->ID, name, value);
    }
}

void Renderer::bindTextures(const MaterialComponent& material) const {
    GLuint textureUnit = 0;
    for (const auto& [name, textureID] : material.textureUniforms) {
        glActiveTexture(GL_TEXTURE0 + textureUnit);
        glBindTexture(GL_TEXTURE_2D, textureID);

        setUniform(material.shader->ID, name, static_cast<int>(textureUnit));
        ++textureUnit;
    }
}

void Renderer::renderMesh(const Mesh& mesh, const MaterialComponent& material, const glm::mat4& modelMatrix) {
    bindMaterial(material);

    // Set the model matrix
    setUniform(material.shader->ID, "model", modelMatrix);

    glBindVertexArray(mesh.getVAO());
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mesh.getIndices().size()), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Renderer::renderBatch(const std::vector<Mesh*>& meshes, const MaterialComponent& material,
                           const std::vector<glm::mat4>& transforms) {
    bindMaterial(material);

    for (size_t i = 0; i < meshes.size(); ++i) {
        renderMesh(*meshes[i], material, transforms[i]);
    }

    glUseProgram(0);
}

void Renderer::renderText(const TextComponent& textComponent) {
    bindMaterial(textComponent.material);

    float xCursor = textComponent.position.x;
    float yBase = textComponent.position.y;

    std::vector<float> vertices;

    for (const char& c : textComponent.text) {
        const Glyph* glyph = textComponent.fontAtlas->getGlyph(c);
        if (!glyph) {
            std::cerr << "[WARNING]::[RENDERER] Missing glyph for character: " << c << "\n";
            continue;
        }

        // Calculate quad position
        float xPos = xCursor + glyph->bearing.x * textComponent.scale;
        float yPos = yBase - (glyph->size.y - glyph->bearing.y) * textComponent.scale;
        float w = glyph->size.x * textComponent.scale;
        float h = glyph->size.y * textComponent.scale;

        // Add quad vertices
        addQuadVertices(vertices, xPos, yPos, w, h);

        xCursor += glyph->advance * textComponent.scale;
    }

    uploadAndDrawText(vertices);
}

void Renderer::addQuadVertices(std::vector<float>& vertices, float x, float y, float w, float h) const {
    vertices.insert(vertices.end(), {
                                        x,     y + h, 0.0f, 1.0f,  // Top-left
                                        x,     y,     0.0f, 0.0f,  // Bottom-left
                                        x + w, y,     1.0f, 0.0f,  // Bottom-right

                                        x,     y + h, 0.0f, 1.0f,  // Top-left
                                        x + w, y,     1.0f, 0.0f,  // Bottom-right
                                        x + w, y + h, 1.0f, 1.0f   // Top-right
                                    });
}

void Renderer::uploadAndDrawText(const std::vector<float>& vertices) const {
    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);  // Position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));  // UV
    glEnableVertexAttribArray(1);

    glDrawArrays(GL_TRIANGLES, 0, vertices.size() / 4);

    glBindVertexArray(0);
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
}

void Renderer::cleanup() { std::cout << "[SYSTEM]::[RENDERER] Cleaning up resources..." << std::endl; }

template <typename T>
void Renderer::setUniform(GLuint program, const std::string& name, const T& value) const {
    GLint location = glGetUniformLocation(program, name.c_str());
    if (location == -1) return;

    if constexpr (std::is_same_v<T, int>) {
        glUniform1i(location, value);
    } else if constexpr (std::is_same_v<T, float>) {
        glUniform1f(location, value);
    } else if constexpr (std::is_same_v<T, glm::vec3>) {
        glUniform3fv(location, 1, &value[0]);
    } else if constexpr (std::is_same_v<T, glm::mat4>) {
        glUniformMatrix4fv(location, 1, GL_FALSE, &value[0][0]);
    }
}
