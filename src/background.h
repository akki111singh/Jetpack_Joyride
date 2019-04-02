#include "main.h"

#ifndef BACKGOUND_H
#define BACKGROUND_H


class Background {
public:
    Background() {}
    Background(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void move_background_left();


private:
    VAO *object;
    VAO * object2;
    VAO *object3;
    VAO * object4;
    VAO * object5;
};

#endif // BACKGROUND_H
