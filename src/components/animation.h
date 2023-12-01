#ifndef ANIM_H
#define ANIM_H

#include "raylib.h"
#include "base_object.h"

struct Anim {
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
    bool isRunning;
};

#endif