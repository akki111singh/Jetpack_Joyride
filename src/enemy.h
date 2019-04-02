#include "main.h"
#include<vector>

#ifndef BACKGOUND_H
#define BACKGROUND_H

class Enemy {
public:
    Enemy() {}
    color_t color ;
    Enemy(float x, float y,float x1, float y1,color_t color);
    bool lineCircle(float x1, float y1, float x2, float y2, float x, float y);\
    float dist(float x1,float y1,float x2,float y2);
    glm::vec3 position;
    float x1;
    float y1;
    float rotation;
    void draw(glm::mat4 VP);
private:
    VAO *object;
    VAO *object2;
    VAO *object3;

};

#endif // BACKGROUND_H
