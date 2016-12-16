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
name = "VELOCITY",
level = 5,
kit = MapKit({size = 25, walls = 625 })
})

map:add_walls(Wall(0, 0), Right(24))
map:add_walls(Wall(1, 0), Down(23))
map:add_walls(Wall(1, 24), Down(23))
map:add_walls(Wall(24, 1), Right(23))
map:add_walls(Wall(1,13), Up(0))
map:add_walls(Wall(2,2), Up(0))
map:add_walls(Wall(2,21), Up(0))
map:add_walls(Wall(3,2), Up(0))
map:add_walls(Wall(3,3), Up(0))
map:add_walls(Wall(3,4), Up(0))
map:add_walls(Wall(3,10), Up(0))
map:add_walls(Wall(3,11), Up(0))
map:add_walls(Wall(3,12), Up(0))
map:add_walls(Wall(3,17), Up(0))
map:add_walls(Wall(4,4), Up(0))
map:add_walls(Wall(4,8), Up(0))
map:add_walls(Wall(4,10), Up(0))
map:add_walls(Wall(4,23), Up(0))
map:add_walls(Wall(5,1), Up(0))
map:add_walls(Wall(5,2), Up(0))
map:add_walls(Wall(5,7), Up(0))
map:add_walls(Wall(5,8), Up(0))
map:set_player(Player(5,9))
map:add_walls(Wall(5,10), Up(0))
map:add_walls(Wall(6,7), Up(0))
map:add_walls(Wall(6,10), Up(0))
map:add_walls(Wall(7,7), Up(0))
map:add_walls(Wall(7,8), Up(0))
map:add_walls(Wall(7,10), Up(0))
map:add_walls(Wall(8,8), Up(0))
map:add_walls(Wall(8,10), Up(0))
map:add_walls(Wall(9,8), Up(0))
map:add_walls(Wall(9,10), Up(0))
map:add_walls(Wall(10,3), Up(0))
map:add_walls(Wall(10,6), Up(0))
map:add_walls(Wall(10,7), Up(0))
map:add_walls(Wall(10,8), Up(0))
map:add_walls(Wall(10,10), Up(0))
map:add_walls(Wall(10,11), Up(0))
map:add_walls(Wall(10,12), Up(0))
map:add_walls(Wall(11,2), Up(0))
map:add_walls(Wall(11,4), Up(0))
map:add_walls(Wall(11,12), Up(0))
map:add_walls(Wall(12,6), Up(0))
map:add_walls(Wall(12,7), Up(0))
map:add_walls(Wall(12,8), Up(0))
map:add_walls(Wall(12,9), Up(0))
map:add_walls(Wall(12,11), Up(0))
map:add_walls(Wall(12,12), Up(0))
map:set_goal(Goal(13,10))
map:add_walls(Wall(14,9), Up(0))
map:add_walls(Wall(14,20), Up(0))
map:add_walls(Wall(15,18), Up(0))
map:add_walls(Wall(15,22), Up(0))
map:add_walls(Wall(17,10), Up(0))
map:add_walls(Wall(18,1), Up(0))
map:add_walls(Wall(22,14), Up(0))
map:add_walls(Wall(23,22), Up(0))

IceRunner.register_map(map);
