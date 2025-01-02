#pragma once

#include "CoreUtility.h"
#include "Event.h"

class InputEvent : public Event
{
    private:
        std::string type;
        int keycode;
        int scancode;
        int action;
        int mods;

    public:
        InputEvent(std::string type, int keycode, int scancode, int action, int mods)
         : type(type), keycode(keycode), scancode(scancode), action(action), mods(mods) {};
        
        const std::string& getType() const { return type; }
        int getKeycode() const { return keycode; }
        int getScancode() const { return scancode; }
        int getAction() const { return action; }
        int getMods() const { return mods; }      

        EventClassType(InputEvent)
};
