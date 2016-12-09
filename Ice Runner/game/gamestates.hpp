#ifndef GAMESTATES_HPP
#define GAMESTATES_HPP
#include <cstdio>
#include <vector>
#include <array>
#include <future>
#include "gamestate.hpp"
#include "rendering/dx11structs.h"
#include "gamerenderstructs.hpp"
#include "maprenderer.h"
#include "resourcemanager.h"
#include "types.hpp"
#include "sound/soundstructs.hpp"

class DeckLoader;

namespace ice
{

namespace game
{

class MainMenuState final : public GameState
{
    friend class ResourceManager;
protected:
    using GameState::GameState;

public:
    static GameState& GetInstance(types::GameSystems& gameSystems);

    virtual void Enter() override;
    virtual void Exit() override;
    virtual GameState* Update() override;
    virtual void Render() override;

private:
    MainMenuState(types::GameSystems& gameSystems_);

private:
    static void RaceListener(void* pState);
    static void TestMapListener(void* pState);

private:
    ResourceManager& resourceManager_;
    dx11rendering::DX11Renderer& renderer_;
    Menu& menu_;
    GameState* pNextState_;
    sound::Effect* pCycleEffect_;
    sound::Effect* pSelectEffect_;
    Background& background_;
};


class MapTestingState final : public GameState
{
    friend class ResourceManager;
public:
    static GameState& GetInstance(types::GameSystems& gameSystems);
    virtual void Enter() override;
    virtual void Exit() override;
    virtual GameState* Update() override;
    virtual void Render() override;
    
private:
    MapTestingState(types::GameSystems& gameSystems);
    
private:
    GameState* UpdateInMenu();
    void UpdateOutOfMenu();
    void RenderInMenu();
    void RenderOutOfMenu();
    void RenderFullBackground();
    void RenderMapBackground();

    bool CreateMapResources();
    void ReleaseMapResources();
    void LoadPhysicsScene();
    void ReleasePhysicsScene();

    // Action listeners
    static void NextMapListener(void* pTestingState);
    static void PreviousMapListener(void* pTestingState);
    static void TestMapListener(void* pTestingState);
    static void ConfigureListener(void* pTestingState);
    static void LoadMapsListener(void* pTestingState);

private:
    bool inMenu_;
    Menu* pMenu_;
    std::future<bool> deckLoadingFuture_;
    bool hadSuccessfullConfigure_;
    std::future<bool> mapLoadingFuture_;
    bool hadSuccessfullMapLoading_;

    BackgroundConstantBuffer backgroundBuffer_;
    dx11rendering::DX11Renderer& renderer_;
    dx11rendering::Geometry* pBackgroundGeometry_;
    dx11rendering::ShaderProgram* pBackgroundShader_;
    dx11rendering::ShaderConstantBuffer* pBackgroundConstantBuffer_;

    dx11rendering::ShaderProgram* pWallShader_;
    dx11rendering::Geometry* pWall1Geometry_;
    dx11rendering::Geometry* pWall2Geometry_;
    ResourceManager& resourceManager_;
    DeckLoader& deckLoader_;
    MapRenderer& mapRenderer_;

    Menu::Field* loadingField_;
    Menu::Field* currentMapField_;
    Menu::ElementRenderDescription loadingFieldOnDescription_;

    std::vector<MapSceneAssociation> mapAssociations_;
    int currentMapIndex_;
    MapUtility::SceneInfo currentSceneInfo_;
    MapRenderer::Scene currentRenderScene_;
    physics::Scene* pCurrentPhysicsScene_;
};

class RacingState final : public GameState
{
    friend class DeckChoosingSubState;
    friend class RacingSubState;
    friend class ResultsSubState;
private:
    struct StatePair;
    class SubState
    {
    public:
        SubState(RacingState& racingState)
            : racingState_(racingState)
        {}

        virtual void Enter() = 0;
        virtual void Exit() = 0;
        virtual StatePair Update() = 0;
        virtual void Render() = 0;

    protected:
        RacingState& racingState_;
    };

    struct StatePair
    {
        StatePair(GameState* pNextGameState = nullptr, SubState* pNextSubState = nullptr)
            : pNextGameState(pNextGameState), pNextSubState(pNextSubState)
        {}

        GameState* pNextGameState;
        SubState* pNextSubState;
    };

    class DeckChoosingSubState final : public SubState
    {
    public:
        static SubState& GetInstance(RacingState& racingState);
        virtual void Enter() override;
        virtual void Exit() override;
        virtual StatePair Update() override;
        virtual void Render() override;

    private:
        DeckChoosingSubState(RacingState& racingState);

    private:
    };

    class RacingSubState final : public SubState
    {
    public:
        static SubState& GetInstance(RacingState& racingState);
        virtual void Enter() override;
        virtual void Exit() override;
        virtual StatePair Update() override;
        virtual void Render() override;

    private:
        RacingSubState(RacingState& racingState);
        ~RacingSubState() = default;

    private:
        std::array<Menu::ElementRenderDescription, 4> countDownRenderDescriptions_;
        MapRenderer::Scene renderScene1_; // hack
        MapRenderer::Scene renderScene2_; // hack

        MapUtility::SceneInfo sceneInfo1_; // hack
        MapUtility::SceneInfo sceneInfo2_; // hack

        int currentCount_;
        int frameCount_;
        bool countingDown_;
    };

    class ResultsSubState final : public SubState
    {
    public:
        static SubState& GetInstance(RacingState& racingState);
        virtual void Enter() override;
        virtual void Exit() override;
        virtual StatePair Update() override;
        virtual void Render() override;

    private:
        ResultsSubState(RacingState& racingState);

    private:
    };

public:
    static GameState& GetInstance(types::GameSystems& gameSystems);
    virtual void Enter() override;
    virtual void Exit() override;
    virtual GameState* Update() override;
    virtual void Render() override;

private:
    RacingState(types::GameSystems& gameSystems);

private:
    ResourceManager& resourceManager_;
    ResourceManager::RacingResources& resources_;
    ResourceManager::RacingResources::HUDResources& hudResources_;
    ResourceManager::RacingResources::Player1Resources& player1Resources_;
    ResourceManager::RacingResources::Player2Resources& player2Resources_;

    GameState* pNextState_;
    sound::Effect* pCycleEffect_;
    sound::Effect* pSelectEffect_;
    Background& background_;
    dx11rendering::DX11Renderer& renderer_;
    SubState* pSubState_;
};

} // namespace game

} // namespace ice

#endif // GAMESTATES_HPP
