#include <iostream>
#include "raylib.h"
#include "components/base_object.h"
#include "components/player.h"


int main(){
    // Set window size
    const int windowWidth{750};
    const int windowHeight{750};
    
    InitWindow(windowWidth,windowHeight,"TASM");

    // Set Player params
    const int playerWidth{80};
    const int playerHeight{160};
    const int playerPosY{(windowHeight/4)*3 - playerHeight/2};
    int playerPosX{windowWidth/4 - playerWidth/2};

    Player myPlayer(playerPosX, playerPosY, playerWidth, playerHeight, BLUE);

    // Set FPS
    SetTargetFPS(60);

    // Main game loop
	while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(WHITE);
        myPlayer.Draw();
        EndDrawing();
    }

    CloseWindow();
}