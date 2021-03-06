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
name = "THROUGH THE GARDEN",
level = 3,
kit = MapKit({size = 25, walls = 625 })
})

map:add_walls(Wall(0, 0), Right(24))
map:add_walls(Wall(1, 0), Down(23))
map:add_walls(Wall(1, 24), Down(23))
map:add_walls(Wall(24, 1), Right(23))
map:add_walls(Wall(1,6), Up(0))
map:add_walls(Wall(1,7), Up(0))
map:add_walls(Wall(1,8), Up(0))
map:add_walls(Wall(1,9), Up(0))
map:add_walls(Wall(1,10), Up(0))
map:add_walls(Wall(1,11), Up(0))
map:add_walls(Wall(2,12), Up(0))
map:add_walls(Wall(2,17), Up(0))
map:add_walls(Wall(2,18), Up(0))
map:add_walls(Wall(2,19), Up(0))
map:add_walls(Wall(2,20), Up(0))
map:add_walls(Wall(2,21), Up(0))
map:add_walls(Wall(2,22), Up(0))
map:add_walls(Wall(3,2), Up(0))
map:add_walls(Wall(3,3), Up(0))
map:add_walls(Wall(3,4), Up(0))
map:add_walls(Wall(3,5), Up(0))
map:add_walls(Wall(3,22), Up(0))
map:add_walls(Wall(4,8), Up(0))
map:add_walls(Wall(4,10), Up(0))
map:set_player(Player(4,12))
map:add_walls(Wall(4,14), Up(0))
map:add_walls(Wall(4,17), Up(0))
map:add_walls(Wall(4,18), Up(0))
map:add_walls(Wall(4,19), Up(0))
map:add_walls(Wall(4,22), Up(0))
map:add_walls(Wall(5,2), Up(0))
map:add_walls(Wall(5,3), Up(0))
map:add_walls(Wall(5,4), Up(0))
map:add_walls(Wall(5,5), Up(0))
map:add_walls(Wall(5,8), Up(0))
map:add_walls(Wall(5,10), Up(0))
map:add_walls(Wall(5,20), Up(0))
map:add_walls(Wall(5,22), Up(0))
map:add_walls(Wall(6,8), Up(0))
map:add_walls(Wall(6,10), Up(0))
map:add_walls(Wall(6,12), Up(0))
map:add_walls(Wall(6,20), Up(0))
map:add_walls(Wall(6,22), Up(0))
map:add_walls(Wall(7,8), Up(0))
map:add_walls(Wall(7,10), Up(0))
map:add_walls(Wall(7,20), Up(0))
map:add_walls(Wall(7,22), Up(0))
map:add_walls(Wall(8,1), Up(0))
map:add_walls(Wall(8,6), Up(0))
map:add_walls(Wall(8,20), Up(0))
map:add_walls(Wall(8,22), Up(0))
map:add_walls(Wall(9,7), Up(0))
map:add_walls(Wall(9,14), Up(0))
map:add_walls(Wall(9,15), Up(0))
map:add_walls(Wall(9,16), Up(0))
map:add_walls(Wall(9,17), Up(0))
map:add_walls(Wall(9,18), Up(0))
map:add_walls(Wall(9,19), Up(0))
map:add_walls(Wall(9,20), Up(0))
map:add_walls(Wall(10,5), Up(0))
map:add_walls(Wall(10,8), Up(0))
map:add_walls(Wall(10,12), Up(0))
map:add_walls(Wall(11,6), Up(0))
map:add_walls(Wall(11,9), Up(0))
map:add_walls(Wall(11,12), Up(0))
map:add_walls(Wall(11,15), Up(0))
map:add_walls(Wall(11,16), Up(0))
map:add_walls(Wall(11,17), Up(0))
map:add_walls(Wall(11,18), Up(0))
map:add_walls(Wall(12,7), Up(0))
map:add_walls(Wall(12,12), Up(0))
map:add_walls(Wall(12,20), Up(0))
map:add_walls(Wall(12,23), Up(0))
map:add_walls(Wall(13,8), Up(0))
map:add_walls(Wall(13,12), Up(0))
map:add_walls(Wall(13,16), Up(0))
map:add_walls(Wall(14,4), Up(0))
map:add_walls(Wall(14,12), Up(0))
map:add_walls(Wall(14,16), Up(0))
map:add_walls(Wall(14,20), Up(0))
map:add_walls(Wall(14,22), Up(0))
map:add_walls(Wall(15,5), Up(0))
map:add_walls(Wall(15,12), Up(0))
map:add_walls(Wall(15,19), Up(0))
map:add_walls(Wall(15,23), Up(0))
map:add_walls(Wall(16,6), Up(0))
map:add_walls(Wall(16,12), Up(0))
map:add_walls(Wall(16,18), Up(0))
map:add_walls(Wall(17,7), Up(0))
map:add_walls(Wall(17,8), Up(0))
map:add_walls(Wall(17,9), Up(0))
map:add_walls(Wall(17,10), Up(0))
map:add_walls(Wall(17,11), Up(0))
map:add_walls(Wall(17,12), Up(0))
map:add_walls(Wall(17,13), Up(0))
map:add_walls(Wall(17,14), Up(0))
map:add_walls(Wall(17,15), Up(0))
map:add_walls(Wall(17,16), Up(0))
map:add_walls(Wall(17,17), Up(0))
map:add_walls(Wall(17,18), Up(0))
map:add_walls(Wall(18,3), Up(0))
map:add_walls(Wall(18,4), Up(0))
map:add_walls(Wall(18,5), Up(0))
map:add_walls(Wall(18,18), Up(0))
map:add_walls(Wall(18,19), Up(0))
map:add_walls(Wall(18,20), Up(0))
map:add_walls(Wall(18,21), Up(0))
map:add_walls(Wall(19,3), Up(0))
map:add_walls(Wall(19,7), Up(0))
map:add_walls(Wall(19,8), Up(0))
map:add_walls(Wall(19,9), Up(0))
map:add_walls(Wall(19,10), Up(0))
map:add_walls(Wall(19,12), Up(0))
map:add_walls(Wall(19,13), Up(0))
map:add_walls(Wall(19,14), Up(0))
map:add_walls(Wall(19,15), Up(0))
map:add_walls(Wall(19,16), Up(0))
map:add_walls(Wall(19,17), Up(0))
map:add_walls(Wall(19,21), Up(0))
map:add_walls(Wall(20,2), Up(0))
map:add_walls(Wall(20,3), Up(0))
map:add_walls(Wall(20,7), Up(0))
map:add_walls(Wall(20,21), Up(0))
map:add_walls(Wall(20,22), Up(0))
map:add_walls(Wall(21,7), Up(0))
map:add_walls(Wall(21,8), Up(0))
map:add_walls(Wall(21,9), Up(0))
map:add_walls(Wall(21,10), Up(0))
map:add_walls(Wall(21,11), Up(0))
map:add_walls(Wall(21,12), Up(0))
map:add_walls(Wall(21,13), Up(0))
map:add_walls(Wall(21,14), Up(0))
map:add_walls(Wall(21,16), Up(0))
map:add_walls(Wall(21,20), Up(0))
map:add_walls(Wall(22,6), Up(0))
map:set_goal(Goal(22,11))
map:add_walls(Wall(22,15), Up(0))
map:add_walls(Wall(22,17), Up(0))
map:add_walls(Wall(22,19), Up(0))
map:add_walls(Wall(23,1), Up(0))
map:add_walls(Wall(23,2), Up(0))
map:add_walls(Wall(23,5), Up(0))
map:add_walls(Wall(23,6), Up(0))

IceRunner.register_map(map);
