#include "main.h"
#include<vector>

#ifndef BACKGOUND_H
#define BACKGROUND_H

class Magnet {
public:
    Magnet() {}
    color_t color ;
    color_t color2 ;
    int n;
    Magnet(float x, float y,color_t color);
    glm::vec3 position;
    float rotation;
    float r;
    void draw(glm::mat4 VP);
private:
    VAO *object;
    VAO *object2;
};

#endif // BACKGROUND_H
