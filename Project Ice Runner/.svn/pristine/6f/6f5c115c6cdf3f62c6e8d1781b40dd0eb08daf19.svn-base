#ifndef MAPKIT_HPP
#define MAPKIT_HPP
#include <cstdint>
#include "map.hpp"

namespace ice
{

namespace game
{

class MapKit
{
public:
    class WallCount
    {
    public:
        explicit WallCount(uint32_t count = 0)
            : count_(count)
        {}

        operator uint32_t() const { return count_; }
        WallCount& operator = (uint32_t rhs)
        {
            count_ = rhs;
            return *this;
        }

    private:
        uint32_t count_;
    };

public:
    struct Description
    {
        Description()
            : dimensions(), wallCount()
        {}

        Map::Dimensions dimensions;
        WallCount wallCount;
    };

public:
    explicit MapKit(Description description = Description{})
        : description_(description)
    {}

    Description GetDescription() const { return description_; }
    void SetDescription(Description description) { description_ = description; }

private:
    Description description_;
};

} // namespace game

} // namespace ice

#endif // MAPKIT_HPP
