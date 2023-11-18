#include <iostream>
#include "raylib.h"
#include "components/base_object.h"
#include "components/player.h"


int main(){
    // Set window size
    const int windowWidth{750};
    const int windowHeight{750};
    
    InitWindow(windowWidth,windowHeight,"TASM");

    // Set Player params (could include consts in Player class later)
    const int playerWidth{80};
    const int playerHeight{160};
    const int playerPosY{(windowHeight/4)*3 - playerHeight/2};
    int playerPosX{windowWidth/4 - playerWidth/2};

    Player myPlayer(playerPosX, playerPosY, playerWidth, playerHeight, BLUE);

    // Set FPS
    SetTargetFPS(60);

    // Main game loop
	while(!WindowShouldClose()){

        const float deltaTime{GetFrameTime()};

        BeginDrawing();
        ClearBackground(WHITE);
        myPlayer.Draw();
        myPlayer.Apply_Gravity(deltaTime);
        EndDrawing();
    }

    CloseWindow();
}