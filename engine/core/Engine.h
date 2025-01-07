#pragma once

#include "Core.h"

class Engine
{   // Variables
    private: // Dependencies
        std::shared_ptr<WindowController>       windowController;
        std::shared_ptr<InputController>        inputController;

        std::shared_ptr<ShaderManager>          shaderManager;
        std::shared_ptr<TextureManager>         textureManager;
        std::shared_ptr<MaterialManager>        materialManager;
        std::shared_ptr<MeshManager>            meshManager;

        std::shared_ptr<ECS::EntityMemoryPool>  entityMemoryPool;
        std::shared_ptr<ECS::EntityManager>     entityManager;
        std::shared_ptr<ECS::EntityBuilder>     builder;

        std::shared_ptr<ECS::ComponentManager>  componentManager;

        std::shared_ptr<Renderer>               renderer;
        std::shared_ptr<RenderSystem>           renderSystem;

        std::shared_ptr<Toolkit::Testbench>     testbench;

    //Functions
    private:
        void construct();
        void engage();

        void run();

        void mark();
        void processInput();
        void update();
        void render();
        void display();

        void shutdown();
    
    public:
        Engine();
       ~Engine();
};


/*
*********************************************************************************************************
*                                            REWORK REQUIRED                                            *
*********************************************************************************************************

    0. All of it at some point.

    1. Render system
        (1/2) sRender holds transform instead of entityID?
        (2/2) filtered entity vectors for active and dirty passed as copies currently.
    2. cInput
    3. eBuilder
        (1/2) new structure rework                                                          - In progress
        (2/2) Transform component initialization?
    4. Double check rework of .h and log/Error macro - Specifically notating // Throw       - In progress
    


*/