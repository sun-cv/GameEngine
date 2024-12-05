#include "TimeManager.h"

TimeManager& TimeManager::getInstance() {
    static TimeManager instance;
    return instance;
}

void TimeManager::update() {
    float currentTime = static_cast<float>(glfwGetTime());
    deltaTime = currentTime - lastTime;
    lastTime = currentTime;

    totalTime += deltaTime;
}
