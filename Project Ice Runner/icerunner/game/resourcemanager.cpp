#include "rendering/dx11renderer.h"
#include "resourcemanager.h"
#include "gamerenderstructs.hpp"

namespace ice
{

namespace game
{

bool ResourceManager::Load()
{
    return LoadBasicResources() &&
           LoadConstantBuffers() &&
           LoadMapTestingResources();
}

bool ResourceManager::LoadBasicResources()
{
    dx11rendering::DX11Renderer::ResourceLoader resourceLoader = renderer_.GetResourceLoader();
    shaders_[(size_t)Shader::eBackground] = resourceLoader.CreateShaderProgram("shaders/background.vs", "shaders/background.ps");
    shaders_[(size_t)Shader::eColored] = resourceLoader.CreateShaderProgram("shaders/colored_quad.vs", "shaders/colored_quad.ps");
    shaders_[(size_t)Shader::eTextured] = resourceLoader.CreateShaderProgram("shaders/textured_quad.vs", "shaders/textured_quad.ps");
    shaders_[(size_t)Shader::eFocusableTextured] = resourceLoader.CreateShaderProgram("shaders/textured_quad.vs", "shaders/focusable_textured_quad.ps");

    for (auto pShaderProgram : shaders_)
        if (!pShaderProgram) goto failure;

    pFullScreenQuad_ = resourceLoader.CreateGeometry();

    if (!pFullScreenQuad_ || !LoadGeometry() || !LoadShaders()) goto failure;

    return true;

failure:
    printf("Unable to load basic resources\n");
    return false;
}

bool ResourceManager::LoadGeometry()
{
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

    if (!pFullScreenQuad_->Describe(&geometryDescription)) goto failure;

    return true;

failure:
    printf("Failed to load geometry\n");
    return false;
}

bool ResourceManager::LoadShaders()
{
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

    void* pError = nullptr;
    size_t errorSize = 0;
    if (!shaders_[(size_t)Shader::eBackground]->Compile(compileDescription, (void**)&pError, &errorSize)) goto failure;

    return true;

failure:
    printf("Failed to load shaders: %s\n", pError);
    return false;
}

bool ResourceManager::LoadConstantBuffers()
{
    dx11rendering::DX11Renderer::ResourceLoader& loader = renderer_.GetResourceLoader();

    constantBuffers_[(size_t)ConstantBuffer::eBackground] = loader.CreateShaderConstantBuffer();
    if (!constantBuffers_[(size_t)ConstantBuffer::eBackground]) goto failure; // FIXME

    BackgroundConstantBuffer backgroundBuffer;
    backgroundBuffer.mixColor = glm::vec4(0, .85, 1, 1);
    backgroundBuffer.phaseShift = glm::vec4();

    dx11rendering::ShaderConstantBuffer::Description constantBufferDesc;
    constantBufferDesc.pInitialData = &backgroundBuffer;
    constantBufferDesc.size = sizeof(BackgroundConstantBuffer);

    if(!constantBuffers_[(size_t)ConstantBuffer::eBackground]->Describe(constantBufferDesc)) goto failure;

    return true;

failure:
    printf("Failed to create constant buffers\n");
    return false;
}

} // namespace game

} // namespace ice
