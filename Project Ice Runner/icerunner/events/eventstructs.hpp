#ifndef EVENTSTRUCTS_HPP
#define EVENTSTRUCTS_HPP
#include <bitset>

namespace ice
{

namespace events
{

enum class MovementEvent
{
    eUp,
    eDown,
    eLeft,
    eRight,
    eNum_ //!< Used for array bounds AND an invalid value
};

enum class MetaEvent
{
    ePause,
    eSelect,
    eBack,
    eNum_ //!< Used for array bounds AND an invalid value
};

class EventManager;
class EventState
{
    friend class EventManager;
public:
    EventState()
        : currentMovementState_(), previousMovementState_(), currentMetaState_(), previousMetaState_(),
          latestMovementEvent_(MovementEvent::eNum_), latestMetaEvent_(MetaEvent::eNum_)
    {}

    bool IsDown(MovementEvent event) const { return currentMovementState_[(size_t)event]; }
    bool IsDown(MetaEvent event) const { return currentMovementState_[(size_t)event]; }

    bool WasDown(MovementEvent event) const { return previousMovementState_[(size_t)event]; }
    bool WasDown(MetaEvent event) const { return previousMovementState_[(size_t)event]; }

    bool IsHeld(MovementEvent event) const { return IsDown(event) && WasDown(event); }
    bool IsHeld(MetaEvent event) const { return IsDown(event) && WasDown(event); }

    MovementEvent GetLatestMovementEvent() const { return latestMovementEvent_; }
    MetaEvent GetLatestMetaEvent() const { return latestMetaEvent_; }

private:
    std::bitset<(size_t)MovementEvent::eNum_> currentMovementState_;
    std::bitset<(size_t)MovementEvent::eNum_> previousMovementState_;
    std::bitset<(size_t)MetaEvent::eNum_> currentMetaState_;
    std::bitset<(size_t)MetaEvent::eNum_> previousMetaState_;
    MovementEvent latestMovementEvent_;
    MetaEvent latestMetaEvent_;
};

} // namespace events

} // namespace ice

#endif // EVENTSTRUCTS_HPP
