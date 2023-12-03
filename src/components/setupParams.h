#ifndef SETUP_H
#define SETUP_H

// SET BASIC GAME VARIABLES AND SETTINGS
// Set window size
const int windowWidth{960};
const int windowHeight{960};
int bgPosX1{0};
int bgPosX2{3835};
int groundPosX1{0};
int groundPosX2{1920};

// Game Params
int obstacleCount{20}; // No.  of obstacles in game
bool menu{true};
bool alive{false};
float volume{0.01};
int level{2};

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