#include "gamestates.hpp"
#include "resourcemanager.h"

namespace ice
{
namespace game
{

//////////////////// HUD ///////////////////////////

bool ResourceManager::RacingResources::HUDResources::Load()
{
    //////////////////// COMMON ///////////////////////////

    NormalizedRect commonCurrentMapGeo;
    commonCurrentMapGeo.topLeftPosition = glm::vec2(-.95, -.5);
    commonCurrentMapGeo.extent.y = .4f;
    commonCurrentMapGeo.extent.x = .5f;

    //////////////////// PLAYER 1 ///////////////////////////

    NormalizedRect commonTitleGeo;
    commonTitleGeo.topLeftPosition = glm::vec2(-.25, .95);
    commonTitleGeo.extent.y = .6f;
    commonTitleGeo.extent.x = .5f;

    Menu::LabelDescription player1LabelsDesc[2];
    player1LabelsDesc[0].elementDescription.geometry = commonCurrentMapGeo;
    player1LabelsDesc[0].elementDescription.pText = "PLAYING";
    player1LabelsDesc[1].elementDescription.geometry = commonTitleGeo;
    player1LabelsDesc[1].elementDescription.pText = "PLAYER 1";

    Menu::Description player1HUDDesc;
    player1HUDDesc.numButtons = 0;
    player1HUDDesc.numLabels = 2;
    player1HUDDesc.pButtonDescriptions = nullptr;
    player1HUDDesc.pLabelDescriptions = player1LabelsDesc;

    player1HUDDesc.colors[0] = glm::vec4(0, 0, 0, 1);
    player1HUDDesc.colors[1] = glm::vec4(0, 0, 0, 1);
    player1HUDDesc.colors[2] = glm::vec4(0, .25, .8, 1);
    player1HUDDesc.colors[3] = glm::vec4(0, .25, .8, 1);

    ResourceManager& resourceManager = ResourceManager::GetInstance(gameSystems_);
    if(!player1HUD_.Describe(resourceManager.renderer_, player1HUDDesc))
    {
        printf("Failed to load player 1's HUD\n");
        return false;
    }

    //NormalizedRect p1CurrentMapGeo; //p1CurrentMapGeo.topLeftPosition = glm::vec2(.25, -.95);
    pPlayer1CurrentMapField = &player1HUD_.AddField(0);

    player1HUDView_.TopLeftX = 0;
    player1HUDView_.TopLeftY = 640;
    player1HUDView_.Width = 600;
    player1HUDView_.Height = 80;

    //////////////////// PLAYER 2 ///////////////////////////

    Menu::LabelDescription player2LabelsDesc[2];
    player2LabelsDesc[0].elementDescription.geometry = commonCurrentMapGeo;
    player2LabelsDesc[0].elementDescription.pText = "PLAYING";
    player2LabelsDesc[1].elementDescription.geometry = commonTitleGeo;
    player2LabelsDesc[1].elementDescription.pText = "PLAYER 2";

    Menu::Description player2HUDDesc;
    player2HUDDesc.numButtons = 0;
    player2HUDDesc.numLabels = 2;
    player2HUDDesc.pButtonDescriptions = nullptr;
    player2HUDDesc.pLabelDescriptions = player2LabelsDesc;

    player2HUDDesc.colors[0] = glm::vec4(0, 0, 0, 1);
    player2HUDDesc.colors[1] = glm::vec4(0, 0, 0, 1);
    player2HUDDesc.colors[2] = glm::vec4(.8, .25, 0, 1);
    player2HUDDesc.colors[3] = glm::vec4(.8, .25, 0, 1);

    if(!player2HUD_.Describe(resourceManager.renderer_, player2HUDDesc))
    {
        printf("Failed to load player 2's HUD\n");
        return false;
    }

    pPlayer2CurrentMapField = &player1HUD_.AddField(0);

    player2HUDView_.TopLeftX = 680;
    player2HUDView_.TopLeftY = 640;
    player2HUDView_.Width = 600;
    player2HUDView_.Height = 80;


    //////////////////// DECK CHOOSING ///////////////////////////

    // TODO:

    //Menu::ButtonDescription deckChoosingMenu1ButtonDescs[2];
    //deckChoosingMenu1ButtonDescs[0].elementDescription.geometry

    //Menu::Description deckChoosingMenuDesc;
    //deckChoosingMenuDesc.numButtons = 0;
    //deckChoosingMenuDesc.numLabels = 0;
    //deckChoosingMenuDesc.pLabelDescriptions = nullptr;
    //deckChoosingMenuDesc.pButtonDescriptions = nullptr;

    //deckChoosingMenu1_.AddField();


    //////////////////// Racing ///////////////////////////

    Menu::Description countDownDesc;
    countDownDesc.numButtons = 0;
    countDownDesc.numLabels = 0;
    countDownDesc.pLabelDescriptions = nullptr;
    countDownDesc.pButtonDescriptions = nullptr;

    countDownDesc.colors[0] = glm::vec4(.1, .1, .1, 1);
    countDownDesc.colors[1] = glm::vec4(.1, .1, .1, 1);
    countDownDesc.colors[2] = glm::vec4(.5, .5, .5, 1);
    countDownDesc.colors[3] = glm::vec4(.5, .5, .5, 1);

    if(!countDownHUD_.Describe(resourceManager.renderer_, countDownDesc))
    {
        printf("Failed to load the count down HUD\n");
        return false;
    }

    pCountDownField_ = &countDownHUD_.AddField(0);

    countDownView_.TopLeftX = 600;
    countDownView_.TopLeftY = 640;
    countDownView_.Width = 80;
    countDownView_.Height = 80;

    NormalizedRect countDown1Geo;
    countDown1Geo.topLeftPosition = glm::vec2(-.40, .6);
    countDown1Geo.extent = glm::vec2(0, 1.5);

    NormalizedRect countDown2Geo;
    countDown2Geo.topLeftPosition = glm::vec2(-.65, .6);
    countDown2Geo.extent = glm::vec2(0, 1.5);

    NormalizedRect countDown3Geo;
    countDown3Geo.topLeftPosition = glm::vec2(-.75, .6);
    countDown3Geo.extent = glm::vec2(1.5, 1.5);

    NormalizedRect goGeo;
    goGeo.topLeftPosition = glm::vec2(-.75, .45);
    goGeo.extent = glm::vec2(1.5, 1.2);

    countDown1RenderDesc_ = countDownHUD_.MakeRenderDescription("1", countDown1Geo);
    countDown2RenderDesc_ = countDownHUD_.MakeRenderDescription("2", countDown2Geo);
    countDown3RenderDesc_ = countDownHUD_.MakeRenderDescription("3", countDown3Geo, countDownView_);
    countDownGoRenderDesc_ = countDownHUD_.MakeRenderDescription("GO!", goGeo, countDownView_);

    if (!countDown1RenderDesc_.IsValid() ||
        !countDown2RenderDesc_.IsValid() ||
        !countDown3RenderDesc_.IsValid())
    {
        printf("Failed to load the count down numbers\n");
        return false;
    }

    return true;
}

void ResourceManager::RacingResources::HUDResources::Unload()
{
    countDown1RenderDesc_.DeleteAndNull();
    countDown2RenderDesc_.DeleteAndNull();
    countDown3RenderDesc_.DeleteAndNull();

    player1HUD_.Free();
    player2HUD_.Free();
    pauseMenu_.Free();
    countDownHUD_.Free();
}

//////////////////// Player 1 ///////////////////////////

bool ResourceManager::RacingResources::Player1Resources::Load()
{
    return true;
}

void ResourceManager::RacingResources::Player1Resources::Unload()
{
}

//////////////////// Player 2 ///////////////////////////

bool ResourceManager::RacingResources::Player2Resources::Load()
{
    return true;
}

void ResourceManager::RacingResources::Player2Resources::Unload()
{
}

} // namespace game
} // namespace ice
