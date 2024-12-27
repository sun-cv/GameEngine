#ifndef MATERIAL_H
#define MATERIAL_H

#include "CoreEngine.h"

#include "Component.h"

class Material : public Component
{
    private:
        std::shared_ptr<Shader> shader;

        std::unordered_map<std::string, int>            intUniforms;
        std::unordered_map<std::string, float>          floatUniforms;
        std::unordered_map<std::string, glm::vec3>      vec3Uniforms;
        std::unordered_map<std::string, glm::mat4>      mat4Uniforms;
        std::unordered_map<std::string, unsigned int>   textureUniforms;


    public:
         Material(std::shared_ptr<Shader> shader) : shader(shader) {};
        ~Material() {};

        void setUniform(const std::string& name, int value)                 { intUniforms[name] = value; }
        void setUniform(const std::string& name, float value)               { floatUniforms[name] = value; }
        void setUniform(const std::string& name, const glm::vec3& value)    { vec3Uniforms[name] = value; }
        void setUniform(const std::string& name, const glm::mat4& value)    { mat4Uniforms[name] = value; }
        void setTextureUniform(const std::string& name, GLuint textureID)   { textureUniforms[name] = textureID; }

        void applyUniforms() const
        {
            // Rework required
            if (!shader)
            {
                Log_(Log::Error, Log::mMaterial, "")
            }
        }
};

#endif