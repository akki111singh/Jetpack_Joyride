#include "main.h"
#include<vector>

#ifndef Viserion_H
#define Viserion_H

class Viserion {
public:
    Viserion() {}
    color_t color ;
    Viserion(float x, float y,color_t color);
    bool lineCircle(float x1, float y1, float x2, float y2, float x, float y);\
    float dist(float x1,float y1,float x2,float y2);
    glm::vec3 position;
    float x1;
    int flag=0;
    void moveup();
    float yvel=0;
    void attack();
    int flag1=0;
    float gravity=0.009;
    float y1;
    float rotation;
    void draw(glm::mat4 VP);
private:
    VAO *object;
    VAO *object2;
    VAO *object3;
    VAO *object4;

};

#endif 
