local Map = IceRunner.Map
local MapKit = IceRunner.MapKit
local Up = IceRunner.MapTools.UpExtent
local Down = IceRunner.MapTools.DownExtent
local Left = IceRunner.MapTools.LeftExtent
local Right = IceRunner.MapTools.RightExtent
local Map = IceRunner.Map
local Wall = IceRunner.Map.Wall
local MapKit = IceRunner.MapTools.MapKit

local map = Map({name = "BREEZE", level = 1, kit = MapKit({size = 15, walls = 100})})
map.add_walls(Wall(0, 0), Right(14))
map.add_walls(Wall(1, 0), Down(13))
map.add_walls(Wall(1, 14), Down(13))
map.add_walls(Wall(14, 1), Right(13))
map.add_walls(Wall(14, 1), Right(13))
map.set_player(Player(0, 0))
map.set_goal(Goal(0, 0))

IceRunner.register_map(map);
