#pragma once

#include "CoreUtility.h"

#include "Component.h"
#include "Texture.h"
#include "Shader.h"

class Material : public Component
{
    private:
        std::shared_ptr<Shader>                         shader;
        std::vector<std::shared_ptr<Texture>>           textures;

        std::unordered_map<std::string, int>            intUniforms;
        std::unordered_map<std::string, float>          floatUniforms;
        std::unordered_map<std::string, glm::vec3>      vec3Uniforms;
        std::unordered_map<std::string, glm::vec4>      vec4Uniforms;
        std::unordered_map<std::string, glm::mat4>      mat4Uniforms;
        std::unordered_map<std::string, unsigned int>   textureUniforms;

    public:
         Material(std::shared_ptr<Shader> shader) : shader(shader) {}
        ~Material() {};

        void bind()   { shader->bind(); applyUniforms(); int unit = 0; for (const auto& texture : textures) texture->bind(unit++); }
        void unbind() { shader->unbind();}
        void setUniform(const std::string& name, int value)                 { intUniforms[name]     = value; }
        void setUniform(const std::string& name, float value)               { floatUniforms[name]   = value; }
        void setUniform(const std::string& name, const glm::vec3& value)    { vec3Uniforms[name]    = value; }
        void setUniform(const std::string& name, const glm::vec4& value)    { vec4Uniforms[name]    = value; }
        void setUniform(const std::string& name, const glm::mat4& value)    { mat4Uniforms[name]    = value; }
        void setTextureUniform(const std::string& name, const unsigned int textureID)   { textureUniforms[name] = textureID; }

        void applyUniforms() const
        {
            if (!shader)
            {
                Log_(Log::Error, Log::mMaterial, "Shader not set! Cannot apply uniforms");
                return;
            }
            for (const auto& [name, value] : intUniforms)   shader->setUniform(name, value);
            for (const auto& [name, value] : floatUniforms) shader->setUniform(name, value);
            for (const auto& [name, value] : vec3Uniforms)  shader->setUniform(name, value);
            for (const auto& [name, value] : vec4Uniforms)  shader->setUniform(name, value);
            for (const auto& [name, value] : mat4Uniforms)  shader->setUniform(name, value);
        }
        
        std::shared_ptr<Shader> getShader() { return shader; };

        void addTexture(const std::shared_ptr<Texture>& texture) { textures.push_back(texture); };

};
