#ifndef MAP_HPP
#define MAP_HPP
#include <functional>
#include <cstdlib>
#include <cstdint>
#include <vector>
#include <glm/vec2.hpp>
#include "maptools.hpp"

namespace ice
{
namespace game
{
class MapLoader;

class Map
{
public:
    friend class MapLoader;

public:
    struct Dimensions
    {
        Dimensions()
            : numRows(), numColumns()
        {}

        Dimensions(uint32_t numRows, uint32_t numColumns)
            : numRows(numRows), numColumns(numColumns)
        {}

        uint32_t numRows;
        uint32_t numColumns;
    };

    class Difficulty
    {
    public:
        using Rep = uint32_t;

    public:
        explicit Difficulty(Rep level = 0)
            : level_(level)
        {}

        operator Rep() const { return level_; }

    private:
        Rep level_;
    };

    class Wall
    {
    public:
        using Rep = glm::ivec2::value_type;

    public:
        explicit Wall(glm::ivec2 pos)
            : pos_(pos)
        {}

        Wall(Rep row, Rep col)
            : pos_(row, col)
        {}

        void ShiftCol(Rep col) { pos_.y += col; }
        void ShiftRow(Rep row) { pos_.x += row; }

        Rep GetRow() const { return pos_.x; }
        Rep GetColumn() const { return pos_.y; }

    private:
        glm::ivec2 pos_;
    };

    struct Description
    {
        Description(Dimensions dimensions = Dimensions(), Difficulty difficulty = Difficulty())
            : dimensions(dimensions), difficulty(difficulty)
        {}

        Dimensions dimensions;
        Difficulty difficulty;
    };

public:
    Map(Description description = Description())
        : walls_(), wallExistenceMap_(description.dimensions.numRows * description.dimensions.numColumns), description_(description)
    {}

    void AddWall(Wall wall)
    {
        walls_.push_back(wall);
        wallExistenceMap_[wall.GetRow()*wall.GetColumn() + wall.GetColumn()] = true;
    }

    void AddWalls(Wall startWall, map_tools::UpExtent extent)
    {
        int startRow = startWall.GetRow();
        int bound = startRow - extent;
        for (int r = startWall.GetRow(); r >= bound; r--, startWall.ShiftRow(-1))
        {
            walls_.push_back(startWall);
            wallExistenceMap_[startWall.GetRow()*startWall.GetColumn() + startWall.GetColumn()] = true;
        }
    }

    void AddWalls(Wall startWall, map_tools::DownExtent extent)
    {
        int startRow = startWall.GetRow();
        int bound = startRow + extent;
        for (int r = startRow; r <= bound; r++, startWall.ShiftRow(1))
        {
            walls_.push_back(startWall);
            wallExistenceMap_[startWall.GetRow()*startWall.GetColumn() + startWall.GetColumn()] = true;
        }
    }

    void AddWalls(Wall startWall, map_tools::LeftExtent extent)
    {
        int startCol = startWall.GetColumn();
        int bound = startCol - extent;
        for (int c = startCol; c >= bound; c--, startWall.ShiftCol(-1))
        {
            walls_.push_back(startWall);
            wallExistenceMap_[startWall.GetRow()*startWall.GetColumn() + startWall.GetColumn()] = true;
        }
    }

    void AddWalls(Wall startWall, map_tools::RightExtent extent)
    {
        int startCol = startWall.GetColumn();
        int bound = startCol + extent;
        for (int c = startCol; c <= bound; c++, startWall.ShiftCol(1))
        {
            walls_.push_back(startWall);
            wallExistenceMap_[startWall.GetRow()*startWall.GetColumn() + startWall.GetColumn()] = true;
        }
    }

    bool HasWall(Wall wall)
    {
        return wallExistenceMap_[wall.GetRow()*wall.GetColumn() + wall.GetColumn()];
    }

    void SetDimensions(Dimensions dimensions)
    {
        wallExistenceMap_.resize(dimensions.numRows * dimensions.numColumns);
        description_.dimensions = dimensions;
    }

    void SetDescription(Description description)
    {
        wallExistenceMap_.resize(description.dimensions.numRows * description.dimensions.numColumns);
        description_ = description;
    }

    Description GetDescription() const { return description_; }

    void Clear() { walls_.clear(); }

    std::vector<Wall>::iterator begin() { return walls_.begin(); }
    std::vector<Wall>::iterator end() { return walls_.end(); }

    std::vector<Wall>::const_iterator begin() const { return walls_.cbegin(); }
    std::vector<Wall>::const_iterator end() const { return walls_.cend(); }

private:
    std::vector<Wall> walls_;
    std::vector<bool> wallExistenceMap_;
    Description description_;
};


} // namespace game

} // namespace ice

//! Allow Map::Difficulty to be used as a key in a map.
template <>
struct std::hash<ice::game::Map::Difficulty> : std::hash<ice::game::Map::Difficulty::Rep> {};

#endif // MAP_HPP
