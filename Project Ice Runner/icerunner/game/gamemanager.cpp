#include "events/eventmanager.h"
#include "rendering/displaymanager.h"
#include "gamemanager.h"
#include "deckloader.h"

namespace ice
{
namespace game
{

bool GameManager::Init()
{
    return game_.Init() && DeckLoader::GetInstance().Init();
}

void GameManager::Update()
{
    game_.Update();
}

bool GameManager::ShouldQuit()
{
    return game_.ShouldQuit();
}

void GameManager::Render()
{
    dx11rendering::DX11Renderer& renderer = gameSystems_.displayManager.GetRenderer();
    renderer.BeginScene(D3DCOLORVALUE{0, 0, 0, 1});

    game_.Render();

    renderer.EndScence();
}

} // namespace game

} // namespace ice
