#include "player.h"
#include <thread>
#include <chrono>

Player::Player(int x, int y, int width, int height, Color color)
    :Object(x, y, color),
    width(width),
    height(height),
    jumpHeight(200),
    jumpRate(0),
    gravity(500),
    isJumping(false),
    isCrouching(false)
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
        jumpRate = 0;
        isJumping = false;
    }
}

// Handle player jumps on key press
void Player::Jump(float dt) {
    // Listen for key to set jumpRate and isJumping
    if ((IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_W)) && !isJumping) {
        jumpRate = 2000;
        isJumping = true;
    }

    // if character is jumping change y pos
    // jump rate lowers gradually after initial liftoff until gravity overtakes
    if (isJumping && posY >= jumpHeight) {
        jumpRate -= 100;
        posY -= jumpRate * dt;
    }
}

// Handle player crouch on keypress
void Player::Crouch(float dt) {
    using namespace std::this_thread;
    using namespace std::chrono_literals;
    // Listen for key to set jumpRate and isJumping
    if ((IsKeyPressed(KEY_LEFT_SHIFT) || IsKeyPressed(KEY_S)) && !isCrouching) {
        isCrouching = true;
        Object::color = RED;
    }
}