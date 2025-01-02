#pragma once

#include "CoreUtility.h"
#include "Testbench.h"

namespace Toolkit 
{
class TestClearColor : public Test
{
    private:
        float clearColor[4];
    public:
        TestClearColor();
        ~TestClearColor();

        void onUpdate(float deltaTime) override;
        void onRender() override;
        void onImGuiRender() override;

};
}
