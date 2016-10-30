#ifndef GAMERENDERSTRUCTS_HPP
#define GAMERENDERSTRUCTS_HPP
#include <vector>
#include <string>
#include <glm/vec4.hpp>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include "rendering/dx11fwd.hpp"

namespace ice
{

namespace game
{

// Vertex Types
struct PositionVertex
{
    glm::vec2 position;
};

struct ColoredVertex
{
    glm::vec2 position;
    glm::vec4 color;
};

struct TexturedVertex
{
    glm::vec2 position;
    glm::vec2 uv;
};

struct NormalizedRect
{
    glm::vec2 topLeftPosition;
    glm::vec2 extent;
};

struct ElementConstantBuffer
{
    glm::vec4 isSelected; // only x used as boolean value;
};

struct BackgroundConstantBuffer
{
    glm::vec4 mixColor;
    glm::vec4 phaseShift;
};

class Menu
{
public:
    using ButtonListener = void(void* pUserData);

public:
    struct ElementDescription
    {
        const char* pText;
        NormalizedRect geometry;
    };

    struct ButtonDescription
    {
        ElementDescription elementDescription;
        ButtonListener* pListener;
        void* pUserData;
    };

    struct LabelDescription
    {
        ElementDescription elementDescription;
    };

    struct Description
    {
        ButtonDescription* pButtonDescriptions;
        LabelDescription* pLabelDescriptions;
        uint32_t numButtons;
        uint32_t numLabels;
    };

private:
    struct Button
    {
        Button()
            : pGeometry(nullptr), pTextTexture(nullptr), pListener(nullptr)
        {}

        dx11rendering::Geometry* pGeometry;
        dx11rendering::Texture* pTextTexture;
        ButtonListener* pListener;
        void* pUserData;
    };

    struct Label
    {
        Label()
            : pGeometry(nullptr), pTextTexture(nullptr)
        {}

        dx11rendering::Geometry* pGeometry;
        dx11rendering::Texture* pTextTexture;
    };

public:
    Menu()
        : pMenuGeometry_(nullptr), pMenuShader_(nullptr), pElementShader_(nullptr), pElementConstantBuffer_(nullptr), focusedButtonPos_(0)
    {}

    ~Menu();

    void Free();

    bool Describe(dx11rendering::DX11Renderer& renderer, const Description& description);
    void Render(dx11rendering::DX11Renderer& renderer);
    void SetButtonText(uint32_t index, dx11rendering::Texture& texture);
    // FIXME: hack
    void SetLabelText(uint32_t index, dx11rendering::Texture& texture, bool freeCurrent = false);
    void FocusNext();
    void FocusPrevious();
    void Press();

private:
    std::vector<Button> buttons_;
    std::vector<Label> labels_;
    dx11rendering::Geometry* pMenuGeometry_;
    dx11rendering::ShaderProgram* pMenuShader_;
    dx11rendering::ShaderProgram* pElementShader_;
    dx11rendering::ShaderConstantBuffer* pElementConstantBuffer_;
    uint32_t focusedButtonPos_;
};

} // namespace game

} // namespace ice

#endif // GAMERENDERSTRUCTS_HPP
