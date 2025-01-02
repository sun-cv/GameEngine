#pragma once

#include "Core.h"

class Engine
{
    private:
        std::shared_ptr<WindowController>       windowController;
        std::shared_ptr<InputController>        inputController;

        std::shared_ptr<TextureManager>         textureManager;
        std::shared_ptr<ShaderManager>          shaderManager;
        std::shared_ptr<MaterialManager>        materialManager;
        std::shared_ptr<MeshManager>            meshManager;

        std::shared_ptr<ECS::EntityManager>     entityManager;
        std::shared_ptr<ECS::EntityBuilder>     builder;

        std::shared_ptr<Renderer>               renderer;
        std::shared_ptr<RenderSystem>           renderSystem;

        std::shared_ptr<Toolkit::Testbench>     testbench;
    public:
        Engine();
        ~Engine();

        void construct();
        void log();
        void engage();

        void run();

        void mark();
        void processInput();
        void update();
        void render();
        void display();

        void shutdown();
};
