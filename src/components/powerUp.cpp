#include "powerUp.h"
#include <thread>

Power::Power()
    :Obstacle()
    {}

bool Power::Activate(bool invincibility) {
    if (IsKeyPressed(KEY_G)){
        invincibility = true;
    }
    return invincibility;
}