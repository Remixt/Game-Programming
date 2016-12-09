local Map = IceRunner.Map
local MapKit = IceRunner.MapKit
local Up = IceRunner.MapTools.UpExtent
local Down = IceRunner.MapTools.DownExtent
local Left = IceRunner.MapTools.LeftExtent
local Right = IceRunner.MapTools.RightExtent
local Wall = IceRunner.Map.Wall
local MapKit = IceRunner.MapTools.MapKit
local Player = Map.Player
local Goal = Map.Goal

local map = Map({
name = "SICK",
level = 1,
kit = MapKit({size = 15, walls = 225})
})

map.add_walls(Wall(0, 0), Right(14))
map.add_walls(Wall(1, 0), Down(13))
map.add_walls(Wall(1, 14), Down(13))
map.add_walls(Wall(14, 1), Right(13))
map:add_walls(Wall(2,1), Up(0))
map:set_player(Player(2,2))
map:set_goal(Goal(1,2))
map:add_walls(Wall(3,2), Up(0))
map:add_walls(Wall(3,3), Up(0))
map:add_walls(Wall(4,2), Up(0))
map:add_walls(Wall(6,10), Up(0))
map:add_walls(Wall(6,11), Up(0))
map:add_walls(Wall(6,12), Up(0))
map:add_walls(Wall(6,13), Up(0))
map:add_walls(Wall(7,8), Up(0))
map:add_walls(Wall(7,10), Up(0))
map:add_walls(Wall(7,13), Up(0))
map:add_walls(Wall(8,9), Up(0))
map:add_walls(Wall(8,13), Up(0))
map:add_walls(Wall(9,8), Up(0))
map:add_walls(Wall(9,9), Up(0))
map:add_walls(Wall(10,9), Up(0))
map:add_walls(Wall(11,8), Up(0))

IceRunner.register_map(map);
