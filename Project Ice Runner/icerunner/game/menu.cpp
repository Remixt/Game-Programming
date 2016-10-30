#include <SDL2/SDL_pixels.h>
#include "game/gamerenderstructs.hpp"
#include "rendering/dx11renderer.h"

#define HACK_DELETE(p) do{delete p; p = nullptr;}while(false)

namespace ice
{

namespace game
{

Menu::~Menu()
{
    Free();
}

void Menu::Free()
{
    HACK_DELETE(pMenuGeometry_);
    HACK_DELETE(pMenuShader_);
    HACK_DELETE(pElementShader_);
    HACK_DELETE(pElementConstantBuffer_);

    for(Button button : buttons_)
    {
        HACK_DELETE(button.pGeometry);
        HACK_DELETE(button.pTextTexture);
    }

    for(Label label : labels_)
    {
        HACK_DELETE(label.pGeometry);
        HACK_DELETE(label.pTextTexture);
    }
}

bool Menu::Describe(dx11rendering::DX11Renderer& renderer, const Description& description)
{
    buttons_.reserve(description.numButtons);
    labels_.reserve(description.numLabels);

    dx11rendering::DX11Renderer::ResourceLoader& resourceLoader = renderer.GetResourceLoader();
    pMenuGeometry_ = resourceLoader.CreateGeometry();
    pMenuShader_ = resourceLoader.CreateShaderProgram("shaders/colored_quad.vs", "shaders/colored_quad.ps");
    pElementShader_ = resourceLoader.CreateShaderProgram("shaders/textured_quad.vs", "shaders/focusable_textured_quad.ps");
    pElementConstantBuffer_ = resourceLoader.CreateShaderConstantBuffer();

    if (!(pMenuGeometry_ && pMenuShader_ && pElementShader_ && pElementConstantBuffer_))
    {
        printf("Failed to allocate high level menu resources\n");
        this->Free();
        return false;
    }

    // 2 triangles: (top left, top right, bottom left), (top right, bottom right, bottom left)
    // The fact that they are common would suggest reuse, but we don't really care about performance right now.
    uint32_t commonIndices[] = { 0, 1, 3, 1, 2, 3 };
    uint32_t numIndices = sizeof(commonIndices)/sizeof(uint32_t);
    uint32_t numVertices = 4; // always drawing rectangles.

    ColoredVertex menuVertices[] =
    {
        {glm::vec2(-1, 1), glm::vec4(0, 0, 0, 1)}, // top left
        {glm::vec2(1, 1), glm::vec4(0, .45, 1, 1)}, // top right
        {glm::vec2(1, -1), glm::vec4(0, 0, 0, 1)}, // bottom right
        {glm::vec2(-1, -1), glm::vec4(0, .45, 1, 1)} // bottom left
    };

    // Create the menu geometry.
    dx11rendering::Geometry::Description menuGeometryDesc;
    menuGeometryDesc.numIndices = numIndices;
    menuGeometryDesc.numVertices = numVertices;
    menuGeometryDesc.pVertices = menuVertices;
    menuGeometryDesc.pIndices = commonIndices;
    menuGeometryDesc.vertexSize = sizeof(ColoredVertex);
    menuGeometryDesc.topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

    if (!pMenuGeometry_->Describe(&menuGeometryDesc))
    {
        printf("Failed to allocate menu geometry\n");
        this->Free();
        return false;
    }

    // Create the menu shader
    D3D11_INPUT_ELEMENT_DESC menuShaderInputDesc[2];
    // position
    menuShaderInputDesc[0].AlignedByteOffset = 0;
    menuShaderInputDesc[0].Format = DXGI_FORMAT_R32G32_FLOAT;
    menuShaderInputDesc[0].InputSlot = 0;
    menuShaderInputDesc[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
    menuShaderInputDesc[0].InstanceDataStepRate = 0;
    menuShaderInputDesc[0].SemanticIndex = 0;
    menuShaderInputDesc[0].SemanticName = "POSITION";

    // color
    menuShaderInputDesc[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
    menuShaderInputDesc[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
    menuShaderInputDesc[1].InputSlot = 0;
    menuShaderInputDesc[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
    menuShaderInputDesc[1].InstanceDataStepRate = 0;
    menuShaderInputDesc[1].SemanticIndex = 0;
    menuShaderInputDesc[1].SemanticName = "COLOR";

    dx11rendering::ShaderProgram::CompileDescription menuShaderCompileDesc;
    menuShaderCompileDesc.inputDescription.numInputElementDescriptions = sizeof(menuShaderInputDesc)/sizeof(D3D11_INPUT_ELEMENT_DESC);
    menuShaderCompileDesc.inputDescription.pInputElementDescriptions = menuShaderInputDesc;
    menuShaderCompileDesc.psDescription.pEntryPoint = "main";
    menuShaderCompileDesc.vsDescription.pEntryPoint = "main";
    menuShaderCompileDesc.psDescription.pShaderModel = "ps_5_0";
    menuShaderCompileDesc.vsDescription.pShaderModel = "vs_5_0";

    void* pErrorBuffer;
    size_t errorBufferSize;
    if (!pMenuShader_->Compile(menuShaderCompileDesc, &pErrorBuffer, &errorBufferSize))
    {
        printf("Failed to compile menu shader: %u, %s\n", errorBufferSize, pErrorBuffer);
        this->Free();
        return false;
    }

    // Create The Element(button and label) shader

    D3D11_INPUT_ELEMENT_DESC elementShaderInputDesc[2];
    // position
    elementShaderInputDesc[0].AlignedByteOffset = 0;
    elementShaderInputDesc[0].Format = DXGI_FORMAT_R32G32_FLOAT;
    elementShaderInputDesc[0].InputSlot = 0;
    elementShaderInputDesc[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
    elementShaderInputDesc[0].InstanceDataStepRate = 0;
    elementShaderInputDesc[0].SemanticIndex = 0;
    elementShaderInputDesc[0].SemanticName = "POSITION";

    // uv
    elementShaderInputDesc[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
    elementShaderInputDesc[1].Format = DXGI_FORMAT_R32G32_FLOAT;
    elementShaderInputDesc[1].InputSlot = 0;
    elementShaderInputDesc[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
    elementShaderInputDesc[1].InstanceDataStepRate = 0;
    elementShaderInputDesc[1].SemanticIndex = 0;
    elementShaderInputDesc[1].SemanticName = "TEXCOORD";

    dx11rendering::ShaderProgram::CompileDescription elementShaderCompileDesc;
    elementShaderCompileDesc.inputDescription.numInputElementDescriptions = sizeof(elementShaderInputDesc)/sizeof(D3D11_INPUT_ELEMENT_DESC);
    elementShaderCompileDesc.inputDescription.pInputElementDescriptions = elementShaderInputDesc;
    elementShaderCompileDesc.psDescription.pEntryPoint = "main";
    elementShaderCompileDesc.vsDescription.pEntryPoint = "main";
    elementShaderCompileDesc.psDescription.pShaderModel = "ps_5_0";
    elementShaderCompileDesc.vsDescription.pShaderModel = "vs_5_0";

    if (!pElementShader_->Compile(elementShaderCompileDesc, &pErrorBuffer, &errorBufferSize))
    {
        std::wstring error((wchar_t*)pErrorBuffer, errorBufferSize);
        printf("Failed to compile element shader: %S\n", error.c_str());
        this->Free();
        return false;
    }

    // Create the menu element constant buffer
    dx11rendering::ShaderConstantBuffer::Description elementConstantBufferDesc;
    elementConstantBufferDesc.size = sizeof(ElementConstantBuffer);

    ElementConstantBuffer initialConstantBuffer;
    initialConstantBuffer.isSelected = glm::vec4(); // false
    elementConstantBufferDesc.pInitialData = &initialConstantBuffer;

    if (!pElementConstantBuffer_->Describe(elementConstantBufferDesc))
    {
        printf("Failed to describe menu element constant buffer\n");
        this->Free();
        return false;
    }

    // For each button description, create the buttons geometry and texture, set them in a button,
    // and add the new button to the vector.
    ButtonDescription* pButtonDescs = description.pButtonDescriptions;
    for (uint32_t i = 0; i < description.numButtons; i++)
    {
        ButtonDescription description = pButtonDescs[i];
        description.elementDescription.geometry.topLeftPosition.x;

        NormalizedRect& buttonGeometry = description.elementDescription.geometry;
        glm::vec2 extent = buttonGeometry.extent;
        TexturedVertex vertices[] =
        {
            {buttonGeometry.topLeftPosition, glm::vec2(0, 0)}, // top left
            {buttonGeometry.topLeftPosition + glm::vec2(extent.x, 0), glm::vec2(1, 0)}, // top right
            {buttonGeometry.topLeftPosition + glm::vec2(extent.x, -extent.y), glm::vec2(1, 1)}, // bottom right
            {buttonGeometry.topLeftPosition + glm::vec2(0, -extent.y), glm::vec2(0, 1)} // bottom left
        };

        dx11rendering::Geometry::Description newButtonDesc;
        newButtonDesc.numIndices = numIndices;
        newButtonDesc.numVertices = numVertices;
        newButtonDesc.pIndices = commonIndices;
        newButtonDesc.pVertices = vertices;
        newButtonDesc.topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
        newButtonDesc.vertexSize = sizeof(TexturedVertex);

        Button newButton;
        newButton.pListener = pButtonDescs[i].pListener;
        newButton.pGeometry = resourceLoader.CreateGeometry();
        newButton.pUserData = pButtonDescs[i].pUserData;
        if (!newButton.pGeometry)
        {
            printf("Failed to allocate button geometry; index: %u\n", i);
            this->Free();
            return false;
        }

        if(!newButton.pGeometry->Describe(&newButtonDesc))
        {
            printf("Failed to allocate button geometry; index: %u\n", i);
            this->Free();
            return false;
        }

        newButton.pTextTexture = resourceLoader.CreateTextureFromFont("fonts/underwhelmed.ttf", description.elementDescription.pText, 60, SDL_Color{0, 220, 255, 255});
        if (!newButton.pTextTexture)
        {
            printf("Failed to allocate button geometry; index: %u\n", i);
            this->Free();
            return false;
        }

        buttons_.push_back(newButton);
    }

    // For each label description, create the labels geometry and texture, set them in a label,
    // and add the new label to the vector.
    LabelDescription* pLabelDescription = description.pLabelDescriptions;
    for (uint32_t i = 0; i < description.numLabels; i++)
    {
        LabelDescription description = pLabelDescription[i];
        description.elementDescription.geometry.topLeftPosition.x;

        NormalizedRect& labelGeometry = description.elementDescription.geometry;
        glm::vec2 extent = labelGeometry.extent;
        TexturedVertex vertices[] =
        {
            {labelGeometry.topLeftPosition, glm::vec2(0, 0)}, // top left
            {labelGeometry.topLeftPosition + glm::vec2(extent.x, 0), glm::vec2(1, 0)}, // top right
            {labelGeometry.topLeftPosition + glm::vec2(extent.x, -extent.y), glm::vec2(1, 1)}, // bottom right
            {labelGeometry.topLeftPosition + glm::vec2(0, -extent.y), glm::vec2(0, 1)} // bottom left
        };

        dx11rendering::Geometry::Description newLabelDesc;
        newLabelDesc.numIndices = numIndices;
        newLabelDesc.numVertices = numVertices;
        newLabelDesc.pIndices = commonIndices;
        newLabelDesc.pVertices = vertices;
        newLabelDesc.topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
        newLabelDesc.vertexSize = sizeof(TexturedVertex);

        Label newLabel;
        newLabel.pGeometry = resourceLoader.CreateGeometry();
        if (!newLabel.pGeometry)
        {
            printf("Failed to allocate label geometry; index: %u\n", i);
            this->Free();
            return false;
        }

        if(!newLabel.pGeometry->Describe(&newLabelDesc))
        {
            printf("Failed to allocate label geometry; index: %u\n", i);
            this->Free();
            return false;
        }

        newLabel.pTextTexture = resourceLoader.CreateTextureFromFont("fonts/underwhe.ttf", description.elementDescription.pText, 80, SDL_Color{0, 220, 255, 255});
        if(!newLabel.pTextTexture)
        {
            printf("Failed to allocate label geometry; index: %u\n", i);
            this->Free();
            return false;
        }

        labels_.push_back(newLabel);
    }

    if (!buttons_.empty()) focusedButtonPos_ = 1;

    return true;
}

void Menu::Render(dx11rendering::DX11Renderer& renderer)
{
    dx11rendering::RenderPass::PipelineDescription pipelineDesc;
    pipelineDesc.pProgram = pMenuShader_;
    pipelineDesc.pPSConstantBuffer = nullptr;
    pipelineDesc.pVSConstantBuffer = nullptr;
    pipelineDesc.pTexture = nullptr;

    dx11rendering::RenderPass menuPass(*pMenuGeometry_, pipelineDesc);
    menuPass.Bind();

    renderer.Draw(*pMenuGeometry_);

    for (auto label : labels_)
    {
        dx11rendering::RenderPass::PipelineDescription labelPipelineDesc;
        labelPipelineDesc.pProgram = pElementShader_;
        labelPipelineDesc.pPSConstantBuffer = pElementConstantBuffer_;
        labelPipelineDesc.pVSConstantBuffer = nullptr;
        labelPipelineDesc.pTexture = label.pTextTexture;

        dx11rendering::RenderPass labelPass(*label.pGeometry, labelPipelineDesc);
        labelPass.Bind();

        renderer.Draw(*label.pGeometry);
    }

    ElementConstantBuffer selectedBuffer;
    selectedBuffer.isSelected.x = 1.0f;

    ElementConstantBuffer unselectedBuffer;
    unselectedBuffer.isSelected.x = 0;

    unsigned focusIndex = focusedButtonPos_-1;
    for (unsigned i = 0; i < buttons_.size(); i++)
    {
        dx11rendering::RenderPass::PipelineDescription buttonPipelineDesc;
        buttonPipelineDesc.pProgram = pElementShader_;
        buttonPipelineDesc.pPSConstantBuffer = pElementConstantBuffer_;
        buttonPipelineDesc.pVSConstantBuffer = nullptr;
        buttonPipelineDesc.pTexture = buttons_[i].pTextTexture;

        dx11rendering::RenderPass buttonPass(*buttons_[i].pGeometry, buttonPipelineDesc);
        buttonPass.Bind();

        if (i == focusIndex)
        {
            pElementConstantBuffer_->Update(&selectedBuffer);
            renderer.Draw(*buttons_[i].pGeometry);
            pElementConstantBuffer_->Update(&unselectedBuffer);
        }
        else
        {
            renderer.Draw(*buttons_[i].pGeometry);
        }
    }
}

void Menu::SetButtonText(uint32_t index, dx11rendering::Texture& texture)
{
    buttons_[index].pTextTexture = &texture;
}

void Menu::SetLabelText(uint32_t index, dx11rendering::Texture& texture, bool freeCurrent)
{
    // FIXME: hack
    if (freeCurrent) delete labels_[index].pTextTexture;

    labels_[index].pTextTexture = &texture;
}

void Menu::FocusNext()
{
    if (buttons_.empty()) return;

    if (focusedButtonPos_ == buttons_.size()) focusedButtonPos_ = 1;
    else focusedButtonPos_++;
}

void Menu::FocusPrevious()
{
    if (buttons_.empty()) return;

    if (focusedButtonPos_ == 1) focusedButtonPos_ = (uint32_t)buttons_.size();
    else focusedButtonPos_--;
}

void Menu::Press()
{
    if (buttons_.empty()) return;
    Button& focusedButton = buttons_[focusedButtonPos_-1];
    focusedButton.pListener(focusedButton.pUserData);
}

} // namespace game

} // namespace ice
