#include "Shader.h"

#include <fstream>
#include "RenderGladGLFW.h"

Shader::Shader(const std::string name, const std::string vertexFilepath, const std::string fragmentFilepath) : name(name), vertexFilepath(vertexFilepath), fragmentFilepath(fragmentFilepath), rendererID(0)
{
    rendererID = createShader(vertexFilepath, fragmentFilepath);
}

Shader::~Shader()
{
    unbind();
    glDeleteProgram(rendererID);
}

static std::string parseShader(const std::string& filepath)
{
    Log(Log::Trace, Log::Shader, "Shader filepath:{}", filepath);

    std::string source;
    std::string line;
    std::ifstream stream(filepath);
    
    while (getline(stream, line))
    {
        source.append(line + "\n");
    };

    return source;
}

unsigned int Shader::compileShader(unsigned int type, const std::string& src)
{

    const char* source = src.c_str();
    unsigned int id = glCreateShader(type);

    glShaderSource(id, 1, &source, nullptr);
    glCompileShader(id);

    Log(Log::Trace, Log::Shader, "Compiled type {} shader id: {}", type, id);

    return id;
}


unsigned int Shader::createShader(const std::string& vertexFilepath, const std::string& fragmentFilepath)
{
 
    std::string vertexShader   = parseShader(vertexFilepath);
    std::string fragmentShader = parseShader(fragmentFilepath);

    Log(Log::Trace, Log::Shader, "Vertex Shader src: \n {}", vertexShader);
    Log(Log::Trace, Log::Shader, "Fragment Shader src: \n {}", fragmentShader);

    unsigned int program = glCreateProgram();
    
    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

    checkCompileErrors(vs, "VERTEX");
    checkCompileErrors(fs, "FRAGMENT");

    glAttachShader(program, vs);
    glAttachShader(program, fs);

    glLinkProgram(program);
    checkCompileErrors(program, "PROGRAM");

    glDeleteShader(vs);
    glDeleteShader(fs);
    return program;
    
}

void Shader::checkCompileErrors(unsigned int shader, const std::string& type) {
    GLint  success;
    GLchar infoLog[1024];

    if (type == "PROGRAM")
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
            Throw(Error::runtime, "Shader linking error of type {} | infoLog: {}", type, infoLog);
        }
    }
    else
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
            Throw(Error::runtime, "Shader compilation error of type {} | infoLog: {}", type, infoLog);
        }
    }
}


void Shader::bind() const
{

    glUseProgram(rendererID);
}

void Shader::unbind()
{
    glUseProgram(0);
}

bool Shader::reload()
{
    glDeleteProgram(rendererID);

    try
    {
        Shader buffer(name, vertexFilepath, fragmentFilepath);

        *this = buffer;

        Log(Log::System, Log::Shader, "Reloaded shader {} successfully", name);
        return true;
    }
    catch(Exceptions)
    {
        Log(Log::Error, Log::Shader, "Reload failed (file or path missing):\n{}", error.what());
        return false;
    }
}

int Shader::getUniformLocation(const std::string & name)
{
    if (uniformLocationCache.find(name) != uniformLocationCache.end())
    {
        return uniformLocationCache[name];
    }

    int location = glGetUniformLocation(rendererID, name.c_str());
    if (location == -1)
    {
        Log(Log::Warning, Log::Shader, "Uniform {} does not exist", name);
    }
    else
    {
        Log(Log::Trace, Log::Shader, "Uniform '{}' location: {}", name, location);
    }
    uniformLocationCache[name] = location;
    return location;
}
