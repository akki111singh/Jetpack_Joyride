#include "main.h"
#include<vector>

#ifndef Ring_H
#define Ring_H

class Rings {
public:
    Rings() {}
    color_t color ;
    color_t color2 ;
    int n;
    Rings(float x, float y,float r,color_t color,color_t color2,int n);
    glm::vec3 position;
    float rotation;
    float r;
    void draw(glm::mat4 VP);
private:
    VAO *object;
    VAO *object2;
};

#endif // BACKGROUND_H
