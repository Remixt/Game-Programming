#include <cstdio>
#include <SDL2/SDL.h>
#include "eventmanager.h"

namespace ice
{

namespace events
{

bool EventManager::Init()
{
    if (SDL_InitSubSystem(SDL_INIT_EVENTS) == 0) return true;

    printf("Couldn't init event manager: %s\n", SDL_GetError());
    return false;
}

EventManager::~EventManager()
{
    SDL_QuitSubSystem(SDL_INIT_EVENTS);
}

void EventManager::Poll()
{
    state_.previousMovementState_ = state_.currentMovementState_;
    state_.previousMetaState_ = state_.currentMetaState_;

    state_.latestMovementEvent_ = MovementEvent::eNum_;
    state_.latestMetaEvent_ = MetaEvent::eNum_;

    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch(event.type)
        {
        case SDL_QUIT:
            shouldQuit_ = true;
            return;
        case SDL_KEYDOWN:
            switch(event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                shouldQuit_ = true;
                return;
            case SDLK_RETURN:
                state_.currentMetaState_.set((size_t)MetaEvent::eSelect);
                state_.latestMetaEvent_ = MetaEvent::eSelect;
                break;
            case SDLK_b:
                state_.currentMetaState_.set((size_t)MetaEvent::eBack);
                state_.latestMetaEvent_ = MetaEvent::eBack;
                break;
            case SDLK_UP:
                state_.currentMovementState_.set((size_t)MovementEvent::eUp);
                state_.latestMovementEvent_ = MovementEvent::eUp;
                break;
            case SDLK_DOWN:
                state_.currentMovementState_.set((size_t)MovementEvent::eDown);
                state_.latestMovementEvent_ = MovementEvent::eDown;
                break;
            case SDLK_LEFT:
                state_.currentMovementState_.set((size_t)MovementEvent::eLeft);
                state_.latestMovementEvent_ = MovementEvent::eLeft;
                break;
            case SDLK_RIGHT:
                state_.currentMovementState_.set((size_t)MovementEvent::eRight);
                state_.latestMovementEvent_ = MovementEvent::eRight;
                break;
            default:
                break;
            }
            break;
        case SDL_KEYUP:
            switch(event.key.keysym.sym)
            {
            case SDLK_UP:
                state_.currentMovementState_.set((size_t)MovementEvent::eUp, false);
                break;
            case SDLK_DOWN:
                state_.currentMovementState_.set((size_t)MovementEvent::eDown, false);
                break;
            case SDLK_LEFT:
                state_.currentMovementState_.set((size_t)MovementEvent::eLeft, false);
                break;
            case SDLK_RIGHT:
                state_.currentMovementState_.set((size_t)MovementEvent::eRight, false);
                break;
            case SDLK_RETURN:
                state_.currentMetaState_.set((size_t)MetaEvent::eSelect, false);
                break;
            case SDLK_b:
                state_.currentMetaState_.set((size_t)MetaEvent::eBack, false);
                break;
            default:
                break;
            }
            break;
        default:
            break;
        }
    }
}

bool EventManager::ShouldQuit()
{
    return shouldQuit_;
}

} // namespace events

} // namespace ice
