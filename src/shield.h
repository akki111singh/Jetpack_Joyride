#include "main.h"
#include<vector>

#ifndef Shield_H
#define Shield_H

class Shield {
public:
    Shield() {}
    color_t color ;
    color_t color2 ;
    int n;
    Shield(float x, float y,color_t color);
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
