#pragma once

#include "CoreUtility.h"
#include "CoreMath.h"

#include "RenderGladGLFW.h"

class Shader
{
    private:
        unsigned int                            rendererID;
        std::string                             name;
        std::string                             vertexFilepath;
        std::string                             fragmentFilepath;

        std::unordered_map<std::string, int>    uniformLocationCache;

    public:
        Shader(
            const std::string                   name,
            const std::string                   vertextFilepath,
            const std::string                   fragmentFilepath);
        ~Shader();


        void bind() const;
        void unbind();
        bool reload();

        inline unsigned int getID   ()const& { return rendererID; };
        inline std::string getName  ()const& { return name; };


    private:
        unsigned int compileShader  (unsigned int type, const std::string& source);
        void checkCompileErrors     (unsigned int shader, const std::string& type);
        unsigned int createShader   (const std::string& vertexShader, const std::string& fragmentShader);
        int getUniformLocation      (const std::string& name);

    public:
        template <typename type>
        void setUniform(const std::string& name, const type& value)
        {
            Log(Log::Warning, Log::Shader, "Uniform type {} not supported", name);
        }
        
        template <>
        void setUniform(const std::string& name, const int& value)
        {
            glUniform1i(getUniformLocation(name), value);
        }

        template <>
        void setUniform(const std::string& name, const float& value)
        {
            glUniform1f(getUniformLocation(name), value);
        }

        template <>
        void setUniform(const std::string& name, const glm::vec3& value)
        {
            glUniform3fv(getUniformLocation(name), 1, glm::value_ptr(value));
        }

        template <>
        void setUniform(const std::string& name, const glm::mat4& value)
        {
            glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &value[0][0]);
        }

        void setUniform(const std::string & name, const glm::vec4& value)
        {
            glUniform4f(getUniformLocation(name), value.w, value.x, value.y, value.z);
        }

        void setTextureUniform(const std::string & name, const unsigned int value)
        {
            glUniform1i(getUniformLocation(name), value);
        }
};
