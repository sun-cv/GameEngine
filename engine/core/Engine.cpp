#include "Engine.h"


Engine::Engine() : running(false)
{
}


Engine::~Engine()
{

}


void Engine::log()
{
    LogLevel                                    (Log::Debug);
    LogCategories                               ();
}


void Engine::construct()
{
    log();

    windowController                            = std::make_unique<WindowController>();

    if (!windowController->initialize())
    {
        return;
    }
    EntityMemoryPool::getInstance();
    
    inputController                             = std::make_unique<InputController>();
    entityManager                               = std::make_unique<EntityManager>();


    engage();
}


void Engine::engage()
{
    running = true;
    Log_(Log::System, Log::Engine, "All systems online. Engage!")
}

void Engine::run()
{

    debug();

while (windowController->active())
    {
        mark();
        processInput();
        update();
        render();
        display();
    }

}


void Engine::debug()
{
}

void Engine::mark()
{ 
    Entity entity = entityManager->addEntity("test");
}

void Engine::processInput()
{
    windowController->pollEvents();
}

void Engine::update()
{
    entityManager->update();
}

void Engine::render()
{
}

void Engine::display()
{
    windowController->clear();
    windowController->swapBuffers();
}

void Engine::shutdown()
{
    Log_(Log::System, Log::Engine, "Core systems powering down..");
    {
        running = false;
        windowController->terminate();
    }
}