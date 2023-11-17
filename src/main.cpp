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
    const int playerWidth{100};
    const int playerHeight{200};
    const int playerPosY{100};
    int playerPosX{100};

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