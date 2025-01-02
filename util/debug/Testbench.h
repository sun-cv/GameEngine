#pragma once

#include "Coreutility.h"

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>


namespace Toolkit
{
class Test
{
    private:
    public:
        Test() {};
        virtual ~Test() {};

        virtual void onUpdate(float deltaTime) {};
        virtual void onRender() {};
        virtual void onImGuiRender() {};
};

class TestMenu : public Test
{
    private:
        Test*& currentTest;
        std::vector<std::pair<std::string, std::function<Test*()>>> tests;

    public:
        TestMenu(Test*& currentTestPointer);

        void onUpdate(float deltaTime) override;
        void onRender() override;
        void onImGuiRender() override;

        template <typename test>
        void registerTest(const std::string& name)
        {
            Log_(Log::Debug, Log::Toolkit, "Registering test {}", name);
            tests.push_back(std::make_pair(name, [](){ return new test(); }));
        }
};

class Testbench
{
    private:
        Test*               currentTest;
        TestMenu*           menu;
        GLFWwindow*         window;
    public:
         Testbench(GLFWwindow* window);
        ~Testbench();

        void registerTests();
        void registerImGui();
        void ImGui();
        void shutdown();


};
}
