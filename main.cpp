#pragma once

#include "Engine.h"

int main()
{

    Log(Log::System, Log::Engine, "Initiating startup sequence..");

    {
        Engine engine;
    }
    
    Log(Log::System, Log::Engine, "Safe shutdown sequence complete!");

    return 1;
};
