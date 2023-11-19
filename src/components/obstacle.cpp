#include "obstacle.h"
#include <thread>

Obstacle::Obstacle(int x, int y, int width, int height, Color color)
    :Object(x, y, color),
    width(width),
    height(height),
    baseSpeed(200)
    {}

// Draw object to screen
void Obstacle::Draw(){
    DrawRectangle(posX, posY, width, height, color);
    posX -= baseSpeed * GetFrameTime();
}
