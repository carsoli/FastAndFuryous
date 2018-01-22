#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <glut.h>
#include <windows.h>
#include <iostream>
#include <string> 
using namespace std;
#include "camera.h"
#include "scene.h"
#include "models.h"
#include "animation.h"
#include "obstacles.h"


#define PI 3.1415926535
#define DtoR(deg) (deg*(PI / 180.0))
#define getrandom(min, max) ((rand() % (int)(((max)+1) - (min))) + (min))

bool rocketInScene = false, bombInScene = false, dynamiteInScene = false, oneDynamiteInScene = false;
float rocketX = 0,rocketY = 7.5, rocketZ = 0; //0
float bombX = 0, bombY = 1, bombZ = 0;//1
float oneDynamiteX = 0, oneDynamiteY = 1, oneDynamiteZ = 0;//2
float dynamiteX = 0, dynamiteY = 1, dynamiteZ = 0;//3
bool game_over = false;
float score = 0;

float obstaclesInitX = -51;//> sky
float coyoteZ = 0, coyoteY = 0, coyoteSideAng = 0, coyoteUpAng = 0, coyoteOscillate = 0, coyoteAmp = 0.5;
bool coyoteUp = true;
float roadRunnerOscillate = 0, roadRunnerAmp = 0.5, roadRunnerAvoidObstacle = false, roadRunnerJump = false, roadRunnerUp= true;

int W = 700; 
int H = 700;
int iX = 150;//initial window position
int iY = 50;
char cam = 'f'; //camera
bool redNose = false;

void print(int x, int y, int z, char *string){
  glRasterPos3f(x, y, z);
  int len = (int)strlen(string);
  //loop to display character by character
  for (int i = 0; i < len; i++){
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
  }
}

void drawBox(float theta){
  float x = 20 * cos(theta); //radius = 20
  float y = 20 * sin(theta);
  glPushMatrix();
  glTranslated(x, y, 0);
  glutSolidCube(1);
  glPopMatrix();
}

void renderModels(){
    bool third = true; 
    if (cam == 'f')
        third = false;
  drawCoyote(coyoteY, coyoteZ, coyoteSideAng, coyoteUpAng, coyoteOscillate, third, redNose);
  drawRoadRunner(roadRunnerOscillate, roadRunnerAvoidObstacle, roadRunnerJump);
  glColor3f(1, 1, 1);
}

void generateRandomZ(int obIndex){
  //hardness can be changed by decreasing random's range 
  int zRand = rand() % 15 -7; //-7 to 7 to decrease chances of overcrowding lanes

  switch (obIndex){
  case 0:
    rocketZ = zRand * 10;
    break;
  case 1: 
    while (dynamiteInScene && dynamiteZ == zRand * 10 || oneDynamiteInScene && oneDynamiteZ == zRand*10){
      zRand = rand() % 15 - 7;
    }
    bombZ = zRand * 10;
    break;
  case 2:
   while (dynamiteInScene && dynamiteZ == zRand*10 || bombInScene && bombZ == zRand*10){
       zRand = rand() % 15 - 7;
    }
    oneDynamiteZ = zRand * 10;
    break;
  case 3:
    while (oneDynamiteInScene && oneDynamiteZ == zRand * 10 || bombInScene && bombZ == zRand * 10){
      zRand = rand() % 15 - 7;
    }
    dynamiteZ = zRand * 10;
    break;
  default:
     break;
  }
}
void setNoseBlack(int value){
    redNose = false; 
}
void resetRoadRunnerLegs(int value){
    roadRunnerAvoidObstacle = false; 
    roadRunnerJump = false;
}

void animateObstacles(){
  if (rocketInScene){//in scene
    rocketX += 0.3; //0.05 slower than scene
    if (rocketX > 45){//height bta3o eh 7.5
      if (coyoteZ == rocketZ ){
          if (coyoteY == -2){
              //ducked 
              score += 100; 
          }
          else {
              score -= 100;
              redNose = true;
              glutTimerFunc(500, setNoseBlack, 0);
          }
      }
      else if(rocketZ >= -10 && rocketZ <= 10){
          score += 100;
      }

      rocketInScene = false;
      rocketZ = 0;

      rocketX = obstaclesInitX; //reset to be used again   
    }
    if (rocketZ == 0 && rocketX >= -0.45 && rocketX <= 0.45 ){ //small range for road runner's x position
        roadRunnerAvoidObstacle = true;
        roadRunnerJump = false;
        glutTimerFunc(200, resetRoadRunnerLegs, 0);
    }
  }
  else {
    generateRandomZ(0);
    rocketInScene = true;
  }
  //----------------------
  if (bombInScene){
    bombX += 0.45; //0.1 faster than scene
    if (bombX > 45){
        if (coyoteZ == bombZ){
            if (coyoteY > 0){
                //jumped 
                score += 100;
            }
            else {
              score -= 100;
              redNose = true;
              glutTimerFunc(500, setNoseBlack, 0);
            }
        }
        else if (bombZ >= -10 && bombZ <= 10){
            score += 100;
        }
      bombInScene = false;
      bombZ = 0;
      bombX = obstaclesInitX; //reset to be used again   
    }
    if (bombZ == 0 && bombX >= -0.45 && bombX <= 0.45){ //small range for road runner's x position
        roadRunnerAvoidObstacle = true;
        roadRunnerJump = true;
        glutTimerFunc(200, resetRoadRunnerLegs, 0);
    }
  } 
  else {
    generateRandomZ(1);
    bombInScene = true; 
  }
  //-----
  if (oneDynamiteInScene){
    oneDynamiteX += 0.35; //as slow as the scene
    if (oneDynamiteX > 45){
        if (coyoteZ == oneDynamiteZ){
            if (coyoteY > 0){
                //jumped 
                score += 100;
            }
            else {
                score -= 100;
                redNose = true;
                glutTimerFunc(500, setNoseBlack, 0);
            }
        }
        else if (oneDynamiteZ >= -10 && oneDynamiteZ <= 10) {
            score += 100;
        }

      oneDynamiteInScene = false;
      oneDynamiteZ = 0;
      oneDynamiteX = obstaclesInitX; //reset to be used again   
    }
    if (oneDynamiteZ == 0 && oneDynamiteX >= -0.45 && oneDynamiteX <= 0.45){ //small range for road runner's x position
        roadRunnerAvoidObstacle = true;
        roadRunnerJump = true;
        glutTimerFunc(200, resetRoadRunnerLegs, 0);
    }
  }
  else {
    generateRandomZ(2);
    oneDynamiteInScene = true;
  }
//-----
  if (dynamiteInScene){
    dynamiteX += 0.35;//as slow as the scene
    if (dynamiteX > 45){
        if (coyoteZ == dynamiteZ){
            if (coyoteY > 0 ){//jumped 
                score += 100;
            }
            else {
                score -= 100;
                redNose = true;
                glutTimerFunc(500, setNoseBlack, 0);
            }
        }
        else if (dynamiteZ >= -10 && dynamiteZ <= 10){
            score += 100;
        }
      dynamiteInScene = false;
      dynamiteZ = 0;
      dynamiteX = obstaclesInitX; //reset to be used again   
    }
    if (dynamiteZ == 0 && dynamiteX >= -0.45 && dynamiteX <= 0.45){ //small range for road runner's x position
        roadRunnerAvoidObstacle = true;
        roadRunnerJump = true;
        glutTimerFunc(200, resetRoadRunnerLegs, 0);
    }
  }
  else {
    generateRandomZ(3);
    dynamiteInScene = true;
  }
}
void resetCoyoteY(int value){
    coyoteY = 0;
}

void Display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(1.0, 1.0, 1.0, 0.0);
  renderScene();

  renderModels();
  updateCamera();
  if (!game_over){
    if (rocketZ >= -10 && rocketZ <= 10){
      drawRocket(rocketX, rocketY, rocketZ);
    }
    if (bombZ >= -10 && bombZ <= 10){
      drawBomb(bombX, bombY, bombZ);
    }
    if (oneDynamiteZ>=-10 && oneDynamiteZ <= 10){
      draw1Dynamite(oneDynamiteX, oneDynamiteY, oneDynamiteZ);
    }
    if (dynamiteZ >= -10 && dynamiteZ <= 10){
      drawDynamite(dynamiteX, dynamiteY, dynamiteZ);
    }
    glColor3f(1, 1, 0);
    char buffer[33];
    char *scoreNum;
    char scoreLabel[] = "SCORE:";
    scoreNum = itoa(score, buffer, 10);//decimal
    print(0, 11, 2, scoreLabel);
    print(0, 10, 2, scoreNum);
  }
  if (game_over){
    if (score < 0){
      glColor3f(1, 0, 0);
      print(0, 9, 0, "You Lost!" );
    }
    else{
      glColor3f(0, 1, 0);
      print(0, 9, 0, "You Won!");
    }
  } 

 
 
  glColor3f(1, 1, 1);
  glFlush();
}

void oscillateRoadRunner(){
    if (roadRunnerOscillate > roadRunnerAmp){
        roadRunnerUp = false;
    }
    if (roadRunnerOscillate <= 0){
        roadRunnerUp = true;
    }

    if (roadRunnerUp){
        roadRunnerOscillate += roadRunnerAmp / 50;
    }
    else {
        roadRunnerOscillate -= roadRunnerAmp/ 50;
    }   
}

void oscillateCoyote(){
  if (coyoteY == 0){
      if (coyoteOscillate > coyoteAmp){
          coyoteUp = false;
      }
      if (coyoteOscillate <= 0){
          coyoteUp = true;
      }

      if (coyoteUp){
          coyoteOscillate += coyoteAmp / 50;
      }
      else {
          coyoteOscillate -= coyoteAmp / 50;
      }
  }
}


void Anim(){
  game_over = animateScene();
  animateCamera();
  if (!game_over){
    animateObstacles();
    oscillateCoyote();
    oscillateRoadRunner();
  }
  glutPostRedisplay();
}



void keyHandler(unsigned char key, int xmouse, int ymouse){
  switch (key){

  case 'c': 
  case 'C': 
    cam = switchCamera(coyoteY, coyoteZ);
    break;
  case 27: //ESC
    exit(0);
    break;
  case 32: //SPACE
    if (cam == 'f' && coyoteY < 5){
      coyoteY += 5;
      glutTimerFunc(900, resetCoyoteY, 0);
    }
    moveCameraUp();
    break;
  case 49: //#1
    cam= switchCamera(1, coyoteY, coyoteZ);
    break;
  case 51: //#3
    cam = switchCamera(3, coyoteY, coyoteZ);
    break;
  case 52: //#4
    cam = switchCamera(4, coyoteY, coyoteZ);
    break;
  case 'a': 
  case 'A':
    if (cam == 'f' && coyoteSideAng <= 60.0){   
      coyoteSideAng += 0.05*180/PI;
    }
    lookLeft();
    break;
  case 'd':
  case 'D':
    if (cam == 'f' && coyoteSideAng >= -60.0){
      coyoteSideAng -= 0.05 * 180 / PI;
    }
    lookRight();
    //rotate his head right
    break;
  case 'w':
  case 'W': 
    if (cam == 'f' && coyoteUpAng <= 15.0){
      coyoteUpAng += 0.1 * 180 / PI;
    }
    lookUp();
    break;
  case 's':
  case 'S':
    if (cam == 'f' && coyoteUpAng >= -5.0){
      coyoteUpAng -= 0.1 * 180 / PI;
    }
    lookDown();
    break;
  default:
    break;
  }
  glutPostRedisplay();
}
void resetSideAng(){
  coyoteSideAng = 0;
  coyoteUpAng = 0;
}
void specialKeyHandler(int key, int xmouse, int ymouse){
  switch (key){
  case GLUT_KEY_RIGHT:
    if (cam == 'f' && coyoteZ > -10){
      coyoteZ -= 10;
    }
    moveCameraRight();
    break;
  case GLUT_KEY_LEFT:
    if (cam == 'f' && coyoteZ < 10){
       coyoteZ += 10;
    }
    moveCameraLeft();
    break;
  case GLUT_KEY_UP:
    if (cam == 'f' && coyoteY < 5){
      coyoteY += 5;
      glutTimerFunc(900, resetCoyoteY, 0);
    }
    moveCameraUp();
    break;
  case GLUT_KEY_DOWN:
    if (cam == 'f' && coyoteY >= 0){
      coyoteY -= 2;
    }
    moveCameraDown();
    break;
  default: 
    break; 
  }
  glutPostRedisplay();
}

void keyUpHandler(unsigned char key, int xmouse, int ymouse){
  switch (key){
  case 'W':
  case 'w':
  case 'S':
  case 's':
  case 'A':
  case 'a':
  case 'D':
  case 'd':
    resetSideAng();
    resetCoyoteY(0);//jump and duck
    resetCamera();
  default:
    break;
  }
}

void specialKeyUpHandler(int key, int xmouse, int ymouse){
  switch (key){
  case GLUT_KEY_DOWN:
    resetCoyoteY(0);
    resetCamera();
    break;
  default: 
    break;
  }
}

void resizeWindow(int nw, int nh){
  glutReshapeWindow(W, H);
  glutPositionWindow(iX, iY);
}

void InitLightSource(){
    // Enable Lighting for this OpenGL Program
    glEnable(GL_LIGHTING);

    // Enable Light Source number 0
    // OpengL has 8 light sources

    // Define Light source 0 ambient light , to make a real light effect set ambient = diffuse 
    GLfloat ambient[] = { 0, 0, 0, 1.0f };
    GLfloat diffuse[] = { 1, 1, 1, 1.0f };
    GLfloat specular[] = { 1, 1, 1, 1.0f };

    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

    // Finally, define light source 0 position in World Space
    GLfloat light_position[] = { 40.0f, 40, 0.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 90.0);
}
void InitMaterial(){
    // Enable Material Tracking
    glEnable(GL_COLOR_MATERIAL);

    // Sich will be assigneet Material Properties whd by glColor
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    // Set Material's Specular Color
    // Will be applied to all objects
    GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);

    //GLfloat emission[] = { 0, 0, 0, 1.0f };
    //glMaterialfv(GL_FRONT, GL_EMISSION, emission);

    // Set Material's Shine value (0->128)
    GLfloat shininess[] = { 90 };
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
}

void main(int argc, char** argv) {
	glutInit(&argc, argv);

	glutInitWindowSize(W, H);
	glutInitWindowPosition(iX, iY);
	glutCreateWindow("FAST AND FURRY-OUS");
	glutDisplayFunc(Display);
  glutReshapeFunc(resizeWindow);
	glutIdleFunc(Anim);
  glutKeyboardFunc(keyHandler);
  glutKeyboardUpFunc(keyUpHandler);
  glutSpecialFunc(specialKeyHandler);
  glutSpecialUpFunc(specialKeyUpHandler);
  //glutTimerFunc(0, timer, 0);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  InitMaterial();
  InitLightSource();
  
  loadSceneAssets();
  glEnable(GL_NORMALIZE);
  glEnable(GL_DEPTH_TEST);
   
  setupCamera(W, H);

	glutMainLoop();
}

