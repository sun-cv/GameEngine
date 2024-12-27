#ifndef MOUSE_EVENT_H
#define MOUSE_EVENT_H

#include "CoreEngine.h"
#include "Event.h"

class MouseEvent : public Event
{
    private:
    protected:
        int buttonCode;
        MouseEvent(int buttonCode) : buttonCode(buttonCode) {};

    public:
        inline int getButtonCode() const { return buttonCode; };

};

class MouseButtonPressedEvent : public MouseEvent
{
    private:
    public:
        MouseButtonPressedEvent(int buttonCode) : MouseEvent(buttonCode) {};
        EventClassType(MouseButtonPressed)

        std::string toString() const override
	    {   
		    std::stringstream ss;
	    	ss << "MouseButtonPressedEvent: " << buttonCode;
	    	return ss.str();
	    }
};

class MouseButtonReleasedEvent : public MouseEvent
{
    private:
    public:
        MouseButtonReleasedEvent(int buttonCode) : MouseEvent(buttonCode) {};
        EventClassType(MouseButtonReleased)

        std::string toString() const override
	    {   
		    std::stringstream ss;
	    	ss << "MouseButtonReleasedEvent: " << buttonCode;
	    	return ss.str();
	    }
};

class MouseScrolledEvent : public MouseEvent
{
    private:
        double xoffset;
        double yoffset;

    public:
        MouseScrolledEvent(double xoffset, double yoffset) : xoffset(xoffset), yoffset(yoffset), MouseEvent(0) {};
        EventClassType(MouseScrolled)

        inline double getxoffset() { return xoffset; };
        inline double getyoffset() { return yoffset; };

        std::string toString() const override
	    {   
		    std::stringstream ss;
	    	ss << "MouseScrolledEvent: " << buttonCode;
	    	return ss.str();
	    }
};

class MouseMovedEvent : public MouseEvent
{
    private:
        double xpos;
        double ypos;

    public:
        MouseMovedEvent(double xpos, double ypos) : xpos(xpos), ypos(ypos), MouseEvent(0) {};
        EventClassType(MouseMoved)

        inline double getxpos() { return xpos; };
        inline double getypos() { return ypos; };

        std::string toString() const override
	    {   
		    std::stringstream ss;
	    	ss << "MouseMovedEvent: " << buttonCode;
	    	return ss.str();
	    }
};

#endif