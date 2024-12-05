#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <fstream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <sstream>
#include <stdexcept>


#include "EngineCore.h"

class Shader {
   private:
    // Utility function to check compile and link errors
    void checkCompileErrors(GLuint shader, const std::string& type);

   public:
    GLuint ID;  // OpenGL shader program ID

    // Constructor: compiles and links shaders from file paths
    Shader(const char* vertexPath, const char* fragmentPath);

    // Destructor: deletes the shader program
    ~Shader();

    // Activates the shader program
    void use() const;

    // Templated function for setting uniforms
    template <typename T>
    void setUniform(const std::string& name, const T& value) const;

    // Specializations for specific uniform types
    template <>
    inline void setUniform(const std::string& name, const glm::vec3& value) const {
        GLint location = glGetUniformLocation(ID, name.c_str());
        if (location != -1) {
            glUniform3fv(location, 1, glm::value_ptr(value));
        } else {
            std::cerr << "[WARNING] Uniform '" << name << "' not found or not used in shader.\n";
        }
    }

    template <>
    inline void setUniform(const std::string& name, const glm::mat4& value) const {
        GLint location = glGetUniformLocation(ID, name.c_str());
        if (location != -1) {
            glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
        } else {
            std::cerr << "[WARNING] Uniform '" << name << "' not found or not used in shader.\n";
        }
    }

    template <>
    inline void setUniform(const std::string& name, const GLint& value) const {
        GLint location = glGetUniformLocation(ID, name.c_str());
        if (location != -1) {
            glUniform1i(location, value);
        } else {
            std::cerr << "[WARNING] Uniform '" << name << "' not found or not used in shader.\n";
        }
    }

    void bindUniformBlock(const std::string& blockName, GLuint bindingPoint) const;

    bool reload(const char* vertexPath, const char* fragmentPath);
};

#endif  // SHADER_H
