#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H
#include <array>
#include "rendering/dx11structs.h"
#include "gamerenderstructs.hpp"
#include "rendering/displaymanager.h"
#include "physics/physicsstructs.hpp"
#include "types.hpp"
#include "sound/soundstructs.hpp"
#include "dj.h"

namespace ice
{

namespace game
{

class ResourceManager
{
public:
    enum class Shader
    {
        eBackground,
        eColored,
        eTextured,
        eFocusableTextured,
        eNum_
    };

    enum class ConstantBuffer
    {
        eBackground,
        eFocusableTextured,
        eNum_
    };

    enum class SoundEffect
    {
        Bump,
        Goal,
        MenuCycle,
        MenuSelect,
        eNum_
    };

    class MainMenuResources
    {
        friend class ResourceManager;
    public:
        MainMenuResources(types::GameSystems& gameSystems)
            : gameSystems_(gameSystems), menu_(gameSystems_)
        {}

        bool Load();
        void Unload();
        Menu& GetMenu() { return menu_; }

    private:
        types::GameSystems& gameSystems_;
        Menu menu_;
    };

    class MapTestingResources
    {
        friend class ResourceManager;
    public:
        MapTestingResources(types::GameSystems& gameSystems)
            : menu_(gameSystems), pCurrentMapField_(nullptr), pLoadingField_(nullptr), gameSystems_(gameSystems)
        {}

        bool Load();
        void Unload();

        Menu& GetMenu() { return menu_; }
        Menu::ElementRenderDescription GetLoadingRenderDescription() { return loadingRenderDescription_; }
        Menu::Field* GetCurrentMapField() { return pCurrentMapField_; }
        Menu::Field* GetLoadingField() { return pLoadingField_; }
        physics::SceneIndex GetSceneIndex() const { return sceneIndex_; }

    private:
        Menu menu_;
        Menu::ElementRenderDescription loadingRenderDescription_;
        physics::SceneIndex sceneIndex_;
        Menu::Field* pCurrentMapField_;
        Menu::Field* pLoadingField_;
        types::GameSystems& gameSystems_;
    };
    
    class RacingResources
    {
        friend class ResourceManager;
    public:
        class Player1Resources
        {
            friend class RacingResources;
        public:
            Player1Resources(types::GameSystems& gameSystems)
                : gameSystems_(gameSystems), menu_(gameSystems)
            {}

            bool Load();
            void Unload();

            Menu& GetMenu() { return menu_; }
            physics::SceneIndex GetSceneIndex() const { return sceneIndex_; }
            Menu::Field* GetDeckField() { return pDeckField_; }

        private:
            Menu menu_;
            Menu::ElementRenderDescription loadingRenderDescription_;
            Menu::Field* pDeckField_;
            Menu::Field* pLoadingField_;
            physics::SceneIndex sceneIndex_;
            types::GameSystems& gameSystems_;
        };

        class Player2Resources
        {
            friend class RacingResources;
        public:
            Player2Resources(types::GameSystems& gameSystems)
                : gameSystems_(gameSystems), menu_(gameSystems)
            {}

            bool Load();
            void Unload();

            Menu& GetMenu() { return menu_; }
            physics::SceneIndex GetSceneIndex() const { return sceneIndex_; }
            Menu::Field* GetDeckField() { return pDeckField_; }

        private:
            Menu menu_;
            Menu::Field* pDeckField_;
            physics::SceneIndex sceneIndex_;
            types::GameSystems& gameSystems_;
        };

        class HUDResources
        {
            friend class RacingResources;
        public:
            HUDResources(types::GameSystems& gameSystems)
                : gameSystems_(gameSystems), player1HUD_(gameSystems),
                  player2HUD_(gameSystems), pauseMenu_(gameSystems),
                  deckChoosingMenu1_(gameSystems), deckChoosingMenu2_(gameSystems),
                  countDownHUD_(gameSystems)
            {}

            bool Load();
            void Unload();

            Menu& GetPauseMenu() { return pauseMenu_; }
            Menu& GetPlayer1HUD() { return player1HUD_; }
            Menu& GetPlayer2HUD() { return player2HUD_; }
            Menu& GetCountDownHUD() { return countDownHUD_; }
            Menu& GetDeckChoosingMenu1() { return deckChoosingMenu1_; }
            Menu& GetDeckChoosingMenu2() { return deckChoosingMenu2_; }

            D3D11_VIEWPORT& GetPlayer1HUDView() { return player1HUDView_; }
            D3D11_VIEWPORT& GetPlayer2HUDView() { return player2HUDView_; }
            D3D11_VIEWPORT& GetPauseMenuView() { return pauseMenuView_; }
            D3D11_VIEWPORT& GetCountDownHUDView() { return countDownView_; }

            Menu::Field* GetPlayer1CurrentMapField() { return pPlayer1CurrentMapField; }
            Menu::Field* GetPlayer2CurrentMapField() { return pPlayer2CurrentMapField; }
            Menu::Field* GetCountDownField() { return pCountDownField_; }

            Menu::ElementRenderDescription GetCountDown1RenderDescription() { return countDown1RenderDesc_; }
            Menu::ElementRenderDescription GetCountDown2RenderDescription() { return countDown2RenderDesc_; }
            Menu::ElementRenderDescription GetCountDown3RenderDescription() { return countDown3RenderDesc_; }
            Menu::ElementRenderDescription GetCountDownGoRenderDescription() { return countDownGoRenderDesc_; }

        private:
            D3D11_VIEWPORT player1HUDView_;
            D3D11_VIEWPORT player2HUDView_;
            D3D11_VIEWPORT pauseMenuView_;
            D3D11_VIEWPORT countDownView_;
            Menu player1HUD_;
            Menu player2HUD_;
            Menu pauseMenu_;
            Menu deckChoosingMenu1_;
            Menu deckChoosingMenu2_;
            Menu countDownHUD_;
            Menu::Field* pPlayer1CurrentMapField;
            Menu::Field* pPlayer2CurrentMapField;
            Menu::Field* pCountDownField_;
            Menu::ElementRenderDescription countDown1RenderDesc_;
            Menu::ElementRenderDescription countDown2RenderDesc_;
            Menu::ElementRenderDescription countDown3RenderDesc_;
            Menu::ElementRenderDescription countDownGoRenderDesc_;
            types::GameSystems& gameSystems_;
        };

    public:
        RacingResources(types::GameSystems& gameSystems)
            : player1Resources_(gameSystems), player2Resources_(gameSystems),
              hudResources_(gameSystems)
        {}

        bool Load()
        {
            return player1Resources_.Load() &&
                   player2Resources_.Load() &&
                   hudResources_.Load();
        }

        void Unload()
        {
            player1Resources_.Unload();
            player2Resources_.Unload();
            hudResources_.Unload();;
        }

        Player1Resources& GetPlayer1Resources() { return player1Resources_; }
        Player2Resources& GetPlayer2Resources() { return player2Resources_; }
        HUDResources& GetHUDResources() { return hudResources_; }

    private:
        Player1Resources player1Resources_;
        Player2Resources player2Resources_;
        HUDResources hudResources_;
    };

    class ResultsResources
    {
    public:
    private:
    };

public:
    static ResourceManager& GetInstance(types::GameSystems& gameSystems)
    {
        static ResourceManager resourceManager(gameSystems);
        return resourceManager;
    }

    bool Load();
    void Unload();
    dx11rendering::RenderPass& GetBackgroundPass() { return backgroundPass_; }
    Background& GetBackground() { return background_; }

    dx11rendering::ShaderProgram* GetShader(Shader shader) { return shaders_[(int)shader]; }
    dx11rendering::ShaderConstantBuffer* GetConstantBuffer(ConstantBuffer buffer) { return constantBuffers_[(int)buffer]; }
    sound::Effect* GetSoundEffect(SoundEffect effect) { return soundEffects_[(int)effect]; }

    dx11rendering::Geometry* GetFullScreenQuad() { return pFullScreenQuad_; }
    const uint32_t* GetCommonIndices() { return indices_; }

    D3D11_VIEWPORT& GetFullScreenView() { return fullScreenView_; }
    D3D11_VIEWPORT& GetPlayer1View() { return player1Vew_; }
    D3D11_VIEWPORT& GetPlayer2View() { return player2Vew_; }
    void LoadViews();

    MapTestingResources& GetMapTestingResources() { return mapTestingResources_; }
    MainMenuResources& GetMainMenuResources() { return mainMenuResources_; }
    RacingResources& GetRacingResources() { return racingResources_; }
    DJ& GetDJ() { return dj_; }

private:
    ResourceManager(types::GameSystems& gameSystems)
        : shaders_{{nullptr}}, constantBuffers_{{nullptr}}, soundEffects_{{nullptr}}, pFullScreenQuad_(),
          renderer_(gameSystems.displayManager.GetRenderer()), physicsManager_(gameSystems.physicsManager), gameSystems_(gameSystems), indices_{0, 1, 3, 1, 2, 3},
          mainMenuResources_(gameSystems), mapTestingResources_(gameSystems), racingResources_(gameSystems), dj_(gameSystems.soundManager)
    {}

    ~ResourceManager();

private:
    bool LoadBasicResources();
    bool LoadGeometry();
    bool LoadShaders();
    bool LoadConstantBuffers();
    bool LoadSound();
    void LoadPasses();
    void LoadAggregates();

    void FreeResources();

private:
    D3D11_VIEWPORT fullScreenView_;
    D3D11_VIEWPORT player1Vew_;
    D3D11_VIEWPORT player2Vew_;

    dx11rendering::RenderPass backgroundPass_;
    Background background_;

    std::array<dx11rendering::ShaderProgram*, (size_t)Shader::eNum_> shaders_;
    std::array<dx11rendering::ShaderConstantBuffer*, (size_t)ConstantBuffer::eNum_> constantBuffers_;
    std::array<sound::Effect*, (size_t)SoundEffect::eNum_> soundEffects_;
    dx11rendering::Geometry* pFullScreenQuad_;
    dx11rendering::DX11Renderer& renderer_;
    physics::PhysicsManager& physicsManager_;
    types::GameSystems& gameSystems_;

    MainMenuResources mainMenuResources_;
    MapTestingResources mapTestingResources_;
    RacingResources racingResources_;
    DJ dj_;
    uint32_t indices_[6];
};

} // namespace game

} // namespace ice

#endif // RESOURCEMANAGER_H
