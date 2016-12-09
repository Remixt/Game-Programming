#include "gamestates.hpp"
#include "core/constants.hpp"
#include "events/eventmanager.h"
#include "deckloader.h"

namespace ice
{
namespace game
{

static constexpr int FRAMES_PER_COUNT = (int)(1000/core::constants::MS_PER_UPDATE);

RacingState::SubState& RacingState::RacingSubState::GetInstance(RacingState& racingState)
{
    static RacingSubState instance(racingState);
    return instance;
}

RacingState::RacingSubState::RacingSubState(RacingState& racingState)
    : SubState(racingState), currentCount_(0), frameCount_(0)
{
    ResourceManager::RacingResources::HUDResources& hudResources = racingState_.hudResources_;

    countDownRenderDescriptions_[0] = hudResources.GetCountDown3RenderDescription();
    countDownRenderDescriptions_[1] = hudResources.GetCountDown2RenderDescription();
    countDownRenderDescriptions_[2] = hudResources.GetCountDown1RenderDescription();
    countDownRenderDescriptions_[3] = hudResources.GetCountDownGoRenderDescription();

    DeckLoader::GetInstance().Configure();
    DeckLoader::GetInstance().LoadMaps();
}

void RacingState::RacingSubState::Enter()
{
    currentCount_ = 0;
    countingDown_ = true;
    frameCount_ = 0;

    DeckLoader::GetInstance().ForEachMap([this](const Map& map) {
        const std::string& name = map.GetDescription().name;
        if (name == "MAZE RUNNER")
        {
            MapUtility::GetSceneInfo(map, sceneInfo1_);
            MapRenderer::GetInstance(this->racingState_.gameSystems_).MakePlayer1Scene(sceneInfo1_, renderScene1_);
        }
        else if (name == "ICE ICE BBY")
        {
            MapUtility::GetSceneInfo(map, sceneInfo2_);
            MapRenderer::GetInstance(this->racingState_.gameSystems_).MakePlayer2Scene(sceneInfo2_, renderScene2_);
        }
    });

    racingState_.resourceManager_.GetDJ().PlayAction();
}

void RacingState::RacingSubState::Exit()
{
    MapRenderer::GetInstance(racingState_.gameSystems_).FreeScene(renderScene1_);
    MapRenderer::GetInstance(racingState_.gameSystems_).FreeScene(renderScene2_);
}

RacingState::StatePair RacingState::RacingSubState::Update()
{
    if (countingDown_)
    {
        if (currentCount_ == countDownRenderDescriptions_.size())
        {
            currentCount_ = 0;
            countingDown_ = false;
        }
        else
        {
            if (frameCount_++ == FRAMES_PER_COUNT)
            {
                currentCount_++;
                frameCount_ = 0;
            }
        }
    }

    const events::GameState& gameState = racingState_.gameSystems_.eventManager.GetEventState();
    const events::PlayerState& player1State = gameState.GetPlayerState(events::PlayerID::e1);

    if (player1State.IsDown(events::MetaEvent::eBack))
        return StatePair(&MainMenuState::GetInstance(racingState_.gameSystems_));
    else return StatePair();
}

void RacingState::RacingSubState::Render()
{
    ResourceManager::RacingResources::HUDResources& hudResources = racingState_.hudResources_;

    racingState_.renderer_.SetViewPort(&racingState_.resourceManager_.GetFullScreenView());
    racingState_.background_.Render();

    D3D11_VIEWPORT player1HUDView = hudResources.GetPlayer1HUDView();
    racingState_.renderer_.SetViewPort(&player1HUDView);
    hudResources.GetPlayer1HUD().Render();

    D3D11_VIEWPORT player2HUDView = hudResources.GetPlayer2HUDView();
    racingState_.renderer_.SetViewPort(&player2HUDView);
    hudResources.GetPlayer2HUD().Render();

    D3D11_VIEWPORT countDownHUDView = hudResources.GetCountDownHUDView();
    racingState_.renderer_.SetViewPort(&countDownHUDView);

    if (countingDown_ && currentCount_ < countDownRenderDescriptions_.size()) // FIXME: hack
        hudResources.GetCountDownField()->SetRenderDescription(countDownRenderDescriptions_[currentCount_]);
    else
        hudResources.GetCountDownField()->SetRenderDescription(countDownRenderDescriptions_.back());
    hudResources.GetCountDownHUD().Render();

    MapRenderer& mapRenderer = MapRenderer::GetInstance(racingState_.gameSystems_);

    racingState_.renderer_.SetViewPort(&renderScene1_.GetView());
    racingState_.background_.SetColor(sceneInfo1_.mapColor);
    racingState_.background_.Render();
    mapRenderer.RenderScene(renderScene1_);

    racingState_.renderer_.SetViewPort(&renderScene2_.GetView());
    racingState_.background_.SetColor(sceneInfo2_.mapColor);
    racingState_.background_.Render(false);
    mapRenderer.RenderScene(renderScene2_);
}

} // namespace game
} // namespace ice
