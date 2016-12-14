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
name = "BEEZLEDUNG",
level = 5,
kit = MapKit({size = 25, walls = 625 })
})

map:add_walls(Wall(0, 0), Right(24))
map:add_walls(Wall(1, 0), Down(23))
map:add_walls(Wall(1, 24), Down(23))
map:add_walls(Wall(24, 1), Right(23))
map:add_walls(Wall(1,1), Up(0))
map:add_walls(Wall(1,9), Up(0))
map:add_walls(Wall(1,16), Up(0))
map:add_walls(Wall(1,21), Up(0))
map:add_walls(Wall(1,22), Up(0))
map:add_walls(Wall(2,1), Up(0))
map:add_walls(Wall(2,4), Up(0))
map:add_walls(Wall(2,7), Up(0))
map:add_walls(Wall(2,9), Up(0))
map:add_walls(Wall(2,14), Up(0))
map:add_walls(Wall(2,15), Up(0))
map:add_walls(Wall(2,16), Up(0))
map:set_goal(Goal(3,5))
map:add_walls(Wall(3,6), Up(0))
map:add_walls(Wall(3,9), Up(0))
map:add_walls(Wall(3,10), Up(0))
map:add_walls(Wall(3,12), Up(0))
map:add_walls(Wall(3,16), Up(0))
map:add_walls(Wall(4,3), Up(0))
map:add_walls(Wall(4,5), Up(0))
map:add_walls(Wall(4,7), Up(0))
map:add_walls(Wall(4,16), Up(0))
map:add_walls(Wall(5,3), Up(0))
map:add_walls(Wall(5,4), Up(0))
map:add_walls(Wall(5,9), Up(0))
map:add_walls(Wall(5,10), Up(0))
map:add_walls(Wall(5,11), Up(0))
map:add_walls(Wall(5,12), Up(0))
map:add_walls(Wall(5,13), Up(0))
map:add_walls(Wall(6,7), Up(0))
map:add_walls(Wall(6,8), Up(0))
map:add_walls(Wall(7,6), Up(0))
map:add_walls(Wall(7,10), Up(0))
map:add_walls(Wall(7,12), Up(0))
map:add_walls(Wall(7,17), Up(0))
map:add_walls(Wall(7,18), Up(0))
map:add_walls(Wall(8,6), Up(0))
map:add_walls(Wall(8,8), Up(0))
map:add_walls(Wall(8,11), Up(0))
map:add_walls(Wall(8,13), Up(0))
map:add_walls(Wall(8,17), Up(0))
map:add_walls(Wall(9,5), Up(0))
map:set_player(Player(9,6))
map:add_walls(Wall(9,8), Up(0))
map:add_walls(Wall(9,13), Up(0))
map:add_walls(Wall(9,15), Up(0))
map:add_walls(Wall(10,5), Up(0))
map:add_walls(Wall(10,7), Up(0))
map:add_walls(Wall(10,8), Up(0))
map:add_walls(Wall(10,11), Up(0))
map:add_walls(Wall(10,15), Up(0))
map:add_walls(Wall(10,18), Up(0))
map:add_walls(Wall(11,5), Up(0))
map:add_walls(Wall(11,8), Up(0))
map:add_walls(Wall(11,11), Up(0))
map:add_walls(Wall(11,15), Up(0))
map:add_walls(Wall(11,18), Up(0))
map:add_walls(Wall(12,5), Up(0))
map:add_walls(Wall(12,6), Up(0))
map:add_walls(Wall(12,9), Up(0))
map:add_walls(Wall(12,11), Up(0))
map:add_walls(Wall(12,14), Up(0))
map:add_walls(Wall(12,17), Up(0))
map:add_walls(Wall(12,18), Up(0))
map:add_walls(Wall(13,3), Up(0))
map:add_walls(Wall(13,4), Up(0))
map:add_walls(Wall(13,5), Up(0))
map:add_walls(Wall(13,6), Up(0))
map:add_walls(Wall(13,12), Up(0))
map:add_walls(Wall(13,13), Up(0))
map:add_walls(Wall(13,17), Up(0))
map:add_walls(Wall(13,18), Up(0))
map:add_walls(Wall(14,1), Up(0))
map:add_walls(Wall(14,3), Up(0))
map:add_walls(Wall(14,6), Up(0))
map:add_walls(Wall(14,13), Up(0))
map:add_walls(Wall(14,17), Up(0))
map:add_walls(Wall(15,7), Up(0))
map:add_walls(Wall(15,8), Up(0))
map:add_walls(Wall(15,17), Up(0))
map:add_walls(Wall(16,9), Up(0))
map:add_walls(Wall(16,10), Up(0))
map:add_walls(Wall(16,12), Up(0))
map:add_walls(Wall(16,13), Up(0))
map:add_walls(Wall(16,15), Up(0))
map:add_walls(Wall(16,16), Up(0))
map:add_walls(Wall(17,2), Up(0))
map:add_walls(Wall(17,6), Up(0))
map:add_walls(Wall(17,11), Up(0))
map:add_walls(Wall(17,12), Up(0))
map:add_walls(Wall(17,13), Up(0))
map:add_walls(Wall(17,14), Up(0))
map:add_walls(Wall(17,20), Up(0))
map:add_walls(Wall(18,8), Up(0))
map:add_walls(Wall(18,21), Up(0))
map:add_walls(Wall(19,6), Up(0))
map:add_walls(Wall(19,7), Up(0))
map:add_walls(Wall(19,9), Up(0))
map:add_walls(Wall(19,12), Up(0))
map:add_walls(Wall(19,16), Up(0))
map:add_walls(Wall(19,20), Up(0))
map:add_walls(Wall(19,21), Up(0))
map:add_walls(Wall(20,6), Up(0))
map:add_walls(Wall(20,11), Up(0))
map:add_walls(Wall(20,23), Up(0))
map:add_walls(Wall(21,7), Up(0))
map:add_walls(Wall(21,9), Up(0))
map:add_walls(Wall(21,16), Up(0))
map:add_walls(Wall(21,22), Up(0))
map:add_walls(Wall(22,8), Up(0))
map:add_walls(Wall(22,9), Up(0))
map:add_walls(Wall(22,10), Up(0))
map:add_walls(Wall(22,16), Up(0))
map:add_walls(Wall(22,23), Up(0))

IceRunner.register_map(map);