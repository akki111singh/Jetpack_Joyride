  #include "main.h"
  #include "timer.h"
  #include "ball.h"
  #include "background.h"
  #include "coins.h"
  #include "enemy.h"
  #include "enemy2.h"
  #include "baloon.h"
  #include "ring.h"
  #include "magnet.h"
  #include "lifeup.h"
  #include "shield.h"
  #include "boomerang.h"
  #include "line.h"
  #include "segmentdisplay.h"
  #include "Viserion.h"
  #include<string.h>
  #include<vector>
  #include <time.h>
  #include "fireballs.h"
  //#include <SDL/SDL_gfxPrimitives.h>
  //#include <SDL/SDL_gfxPrimitives_font.h>



  using namespace std;
  int score=0;
  int win=0;
  bool Ring=false;
  int flag=0;
  bool move_forward=true;
  bool shoot = false;
  bool shooting=false;
  Segmentdisplay Score;
  Segmentdisplay Lives;
  GLMatrices Matrices;
  GLuint     programID;
  GLFWwindow *window;
  int lives=3;
  int check;

  /**************************
  * Customizable functions *
  **************************/

  Coins moon;
  int c=0;
  Background background;
  vector<Background> back;
  vector<Coins>coins;
  vector<Enemy> enemy1;
  Ball ball1;
  vector<Baloon>baloon;
  vector<Rings>ring;
  vector<Magnet> magnet;
  vector<Enemy2> enemy2;
  vector<Boomerang> boom;
  vector<Lifeup> lifeup;
  vector<Shield> shield;

  Fireballs fireball;
  Viserion dragon;

  time_t seconds;
  time_t seconds2;
  bounding_box_t player,coin,enemy_2,boomy,lify,shildy,drag,fire;

  //float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
  float camera_rotation_angle = 0;

  float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0.0;
  double mouse_x = 0.0, mouse_y=0.0;
  int mouse_action = 0;

  Timer t60(1.0 / 60);

  /* Render the scene with openGL */
  /* Edit this function according to your assignment */
  void draw() {
      // clear the color and depth in the frame buffer
      glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      // use the loaded shader program
      // Don't change unless you know what you are doing
      glUseProgram (programID);

      // Eye - Location of camera. Don't change unless you are sure!!
      glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
      // Target - Where is the camera looking at.  Don't change unless you are sure!!
      glm::vec3 target (0, 0, 0);
      // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
      glm::vec3 up (0, 1, 0);

      // Compute Camera matrix (view)
   //    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
      // Don't change unless you are sure!!
       Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

      // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
      // Don't change unless you are sure!!
      glm::mat4 VP = Matrices.projection * Matrices.view;

      // Send our transformation to the currently bound shader, in the "MVP" uniform
      // For each model you render, since the MVP will be different (at least the M part)
      // Don't change unless you are sure!!
      glm::mat4 MVP;  // MVP = Projection * View * Model

      // Scene render
      back[0].draw(VP);

      back[1].draw(VP);
      moon.draw(VP);

      if(!ring.empty())
      ring[0].draw(VP);

      for(int i =0 ;i<10;i++)
      coins[i].draw(VP);

      dragon.draw(VP);
      fireball.draw(VP);


      //enemy1[i].draw(VP);
    //  if(shooting==true)

    if(shoot == true)
      baloon[0].draw(VP);

    //if(Ring==true)
    //  ball2.draw(VP);
    if(!magnet.empty())
      magnet[0].draw(VP);

      if(!lifeup.empty())
      lifeup[0].draw(VP);

      if(!shield.empty())
      shield[0].draw(VP);

      if(!boom.empty())
      boom[0].draw(VP);


      enemy2[0].draw(VP);
      enemy2[1].draw(VP);

      ball1.draw(VP);
      Score.draw(VP);

      Score.update(score);

      Lives.draw(VP);

      Lives.update(lives);
      Lives.set_position(-7,3.3);



    for(int i=0;i<enemy1.size();i++)
     enemy1[i].draw(VP);
  }

  void tick_input(GLFWwindow *window) {
      int left  = glfwGetKey(window, GLFW_KEY_LEFT);
      int right = glfwGetKey(window, GLFW_KEY_RIGHT);
      int space = glfwGetKey(window,GLFW_KEY_SPACE);
      int shoot_baloons=glfwGetKey(window,GLFW_KEY_S);
      if (left) {
          ball1.move_left();
      }
      if(shoot_baloons){

        baloon[0].yvel=0.2;
        baloon[0].gravity=0.009;
        baloon[0].friction = 0.01;
        baloon[0].flag=0;

        baloon[0].position.x=ball1.position.x+0.2;
        baloon[0].position.y=ball1.position.y+0.2;
        shooting=true;

        if(baloon.empty())
        baloon.push_back(Baloon(baloon[0].position.x,baloon[0].position.y,0.1,COLOR_baloon));
      };
    //  else shooting=false;

          back[0].move_background_left();

          ring[0].position.x-=0.05;

          magnet[0].position.x-=0.05;

        //  boom[0].position.x-=0.05;

          for(int i=0;i<enemy1.size();i++){
            if(!enemy1.empty())
            enemy1[i].position.x-=0.05;
          }

          for(int i=0;i<enemy2.size();i++){
          if(!enemy2.empty())
            enemy2[i].position.x-=0.05;
          }

          for(int i =0;i<10;i++)
          coins[i].position.x-=.05;

          back[1].move_background_left();


          if(ball1.position.x >0.24)
          ball1.position.x=0.24;

          if(ball1.position.x < -3 )
          ball1.position.x=-3;
        //  else
        //  ball1.move_right();
      if(right and Ring==false){
        ball1.position.x+=0.03;

      }
      if(left)
      {
        ball1.position.x-=0.03;
      }

      if(space)
      {
          ball1.jumping=true;
          ball1.jump();
      }
      else
      {
          ball1.jumping=false;
          ball1.jump();
      }
  }


  void tick_elements() {

    player.x = ball1.position.x;
    player.y = ball1.position.y - 0.5;
    player.height =0.8f;
    player.width = 0.3f;
    boomy.height=0.3;
    boomy.width=0.1;
    lify.height=0.3;
    lify.width=0.1;
    shildy.height=0.3;
    shildy.width=0.1;



    if(back[0].position.x <= -12 ){
        back.erase(back.begin());
        back.push_back(Background(6,0,COLOR_WHITE));
    }

  //  cout<<coins.size()<<endl;

    //  add random firelines
    if(rand()%200==0 && enemy2.size() < 1){
      //float x=(rand()%60)/10 + (rand()%20)/10;
      enemy2.push_back(Enemy2(6,0,8,0,COLOR_RED));
      enemy2.push_back(Enemy2(6,0,8,0,COLOR_RED));
    }

    if(rand()%3000==0 && boom.size() < 1){
      boom.push_back(Boomerang(8,2,COLOR_boom));
    }

    if(rand()%1000==0 && lifeup.size() < 1){
      lifeup.push_back(Lifeup(10,2,COLOR_life));
    }

    if(rand()%2000==0 && shield.size() < 1){
      shield.push_back(Shield(4,2,COLOR_shield));
    }

    if(lifeup[0].position.y < -2.8 and !lifeup.empty()){
      lifeup.erase(lifeup.begin());
    }
    if(shield[0].position.y < -2.8 and !shield.empty()){
      shield.erase(shield.begin());
    }


    if(boom[0].position.y < -2.8 and !boom.empty()){
      boom.erase(boom.begin());
    }


    boom[0].attack();
    lifeup[0].attack();
    shield[0].attack();

    //cout<<magnet.size()<<endl;


    if(magnet[0].position.x - ball1.position.x  < 2 and magnet[0].position.x - ball1.position.x  > -2 )
    {
      ball1.jumping=true;
      ball1.jump();
      if(ball1.position.x > magnet[0].position.x)
        ball1.position.x-=0.05;
      else
        ball1.position.x+=0.05;
    }

    if(magnet[0].position.x < -12 and !magnet.empty()){
      magnet.erase(magnet.begin());
    }

    if(rand()%2000==0 && magnet.size() < 1){
      magnet.push_back(Magnet(6,2.8,COLOR_BLUE));
    }

  //if(!ring.empty())
  //  cout<<ring.size()<<endl;


    if(rand()%200==0 && enemy1.size() < 2){
      float x = (rand()% 40)/10 + 4;
      float y = (rand()%14)/10-(rand()%38)/10;
      enemy1.push_back(Enemy(x,y,x+0.7,y+1,COLOR_RED));
      //enemy1.push_back(Enemy(x,y,x+0.7,y+1,COLOR_RED));

    }

  //Erasing firelines
      if(!enemy2.empty()){
        if(enemy2[0].position.x < -12.5){
        enemy2.erase(enemy2.begin());
        enemy2.erase(enemy2.begin());
      }
    }

  //cout<<enemy1[0].position.x<<endl;

      if(!enemy1.empty()){
        if(enemy1[0].position.x < -12 ){
          enemy1.erase(enemy1.begin());
    //  cout<<"akhil singh"<<endl;
    }
  }

  //check collision of firelines with player;
      for(int i=0;i<enemy1.size();i++){
        float x1=enemy1[i].position.x;
        float y1=enemy1[i].position.y;

        if(enemy1[i].lineCircle(x1,y1,x1+0.7,y1+1,baloon[0].position.x,baloon[0].position.y)){
          enemy1.erase(enemy1.begin()+i);
          score+=20;
        }
        //  enemy1.push_back(Enemy(x,y,0,0,COLOR_RED));
      }

        float x1=enemy2[0].position.x+0.1;
        float y1=enemy2[0].position.y;

        float x2=enemy2[1].position.x+0.1;
        float y2=enemy2[1].position.y;



       if(ball1.rectangle_line_collision(x1,y1,x1+2,y1,player.x,player.y-0.4,player.width,1.0)and ball1.shield==false){
            enemy2[0].position.y=5;

            dec_lives();
          }

      if(ball1.rectangle_line_collision(x2,y2,x2+2,y2,player.x,player.y-0.4,player.width,1.0) and ball1.shield==false){
            enemy2[1].position.y=5;

            dec_lives();
          }

        boomy.x=boom[0].position.x;
        boomy.y=boom[0].position.y;

        lify.x=lifeup[0].position.x;
        lify.y=lifeup[0].position.y;

        shildy.x=shield[0].position.x;
        shildy.y=shield[0].position.y;

      //  cout<<"shield "<<shield[0].position.x<<endl;
      //  cout<<"boom "<<boom[0].position.x<<endl;

      if(detect_collision(player,boomy) and ball1.shield==false){
      boom[0].position.y=5;

      dec_lives();
      //ball1.position.y=5;
      }
      if(detect_collision(player,lify)){
        lives=lives+1;
        lifeup[0].position.y=-4;
      }

      if(detect_collision(player,shildy)){
        ball1.shield=true;
        seconds=time(NULL);
      //  cout<<"shield up"<<endl;
      //ball1.position.y=5;
    }





      //coins removal
      if(coins[0].position.x < -4.25) {
        coins.erase(coins.begin());
        float x = rand() % 12 + 5;
        float y = (rand() % 35 -10)/10;
        coins.push_back(Coins(x,y,0.1,COLOR_coins,COLOR_RED,100));
        coins.push_back(Coins(x+0.4,y,0.1,COLOR_coins,COLOR_RED,100));
        coins.push_back(Coins(x+0.8,y,0.1,COLOR_coins,COLOR_RED,100));
        coins.push_back(Coins(x+1.2,y,0.1,COLOR_coins,COLOR_RED,100));

      }

      for(int i=0;i<10;i++){
        coin.x = coins[i].position.x ;
        coin.y = coins[i].position.y;

        if(ball1.rectangle_line_collision(coin.x,coin.y,coin.x+0.2,coin.y+0.4,player.x,player.y,player.width,player.height)){
          score+=10;
          coins.erase(coins.begin()+i);
          float x = rand() % 12 + 5;
          float y = (rand() % 35 -10)/10;
          coins.push_back(Coins(x,y,0.1,COLOR_coins,COLOR_RED,100));
        }
      }


      for(int i=0;i<enemy1.size();i++){
        float x1=enemy1[i].position.x-0.1;
        float y1=enemy1[i].position.y-0.1;
        float x2=x1+0.8;
        float y2=y1+1.2;
        if(ball1.rectangle_line_collision(x1,y1,x2,y2,player.x,player.y,player.width,player.height) and ball1.shield==false){
          enemy1[i].position.y=5;
          dec_lives();
      }
    }
    //cout<<coins.size()<<endl;


    if(shooting==true){
      shoot = true;
      baloon[0].Baloon_attack();

    if(baloon[0].position.y <= -3){
      baloon.erase(baloon.begin());
      shoot=false;
      shooting=false;
    }
  }
    enemy2[0].moveup();
    enemy2[1].movedown();
    dragon.moveup();


    if(!ring.empty() and player.x >= ring[0].position.x-3 and player.x <=ring[0].position.x and ball1.position.y<=1.2){
     Ring=true;
     //ball1.angle=-180;
     //ring.erase(ring.begin());
   }
    if(Ring==false)
      ball1.angle=-180;


     if(Ring){
       ball1.position.x= ring[0].position.x + cos(ball1.angle)*3;
       ball1.position.y= ring[0].position.y + sin(ball1.angle)*3;
       ball1.angle-=0.02;
       //ring[0].position.x-=0.02;


    //   cout<<ball1.position.x<<endl;

       if(ball1.position.y < -2.4){
         Ring=false;
         ball1.angle=-180;
       }
      }

      if(ring[0].position.x < -8){
        ring.erase(ring.begin());
        Ring=false;
        ball1.angle=-180;
      }

      if(dragon.position.y > 2.6){
          fireball.position.x=dragon.position.x;
          fireball.position.y=dragon.position.y;
          check=1;
      }
      if(check==1){
      fireball.Fireballs_attack();
    //  check=0;
    }

    if(fireball.position.y < -4.2){
    check=0;
    fireball.gravity=0.009;
    fireball.yvel=0.2;
    fireball.flag=0;
  }

    drag.x=dragon.position.x;
    drag.y=dragon.position.y;
    drag.height=0.8;
    drag.width=0.3;

    fire.x=fireball.position.x;
    fire.y=fireball.position.y;
    fire.height=0.8;
    fire.width=0.3;

    if(enemy1[0].lineCircle(drag.x,drag.y,drag.x-0.4,drag.y-1,baloon[0].position.x,baloon[0].position.y)){
      c+=1;
      cout<<"c "<<c<<endl;
      if(c==30){
        win=1;
      lives=0;
      }
    }

    if(enemy1[0].lineCircle(player.x,player.y,player.x+0.4,player.y-0.8,fireball.position.x,fireball.position.y) && ball1.shield==false){
      lives=0;

      score+=20;
    }
  //  cout<<dragon.position.x<<endl;


    camera_rotation_angle += 1;
  }

  /* Initialize the OpenGL rendering properties */
  /* Add all the models to be created here */
  void initGL(GLFWwindow *window, int width, int height) {
      /* Objects should be created before any other gl function and shaders */
      // Create the models
      ball1 = Ball(-3,0,COLOR_RED);
      //ball2 = Ball(-3,0,COLOR_RED);

      background = Background(-3,0,COLOR_WHITE);
      moon = Coins(-3,2.2,0.5,COLOR_moon,COLOR_moon,100);

      enemy2.push_back(Enemy2(0,0,2,0,COLOR_RED));
      enemy2.push_back(Enemy2(0,0,2,0,COLOR_RED));

      enemy1.push_back(Enemy(4,0,0.7,1,COLOR_RED));
      //enemy1.push_back(Enemy(0,0,0.7,1,COLOR_RED));

      magnet.push_back(Magnet(8,2.4,COLOR_BLUE));

      boom.push_back((Boomerang(0,2,COLOR_boom)));
      lifeup.push_back((Lifeup(0,10,COLOR_life)));
      shield.push_back((Shield(0,20,COLOR_shield)));
      dragon=Viserion(1,0,COLOR_RED);
      fireball=Fireballs(200,5,0.2,COLOR_fire);

      baloon.push_back(Baloon(1,6,0.1,COLOR_baloon));
      ring.push_back(Rings(40,-2.8,3,COLOR_RED,COLOR_fire,500));

      for(int i=0;i<10;i++){
        coins.push_back(Coins(0,0,0.1,COLOR_coins,COLOR_RED,100));
      }
      back.push_back(background);
      back.push_back(Background(6,0,COLOR_WHITE));


      coin.width=0.2;
      coin.height=0.2;

      // Create and compile our GLSL program from the shaders
      programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
      // Get a handle for ou2r "MVP" uniform
      Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


      reshapeWindow (window, width, height);

      // Background color of the scene
      glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
      glClearDepth (1.0f);

      glEnable (GL_DEPTH_TEST);
      glDepthFunc (GL_LEQUAL);

      cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
      cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
      cout << "VERSION: " << glGetString(GL_VERSION) << endl;
      cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
  }


  int main(int argc, char **argv) {
      srand(time(0));
      int width  = 1024;
      int height = 800;

      window = initGLFW(width, height);

      initGL (window, width, height);


      /* Draw in loop */
      while (!glfwWindowShouldClose(window)) {
        if(lives==0 and win==0){
          cout<<"GAME OVER"<<endl;
          cout<<"FINAL SCORE::"<<score<<endl;
          //cout<<"FINAL SCORE::"<<score<<endl;
          break;
        }
        if(lives==0 and win==1){
          cout<<"You won"<<endl;
          cout<<"FINAL SCORE::"<<score<<endl;
          //cout<<"FINAL SCORE::"<<score<<endl;
          break;
        }
      //  glListBase(1);
  //glCallLists(1, GL_UNSIGNED_BYTE, "akhil");
        //ball1.position.x+=0.001;
          // Process timers
        //  ball1.position.x+=0.001;

          if (t60.processTick()) {

              // 60 fps
              // OpenGL Draw commands
              //if(ball1.shield==true)
              seconds2=time(NULL);


              if(seconds2-seconds > 10)
              ball1.shield=false;

      //        cout<<seconds-seconds<<endl;

              draw();
              // Swap Frame Buffer in double buffering
              glfwSwapBuffers(window);
              reset_screen();
              tick_elements();
              tick_input(window);

          }

          // Poll for Keyboard and mouse events
          glfwPollEvents();

      }
      quit(window);
  }


  bool detect_collision(bounding_box_t a, bounding_box_t b) {
      return (abs(a.x - b.x)  < (a.width + b.width)) &&
             (abs(a.y - b.y)  < (a.height + b.height));
  }


  void reset_screen() {
      float top    = screen_center_y + 4 / screen_zoom;
      float bottom = screen_center_y - 4 / screen_zoom;
      float left   = screen_center_x - 4 / screen_zoom;
      float right  = screen_center_x + 4 / screen_zoom;
      Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
  }

  void add_lives(){
    if(flag==1)
    lives+=1;

  }
  void dec_lives(){
    lives-=1;
  }
