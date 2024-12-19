#ifndef MAIN_H
#define MAIN_H

#include <iostream>

#include "Engine.h"
#include "EngineCore.h"

namespace Sun {
    Engine engine;
}

int main()
{
    Log_(Log::System, Log::Engine, "Initiating startup sequence..");

    {
        Sun::engine.construct();

        Sun::engine.run();

        Sun::engine.shutdown();
    }

    Log_(Log::System, Log::Engine, "Safe shutdown sequence complete!");

    return 1;
};

#endif
