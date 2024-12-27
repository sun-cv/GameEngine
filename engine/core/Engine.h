#ifndef ENGINE_H
#define ENGINE_H

#include "Core.h"

#include "WindowController.h"
#include "InputController.h"

#include "ShaderManager.h"
#include "materialManager.h"

class Engine
{
    private:
        bool running;   

        std::shared_ptr<Toolkit::Debug>                  debug;

        std::shared_ptr<WindowController>       windowController;
        std::shared_ptr<InputController>        inputController;

        std::shared_ptr<ECS::EntityManager>     entityManager;
        
        std::shared_ptr<TextureManager>         textureManager;
        std::shared_ptr<ShaderManager>          shaderManager;
        std::shared_ptr<MaterialManager>        materialManager;

        std::shared_ptr<Renderer>               renderer;

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

#endif
