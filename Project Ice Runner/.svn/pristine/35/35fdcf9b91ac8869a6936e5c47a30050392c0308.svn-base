#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H
#include "eventstructs.hpp"
#include "hidmanager.h"

namespace ice
{

namespace events
{

class EventManager
{
public:
    EventManager()
        : state_(), shouldQuit_(false)
    {}

    ~EventManager();

    bool Init();
    void Poll();
    bool ShouldQuit();

    const EventState GetState() const { return state_; }

private:
    EventState state_;
    bool shouldQuit_;
};

} // namespace events

} // namespace ice

#endif // EVENTMANAGER_H
