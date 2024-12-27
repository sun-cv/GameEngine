#ifndef DEBUG_H
#define DEBUG_H 


#include "CoreEngine.h"
#include "imgui/imgui.h"


namespace Toolkit
{
class Debug
{
    private:
    public:
        Debug() {};
        virtual ~Debug() {};

        virtual void onUpdate(float deltaTime) {};
        virtual void onRender() {};
        virtual void onImGuiRender() {};
};

class DebugMenu : public Debug
{
    private:
        Debug*& currentTest;
        std::vector<std::pair<std::string, std::function<Debug*()>>> tests;

    public:
        DebugMenu(Debug*& currentTestPointer);

        void onUpdate(float deltaTime) override;
        void onRender() override;
        void onImGuiRender() override;

        template <typename T>
        void registerTest(const std::string& name)
        {
            Log_(Log::Debug, Log::Toolkit, "Registering test {}", name);
            tests.push_back(std::make_pair(name, [](){ return new T(); }));
        }
};
}

#endif