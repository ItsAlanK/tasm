#include "obstacle.h"
#include <thread>

Obstacle::Obstacle(int x, int y, int width, int height, Color color)
    :Object(x, y, color),
    width(width),
    height(height),
    obstacleCount(5),
    baseSpeed(10)
    {}

// Draw object to screen
void Obstacle::Draw(){
    for (int i = 0; i < obstacleCount; i++) {
        int startPosX = posX + (500 * i);
        DrawRectangle(startPosX, posY, width, height, color);
    }
}

void Obstacle::Update() {
    posX -= baseSpeed;
}
