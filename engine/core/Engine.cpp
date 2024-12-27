#include "Engine.h"

Engine::Engine() : running(false)
{
    log();
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
    windowController                            = std::make_shared<WindowController>();
    inputController                             = std::make_shared<InputController>(windowController);
    if (!windowController->active())
    {
        return;
    }

    entityManager                               = std::make_shared<ECS::EntityManager>();

    textureManager                              = std::make_shared<TextureManager>();
    shaderManager                               = std::make_shared<ShaderManager>();
    materialManager                             = std::make_shared<MaterialManager>(shaderManager, textureManager);
    
    renderer                                    = std::make_shared<Renderer>();

    debug                                       = std::make_shared<Toolkit::Debug>();
    engage();
}


void Engine::engage()
{
    running = true;
    Log_(Log::System, Log::Engine, "All systems online. Engage!")
}

void Engine::run()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(windowController->getWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 330");
    ImGui::StyleColorsDark();

    Toolkit::Debug* currentTest = nullptr;
    Toolkit::DebugMenu* menu = new Toolkit::DebugMenu(currentTest);
    
    currentTest = menu;
    menu->registerTest<Toolkit::TestClearColor>("Clear Color");
    menu->registerTest<Toolkit::TestTexture2D>("Texture 2D");
    menu->registerTest<Toolkit::BatchRender>("Batch Rendering");

    while (windowController->active())
    {
        mark();
        processInput();

        {
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
            if (currentTest)
            {
                currentTest->onUpdate(0.0f);
                currentTest->onRender();
                ImGui::Begin("Debug");
                if (currentTest != menu && ImGui::Button("<-"))
                {
                    delete currentTest;
                   currentTest = menu;
                }
            currentTest->onImGuiRender();
            ImGui::End();
            }
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        }

        update();
        render();
        display();
    }
}




void Engine::mark()
{
    renderer->clear();
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
    windowController->swapBuffers();
}

void Engine::shutdown()
{
    Log_(Log::System, Log::Engine, "Core systems powering down..");
    {
        running = false;
        windowController->terminate();

        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
    }
}