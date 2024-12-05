#include <iostream>

#include "Engine.h"

int main() {
    std::cout << "[SYSTEM]::[ENGINE] Initiating startup sequence.." << std::endl;
    {
        Engine engine;

        engine.initialize();

        engine.shutdown();
    }
    std::cout << "[SYSTEM]::[ENGINE] Safe shutdown sequence complete!" << std::endl;
    return 0;
}