#include <string.h>
#include <iostream>
#include <tile.h>
#include <string>
#include <sstream>
#include <cstring>
#include <SDL_image.h>

Tile::Tile(){
    this->icon = '.';
    this->num_alt_textures = 0;
    strcpy(this->texture_path,"../img/empty.png");
    strcpy(this->name, "air");
    this->texture = IMG_Load(texture_path);
    
}

Tile::Tile(char icon, const char* texture_path){
    this->icon = icon;
    this->num_alt_textures = 0;
    char new_path[100];
    strcpy(this->name, texture_path);
    strcpy(new_path, "../img/");
    strcat(new_path, texture_path);
    strcat(new_path, ".png");
    strcpy(this->texture_path,new_path);
    
    this->texture = IMG_Load(new_path);
}

Tile::Tile(char icon, const char* name, const char* texture_path){
    this->icon = icon;
    this->num_alt_textures = 0;
    char new_path[100];
    strcpy(this->name, name);
    strcpy(new_path, "../img/");
    strcat(new_path, texture_path);
    strcat(new_path, ".png");
    strcpy(this->texture_path,new_path);
    std::cout<<"name="<<this->name<<" texture="<<this->texture_path<<"\n";
    
    this->texture = IMG_Load(new_path);   
}

Tile::Tile(char icon, const char* name, const char* texture_path, enum Tile_Type type){
    this->icon = icon;
    this->num_alt_textures = 0;
    char new_path[100];
    strcpy(this->name, name);
    strcpy(new_path, "../img/");
    strcat(new_path, texture_path);
    strcat(new_path, ".png");
    strcpy(this->texture_path,new_path);
    std::cout<<"name="<<this->name<<" texture="<<this->texture_path<<"\n";
    
    this->type = type;
    this->texture = IMG_Load(new_path);    
}

Tile::Tile(char icon, const char* texture_path, int num_alt_textures){
    if(!ENABLE_ALT_TEXTURES){
        this->icon = icon;
        this->num_alt_textures = 0;
        char new_path[100];
        strcpy(this->name, texture_path);
        strcpy(new_path, "../img/");
        strcat(new_path, texture_path);
        strcat(new_path, ".png");
        strcpy(this->texture_path,new_path);
        
        this->texture = IMG_Load(new_path);
    }
    else{
        this->icon = icon;
        char new_path[100];
        strcpy(this->name, texture_path);
        strcpy(new_path, "../img/");
        strcat(new_path, texture_path);
        strcpy(this->texture_path,new_path);
        this->num_alt_textures = num_alt_textures;
        
        for(int i = 0; i<num_alt_textures; i++){
            std::stringstream strs;
            strs << i;
            std::string temp_str = strs.str();
            const char* index_str = (char*) temp_str.c_str();

            char new_path_alt[100];
            strcpy(new_path_alt, new_path);
            strcat(new_path_alt, index_str);
            strcat(new_path_alt,".png");
            std::cout << "Found=" << new_path_alt << "\n";
            this->textures.push_back(IMG_Load(new_path_alt));
        } 
    }  
}

Tile::~Tile(){
    // SDL_DestroyTexture(this->texture);
    // SDL_FreeSurface(this->texture);
    this->texture = NULL;
    // delete this->texture;
    // delete this->name;
    // delete this->texture_path;
}

void Tile::copy(Tile t){
    this->texture = t.texture;
    strcpy(this->texture_path,t.texture_path);
}