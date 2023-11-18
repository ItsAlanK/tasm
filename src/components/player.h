#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include "base_object.h"

// Player class building off base object 'Object'
class Player: public Object {
    private: 
        int width;
        int height;
        int jumpHeight;
        const int gravity;
        bool isJumping;
        
    public:
        Player(int x, int y, int width, int height, Color color);

        void Draw();
        void Apply_Gravity(float dt);
};

#endif