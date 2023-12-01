#ifndef SETUP_H
#define SETUP_H

#include "raylib.h"


// Set window size
const int windowWidth{960};
const int windowHeight{960};

// Game Params
int obstacleCount{10}; // No.  of obstacles in game
bool alive{true};

// Set Player params (could include consts in Player class later)
const int playerWidth{80};
const int playerHeight{160};
const int playerPosY{(windowHeight/4)*3 - playerHeight/2};
int playerPosX{windowWidth/4 - playerWidth/2};

// Set Obstacle params
const int obstacleWidth{80};
const int obstacleHeight(40);
int highObsY{playerPosY}; // Flying obstacle Y position
int lowObsY{(playerPosY + playerHeight) - obstacleHeight}; // Grounded obstacle Y position

#endif