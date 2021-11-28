#include <tt.h>

#include <iostream>
#include <vector>

Tile Tile_empty = Tile('.',"empty");
Tile Tile_grass = Tile('g',"grass");
Tile Tile_cursor = Tile('>',"cursor");
Tile Tile_sand = Tile('s',"sand");
Tile Tile_stone = Tile('S',"stone");
Tile Tile_clay = Tile('c',"clay");
Tile Tile_water = Tile('w',"water");

Tile Tile_tree = Tile('t',"tree", 3);

std::vector<Tile> Tiles;

Tile Tiles_get_Tile(const char* name){
    for(Tile t : Tiles){
        if(strcmp(t.name,name)==0) return t;
    }
    return Tile_empty;
}

Tile Tiles_get_Tile(char icon){
    for(Tile t : Tiles){
        if(t.icon == icon) return t;
    }
    return Tile_empty;
}

void load_Tiles(){
    Tiles.push_back(Tile_empty);
    Tiles.push_back(Tile_grass);
    Tiles.push_back(Tile_cursor);
    Tiles.push_back(Tile_sand);
    Tiles.push_back(Tile_stone);
    Tiles.push_back(Tile_clay);
    Tiles.push_back(Tile_water);
    Tiles.push_back(Tile_tree);
}

bool Tile_is(Tile t, const char* name){
    return t.icon == Tiles_get_Tile(name).icon;
}

bool Tile_is_Water(Tile t){
    return Tile_is(t, "water");
}

bool Tile_is_Grass(Tile t){
    return Tile_is(t, "grass");
}

bool Tile_is_Vegetation(Tile t){
    return Tile_is(t,"grass") || Tile_is(t,"tree");
}