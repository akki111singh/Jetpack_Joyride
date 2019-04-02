#include "main.h"
#include<vector>

#ifndef Lifeup_H
#define Lifeup_H

class Lifeup {
public:
    Lifeup() {}
    color_t color ;
    color_t color2 ;
    int n;
    Lifeup(float x, float y,color_t color);
    void attack();
    glm::vec3 position;
    float rotation;
    float r;
    void draw(glm::mat4 VP);
private:
    VAO *object;
    VAO *object2;
};

#endif // BACKGROUND_H
