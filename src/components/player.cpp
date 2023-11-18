#include "player.h"

Player::Player(int x, int y, int width, int height, Color color)
    :Object(x, y, color),
    width(width),
    height(height),
    gravity(500),
    isJumping(false)
    {}

// Draw object to screen
void Player::Draw(){
    DrawRectangle(posX, posY, width, height, color);
}

// Pull player back to ground level whenever jumping
void Player::Apply_Gravity(float dt) {
    if (Player::isJumping){
        Player::posY += Player::gravity * dt;
    }
}