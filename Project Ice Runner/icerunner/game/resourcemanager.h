#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H
#include <array>
#include "rendering/dx11structs.h"
#include "gamerenderstructs.hpp"

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
        eNum_
    };

public:
    static ResourceManager& GetInstance(dx11rendering::DX11Renderer& renderer)
    {
        static ResourceManager resourceManager(renderer);
        return resourceManager;
    }

    bool Load();
    dx11rendering::RenderPass& GetBackgroundPass() { return backgroundPass_; }
    Menu& GetMapTestingMenu() { return mapTestingMenu_; }
    dx11rendering::ShaderProgram* GetShader(Shader shader) { return shaders_[(size_t)shader]; }

    D3D11_VIEWPORT& GetFullScreenView() { return fullScreenView_; }
    D3D11_VIEWPORT& GetPlayer1View() { return player1Vew_; }
    D3D11_VIEWPORT& GetPlayer2View() { return player2Vew_; }

private:
    ResourceManager(dx11rendering::DX11Renderer& renderer)
        : shaders_{{nullptr}}, constantBuffers_{{nullptr}}, pFullScreenQuad_(), renderer_(renderer)
    {}

private:
    bool LoadBasicResources();
    bool LoadGeometry();
    bool LoadShaders();

    bool LoadConstantBuffers();
    bool LoadMapTestingResources();

private:
    D3D11_VIEWPORT fullScreenView_;
    D3D11_VIEWPORT player1Vew_;
    D3D11_VIEWPORT player2Vew_;
    Menu mapTestingMenu_;

    dx11rendering::RenderPass backgroundPass_;
    std::array<dx11rendering::ShaderProgram*, (size_t)Shader::eNum_> shaders_;
    std::array<dx11rendering::ShaderConstantBuffer*, (size_t)Shader::eNum_> constantBuffers_;
    dx11rendering::Geometry* pFullScreenQuad_;
    dx11rendering::DX11Renderer& renderer_;
};

} // namespace game

} // namespace ice

#endif // RESOURCEMANAGER_H
