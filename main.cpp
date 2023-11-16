#include "raylib.h"

int main(){
    // Set window size
    const int windowWidth{750};
    const int windowHeight{750};
    
    InitWindow(windowWidth,windowHeight,"TASM");

    // Set FPS
    SetTargetFPS(60);

    // Main game loop
	while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(WHITE);
        EndDrawing();
    }

    CloseWindow();
}