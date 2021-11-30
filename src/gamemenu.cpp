#include <gamemenu.h>
// #include <SDL_image.h>

Menu::Menu(){
    this->menu_index = 0;
    this->menu_len= MENU_MAX_INDEX;
    // this->texture = IMG_Load("../img/menu.png");
}

Menu::Menu(int menu_len){
    this->menu_index = 0;
    this->menu_len = menu_len;
    // this->texture = IMG_Load("../img/menu.png");  
}

Menu::~Menu(){

}

void Menu::set_index(int i){
    this->menu_index = i;
    if(this->menu_index < 0) this->menu_index = 0;
    else if(this->menu_index > this->menu_len) this->menu_index = this->menu_len;
}

void Menu::up_index(){
    this->set_index(this->menu_index-1);
}

void Menu::down_index(){
    this->set_index(this->menu_index+1);
}


// void Menu::draw(SDL_Renderer *renderer, int x, int y){
//     if(this->texture != NULL){
//         SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, this->texture);
//         SDL_Rect dstrect = { x, y, 256, 512 };
//         SDL_RenderCopy(renderer, texture, NULL, &dstrect);
//         SDL_DestroyTexture(texture);
//     }
// }