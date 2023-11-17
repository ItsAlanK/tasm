#include "player.h"

Player::Player(int x, int y, int width, int height, Color color)
    :Object(x, y, color),
    width(width),
    height(height){}

// Draw object to screen
void Player::Draw(){
    DrawRectangle(posX, posY, width, height, color);
}