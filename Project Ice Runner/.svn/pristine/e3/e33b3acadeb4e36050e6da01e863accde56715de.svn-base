#ifndef GAMESTATES_HPP
#define GAMESTATES_HPP
#include <cstdio>
#include <vector>
#include "gamestate.hpp"
#include "rendering/dx11structs.h"
#include "gamerenderstructs.hpp"

namespace ice
{

namespace game
{

class MenuState final : public GameState
{
protected:
    using GameState::GameState;

public:
    static GameState& GetInstance(types::GameSystems& gameSystems);

    virtual void Enter() override;
    virtual void Exit() override;
    virtual GameState* Update() override;
    virtual void Render() override;
};


class MapTestingState final : public GameState
{
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
    // FIXME: hack
    void RenderBackground();

    // FIXME: hack
    bool CreateBackgroundResources();
    void ReleaseBackgroundResources();
    bool CreateMapResources();
    void ReleaseMapResources();

    // Action listeners
    static void NextMapListener(void* pTestingState);
    static void PreviousMapListener(void* pTestingState);
    static void TestMapListener(void* pTestingState);

private:
    bool inMenu_;
    Menu menu_;
    BackgroundConstantBuffer backgroundBuffer_;
    dx11rendering::DX11Renderer& renderer_;
    dx11rendering::Geometry* pBackgroundGeometry_;
    dx11rendering::ShaderProgram* pBackgroundShader_;
    dx11rendering::ShaderConstantBuffer* pBackgroundConstantBuffer_;

    dx11rendering::ShaderProgram* pWallShader_;
    dx11rendering::Geometry* pWall1Geometry_;
    dx11rendering::Geometry* pWall2Geometry_;
};

class RacingState final : public GameState
{
protected:
    using GameState::GameState;

public:
    static GameState& GetInstance(types::GameSystems& gameSystems);
    virtual void Enter() override;
    virtual void Exit() override;
    virtual GameState* Update() override;
    virtual void Render() override;

private:
};

} // namespace game

} // namespace ice

#endif // GAMESTATES_HPP
