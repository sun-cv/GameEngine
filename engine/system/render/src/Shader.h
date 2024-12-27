#ifndef SHADER_H
#define SHADER_H

#include <fstream>

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glm/gtc/type_ptr.hpp>

#include "CoreEngine.h"


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

        inline unsigned int getID() const& { return rendererID; };
        inline std::string getName()const& { return name; };


    private:
        unsigned int compileShader  (unsigned int type, const std::string& source);
        void checkCompileErrors     (unsigned int shader, const std::string& type);
        unsigned int createShader   (const std::string& vertexShader, const std::string& fragmentShader);
        int getUniformLocation      (const std::string& name);

    public:
        template <typename type>
        void setUniform(const std::string& name, const type& value)
        {
            Log_(Log::Warning, Log::Shader, "Uniform type {} not supported", name);
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

        void setUniform(const std::string & name, const float v0, const float v1, const float v2, const float v3)
        {
            glUniform4f(getUniformLocation(name), v0, v1, v2, v3);
        }

};

#endif