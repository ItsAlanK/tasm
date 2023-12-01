#include "player.h"
#include <thread>

Player::Player(int x, int y, int width, int height, Color color)
    :Object(x, y, color),
    width(width),
    height(height),
    jumpHeight(200),
    jumpRate(0),
    gravity(500),
    isJumping(false),
    isCrouching(false),
    collision(false),
    jump(LoadSound("src/resources/sounds/jump.wav")),
    crouch(LoadSound("src/resources/sounds/crouch.wav"))
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
        hitbox.y = posY;
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
        PlaySound(jump);
    }

    // if character is jumping change y pos
    // jump rate lowers gradually after initial liftoff until gravity overtakes
    if (isJumping && posY >= jumpHeight) {
        jumpRate -= 100;
        posY -= jumpRate * dt;
        hitbox.y = posY;
    }
}

/**
 * Handle crouching in key hold and release
 * Takes init Y, width and height for player to set new ones relative
 * to initial state and not continually adding/subtracting with each game loop
 * Key released used instead of else statement to not overwrite Y position contantly which breaks jump
*/
void Player::Crouch(float initX, float initY, float initWidth, float initHeight) {
    // Listen for key to set crouch sizes and pos
    if(IsKeyPressed(KEY_LEFT_SHIFT) || IsKeyPressed(KEY_S)){
        PlaySound(crouch);
    }

    if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_S)) {
        isCrouching = true;
        width = initWidth * 2;
        posX = initX - initWidth;
        posY = initY + initWidth;
        height = initHeight / 2;
        hitbox.x = posX;
        hitbox.y = posY;
        hitbox.width = width;
        hitbox.height = height;
    }
    
    if (IsKeyReleased(KEY_LEFT_SHIFT) || IsKeyDown(KEY_S)) {
        isCrouching = false;
        width = initWidth;
        height = initHeight;
        posX = initX;
        posY = initY;
        hitbox.x = posX;
        hitbox.y = posY;
        hitbox.width = width;
        hitbox.height = height;
    }

}