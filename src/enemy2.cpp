  #include "ball.h"
  #include "main.h"
  #include "enemy2.h"
  using namespace std;

  Enemy2::Enemy2(float x, float y,float x1,float y1,color_t color) {
      this->position = glm::vec3(x, y, 0);
    //this->position2 = glm::vec3(x1, y1, 0);
      this->rotation = 0;
      this->x1=x1;
      this->y1=y1;
      this->color=color;

      // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
      // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices

      static const GLfloat vertex_buffer_data[] = {
        x,y,0.0f,
        x1,y1,0.0f,
        x,y+0.1f,0.0f,

        x1,y1+0.1f,0.0f,
        x1,y1,0.0f,
        x,y+0.1f,0.0f,

      };
      static const GLfloat vertex_buffer_data1[] = {
      x-0.1f,y+0.1f,0.0f,
      x-0.1f,y-0.1f,0.0f,
      x+0.1f,y-0.1f,0.0f,

      x-0.1f,y+0.1f,0.0f,
      x+0.1f,y+0.1f,0.0f,
      x+0.1f,y-0.1f,0.0f


      };

      static const GLfloat vertex_buffer_data2[] = {
        x1-0.1f,y1+0.1f,0.0f,
        x1-0.1f,y1-0.1f,0.0f,
        x1+0.1f,y1-0.1f,0.0f,

        x1-0.1f,y1+0.1f,0.0f,
        x1+0.1f,y1+0.1f,0.0f,
        x1+0.1f,y1-0.1f,0.0f,
      };

      this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, COLOR_fire, GL_FILL);
      this->object2 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data1, COLOR_block, GL_FILL);
      this->object3 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data2, COLOR_block, GL_FILL);

  }

  void Enemy2::draw(glm::mat4 VP) {
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
      draw3DObject(this->object2);
      draw3DObject(this->object3);

  }
  float Enemy2::dist(float x1,float y1,float x2,float y2)
  {
    return sqrt((x2-x1)* (x2-x1) +(y2-y1)*(y2-y1));
  }

  bool Enemy2::lineCircle(float x1, float y1, float x2, float y2, float x, float y) {
    float d1 = this->dist(x,y, x1,y1);
    float d2 = this->dist(x,y, x2,y2);

    float lineLen = dist(x1,y1, x2,y2);
    float buffer = 0.1;
    if (d1+d2 >= lineLen-buffer && d1+d2 <= lineLen+buffer) {
      return true;
    }
    return false;
  }

  void Enemy2::moveup()
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

  void Enemy2::movedown()
  {   this->yvel=0;

    if(this->position.y <= 0 and this->position.y > -2.8 )
    {
      this->yvel+=0.01;
      this->position.y-=this->yvel;

      if(this->position.y < -2.7){
        this->flag1=1;
        //this->yvel=0;
      }

      if(this->flag1==1)
      {
        this->yvel+=0.01;
        this->position.y+=this->yvel;
      }
      if(this->position.y > -0.2)
          this->flag1=0;
    }
  }
  bool Enemy2::rectRect(float r1x, float r1y, float r1w, float r1h, float r2x, float r2y, float r2w, float r2h) {
    if (r1x + r1w >= r2x &&    // r1 right edge past r2 left
        r1x <= r2x + r2w &&    // r1 left edge past r2 right
        r1y + r1h >= r2y &&    // r1 top edge past r2 bottom
        r1y <= r2y + r2h) {    // r1 bottom edge past r2 top
          return true;
    }
    return false;
  }
