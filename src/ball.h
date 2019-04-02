#include "main.h"

#ifndef BALL_H
#define BALL_H


class Ball {
public:
    Ball() {}
    Ball(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    bool line_line_collision(float x1,float y1 ,float x2, float y2 , float x3,float y3 ,float x4, float y4);
    bool rectangle_line_collision(float x1, float y1, float x2, float y2, float rx, float ry, float rw, float rh);
    void tick();
    void move_semicircular(float x, float y);
    void move_left();
    void move_right();
    void jump();
    double speed;
    double xvel;
    double yvel;
    double yvel1;
    double friction1;
    double gravity1;
    float angle;
    double friction;
    double gravity;
    int flag=0;
    bool shield;
    bool jumping;
    color_t color;
private:
    VAO *object;
    VAO * object2;
    VAO *object3;
    VAO * object4;
    VAO * object5;
    VAO * object6;

};

#endif // BALL_H
