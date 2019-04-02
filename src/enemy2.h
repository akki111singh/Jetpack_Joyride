#include "main.h"
#include<vector>

#ifndef BACKGOUND_H
#define BACKGROUND_H

class Enemy2 {
public:
    Enemy2() {}
    color_t color ;
    Enemy2(float x, float y,float x1, float y1,color_t color);
    bool lineCircle(float x1, float y1, float x2, float y2, float x, float y);\
    float dist(float x1,float y1,float x2,float y2);
    bool rectRect(float r1x, float r1y, float r1w, float r1h, float r2x, float r2y, float r2w, float r2h);
    glm::vec3 position;
    void moveup();
    void movedown();
    float x1;
    float y1;
    float yvel=0;
    int flag=0;
    int flag1=0;
    float rotation;
    void draw(glm::mat4 VP);
private:
    VAO *object;
    VAO *object2;
    VAO *object3;

};

#endif // BACKGROUND_H
