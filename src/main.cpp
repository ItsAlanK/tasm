#include <iostream>
#include "raylib.h"
#include "components/base_object.h"


int main(){
    // Set window size
    const int windowWidth{750};
    const int windowHeight{750};
    
    InitWindow(windowWidth,windowHeight,"TASM");

    Object myObject(100,100,100,100, BLUE);

    // Set FPS
    SetTargetFPS(60);

    // Main game loop
	while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(WHITE);
        myObject.Draw();
        EndDrawing();
    }

    CloseWindow();
}