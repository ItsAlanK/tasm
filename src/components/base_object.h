#ifndef OBJECT_H
#define OBJECT_H
#include "raylib.h"

// Base object class that Player and other collision objects will be built from
class Object{
    public: 
        int posX;
        int posY;
        Color color;

        Object(int x, int y, Color color);
};

#endif