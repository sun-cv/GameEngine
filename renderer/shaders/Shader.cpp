#include "Shader.h"

// Constructor: Compile and link shader from file paths
Shader::Shader(const char* vertexPath, const char* fragmentPath) {
    std::string vertexCode, fragmentCode;

    // Load shader source code
    try {
        std::ifstream vertexFile(vertexPath);
        std::ifstream fragmentFile(fragmentPath);
        std::stringstream vertexStream, fragmentStream;

        vertexStream << vertexFile.rdbuf();
        fragmentStream << fragmentFile.rdbuf();

        vertexCode = vertexStream.str();
        fragmentCode = fragmentStream.str();
    } catch (const std::ifstream::failure& error) {
        std::cout << "[FAILED]::[SHADER] File read error" << error.what() << std::endl;
    }

    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    GLuint vertex, fragment;

    // Compile vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, nullptr);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX");

    // Compile fragment shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, nullptr);
    glCompileShader(fragment);
    checkCompileErrors(fragment, "FRAGMENT");

    // Link shaders into a program
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    checkCompileErrors(ID, "PROGRAM");

    // Cleanup intermediate shader objects
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

// Destructor: Clean up the shader program
Shader::~Shader() {
    if (ID) {
        glDeleteProgram(ID);
        std::cout << "[SYSTEM]::[SHADER] Program deleted: " << ID << std::endl;
    }
}

// Activate the shader program
void Shader::use() const { glUseProgram(ID); }

// Check for compile/link errors
void Shader::checkCompileErrors(GLuint shader, const std::string& type) {
    GLint success;
    GLchar infoLog[1024];

    if (type == "PROGRAM") {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
            std::cerr << "[FAILED]::[SHADER] Linking error of type: " << type << "\n" << infoLog << "\n";
        }
    } else {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
            std::cerr << "[FAILED]::[SHADER] Compilation error of type: " << type << "\n" << infoLog << "\n";
        }
    }
}

// Bind a uniform block to a binding point
void Shader::bindUniformBlock(const std::string& blockName, GLuint bindingPoint) const {
    GLuint index = glGetUniformBlockIndex(ID, blockName.c_str());
    if (index != GL_INVALID_INDEX) {
        glUniformBlockBinding(ID, index, bindingPoint);
    } else {
        std::cerr << "[NOTICE] Uniform block not found in shader: " << blockName << std::endl;
    }
}

bool Shader::reload(const char* vertexPath, const char* fragmentPath) {
    glDeleteProgram(ID);  // Clean up existing program

    try {
        Shader temp(vertexPath, fragmentPath);  // Recompile the shaders
        *this = temp;                           // Replace the current shader
        std::cout << "[SYSTEM]::[SHADER] Reloaded successfully" << std::endl;
        return true;
    } catch (const std::exception& e) {
        std::cerr << "[FAILED] Reload failed (file or path missing): " << e.what() << std::endl;
        return false;
    }
}
