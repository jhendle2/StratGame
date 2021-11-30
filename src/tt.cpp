#include <tt.h>

#include <iostream>
#include <vector>

std::vector<Tile> Tiles;

Tile Tile_air = Tile(TILE_AIR_ICON,"air","",Tile_Type_Air);

Tile Tiles_get_Tile(const char* name){
    for(Tile t : Tiles){
        if(strcmp(t.name,name)==0) return t;
    }
    return Tile_air;
}

Tile Tiles_get_Tile(char icon){
    for(Tile t : Tiles){
        if(t.icon == icon) return t;
    }
    return Tile_air;
}

void load_Tiles(){
    Tile Tile_grass = Tile('g',"grass","grass",Tile_Type_Ground);
    Tile Tile_cursor = Tile('>',"cursor", "player",Tile_Type_Actor);
    Tile Tile_sand = Tile('s',"sand","sand",Tile_Type_Ground);
    Tile Tile_stone = Tile('S',"stone","stone",Tile_Type_Ground);
    Tile Tile_clay = Tile('c',"clay","clay",Tile_Type_Ground);
    Tile Tile_water = Tile('w',"water","water",Tile_Type_Fluid);
    Tile Tile_deepwater = Tile('W',"deepwater","deepwater",Tile_Type_Fluid);

    Tile Tile_tree = Tile('t',"tree","/vegetation/pine-none04",Tile_Type_Vegetation); //, 3);
    Tile Tile_shrub = Tile('t',"shrub","/vegetation/shrub2-02",Tile_Type_Vegetation);
    Tile Tile_bush = Tile('t',"bush","/vegetation/bush02",Tile_Type_Vegetation);
    Tile Tile_grasses = Tile('t',"grasses","/vegetation/grasses02",Tile_Type_Vegetation);

    Tiles.push_back(Tile_air);

    Tiles.push_back(Tile_cursor);

    Tiles.push_back(Tile_grass);
    Tiles.push_back(Tile_sand);
    Tiles.push_back(Tile_stone);
    Tiles.push_back(Tile_clay);

    Tiles.push_back(Tile_water);
    Tiles.push_back(Tile_deepwater);

    Tiles.push_back(Tile_tree);
    Tiles.push_back(Tile_shrub);
    Tiles.push_back(Tile_bush);
    Tiles.push_back(Tile_grasses);
}

bool Tile_Type_is(Tile t, enum Tile_Type type){
    return t.type == type;
}

bool Tile_is(Tile t, const char* name){
    return t.icon == Tiles_get_Tile(name).icon;
}

bool Tile_is_Water(Tile t){
    return Tile_is(t, "water") || Tile_is(t, "deepwater");
}

bool Tile_is_Grass(Tile t){
    return Tile_is(t, "grass");
}

bool Tile_is_Vegetation(Tile t){
    return Tile_is_Grass(t) || Tile_Type_is(t,Tile_Type_Vegetation);
    // return Tile_is(t,"grass") || Tile_is(t,"tree");
}