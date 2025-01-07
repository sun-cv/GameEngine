#pragma once

namespace Log
{

enum LogLevel {
    Loop,
    Trace,
    Debug,
    System,
    Warning,
    Error,
    Fatal,
};

static const char* levelStrings[] = 
{
    "   [Loop]",
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
    Testbench,
    OpenGL,
    mFile,
    Event,
    EventDispatcher,
    cWindow,
    cInput,
    sRender,
    Renderer,
    mMesh,
    Mesh,
    mMaterial,
    Material,
    mShader,
    Shader,
    mTexture,
    Texture,
    EMP, 
    mEntity,
    bEntity,
    mComponent,

    Count,
};

static const char* categoryStrings[] = 
{
    "Engine",
    "Toolkit",
    "Testbench",
    "OpenGL",
    "FileManager",
    "Event",
    "EventDispatcher",
    "WindowController",
    "InputController",
    "RenderSystem",
    "Renderer",
    "MeshManager",
    "Mesh",
    "MaterialManager",
    "Material",
    "ShaderManager",
    "Shader",
    "TextureManager",
    "Texture",
    "EntityMemoryPool",
    "EntityManager",
    "EntityBuilder",
    "ComponentManager",

    "Count"
};

}
