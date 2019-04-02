#include "ball.h"
#include "main.h"
#include "background.h"
#include<bits/stdc++.h>
using namespace std;

Background::Background(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;

    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a tridelta.
    // A cube has 6 faces with 2 trideltas each, so this makes 6*2=12 trideltas, and 12*3 vertices

    static const GLfloat vertex_buffer_data[] = {

          8.0f,3.0f,0.0f,
          8.0f,-3.0f,0.0f,
         -1.0f,3.0f,0.0f,

          8.0f,-3.0f,0.0f,
         -1.0f,-3.0f,0.0f,
         -1.0f,3.0f,0.0f,


    };

    static const GLfloat vertex_buffer_data2[] = {
          8.0f,-3.4f,0.0f,
         -1.0f,-3.4f,0.0f,
         -1.0f,-3.0f,0.0f,

          8.0f,-3.4f,0.0f,
          8.0f,-3.0f,0.0f,
         -1.0f,-3.0f,0.0f,

    };

    static const GLfloat vertex_buffer_data3[] = {
          8.0f,-3.4f,0.0f,
         -1.0f,-3.4f,0.0f,
         -1.0f,-4.0f,0.0f,

          8.0f,-3.4f,0.0f,
         -1.0f,-4.0f,0.0f,
          8.0f,-4.0f,0.0f,
    };

    static const GLfloat vertex_buffer_data4[] = {
        -1.0f,1.4f,0.0f,
        -1.0f,-3.0f,0.0f,
         1.0f,-3.0f,0.0f,

         -1.0f,1.4f,0.0f,
          1.0f,1.4f,0.0f,
          1.0f,-3.0f,0.0f,

          1.0f,-0.8f,0.0f,
          1.0f,-3.0f,0.0f,
          3.0f,-3.0f,0.0f,

          1.0f,-0.8f,0.0f,
          3.0f,-0.8f,0.0f,
          3.0f,-3.0f,0.0f,

          3.0f,0.4f,0.0f,
          3.0f,-3.0f,0.0f,
          8.0f,-3.0f,0.0f,

          3.0f,0.4f,0.0f,
          8.0f,0.4f,0.0f,
          8.0f,-3.0f,0.0f,

    };

     static const GLfloat vertex_buffer_data5[] = {
          5.0f,-1.5f,0.0f,
          4.0f,-1.5f,0.0f,
          4.0f,-2.0f,0.0f,

          5.0f,-1.5f,0.0f,
          4.0f,-2.0f,0.0f,
          5.0f,-2.0f,0.0f,

          5.0f,-2.2f,0.0f,
          4.0f,-2.2f,0.0f,
          4.0f,-2.7f,0.0f,

          5.0f,-2.2f,0.0f,
          4.0f,-2.7f,0.0f,
          5.0f,-2.7f,0.0f,

          7.0f,-1.5f,0.0f,
          6.0f,-1.5f,0.0f,
          6.0f,-2.0f,0.0f,

          7.0f,-1.5f,0.0f,
          6.0f,-2.0f,0.0f,
          7.0f,-2.0f,0.0f,

          7.0f,-2.2f,0.0f,
          6.0f,-2.2f,0.0f,
          6.0f,-2.7f,0.0f,

          7.0f,-2.2f,0.0f,
          6.0f,-2.7f,0.0f,
          7.0f,-2.7f,0.0f,

          0.0f,0.0f,0.0f,
          -0.4f,0.0f,0.0f,
          -0.4f,0.5f,0.0f,

          0.0f,0.0f,0.0f,
          -0.4f,0.5f,0.0f,
          0.0f,0.5f,0.0f,

          0.0f,0.6f,0.0f,
          -0.4f,0.6f,0.0f,
          -0.4f,1.1f,0.0f,

          0.0f,0.6f,0.0f,
          -0.4f,1.1f,0.0f,
          0.0f,1.1f,0.0f,

          0.1f,0.0f,0.0f,
          0.5f,0.0f,0.0f,
          0.5f,0.5f,0.0f,

          0.1f,0.0f,0.0f,
          0.5f,0.5f,0.0f,
          0.1f,0.5f,0.0f,

          0.1f,0.6f,0.0f,
          0.5f,0.6f,0.0f,
          0.5f,1.1f,0.0f,

          0.1f,0.6f,0.0f,
          0.5f,1.1f,0.0f,
          0.1f,1.1f,0.0f,

    };

    this->object = create3DObject(GL_TRIANGLES, 4*3, vertex_buffer_data, COLOR_GREY, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data2, COLOR_DARKGREY, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data3, COLOR_gray, GL_FILL);
    this->object4 = create3DObject(GL_TRIANGLES, 6*3, vertex_buffer_data4, COLOR_black, GL_FILL);
    this->object5 = create3DObject(GL_TRIANGLES, 16*3, vertex_buffer_data5, COLOR_red, GL_FILL);



}

void Background::draw(glm::mat4 VP) {
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
    draw3DObject(this->object5);
}

void Background::move_background_left() {
    this->position.x-=.05;
}
