#pragma once

#include "Engine.h"

Engine::Engine()
{
    LogLevel                                    (Log::Debug);
    LogCategories                               ();
    construct();
}


Engine::~Engine()
{
    shutdown();
}

void Engine::construct()
{
    LogStartupSequence();
    
    windowController                            = std::make_shared<WindowController>();
    inputController                             = std::make_shared<InputController>(windowController);

    if (!windowController->active()) return;

    meshManager                                 = std::make_shared<MeshManager>();
    shaderManager                               = std::make_shared<ShaderManager>();
    textureManager                              = std::make_shared<TextureManager>();
    materialManager                             = std::make_shared<MaterialManager>(shaderManager, textureManager);

    entityMemoryPool                            = std::make_shared<ECS::EntityMemoryPool>();
    entityManager                               = std::make_shared<ECS::EntityManager>(entityMemoryPool);
    componentManager                            = std::make_shared<ECS::ComponentManager>(entityMemoryPool);
    builder                                     = std::make_shared<ECS::EntityBuilder>(entityManager, componentManager);

    renderer                                    = std::make_shared<Renderer>();
    renderSystem                                = std::make_shared<RenderSystem>(renderer, entityManager, componentManager, meshManager, materialManager);
    
    testbench                                   = std::make_shared<Toolkit::Testbench>(windowController->getWindow());

    engage();
}


void Engine::engage()
{
    LogSystemsOnline();
    run();
}


void Engine::run()
{
    while (windowController->active())
    {
        mark();
        processInput();
        update();
        render();
        display();
    }
}



void Engine::mark()
{
    renderSystem->clear();
}


void Engine::processInput()
{
    windowController->pollEvents();
}


void Engine::update()
{
    // renderSystem->update();
}


void Engine::render()
{
    // renderSystem->render();
    testbench->ImGui();
}


void Engine::display()
{
    windowController->swapBuffers();
}


void Engine::shutdown()
{
    Log(Log::System, Log::Engine, "Core systems powering down..");
    {
        windowController->shutdown();
        testbench->shutdown();
    }
}