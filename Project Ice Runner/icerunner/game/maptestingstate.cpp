#include <iostream>
#include <glm/vec2.hpp>
#include "rendering/displaymanager.h"
#include "events/eventmanager.h"
#include "gamestates.hpp"
#include "deckloader.h"
#include "constants.hpp"
#include "maputility.hpp"

// FIXME: hack
#include <SDL2/SDL_pixels.h>

#define HACK_DELETE(p) do{ delete p; p = nullptr; }while(false);


namespace ice
{

namespace game
{

// FIXME: hack
static dx11rendering::Texture* testMapTextures[2] = {nullptr};
static int32_t activeMapIndex = 0;
static Map testMap1;
static MapUtility::RenderInfo testMap1info;
static Map testMap2;
static MapUtility::RenderInfo testMap2info;
enum class ActiveMap
{
    eMap1,
    eMap2
};

static ActiveMap activeMap = ActiveMap::eMap1;



MapTestingState::MapTestingState(types::GameSystems& gameSystems)
    : GameState(gameSystems), inMenu_(true), renderer_(gameSystems.displayManager.GetRenderer())
{}

GameState& MapTestingState::GetInstance(types::GameSystems& gameSystems)
{
    static MapTestingState deckChoosingState(gameSystems);
    return deckChoosingState;
}

void MapTestingState::Enter()
{
    DeckLoader& loader = DeckLoader::GetInstance();
    if(!loader.Configure())
        std::cout << loader.GetError() << std::endl;

    DeckSettings& settings = loader.GetDeckSettings();
    for (int i = 1; i <= settings.GetSize(); i++)
    {
        MapFactory* pFactory = &settings.MapFactoryAt(Map::Difficulty(i));
        std::cout << "Got factory:" << '\n';
        glm::vec3 mapColor = pFactory->GetMapColor();
        std::cout << "\tMap Color (RGB): " << mapColor.x << ',' << mapColor.y << ',' << mapColor.z << '\n';
        std::cout << "\tMap Difficulty: " << pFactory->GetDifficulty() << '\n';
        std::cout << "\tMap Square Size: " << pFactory->GetMapKit().GetDescription().dimensions.numRows << std::endl;
    }

    if (!CreateBackgroundResources())
        std::cout << "(MapTestingState): ERROR: Failed to create background resources" << std::endl;

    // FIXME: Hack
    testMapTextures[0] = renderer_.GetResourceLoader().CreateTextureFromFont("fonts/underwhe.ttf", "Foo Bar", 60, SDL_Color{0, 220, 255, 255});
    testMapTextures[1] = renderer_.GetResourceLoader().CreateTextureFromFont("fonts/underwhe.ttf", "Bar Foo", 60, SDL_Color{0, 220, 255, 255});
    if (!testMapTextures[0] || !testMapTextures[1])
        std::cout << "Unable to create textures\n" << std::endl;

    NormalizedRect titleGeo;
    titleGeo.topLeftPosition = glm::vec2(-.75, .75);
    titleGeo.extent.x = 1.5;
    titleGeo.extent.y = .2;

    NormalizedRect availableGeo;
    availableGeo.topLeftPosition = glm::vec2(-.75, 0);
    availableGeo.extent.x = .5;
    availableGeo.extent.y = .09;

    NormalizedRect underlineGeo;
    underlineGeo.topLeftPosition = glm::vec2(0, -.06);
    underlineGeo.extent.x = .9;
    underlineGeo.extent.y = .05;

    NormalizedRect testMapGeo;
    testMapGeo.topLeftPosition = glm::vec2(.1, 0);
    testMapGeo.extent.x = .6;
    testMapGeo.extent.y = .09;

    Menu::LabelDescription labelDesc[4];
    labelDesc[0].elementDescription.geometry = titleGeo;
    labelDesc[0].elementDescription.pText = "MAP TESTING";

    labelDesc[1].elementDescription.geometry = availableGeo;
    labelDesc[1].elementDescription.pText = "Available";

    labelDesc[2].elementDescription.geometry = underlineGeo;
    labelDesc[2].elementDescription.pText = ".................";

    labelDesc[3].elementDescription.geometry = testMapGeo;
    labelDesc[3].elementDescription.pText = "Test Map 1";

    NormalizedRect button1Geo;
    button1Geo.topLeftPosition = glm::vec2(-.75, -.3);
    button1Geo.extent.x = .2;
    button1Geo.extent.y = .07;

    NormalizedRect button2Geo;
    button2Geo.topLeftPosition = glm::vec2(-.75, -.5);
    button2Geo.extent.x = .2;
    button2Geo.extent.y = .07;

    NormalizedRect button3Geo;
    button3Geo.topLeftPosition = glm::vec2(-.75, -.7);
    button3Geo.extent.x = .25;
    button3Geo.extent.y = .07;

    Menu::ButtonDescription buttonDesc[3];
    buttonDesc[0].elementDescription.geometry = button1Geo;
    buttonDesc[0].elementDescription.pText = "NEXT";
    buttonDesc[0].pListener = &NextMapListener;
    buttonDesc[0].pUserData = this;

    buttonDesc[1].elementDescription.geometry = button2Geo;
    buttonDesc[1].elementDescription.pText = "PREV";
    buttonDesc[1].pListener = &PreviousMapListener;
    buttonDesc[1].pUserData = this;

    buttonDesc[2].elementDescription.geometry = button3Geo;
    buttonDesc[2].elementDescription.pText = "SELECT";
    buttonDesc[2].pListener = &TestMapListener;
    buttonDesc[2].pUserData = this;

    Menu::Description desc;
    desc.numButtons = 3;
    desc.numLabels = 4;
    desc.pButtonDescriptions = buttonDesc;
    desc.pLabelDescriptions = labelDesc;

    if(!menu_.Describe(renderer_, desc))
        printf("unable to describe menu\n");

    // FIXME: hack
    menu_.SetLabelText(3, *testMapTextures[0], true);

    CreateMapResources();
}

void MapTestingState::Exit()
{
    ReleaseBackgroundResources();
    ReleaseMapResources();
}


GameState* MapTestingState::Update()
{
    if (inMenu_) return UpdateInMenu();
    else UpdateOutOfMenu();

    return nullptr;
}

GameState* MapTestingState::UpdateInMenu()
{
    events::EventState eventState = gameSystems_.eventManager.GetState();

    switch(eventState.GetLatestMovementEvent())
    {
    case events::MovementEvent::eDown:
        menu_.FocusNext();
        break;
    case events::MovementEvent::eUp:
        menu_.FocusPrevious();
        break;
    default:
        break;
    }

    switch(eventState.GetLatestMetaEvent())
    {
    case events::MetaEvent::eSelect:
        menu_.Press();
        break;
    default:
        break;
    }

    return nullptr;
}

void MapTestingState::UpdateOutOfMenu()
{
    events::EventState eventState = gameSystems_.eventManager.GetState();

    switch(eventState.GetLatestMetaEvent())
    {
    case events::MetaEvent::eBack:
        inMenu_ = true;
        break;
    default:
        break;
    }

}

void MapTestingState::NextMapListener(void* pTestingState)
{
    if (activeMapIndex == 1) activeMapIndex = 0;
    else activeMapIndex = 1;

    if (activeMap == ActiveMap::eMap1) activeMap = ActiveMap::eMap2;
    else activeMap = ActiveMap::eMap1;

    // FIXME: hack
    ((MapTestingState*)pTestingState)->menu_.SetLabelText(3, *testMapTextures[activeMapIndex]);
}

void MapTestingState::PreviousMapListener(void* pTestingState)
{
    if (activeMapIndex == 0) activeMapIndex = 1;
    else activeMapIndex = 0;

    if (activeMap == ActiveMap::eMap1) activeMap = ActiveMap::eMap2;
    else activeMap = ActiveMap::eMap1;

    // FIXME: hack
    ((MapTestingState*)pTestingState)->menu_.SetLabelText(3, *testMapTextures[activeMapIndex]);
}

void MapTestingState::TestMapListener(void* pTestingState)
{
    ((MapTestingState*)pTestingState)->inMenu_ = false;
}

void MapTestingState::Render()
{
    if (inMenu_) RenderInMenu();
    else RenderOutOfMenu();
}

void MapTestingState::RenderInMenu()
{
    D3D11_VIEWPORT menuView;
    menuView.Width = 800;
    menuView.Height = 600;
    menuView.MaxDepth = 0;
    menuView.MinDepth = 0;
    menuView.TopLeftX = (1280-800)/2;
    menuView.TopLeftY = (720-600)/2;

    RenderBackground();

    renderer_.SetViewPort(&menuView);
    menu_.Render(renderer_);
}

void MapTestingState::RenderOutOfMenu()
{
    dx11rendering::RenderPass::PipelineDescription pipelineDesc;
    pipelineDesc.pProgram = pWallShader_;
    pipelineDesc.pPSConstantBuffer = nullptr;
    pipelineDesc.pVSConstantBuffer = nullptr;
    pipelineDesc.pTexture = nullptr;

    dx11rendering::Geometry* activeGeo = activeMap == ActiveMap::eMap1 ? pWall1Geometry_ : pWall2Geometry_;
    dx11rendering::RenderPass pass(*activeGeo, pipelineDesc);
    auto& viewports = activeMap == ActiveMap::eMap1 ? testMap1info.viewPorts : testMap2info.viewPorts;

    RenderBackground();
    for (auto& view : viewports)
    {
        pass.Bind();
        renderer_.SetViewPort(&view);
        renderer_.Draw(*activeGeo);
    }
}

void MapTestingState::RenderBackground()
{
    dx11rendering::RenderPass::PipelineDescription pipelineDesc;
    pipelineDesc.pProgram = pBackgroundShader_;
    pipelineDesc.pPSConstantBuffer = pBackgroundConstantBuffer_;
    pipelineDesc.pVSConstantBuffer = nullptr;
    pipelineDesc.pTexture = nullptr;
    dx11rendering::RenderPass backgroundPass(*pBackgroundGeometry_, pipelineDesc);

    if (backgroundBuffer_.phaseShift.x <= -1250.0)
        backgroundBuffer_.phaseShift.x += 1250.0;
    else
        backgroundBuffer_.phaseShift.x -= inMenu_ ? constants::MENU_BACKGROUND_SPEED : constants::GAMEPLAY_BACKGROUND_SPEED;

    backgroundBuffer_.mixColor = (activeMap == ActiveMap::eMap1 ? glm::vec4(0, .85, 1, 1) : glm::vec4(.5, 0, .7, 1));
    pBackgroundConstantBuffer_->Update(&backgroundBuffer_);

    backgroundPass.Bind();

    D3D11_VIEWPORT fullView;
    fullView.Width = 1280;
    fullView.Height = 720;
    fullView.MaxDepth = 0;
    fullView.MinDepth = 0;
    fullView.TopLeftX = 0;
    fullView.TopLeftY = 0;

    renderer_.SetViewPort(&fullView);
    renderer_.Draw(*pBackgroundGeometry_);
}

bool MapTestingState::CreateBackgroundResources()
{
    dx11rendering::DX11Renderer::ResourceLoader resourceLoader = renderer_.GetResourceLoader();

    pBackgroundGeometry_ = resourceLoader.CreateGeometry();
    pBackgroundConstantBuffer_ = resourceLoader.CreateShaderConstantBuffer();
    pBackgroundShader_ = resourceLoader.CreateShaderProgram("shaders/background.vs", "shaders/background.ps");

    if (!(pBackgroundGeometry_ && pBackgroundConstantBuffer_ &&  pBackgroundShader_)) return false;

    PositionVertex vertices[] =
    {
        {glm::vec2(-1, 1)},  // top left
        {glm::vec2(1, 1)},  // top right
        {glm::vec2(1, -1)},  // bottom right
        {glm::vec2(-1, -1)},  // bottom left
    };
    
    uint32_t indices[] = { 0, 1, 3, 1, 2, 3 };

    dx11rendering::Geometry::Description geometryDescription;
    geometryDescription.numIndices = sizeof(indices)/sizeof(uint32_t);
    geometryDescription.numVertices = sizeof(vertices)/sizeof(PositionVertex);
    geometryDescription.pIndices = indices;
    geometryDescription.pVertices = vertices;
    geometryDescription.vertexSize = sizeof(PositionVertex);
    geometryDescription.topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

    if (!pBackgroundGeometry_->Describe(&geometryDescription))
    {
        std::cout << "Failed to describe geometry" << std::endl;
        return false;
    }
    
    D3D11_INPUT_ELEMENT_DESC inputDesc;
    inputDesc.SemanticName = "POSITION";
    inputDesc.SemanticIndex = 0;
    inputDesc.Format = DXGI_FORMAT_R32G32_FLOAT;
    inputDesc.InputSlot = 0;
    inputDesc.AlignedByteOffset = 0;
    inputDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
    inputDesc.InstanceDataStepRate = 0;
    
    dx11rendering::ShaderProgram::CompileDescription compileDescription;
    compileDescription.vsDescription.pEntryPoint = "main";
    compileDescription.vsDescription.pShaderModel = "vs_5_0";
    compileDescription.psDescription.pEntryPoint = "main";
    compileDescription.psDescription.pShaderModel = "ps_5_0";
    compileDescription.inputDescription.numInputElementDescriptions = 1;
    compileDescription.inputDescription.pInputElementDescriptions = &inputDesc;
    
    wchar_t* pError = nullptr;
    size_t errorSize = 0;
    if (!pBackgroundShader_->Compile(compileDescription, (void**)&pError, &errorSize))
    {
        printf("Error compiling background shader: %S\n", pError);
        return false;
    }

    backgroundBuffer_.mixColor = glm::vec4(0, .85, 1, 1);
    backgroundBuffer_.phaseShift = glm::vec4();
    dx11rendering::ShaderConstantBuffer::Description constantBufferDesc;
    constantBufferDesc.pInitialData = &backgroundBuffer_;
    constantBufferDesc.size = sizeof(BackgroundConstantBuffer);

    if(!pBackgroundConstantBuffer_->Describe(constantBufferDesc))
    {
        printf("Unable to describe constant buffer\n");
        return false;
    }

    return true;
}


void MapTestingState::ReleaseBackgroundResources()
{
    // gross and temporary
    HACK_DELETE(pBackgroundGeometry_);
    HACK_DELETE(pBackgroundConstantBuffer_);
    HACK_DELETE(pBackgroundShader_);
}

bool MapTestingState::CreateMapResources()
{
    Map::Description map1Desc(Map::Dimensions(12, 20), Map::Difficulty(1));
    testMap1.SetDescription(map1Desc);

    testMap1.AddWalls(Map::Wall(5, 3), map_tools::DownExtent(3));
    testMap1.AddWalls(Map::Wall(8, 4), map_tools::RightExtent(2));
    testMap1.AddWalls(Map::Wall(3, 7), map_tools::DownExtent(5));
    testMap1.AddWalls(Map::Wall(6, 19), map_tools::LeftExtent(8));
    testMap1.AddWalls(Map::Wall(11, 5), map_tools::RightExtent(2));
    testMap1.AddWalls(Map::Wall(3, 15), map_tools::DownExtent(2));
    testMap1.AddWalls(Map::Wall(0, 12), map_tools::DownExtent(3));

    Map::Description map2Desc(Map::Dimensions(15, 25), Map::Difficulty(2));
    testMap2.SetDescription(map2Desc);
    testMap2.AddWalls(Map::Wall(4, 3), map_tools::DownExtent(3));
    testMap2.AddWalls(Map::Wall(8, 5), map_tools::RightExtent(2));
    testMap2.AddWalls(Map::Wall(3, 7), map_tools::DownExtent(5));
    testMap2.AddWalls(Map::Wall(6, 19), map_tools::LeftExtent(8));
    testMap2.AddWalls(Map::Wall(11, 4), map_tools::RightExtent(2));
    testMap2.AddWalls(Map::Wall(4, 15), map_tools::DownExtent(2));
    testMap2.AddWalls(Map::Wall(1, 12), map_tools::DownExtent(3));


    pWallShader_ = renderer_.GetResourceLoader().CreateShaderProgram("shaders/colored_quad.vs", "shaders/colored_quad.ps");
    if (!pWallShader_)
    {
        printf("Unable to create wall shader\n");
        return false;
    }

    // FIXME: hack
    D3D11_INPUT_ELEMENT_DESC wallShaderInputDesc[2];
    // position
    wallShaderInputDesc[0].AlignedByteOffset = 0;
    wallShaderInputDesc[0].Format = DXGI_FORMAT_R32G32_FLOAT;
    wallShaderInputDesc[0].InputSlot = 0;
    wallShaderInputDesc[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
    wallShaderInputDesc[0].InstanceDataStepRate = 0;
    wallShaderInputDesc[0].SemanticIndex = 0;
    wallShaderInputDesc[0].SemanticName = "POSITION";

    // color
    wallShaderInputDesc[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
    wallShaderInputDesc[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
    wallShaderInputDesc[1].InputSlot = 0;
    wallShaderInputDesc[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
    wallShaderInputDesc[1].InstanceDataStepRate = 0;
    wallShaderInputDesc[1].SemanticIndex = 0;
    wallShaderInputDesc[1].SemanticName = "COLOR";

    dx11rendering::ShaderProgram::CompileDescription wallShaderCompileDesc;
    wallShaderCompileDesc.inputDescription.numInputElementDescriptions = sizeof(wallShaderInputDesc)/sizeof(D3D11_INPUT_ELEMENT_DESC);
    wallShaderCompileDesc.inputDescription.pInputElementDescriptions = wallShaderInputDesc;
    wallShaderCompileDesc.psDescription.pEntryPoint = "main";
    wallShaderCompileDesc.vsDescription.pEntryPoint = "main";
    wallShaderCompileDesc.psDescription.pShaderModel = "ps_5_0";
    wallShaderCompileDesc.vsDescription.pShaderModel = "vs_5_0";

    void* pErrorBuffer;
    size_t errorBufferSize;
    if (!pWallShader_->Compile(wallShaderCompileDesc, &pErrorBuffer, &errorBufferSize))
    {
        printf("Failed to compile wall shader: %u, %s\n", errorBufferSize, pErrorBuffer);
        return false;
    }

    MapUtility::GetRenderInfo(testMap1, 1280, 720, testMap1info);
    MapUtility::GetRenderInfo(testMap2, 1280, 720, testMap2info);


    pWall1Geometry_ = renderer_.GetResourceLoader().CreateGeometry();
    pWall2Geometry_ = renderer_.GetResourceLoader().CreateGeometry();
    if (!pWall1Geometry_ || !pWall2Geometry_)
    {
        printf("Failed to create wall geometry\n");
        return false;
    }

    uint32_t indices[] = { 0, 1, 3, 1, 2, 3 };
    dx11rendering::Geometry::Description wallDesc;
    wallDesc.numIndices = 6;
    wallDesc.numVertices = 4;
    wallDesc.pIndices = indices;
    wallDesc.pVertices = testMap1info.wallVertices;
    wallDesc.topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
    wallDesc.vertexSize = sizeof(ColoredVertex);

    if(!pWall1Geometry_->Describe(&wallDesc))
    {
        printf("Failed to create wall geometry\n");
        return false;
    }

    testMap2info.wallVertices[0].color = glm::vec4(0, 0, 0, 1);
    testMap2info.wallVertices[2].color = glm::vec4(0, 0, 0, 1);
    wallDesc.pVertices = testMap2info.wallVertices;
    if(!pWall2Geometry_->Describe(&wallDesc))
    {
        printf("Failed to create wall geometry\n");
        return false;
    }

    return true;
}

void MapTestingState::ReleaseMapResources()
{
    HACK_DELETE(pWallShader_);
    HACK_DELETE(pWall1Geometry_);
}

} // namespace game

} // namespace ice
