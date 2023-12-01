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
        int jumpRate;
        const int gravity;
        
    public:
        Rectangle hitbox;
        Sound jump;
        Sound crouch;
        bool isJumping;
        bool isCrouching;
        bool collision;
        Player(int x, int y, int width, int height, Color color);

        void Draw();
        void Apply_Gravity(float dt, int initY);
        void Jump(float dt);
        void Crouch(float initX, float initY, float initWidth, float initHeight);
};

#endif