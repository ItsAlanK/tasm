#ifndef SETUP_H
#define SETUP_H

// SET BASIC GAME VARIABLES AND SETTINGS
// Set window size
const int windowWidth{960};
const int windowHeight{960};

// Set Player params (could include consts in Player class later)
const int playerWidth{80};
const int playerHeight{160};
const int playerPosY{(windowHeight/4)*3 - playerHeight/2};

// Set Obstacle params
const int obstacleWidth{80};
const int obstacleHeight(40);


#endif