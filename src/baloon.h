#include "main.h"
#include<vector>

#ifndef Baloon_H
#define Baloon_H

class Baloon {
public:
    Baloon() {}
    color_t color ;
    Baloon(float x, float y,float r,color_t color);
    void Baloon_attack();
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
