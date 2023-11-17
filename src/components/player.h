#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include "base_object.h"

// Player class building off base object 'Object'
class Player: public Object {
    private: 
        int width;
        int height;
        
    public:
        Player(int x, int y, int width, int height, Color color);

        void Draw();
};

#endif