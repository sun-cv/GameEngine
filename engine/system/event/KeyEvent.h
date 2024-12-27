#ifndef KEY_EVENT_H
#define KEY_EVENT_H

#include "CoreEngine.h"
#include "Event.h"


class KeyEvent : public Event
{
    private: 
    protected:
        int keyCode;
        KeyEvent(int keyCode) : keyCode(keyCode) {};
		
    public:
        inline int getKeyCode() const { return keyCode; };
};


class KeyPressedEvent : public KeyEvent
{
    private:
    public:
        KeyPressedEvent(int keycode) : KeyEvent(keycode) {};
        EventClassType(KeyPressed)

		std::string toString() const override
	    {   
		    std::stringstream ss;
	    	ss << "KeyPressedEvent: " << keyCode;
	    	return ss.str();
	    }
};


class KeyReleasedEvent : public KeyEvent
{
    private:
    public:
	    KeyReleasedEvent(int keycode) : KeyEvent(keycode) {}
	    EventClassType(KeyReleased)

	    std::string toString() const override
	    {
		    std::stringstream ss;
		    ss << "KeyReleasedEvent: " << keyCode;
		    return ss.str();
	    }
};

class KeyRepeatedEvent : public KeyEvent
{
    private:
    public:
	    KeyRepeatedEvent(int keycode) : KeyEvent(keycode) {}
	    EventClassType(KeyRepeated)

	    std::string toString() const override
	    {
		    std::stringstream ss;
		    ss << "KeyRepeatedEvent: " << keyCode;
		    return ss.str();
	    }
};

class KeyTypedEvent : public KeyEvent
{
    private:
    public:
	    KeyTypedEvent(int keycode) : KeyEvent(keycode) {}
	    EventClassType(KeyTyped)
	    std::string toString() const override
	    {
	    	std::stringstream ss;
	    	ss << "KeyTypedEvent: " << keyCode;
	    	return ss.str();
	    }
};



#endif