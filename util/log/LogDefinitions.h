#ifndef LOG_DEFINITIONS_H
#define LOG_DEFINITIONS_H

namespace Log
{

enum LogLevel {
    Trace,
    Debug,
    System,
    Warning,
    Error,
    Fatal,
};

static const char* levelStrings[] = 
{
    "  [Trace]",
    "  [Debug]",
    " [System]",
    "[Warning]",
    "  [Error]",
    "  [Fatal]"
};
 



enum LogCategory {
    Engine,
    Toolkit,
    OpenGL,
    FileSystem,
    Event,
    EventDispatcher,
    cWindow,
    cInput,
    sRender,
    Renderer,
    mMaterial,
    Material,
    mShader,
    Shader,
    mTexture,
    Texture,
    EMP, 
    EntityManager,

    Count,
};

static const char* categoryStrings[] = 
{
    "Engine",
    "Toolkit",
    "OpenGL",
    "FileSystem",
    "Event",
    "EventDispatcher",
    "WindowController",
    "InputController",
    "RenderSystem",
    "Renderer",
    "MaterialManager",
    "Material",
    "ShaderManager",
    "Shader",
    "TextureManager",
    "Texture",
    "EntityMemoryPool",
    "EntityManager",
    "Count"
};

}


#endif