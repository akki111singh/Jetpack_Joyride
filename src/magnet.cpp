  #include "ball.h"
  #include "main.h"
  #include<bits/stdc++.h>
  #include "magnet.h"
  using namespace std;

  Magnet::Magnet(float x, float y,color_t color) {
      this->position = glm::vec3(x, y, 0);
      this->rotation = 0;
      this->color=color;
  //    this->color2=color2;

      static const GLfloat vertex_buffer_data[] = {
      0.0f,0.0f,0.0f,
      0.5f,0.0f,0.0f,
      0.0f,0.2f,0.0f,

      0.5f,0.0f,0.0f,
      0.5f,0.2f,0.0f,
      0.0,0.2f,0.0f,
      };

      static const GLfloat vertex_buffer_data2[] = {

      0.0f,0.0f,0.0f,
      0.1f,0.0f,0.0f,
      0.0f,-0.5f,0.0f,

      0.1f,0.0f,0.0f,
      0.1f,-0.5f,0.0f,
      0.0f,-0.5f,0.0f,

      0.4f,0.0f,0.0f,
      0.5f,0.0f,0.0f,
      0.4f,-0.5f,0.0f,

      0.5f,0.0f,0.0f,
      0.5f,-0.5f,0.0f,
      0.4f,-0.5f,0.0f,

      };


      this->object = create3DObject(GL_TRIANGLES,3*2,vertex_buffer_data, this->color, GL_FILL);
      this->object2 = create3DObject(GL_TRIANGLES,3*4,vertex_buffer_data2, COLOR_magnet, GL_FILL);

  }

  void Magnet::draw(glm::mat4 VP) {
      Matrices.model = glm::mat4(0.1f);
      glm::mat4 translate = glm::translate (this->position);    // glTranslatef
      glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
      // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
      //rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
      Matrices.model *= (translate * rotate);
      glm::mat4 MVP = VP * Matrices.model;
      glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
      draw3DObject(this->object);
      draw3DObject(this->object2);

  }
