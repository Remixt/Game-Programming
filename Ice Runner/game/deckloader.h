#ifndef DECKLOADER_H
#define DECKLOADER_H
#include <cstdlib>
#include <string>
#include <vector>
#include "deckettings.hpp"
#include "luainterface.h"

namespace ice
{

namespace game
{

class MapKit;

class Deck
{
private:
    using MapContainer = std::vector<Map*>;

    template <typename WrappedIterator_>
    class CustomMapIterator
    {
    public:
        CustomMapIterator(WrappedIterator_ iter)
            : iter_(iter)
        {}

        typename WrappedIterator_::value_type & operator->() { return **iter_; }

    private:
        WrappedIterator_ iter_;
    };

public:
    using MapIterator = typename CustomMapIterator<typename MapContainer::iterator>;
    using CMapIterator = const CustomMapIterator<typename MapContainer::const_iterator>;

public:
    MapIterator begin() { return maps_.begin(); }
    MapIterator end() { return maps_.end(); }

    CMapIterator cbegin() const { return maps_.cbegin(); }
    CMapIterator cend() const { return maps_.cend(); }

    Map::Difficulty GetMaxDifficulty() const { return Map::Difficulty((Map::Difficulty::Rep)(maps_.size())); }

    Map& MapAt(Map::Difficulty difficulty) { return *maps_[difficulty-1]; }
    const Map& MapAt(Map::Difficulty difficulty) const { return *maps_[difficulty-1]; }

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
    friend class LuaInterface;
public:
    static DeckLoader& GetInstance()
    {
        static DeckLoader deckLoader;
        return deckLoader;
    }

public:
    bool Init();
    bool Configure();
    bool LoadDecks();
    bool LoadMaps();

    const std::string& GetError() const { return luaInterface_.GetError(); }
    DeckSettings& GetDeckSettings() { return settings_; }
    void ClearAll()
    {
        ClearSettings();
        ClearDecks();
        ClearMaps();
    }

    void ClearSettings()
    {
        settings_.Clear();
    }

    void ClearDecks()
    {
        player1Decks_.clear();
        player2Decks_.clear();
    }

    void ClearMaps()
    {
        maps_.clear();
        mapNameToStorageMap_.clear();
    }

    void SetPlayer1Folder(const std::string& folder)
    {
        player1Folder_ = folder;
    }

    void SetPlayer2Folder(const std::string& folder)
    {
        player2Folder_ = folder;
    }

    //! Called by the LuaInterface. Kind of a hack to keep it public.
    void AddMap(const Map& map) { maps_.push_back(map); }

    template <typename MapHandler_>
    void ForEachMap(MapHandler_ handler)
    {
        for (auto& map : maps_)
            handler(map);
    }

private:
    DeckLoader()
        : settings_(), player1Folder_("res\\scripts\\player1\\"), player2Folder_("res\\scripts\\player2\\")
    {}

    bool ExportInterface(lua_State* L);

    //! Only for internal use.
    void NameMaps()
    {
        for (auto& map : maps_)
            mapNameToStorageMap_.insert({map.GetDescription().name, &map});
    }

    void AddPlayer1Deck(const Deck& deck) { player1Decks_.push_back(deck); }
    void AddPlayer2Deck(const Deck& deck) { player2Decks_.push_back(deck); }


private:
    LuaInterface luaInterface_;
    DeckSettings settings_;
    std::vector<Deck> player1Decks_;
    std::vector<Deck> player2Decks_;
    std::vector<Map> maps_;
    std::unordered_map<std::string, Map*> mapNameToStorageMap_;
    std::string player1Folder_;
    std::string player2Folder_;
};

} // namespace game

} // namespace ice

#endif // DECKLOADER_H
