#ifndef MAPUTILITY_HPP
#define MAPUTILITY_HPP
#include <vector>
#include "rendering/dx11structs.h"
#include "gamerenderstructs.hpp"
#include "deckloader.h"

namespace ice
{

namespace game
{

class MapUtility
{
public:
    struct RenderInfo
    {
        std::vector<D3D11_VIEWPORT> viewPorts;
        ColoredVertex wallVertices[4];
        ColoredVertex playerVertices[4];
    };

public:
    static inline void GetRenderInfo(const Map& map, size_t screenWidth, size_t screenHeight, RenderInfo& info)
    {
        DeckLoader& loader = DeckLoader::GetInstance();
        MapFactory& factory = loader.GetDeckSettings().MapFactoryAt(map.GetDescription().difficulty);

        info.wallVertices[0] = ColoredVertex{glm::vec2(-1, 1), glm::vec4(0, 0, 1, 1)};
        info.wallVertices[1] = ColoredVertex{glm::vec2(1, 1), glm::vec4(factory.GetMapColor(), 1)};
        info.wallVertices[2] = ColoredVertex{glm::vec2(1, -1), glm::vec4(0, 0, 1, 1)};
        info.wallVertices[3] = ColoredVertex{glm::vec2(-1, -1), glm::vec4(factory.GetMapColor(), 1)};

        Map::Dimensions dimensions = map.GetDescription().dimensions;
        float wallWidth = (float)(int)(screenWidth/dimensions.numColumns);
        float wallHeight = (float)(int)(screenHeight/dimensions.numRows);

        D3D11_VIEWPORT viewPort = {};
        viewPort.Width = wallWidth;
        viewPort.Height = wallHeight;

        for (Map::Wall w : map)
        {
            viewPort.TopLeftX = wallWidth * w.GetColumn();
            viewPort.TopLeftY = wallHeight * w.GetRow();
            info.viewPorts.push_back(viewPort);
        }
    }
};

} // namespace game

} // namespace ice

#endif // MAPUTILITY_HPP
