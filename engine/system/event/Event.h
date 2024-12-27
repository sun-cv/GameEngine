#ifndef EVENT_H
#define EVENT_H

#include "CoreEngine.h"
#include <functional>


enum class EventType
{
    None                                        = 0,

    Action,

    InputEvent,

    WindowEventsToCome,
    CloseWindow,

    AppEventsToCome,

    KeyPressed,
    KeyReleased,
    KeyRepeated,
    KeyTyped,

    MouseButtonPressed,
    MouseButtonReleased,
    MouseMoved,
    MouseScrolled
};

static const char* eventStrings[] = {
    "None",
    "Action",

    "InputEvent",

    "WindowEventsToCome",
    "CloseWindow",

    "AppEventsToCome",

    "KeyPressed",
    "KeyReleased",
    "KeyRepeated",
    "KeyTyped",

    "MouseButtonPressed",
    "MouseButtonReleased",
    "MouseMoved",
    "MouseScrolled"
};


#define EventClassType(type)\
    virtual EventType   getEventType()  const override  { return getStaticType(); }\
    virtual const char* getName()       const override  { return #type; }\
    static EventType    getStaticType()                 { return EventType::type; }


class Event 
{
    private:
    public:
        bool handled                            = false;
    
        virtual ~Event()                        = default;
        virtual EventType getEventType()        const = 0;
        virtual const char* getName()           const = 0;
            
        virtual std::string toString()          const { return getName(); }

};


class EventDispatcher
{
    using EventCallbackFn = std::function<void(Event&)>;

    private: 
        EventDispatcher()                       = default;
        std::unordered_map<EventType, std::vector<EventCallbackFn>> listeners;

    public:
        static EventDispatcher& getInstance()
        {
            static EventDispatcher instance;
            return instance;
        }

        void registerListener(EventType type, EventCallbackFn callback)
        {
            listeners[type].push_back(callback);
            auto eventTypeIndex = static_cast<size_t>(type); 
            Log_(Log::Debug, Log::EventDispatcher, "Registering listener {}", eventStrings[eventTypeIndex] );
        }

        void dispatch(Event& event)
        {
            auto& callbacks = listeners[event.getEventType()];
            for (auto callback : callbacks)
            {
                callback(event);
                if(event.handled)
                {
                    break;
                }
            }
        }

};

inline std::ostream& operator<<(std::ostream& os, const Event& e)
{
	return os << e.toString();
}



#define Listener_(eventType, callback)          EventDispatcher::getInstance().registerListener(eventType, callback);
#define Emit_(event)                            EventDispatcher::getInstance().dispatch(event);

#endif