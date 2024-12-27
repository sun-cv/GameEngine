#ifndef WINDOW_EVENT_H
#define WINDOW_EVENT_H

#include "CoreEngine.h"
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

#endif