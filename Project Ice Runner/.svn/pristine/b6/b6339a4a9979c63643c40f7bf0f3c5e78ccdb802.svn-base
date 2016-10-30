#ifndef DECKLOADER_H
#define DECKLOADER_H
#include <cstdlib>
#include <string>
#include <vector>
#include "deckettings.hpp"

typedef struct lua_State lua_State;

namespace ice
{

namespace game
{

class MapKit;

class Deck
{
private:
    using MapContainer = std::vector<Map>;
    using MapIterator = typename MapContainer::iterator;
    using CMapIterator = typename MapContainer::const_iterator;

public:
    MapIterator begin() { return maps_.begin(); }
    MapIterator end() { return maps_.end(); }

    CMapIterator cbegin() const { return maps_.cbegin(); }
    CMapIterator cend() const { return maps_.cend(); }

    Map::Difficulty GetMaxDifficulty() const { return Map::Difficulty((Map::Difficulty::Rep)(maps_.size())); }

    Map& MapAt(Map::Difficulty difficulty) { return maps_[difficulty-1]; }
    const Map& MapAt(Map::Difficulty difficulty) const { return maps_[difficulty-1]; }

    void SetName(const std::string& name) { name_ = name; }
    std::string GetName() const { return name_; }

    MapIterator FindMapWith(Map::Difficulty difficulty)
    {
        auto index = difficulty-1;
        return index < maps_.size() && index > 0 ? (maps_.begin() + index) : end();
    }

    CMapIterator FindMapWith(Map::Difficulty difficulty) const
    {
        auto index = difficulty-1;
        return index < maps_.size() && index > 0 ? (maps_.cbegin() + index) : cend();
    }

private:
    MapContainer maps_;
    std::string name_;
};

class DeckLoader
{
public:
    static DeckLoader& GetInstance()
    {
        static DeckLoader deckLoader;
        return deckLoader;
    }

public:
    ~DeckLoader();

    bool Init();
    bool Configure();
    bool Load();

    std::string GetError() const { return error_; }
    DeckSettings& GetDeckSettings() { return settings_; }

private:
    DeckLoader()
        : settings_(), error_(), decksFolder_(), pLuaState_(nullptr)
    {}

    bool ExportConfigInterface(lua_State* L);

private:
    DeckSettings settings_;
    std::string error_;
    std::string decksFolder_;
    lua_State* pLuaState_;
};

} // namespace game

} // namespace ice

#endif // DECKLOADER_H
