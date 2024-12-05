#ifndef MATERIAL_COMPONENT_H
#define MATERIAL_COMPONENT_H

#include "EngineCore.h"
#include "Shader.h"

struct MaterialComponent {
    std::string shaderName;
    std::shared_ptr<Shader> shader;
    std::unordered_map<std::string, int> intUniforms;
    std::unordered_map<std::string, float> floatUniforms;
    std::unordered_map<std::string, glm::vec3> vec3Uniforms;
    std::unordered_map<std::string, glm::mat4> mat4Uniforms;
    std::unordered_map<std::string, GLuint> textureUniforms;

    void setUniform(const std::string& name, int value) { intUniforms[name] = value; }
    void setUniform(const std::string& name, float value) { floatUniforms[name] = value; }
    void setUniform(const std::string& name, const glm::vec3& value) { vec3Uniforms[name] = value; }
    void setUniform(const std::string& name, const glm::mat4& value) { mat4Uniforms[name] = value; }
    void setTextureUniform(const std::string& name, GLuint textureID) { textureUniforms[name] = textureID; }

    void applyUniforms() const {
        if (!shader) {
            std::cout << "[WARNING] Shader not set. Cannot apply uniforms." << std::endl;

            return;
        }
        // REWORK REQUIRED MISSING SETUNIFORM OVERLOADS - MAY NOT BE REQUIRED
        // for (const auto& [name, value] : intUniforms) shader->setUniform(name, value);
        // for (const auto& [name, value] : floatUniforms) shader->setUniform(name, value);
        for (const auto& [name, value] : vec3Uniforms) shader->setUniform(name, value);
        for (const auto& [name, value] : mat4Uniforms) shader->setUniform(name, value);
    }
};

#endif  // MATERIAL_COMPONENT_H
