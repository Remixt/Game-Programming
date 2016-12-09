#ifndef MAPUTILITY_HPP
#define MAPUTILITY_HPP
#include <vector>
#include "rendering/dx11structs.h"
#include "gamerenderstructs.hpp"
#include "deckloader.h"
#include "rendering/dx11fwd.hpp"

namespace ice
{

namespace game
{

class MapUtility
{
public:
    struct SceneInfo
    {
        std::vector<glm::vec2> wallPositions;
        glm::vec2 playerPos;
        glm::vec2 goalPos;
        ColoredVertex wallVertices[4];
        ColoredVertex playerVertices[4];
        ColoredVertex goalVertices[4];
        glm::vec3 mapColor;
        glm::vec2 wallExtent;
    };

public:
    static void GetSceneInfo(const Map& map, SceneInfo& info)
    {
        DeckLoader& loader = DeckLoader::GetInstance();
        MapFactory& factory = loader.GetDeckSettings().MapFactoryAt(map.GetDescription().difficulty);

        info.wallPositions.clear();

        info.mapColor = factory.GetMapColor();

        info.wallVertices[0] = ColoredVertex{glm::vec2(-1, 1), glm::vec4(factory.GetWallColor(), 1)};
        info.wallVertices[1] = ColoredVertex{glm::vec2(1, 1), glm::vec4(info.mapColor, 1)};
        info.wallVertices[2] = ColoredVertex{glm::vec2(1, -1), glm::vec4(factory.GetWallColor(), 1)};
        info.wallVertices[3] = ColoredVertex{glm::vec2(-1, -1), glm::vec4(info.mapColor, 1)};

        info.playerVertices[0] = ColoredVertex{glm::vec2(-1, 1), glm::vec4(info.mapColor, 1)};
        info.playerVertices[1] = ColoredVertex{glm::vec2(1, 1), glm::vec4(factory.GetPlayerColor(), 1)};
        info.playerVertices[2] = ColoredVertex{glm::vec2(1, -1), glm::vec4(info.mapColor, 1)};
        info.playerVertices[3] = ColoredVertex{glm::vec2(-1, -1), glm::vec4(factory.GetPlayerColor(), 1)};

        info.goalVertices[0] = ColoredVertex{glm::vec2(-1, 1), glm::vec4(factory.GetGoalColor(), 1)};
        info.goalVertices[1] = ColoredVertex{glm::vec2(1, 1), glm::vec4(factory.GetGoalColor(), 1)};
        info.goalVertices[2] = ColoredVertex{glm::vec2(1, -1), glm::vec4(factory.GetGoalColor(), 1)};
        info.goalVertices[3] = ColoredVertex{glm::vec2(-1, -1), glm::vec4(factory.GetGoalColor(), 1)};

        MapKit::Dimensions dimensions = map.GetKit().GetDimensions();

        float wallWidth = 1.0f/dimensions.numColumns;
        float wallHeight = 1.0f/dimensions.numRows;
        info.wallExtent.x = wallWidth;
        info.wallExtent.y = wallHeight;

        auto player = map.GetPlayer();
        info.playerPos.x = player.GetColumn()*wallWidth;
        info.playerPos.y = player.GetRow()*wallHeight;

        auto goal = map.GetGoal();
        info.goalPos.x = goal.GetColumn()*wallWidth;
        info.goalPos.y = goal.GetRow()*wallHeight;

        glm::vec2 topLeft;
        for (Map::Wall w : map)
        {
            topLeft.x = wallWidth * w.GetColumn();
            topLeft.y = wallHeight * w.GetRow();
            info.wallPositions.push_back(topLeft);
        }
    }
};

} // namespace game

} // namespace ice

#endif // MAPUTILITY_HPP
