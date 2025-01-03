#include "Testbench.h"

#include "RenderGladGLFW.h"
#include "TestRegistry.h"


namespace Toolkit
{

TestMenu::TestMenu(Test *& currentTestPointer) : currentTest(currentTestPointer)
{
}

void TestMenu::onUpdate(float deltaTime)
{
}

void TestMenu::onRender()
{
}

void TestMenu::onImGuiRender()
{
    for (auto& test : tests)
    {
        if (ImGui::Button(test.first.c_str()))
        {
            currentTest = test.second();
        }
    }
}


Testbench::Testbench(GLFWwindow* window) : window(window)
{
    Log_(Log::System, Log::Testbench, "Initializing..");
    registerTests();
    registerImGui();
    Log_(Log::System, Log::Testbench, "Initialized successfully!");
}

Testbench::~Testbench()
{
}

void Testbench::registerTests()
{
    currentTest = nullptr;
    menu = new TestMenu(currentTest);
    currentTest = menu;

    menu->registerTest<TestClearColor>("Clear Color");
    menu->registerTest<TestTexture2D>("Texture 2D");
    menu->registerTest<BatchRender>("Batch Rendering");
    menu->registerTest<TestMesh>("Mesh rendering");
    menu->registerTest<TestMeshMaterial>("Mesh & Material rendering");
    menu->registerTest<TestECSComponents>("ECS Component builder");
    menu->registerTest<TestInstancedRender>("Instanced rendering");
}

void Testbench::registerImGui()
{
    //Render blending code rework required
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
    ImGui::StyleColorsDark();
}

void Testbench::ImGui()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    if (currentTest)
    { 
        currentTest->onUpdate(0.0f);
        currentTest->onRender();
        ImGui::Begin("Testbench");
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

void Testbench::shutdown()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    Log_(Log::System, Log::Testbench, "Powering down..")
}
}