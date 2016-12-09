#include "gamestates.hpp"

namespace ice
{
namespace game
{

RacingState::SubState& RacingState::ResultsSubState::GetInstance(RacingState& racingState)
{
    static ResultsSubState instance(racingState);
    return instance;
}

RacingState::ResultsSubState::ResultsSubState(RacingState& racingState)
    : SubState(racingState)
{}

void RacingState::ResultsSubState::Enter()
{
}

void RacingState::ResultsSubState::Exit()
{
}

RacingState::StatePair RacingState::ResultsSubState::Update()
{
    return StatePair(&MainMenuState::GetInstance(racingState_.gameSystems_));
}

void RacingState::ResultsSubState::Render()
{
}

} // namespace game
} // namespace ice
