#include "base_object.h"

Object::Object(int x, int y, int width, int height, Color color):posX(x), posY(y), width(width), height(height), color(color) {}

void Object::Draw(){
    DrawRectangle(posX, posY, width, height, color);
}