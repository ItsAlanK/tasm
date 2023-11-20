#include <iostream>
#include "raylib.h"
#include "components/base_object.h"
#include "components/player.h"
#include "components/obstacle.h"


int main(){
    // Set window size
    const int windowWidth{960};
    const int windowHeight{960};
    
    InitWindow(windowWidth,windowHeight,"TASM");

    // Set Player params (could include consts in Player class later)
    const int playerWidth{80};
    const int playerHeight{160};
    const int playerPosY{(windowHeight/4)*3 - playerHeight/2};
    int playerPosX{windowWidth/4 - playerWidth/2};

    Player myPlayer(playerPosX, playerPosY, playerWidth, playerHeight, BLUE);

    // Init Obstacle
    Obstacle myObstacle(windowWidth, 600, 80, 40, RED);

    // Set FPS
    SetTargetFPS(60);

    // Main game loop
	while(!WindowShouldClose()){

        // Quick close button
        if(IsKeyPressed(KEY_ESCAPE)) {
            CloseWindow();
        }

        const float deltaTime{GetFrameTime()};

        // Impose gravity on player
        myPlayer.Apply_Gravity(deltaTime, playerPosY);

        // listen for inputs
        myPlayer.Jump(deltaTime);
        myPlayer.Crouch(playerPosX, playerPosY, playerWidth, playerHeight);

        BeginDrawing();
        ClearBackground(LIGHTGRAY);
        myPlayer.Draw();
        myObstacle.Draw();
        myObstacle.Update();
        EndDrawing();
    }

    CloseWindow();
}