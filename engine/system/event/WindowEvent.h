#pragma once

#include "CoreUtility.h"
#include "Event.h"

class WindowEvent : public Event
{
    private:
    protected:
        WindowEvent()                           = default;

    public:


};

class CloseWindow : public WindowEvent
{
    private:
    public:
        CloseWindow() {};
        EventClassType(CloseWindow)

        std::string toString() const override
	    {   
		    std::stringstream ss;
	    	ss << "CloseWindow: ";
	    	return ss.str();
	    }
};