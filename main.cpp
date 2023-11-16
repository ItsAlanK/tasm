#include <iostream>
#include "raylib.h"
#include "src/base_object.h"


// Basic rectangle object class player char and obstacles will build off
// I'm going to move things to their own files once they're tested as working here to be safe
class Object {
    private:
    int posX;
    int posY;
    int width;
    int height;
    Color color;

    public:
    Object(int x, int y, int width, int height, Color color)
    :posX(x), posY(y), width(width), height(height), color(color) {}

    void Draw() const{
        DrawRectangle(posX, posY, width, height, color);
    }
};

int main(){
    // Set window size
    const int windowWidth{750};
    const int windowHeight{750};
    
    InitWindow(windowWidth,windowHeight,"TASM");

    Ball myBall({windowWidth/2, windowHeight/2}, 50, BLUE);

    // Set FPS
    SetTargetFPS(60);

    // Main game loop
	while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(WHITE);
        myBall.Draw();
        EndDrawing();
    }

    CloseWindow();
}