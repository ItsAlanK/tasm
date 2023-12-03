#ifndef POWERUP_H
#define POWERUP_H
#include "raylib.h"
#include "obstacle.h"

// Base object class that Player and other collision objects will be built from
class Power: public Obstacle {
    public: 

        Power();
        bool Activate(bool invincibility);
};

#endif