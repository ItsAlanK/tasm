#include "raylib.h"

int main(){
    // Set window size
    const int windowWidth{500};
    const int windowHeight{500};
    
    InitWindow(windowWidth,windowHeight,"My Window");

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