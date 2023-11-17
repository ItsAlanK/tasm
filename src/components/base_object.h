#include "raylib.h"

class Object{
    public: 
        int posX;
        int posY;
        int width;
        int height;
        Color color;

        Object(int x, int y, int width, int height, Color color);

        void Draw();
};