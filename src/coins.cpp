#include "ball.h"
#include "main.h"
#include<bits/stdc++.h>
#include "coins.h"
using namespace std;
Coins::Coins(float x, float y,float r, color_t color,color_t color2,int n) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->color=color;
    this->color2=color2;


      float theta;
      float delta = (2 * (3.141592)) / n;
      theta = delta;
      GLfloat g_vertex_buffer_data[9 * n];
      g_vertex_buffer_data[0] = g_vertex_buffer_data[1] = g_vertex_buffer_data[2] = 0.0f;
      for(int i = 0; i < 9 * n; i++)
      {
          if(i % 9 == 0 || i % 9 == 1 || i % 9 == 2 || i % 9 == 5 || i % 9 == 8)
              g_vertex_buffer_data[i] = 0.0f;
          else if(i % 9 == 3)
              g_vertex_buffer_data[i] = r * cos(theta - delta);
          else if(i % 9 == 4)
              g_vertex_buffer_data[i] = r * sin(theta - delta);
          else if(i % 9 == 6)
              g_vertex_buffer_data[i] = r * cos(theta);
          else
              g_vertex_buffer_data[i] = r * sin(theta), theta += delta;
      }


    this->object = create3DObject(GL_TRIANGLES,3*n,g_vertex_buffer_data, this->color, GL_FILL);

}

void Coins::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(0.1f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    //rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);


}
