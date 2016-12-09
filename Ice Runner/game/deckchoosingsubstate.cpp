#include "gamestates.hpp"
#include "events/eventmanager.h"

namespace ice
{
namespace game
{

RacingState::SubState& RacingState::DeckChoosingSubState::GetInstance(RacingState& racingState)
{
    static DeckChoosingSubState instance(racingState);
    return instance;
}

RacingState::DeckChoosingSubState::DeckChoosingSubState(RacingState& racingState)
    : SubState(racingState)
{}

void RacingState::DeckChoosingSubState::Enter()
{
}

void RacingState::DeckChoosingSubState::Exit()
{
}

RacingState::StatePair RacingState::DeckChoosingSubState::Update()
{
    //const events::GameState& gameState = racingState_.gameSystems_.eventManager.GetEventState();
    //const events::PlayerState& player1State = gameState.GetPlayerState(events::PlayerID::e1);

    //if (player1State.IsDown(events::MetaEvent::eBack))
    //    return StatePair(&MainMenuState::GetInstance(racingState_.gameSystems_));
    //else return StatePair();
    return StatePair(nullptr, &RacingSubState::GetInstance(racingState_));
}

void RacingState::DeckChoosingSubState::Render()
{
}

} // namespace game
} // namespace ice
