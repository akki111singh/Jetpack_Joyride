  #include "ball.h"
  #include "main.h"
  #include "Viserion.h"

  using namespace std;

  Viserion::Viserion(float x, float y,color_t color) {
      this->position = glm::vec3(x, y, 0);
    //this->position2 = glm::vec3(x1, y1, 0);
      this->rotation = 0;
      this->color=color;
      this->flag1=0;
      this->flag=0;
      this->yvel=0;
      this->gravity=0.009;

      // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
      // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices

      static const GLfloat vertex_buffer_data[] = {

        0.0f,0.0f,0.0f,
        0.2f,0.0f,0.0f,
        0.0f,-0.4f,0.0f,

        0.0f,-0.4f,0.0f,
        0.05f,-0.3f,0.0f,
        0.4,-0.6,0.0f,

        -0.2,0.4,0.0f,
        0.0f,0.0f,0.0f,
        0.2f,0.0f,0.0f,

        0.0f,0.0f,0.0f,
        0.2f,0.3f,0.0f,
        0.2f,0.0f,0.0f,

        0.2f,0.3f,0.0f,
        0.2f,0.0f,0.0f,
        0.6f,0.2f,0.0f,

        0.2f,0.5f,0.0f,
        0.1f,0.4f,0.0f,
        0.1f,0.2f,0.0f,

        0.1f,0.4f,0.0f,
        0.1f,0.2f,0.0f,
        0.0f,0.0f,0.0f,

        -0.2f,0.4f,0.0f,
        -0.4f,0.3f,0.0f,
        -0.1f,0.3f,0.0f,

        -0.3f,0.1f,0.0f,
        -0.4f,0.3f,0.0f,
        -0.1f,0.3f,0.0f,

        -0.2, 0.2, 0.0,
        -0.6, 0.1, 0.0,
        -0.6, 0.0, 0.0,

        -0.6, 0.1, 0.0,
        -0.6, 0.0, 0.0,
        -0.9,0.05,0.0,

        };

        static const GLfloat vertex_buffer_data2[] = {

             -0.2, 0.2, 0.0,
             -0.6, 0.1, 0.0,
             -0.6, 0.0, 0.0,

             -0.6, 0.1, 0.0,
             -0.6, 0.0, 0.0,
             -0.9,0.05,0.0,

          };


      this->object = create3DObject(GL_TRIANGLES, 9*3, vertex_buffer_data, COLOR_dragon, GL_FILL);
      this->object2 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data2, COLOR_fire, GL_FILL);

  }

  void Viserion::draw(glm::mat4 VP) {
      Matrices.model = glm::mat4(0.1f);
      glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    //  glm::mat4 translate2 = glm::translate (this->position2);    // glTranslatef

      glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
      // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
      // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
      Matrices.model *= (translate);
      glm::mat4 MVP = VP * Matrices.model;
      glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
      draw3DObject(this->object2);
      draw3DObject(this->object);


  }
  void Viserion::moveup()
  {   this->yvel=0;
    if(this->position.y >=0  and this->position.y < 2.8 )
    {
      this->yvel+=0.01;
      this->position.y+=this->yvel;

      if(this->position.y >=2.7){
        this->flag=1;
        //this->yvel=0;
      }
      if(this->flag==1)
      {
        this->yvel+=0.01;
        this->position.y-=this->yvel;
      }
      if(this->position.y < 0.2)
          this->flag=0;
    }
  }
  float Viserion::dist(float x1,float y1,float x2,float y2){
    return sqrt((x2-x1)* (x2-x1) +(y2-y1)*(y2-y1));
  }

  bool Viserion::lineCircle(float x1, float y1, float x2, float y2, float x, float y) {
    float d1 = this->dist(x,y, x1,y1);
    float d2 = this->dist(x,y, x2,y2);

    float lineLen = dist(x1,y1, x2,y2);
    float buffer = 0.1;
    if (d1+d2 >= lineLen-buffer && d1+d2 <= lineLen+buffer) {
      return true;
    }
    return false;
  }
