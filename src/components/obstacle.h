#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "raylib.h"
#include "base_object.h"

// Obstacle class building off base object 'Object'
class Obstacle: public Object {
    private: 
        int width;
        int height;
        int obstacleCount;
        int baseSpeed;
        
    public:
        Rectangle hitbox;
        Obstacle();
        Obstacle(int x, int y, int width, int height, Color color);
        void Draw();
        void Update();
};

#endif