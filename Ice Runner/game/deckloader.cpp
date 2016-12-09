#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <utility>
#include <algorithm>
#include <lua.hpp>
#include "core/utility.hpp"
#include "deckloader.h"
#include "map.hpp"

namespace ice
{

namespace game
{

bool DeckLoader::Init()
{
    return luaInterface_.Init() && luaInterface_.Export();
}

bool DeckLoader::Configure()
{
    ClearSettings();
    return luaInterface_.RunFile("res/scripts/config.lua");
}

bool DeckLoader::LoadDecks()
{
    ClearDecks();
    ClearMaps();
    return false;
}

bool DeckLoader::LoadMaps()
{
    ClearMaps();

    bool success = false;
    std::string player1MapsFolder = player1Folder_ + "maps\\";
    core::utility::ForEachFile(player1MapsFolder, [this, &success, &player1MapsFolder](const std::string& fileName) {
        success = luaInterface_.RunFile(player1MapsFolder + fileName);
    });
    if (!success)
        printf("Error during map loading: %s\n", luaInterface_.GetError().c_str());

    std::string player2MapsFolder = player2Folder_ + "maps\\";
    core::utility::ForEachFile(player2MapsFolder, [this, &success, &player2MapsFolder](const std::string& fileName) {
        success = luaInterface_.RunFile(player2MapsFolder + fileName);
    });
    if (!success)
        printf("Error during map loading: %s\n", luaInterface_.GetError().c_str());

    NameMaps();
    return success;
}

} // namespace game

} // namespace ice
