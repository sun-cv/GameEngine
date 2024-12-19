#ifndef ENGINE_H
#define ENGINE_H

#include <iostream>

#include "EngineCore.h"
#include "EventCore.h"
#include "WindowController.h"
#include "InputController.h"
#include "EntityMemoryPool.h"
#include "EntityManager.h"

class Engine
{
    private:
        bool running;   

        std::unique_ptr<WindowController>           windowController;
        std::unique_ptr<InputController>            inputController;
        std::unique_ptr<EntityManager>              entityManager;

    public:
        Engine();
        ~Engine();

        void construct();
        void log();
        void engage();

        void run();

        void debug();
        void mark();
        void processInput();
        void update();
        void render();
        void display();

        void shutdown();
};

#endif
