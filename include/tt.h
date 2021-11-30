#pragma once

#include <tile.h>

#define TILE_AIR_ICON '.'

Tile Tiles_get_Tile(char icon);
Tile Tiles_get_Tile(const char* name);

bool Tile_Type_is(Tile t, enum Tile_Type type);
bool Tile_is(Tile t, const char* name);
bool Tile_is_Water(Tile t);
bool Tile_is_Grass(Tile t);
bool Tile_is_Vegetation(Tile t);

void load_Tiles();