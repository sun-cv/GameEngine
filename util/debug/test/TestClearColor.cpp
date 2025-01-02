#include "TestClearColor.h"

#include "RenderGladGLFW.h"

namespace Toolkit
{
TestClearColor::TestClearColor() : clearColor { 0.2f, 0.3f, 0.8f, 1.0f }
{
}

TestClearColor::~TestClearColor()
{
}


void TestClearColor::onUpdate(float deltaTime)
{
}

void TestClearColor::onRender()
{
    glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);
    glClear(GL_COLOR_BUFFER_BIT);

}

void TestClearColor::onImGuiRender()
{

    ImGui::ColorEdit4("Clear Color", clearColor);
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
}
}