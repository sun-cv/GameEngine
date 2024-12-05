#ifndef TIME_MANAGER_H
#define TIME_MANAGER_H

#include <glfw/glfw3.h>

#include "EngineCore.h"

class TimeManager {
   public:
    static TimeManager& getInstance();

    void update();

    float getDeltaTime() const { return deltaTime; }
    float getTotalTime() const { return totalTime; }

   private:
    TimeManager() : lastTime(0.0f), deltaTime(0.0f), totalTime(0.0f) {}
    ~TimeManager() = default;

    float lastTime;
    float deltaTime;
    float totalTime;

    TimeManager(const TimeManager&) = delete;
    TimeManager& operator=(const TimeManager&) = delete;
};

#endif
