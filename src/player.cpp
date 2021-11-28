#include <player.h>

Player::Player(){
    this->x = 0;
    this->y = 0;
    this->vx = 0;
    this->vy = 0;
    this->vmax = 0;
    this->friction = 0;
}

Player::~Player(){

}

void Player::set_v(int vx, int vy){
    this->vx = vx * this->vmax;
    this->vy = vy * this->vmax;
}

void Player::change_v(int h, int v){
    this->vx += h * this->vmax;
    this->vy += v * this->vmax;
}

void Player::update(int screen_x, int screen_y){
    this->vx *= this->friction;
    this->vy *= this->friction;

    this->x += this->vx;
    this->y += this->vy;

    if(this->x < 0) this->x = 0;
    else if(this->x > screen_x) this->x = screen_x-1-10;

    if(this->y < 0) this->y = 0;
    else if(this->y > screen_y) this->y = screen_y-1-10;
}

void Player::draw(SDL_Renderer* renderer)
{
    SDL_Rect rect;

    rect.x = (int)this->x;
    rect.y = (int)this->y;
    rect.w = 10;
    rect.h = 10;

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
    SDL_RenderDrawRect(renderer, &rect);

    SDL_RenderPresent(renderer);
}