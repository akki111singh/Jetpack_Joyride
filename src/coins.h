#include "main.h"
#include<vector>

#ifndef BACKGOUND_H
#define BACKGROUND_H

class Coins {
public:
    Coins() {}
    color_t color ;
    color_t color2 ;
    int n;
    Coins(float x, float y,float r,color_t color,color_t color2,int n);
    glm::vec3 position;
    float rotation;
    float r;
    void draw(glm::mat4 VP);
private:
    VAO *object;
    VAO *object2;
};

#endif // BACKGROUND_H
