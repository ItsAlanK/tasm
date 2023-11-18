#include "player.h"

Player::Player(int x, int y, int width, int height, Color color)
    :Object(x, y, color),
    width(width),
    height(height),
    jumpHeight(200),
    jumpRate(0),
    gravity(500),
    isJumping(false)
    {}

// Draw object to screen
void Player::Draw(){
    DrawRectangle(posX, posY, width, height, color);
}

/**
 * Pull player back to ground level whenever jumping
 * 
 * Uses delta time to keep speed consistent
 * Take intitial Player Y position since it is derived from window size in main
*/
void Player::Apply_Gravity(float dt, int initY) {
    if (isJumping && posY < initY) {
        posY += gravity * dt;
    } else {
        isJumping = false;
        jumpRate = 0;
    }
}

// Handle player jumps on key press
void Player::Jump(float dt) {
    // Listen for key to set jumpRate and isJumping
    if (IsKeyPressed(KEY_SPACE) && !isJumping) {
        isJumping = true;
        jumpRate = 2000;
    }

    // if character is jumping change y pos
    // jump rate lowers gradually after initial liftoff until gravity overtakes
    if (isJumping && posY >= jumpHeight) {
        jumpRate -= 100;
        posY -= jumpRate * dt;
    }
}