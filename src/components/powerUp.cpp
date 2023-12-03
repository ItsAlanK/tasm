#include "powerUp.h"
#include <thread>

Power::Power()
    :Obstacle()
    {}

bool Power::Activate(bool invincibility) {
    if (IsKeyPressed(KEY_F)){
        invincibility = true;
    }
    return invincibility;
}

void Power::Key(int posX, int posY) {
    DrawText("F", posX + 50, posY + 50, 50, Color{200, 133, 27, 255});
}