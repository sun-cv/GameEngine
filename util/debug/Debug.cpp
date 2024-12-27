#include "Debug.h"

namespace Toolkit
{
DebugMenu::DebugMenu(Debug *& currentTestPointer) : currentTest(currentTestPointer)
{
}



void DebugMenu::onUpdate(float deltaTime)
{
}

void DebugMenu::onRender()
{
}

void DebugMenu::onImGuiRender()
{
    for (auto& test : tests)
    {
        if (ImGui::Button(test.first.c_str()))
        {
            currentTest = test.second();
        }
    }
}
}