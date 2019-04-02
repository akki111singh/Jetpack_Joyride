#include "main.h"
#include<vector>

#ifndef Fireballs_H
#define Fireballs_H

class Fireballs {
public:
    Fireballs() {}
    color_t color ;
    Fireballs(float x, float y,float r,color_t color);
    void Fireballs_attack();
    glm::vec3 position;
    float rotation;
    float friction;
    int flag=0;
    float yvel;
    float gravity;
    float r;
    void draw(glm::mat4 VP);
private:
    VAO *object;
};

#endif // BACKGROUND_H
