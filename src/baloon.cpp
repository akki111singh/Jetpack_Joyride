  #include "ball.h"
  #include "main.h"
  #include "baloon.h"

  using namespace std;

  Baloon::Baloon(float x, float y,float r,color_t color) {
      this->position = glm::vec3(x, y, 0);
      this->rotation = 0;
      this->color=color;
      this->r =r;
      this->yvel=0.2;
      this->gravity=0.009;
      this->friction = 0.01;
      // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
      // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
            int n=100;
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

      //this->object = create3DObject(GL_TRIANGLES, 4*3, vertex_buffer_data, COLOR_fire, GL_FILL);


  }

  void Baloon::draw(glm::mat4 VP) {
      Matrices.model = glm::mat4(0.1f);
      glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    //  glm::mat4 translate2 = glm::translate (this->position2);    // glTranslatef

      glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
      // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
      // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
      Matrices.model *= (translate);
      glm::mat4 MVP = VP * Matrices.model;
      glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
      draw3DObject(this->object);

  }

  void Baloon:: Baloon_attack(){
      if(this->yvel <= 0)
        this->flag = 1;

      this->position.x += 0.05;
      if(this->flag == 0)
      {
        this->yvel -= this->gravity;
        this->position.y += this->yvel;
      }
      else
      {
        this->yvel += this->gravity;
        this->position.y -= this->yvel;
      }
  }
    //if(this->position.x=x+)
