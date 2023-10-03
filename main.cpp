#include "raylib.h"
int main(){
 const int windowWidth{500};
 const int windowHeight{500};
InitWindow(windowWidth,windowHeight,"My Window");

SetTargetFPS(60);  
	while(!WindowShouldClose()){
	
BeginDrawing();
ClearBackground(WHITE); 
EndDrawing();
}
CloseWindow();
}