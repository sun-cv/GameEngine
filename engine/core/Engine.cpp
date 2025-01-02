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
    Log_(Log::System, Log::Engine, "Initiating startup sequence..");

    windowController                            = std::make_shared<WindowController>();
    inputController                             = std::make_shared<InputController>(windowController);
    if (!windowController->active())
    {
        return;
    }

    meshManager                                 = std::make_shared<MeshManager>();
    textureManager                              = std::make_shared<TextureManager>();
    shaderManager                               = std::make_shared<ShaderManager>();
    materialManager                             = std::make_shared<MaterialManager>(shaderManager, textureManager);

    entityManager                               = std::make_shared<ECS::EntityManager>();
    builder                                     = std::make_shared<ECS::EntityBuilder>(entityManager, meshManager, materialManager);

    renderer                                    = std::make_shared<Renderer>();
    renderSystem                                = std::make_shared<RenderSystem>(renderer, entityManager);
    
    testbench                                   = std::make_shared<Toolkit::Testbench>(windowController->getWindow());

    engage();
}


void Engine::engage()
{
    Log_(Log::System, Log::Engine, "All systems online. Engage!")
    run();
}

void Engine::run()
{
    while (windowController->active())
    {
        mark();
        processInput();
        render();
        update();
        display();
    }
}




void Engine::mark()
{
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
    renderSystem->render();
    testbench->ImGui();
}

void Engine::display()
{
    windowController->swapBuffers();
}

void Engine::shutdown()
{
    Log_(Log::System, Log::Engine, "Core systems powering down..");
    {
        windowController->shutdown();
        testbench->shutdown();
    }
}