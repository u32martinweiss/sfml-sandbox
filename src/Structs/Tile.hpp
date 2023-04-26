#ifndef TILE_STRUCT_HPP
#define TILE_STRUCT_HPP

enum TileType : unsigned int {
  AIR = 0,
  SAND = 1,
};

struct Tile {
  TileType type = TileType::AIR;
};

#endif // TILE_STRUCT_HPP
