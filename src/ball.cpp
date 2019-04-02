#include "ball.h"
#include "main.h"
#include<bits/stdc++.h>
using namespace std;
Ball::Ball(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->yvel = 0;
    this->color=color;
    this->shield=false;
    this->gravity = 0.004;
    this->friction = 0.01;

    this->yvel1=0.2;
    this->angle=-180;
    this->gravity1=0.009;
    this->friction1 = 0.01;

    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices

    static const GLfloat vertex_buffer_data[] = {
         0.0f,0.0f,0.0f,
         0.0f,-0.3f,0.0f,
         0.2f,-0.3f,0.0f,

         0.0f,0.0f,0.0f,
         0.2f,-0.3f,0.0f,
         0.2f,0.0f,0.0f,

         0.08f,-0.3f,0.0f,
         0.08f,-0.4f,0.0f,
         0.13f,-0.4f,0.0f,

         0.08f,-0.3f,0.0f,
         0.13f,-0.4f,0.0f,
         0.13f,-0.3f,0.0f,

         0.0f,-0.4f,0.0f,
         0.0f,-0.7f,0.0f,
         0.2f,-0.7f,0.0f,

         0.0f,-0.4f,0.0f,
         0.2f,-0.7f,0.0f,
         0.2f,-0.4f,0.0f,

    };
    static const GLfloat vertex_buffer_data2[] = {
         0.0f,-0.7f,0.0f,
         0.0f,-0.9f,0.0f,
         0.2f,-0.7f,0.0f,

         0.2f,-0.7f,0.0f,
         0.2f,-0.9f,0.0f,
         0.0f,-0.7f,0.0f,

         0.1f,-0.06f,0.0f,
         0.2f,-0.15f,0.0f,
         0.2f,-0.06f,0.0f


    };
    static const GLfloat vertex_buffer_data3[]={

          0.0f,-0.4f,0.0f,
          0.0f,-0.7f,0.0f,
         -0.1f,-0.7f,0.0f,

         0.0f,-0.4f,0.0f,
         -0.1f,-0.7f,0.0f,
         -0.1f,-0.4f,0.0f,


    };
    static const GLfloat vertex_buffer_data4[] = {
        0.0f,0.0f,0.0f,
         0.0f,0.1f,0.0f,
         0.3f,0.1f,0.0f,

         0.0f,0.0f,0.0f,
         0.3f,0.1f,0.0f,
         0.3f,0.0f,0.0f,

          0.0f,0.0f,0.0f,
         0.3f,0.15f,0.0f,
         0.3f,0.0f,0.0f
    };

    static const GLfloat vertex_buffer_data5[]={
          -0.2f,-0.9f,0.0f,
          0.0f,-0.75f,0.0f,
         -0.1f,-0.75f,0.0f,

    };

        static const GLfloat vertex_buffer_data6[]={
              0.0f,0.2f,0.0f,
              0.4f,0.2f,0.0f,
              0.2f,0.3f,0.0f,

        };
    this->object = create3DObject(GL_TRIANGLES, 6*3, vertex_buffer_data,COLOR_player, GL_FILL);
    this->object2= create3DObject(GL_TRIANGLES, 3*3, vertex_buffer_data2, COLOR_BLUE, GL_FILL);
    this->object3= create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data3, COLOR_RED, GL_FILL);
    this->object4= create3DObject(GL_TRIANGLES, 3*3, vertex_buffer_data4, COLOR_BLACK, GL_FILL);
    this->object5= create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data5, COLOR_YELLOW, GL_FILL);
    this->object6= create3DObject(GL_TRIANGLES, 1*3, vertex_buffer_data6, COLOR_shield, GL_FILL);

}

void Ball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(0.1f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object2);
    draw3DObject(this->object3);
    draw3DObject(this->object4);
    if(jumping ==  true )
    draw3DObject(this->object5);
    if(this->shield == true)
    draw3DObject(this->object6);
}

void Ball::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Ball::move_left() {

    if(this->position.x > -3.44)
    this->position.x-=.05;
}

void Ball::move_right() {
    this->position.x+=.05;
}
void Ball::jump() {
    if(jumping == true){
        this->position.x =  this->position.x;
        this->position.y =  this->position.y + .10;
        if(this->position.y >=2.89) this->position.y=2.89;
        this->yvel = 0;
    }
    else{
        if(this->position.y >=-2.38){
        this->yvel += (0.001 *this->friction) + this->gravity;
        this->position.y -= this->yvel;
        }

}
}
bool Ball::line_line_collision(float x1,float y1 ,float x2, float y2 , float x3,float y3 ,float x4, float y4){
  float uA = ((x4-x3)*(y1-y3) - (y4-y3)*(x1-x3)) / ((y4-y3)*(x2-x1) - (x4-x3)*(y2-y1));
  float uB = ((x2-x1)*(y1-y3) - (y2-y1)*(x1-x3)) / ((y4-y3)*(x2-x1) - (x4-x3)*(y2-y1));
  if (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1) {
    return true;
}
return false;
}


bool Ball::rectangle_line_collision(float x1, float y1, float x2, float y2, float rx, float ry, float rw, float rh){
  bool left = this->line_line_collision(x1,y1,x2,y2, rx,ry,rx, ry+rh);
  bool right = this->line_line_collision(x1,y1,x2,y2, rx+rw,ry, rx+rw,ry+rh);
  bool top = this->line_line_collision(x1,y1,x2,y2, rx,ry, rx+rw,ry);
  bool bottom =this->line_line_collision(x1,y1,x2,y2, rx,ry+rh, rx+rw,ry+rh);
  if (left || right || top || bottom) {
    return true;
  }
  return false;
}

void Ball::tick() {
    //this->rotation += speed;
    //this->position.x -= speed;
    //this->position.y -= speed;
}
