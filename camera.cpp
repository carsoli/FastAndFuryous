#include <glut.h>
#include <math.h>
#include "camera.h"

#define PI 3.1415926535

char  const FIRST_PERSON = 'f';
char const THIRD_PERSON_RIGHT = 'r';
char const THIRD_PERSON_LEFT = 'l';
//enums of coyote's lane 
char const CENTER = 'c', RIGHT = 'r', LEFT = 'l';
char const DUCK = 'd', JUMP = 'j', NONE = 'n';
//initially camera is for first person 
//and lane is center
//and coyote is neither ducked nor jumping 
char camera = FIRST_PERSON;
char verticalPos = NONE;
float amp = 0.5; //oscillation amplitude
bool oscillateUp = true; 
float oscillateCameraY = 0;
char lane = CENTER;

//y should match the height of coyote later
GLdouble const eyeXFirst = 40, eyeYFirst = 8.5, eyeZFirst = 0;
GLdouble const cofXFirst = 0, cofYFirst = 0, cofZFirst = 0;
//make y be as high as our highest model to have an overview
//make x half the distance b/w coyote and road runner 
//third person can be on both right and left side
GLdouble const eyeXThird = -30, eyeYThird = 15, eyeZThirdL = 10, eyeZThirdR = -eyeZThirdL;
GLdouble const cofXThird = 0.5*eyeXFirst, cofYThird = 0, cofZThird = 0;
GLdouble const initRotAngZ = PI;

GLdouble rotRadius = eyeXFirst, rotAngZ = initRotAngZ, rotAngY = 0;

GLdouble eyex = eyeXFirst,
eyey = eyeYFirst,
eyez = eyeZFirst,
cofx = cofXFirst, //center of focus 
cofy = cofYFirst,
cofz = cofZFirst;


void setupCamera(int w, int h){
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0f, w / h, 0.1f, 300.0f); //fovy, aspect, zNear, zFar
}

void updateCamera(){
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(eyex, eyey, eyez, cofx, cofy, cofz, 0.0f, 1.0f, 0.0f);
}

//first perspective --> third perspective right --> third perspective left 
char switchCamera(float coyoteY, float coyoteZ){//this works with C
  if (camera == FIRST_PERSON){
    camera = THIRD_PERSON_RIGHT;
    eyex = eyeXThird;
    eyey = eyeYThird;
    eyez = eyeZThirdR;
    cofx = cofXThird;
    cofy = cofYThird;
    cofz = cofZThird;
  }else if (camera == THIRD_PERSON_RIGHT){
    camera = THIRD_PERSON_LEFT;
    eyex = eyeXThird;
    eyey = eyeYThird;
    eyez = eyeZThirdL;
    cofx = cofXThird;
    cofy = cofYThird;
    cofz = cofZThird;
  } else {
    camera = FIRST_PERSON;
    eyey = eyeYFirst + coyoteY;
    eyez = eyeZFirst + coyoteZ;
    eyex = eyeXFirst;
    cofx = cofXFirst;
    cofy = cofYFirst + coyoteY;
    cofz = cofZFirst + coyoteZ;
    rotAngZ = initRotAngZ;
  }
  return camera;
}

char switchCamera(int p, float coyoteY, float coyoteZ){//this works with 1 2 3
  switch (p){
  case 1://first person
    camera = THIRD_PERSON_LEFT; //hack
    switchCamera(coyoteY, coyoteZ);
    break;
  case 3://third person right
    camera = FIRST_PERSON; 
    switchCamera(coyoteY, coyoteZ);
    break;
  case 4://third person left
    camera = THIRD_PERSON_RIGHT;
    switchCamera(coyoteY, coyoteZ);
    break;
  default:
    break;
  }
  return camera;
}

void lookUp(){
  if (camera == FIRST_PERSON){
    if (rotAngY < 20 * PI / 180){
      rotAngY += 0.05;
      cofx = rotRadius*cos(rotAngY) - eyeXFirst;
      cofy = rotRadius*sin(rotAngY);// +eyey;
    }
  }
}

void lookDown(){
  if (camera == FIRST_PERSON){
    if (rotAngY > -10 * PI / 180){
      rotAngY -= 0.05;
      cofx = rotRadius*cos(rotAngY) - eyeXFirst;
      cofy = rotRadius*sin(rotAngY);// -eyey;
    }
  }
}

void lookLeft(){
  if (camera == FIRST_PERSON){
    if (rotAngZ >= (120.0/180)*PI){ //120 deg
      rotAngZ -= 0.05;
      cofx = rotRadius*cos(rotAngZ) + eyeXFirst;
      cofz = rotRadius*sin(rotAngZ) + eyez; //+eyez is only for move left zero
    }
  }
}

void lookRight(){
  if (camera == FIRST_PERSON){
    if (rotAngZ <= (240.0/180)*PI ){ //240
      rotAngZ += 0.05;
      cofx = rotRadius*cos(rotAngZ) + eyeXFirst;
      cofz = rotRadius*sin(rotAngZ) + eyez;
    }
  }
}

void moveCameraLeft(){
  if (camera == FIRST_PERSON){
    switch (lane){
      case CENTER:         
        lane = LEFT;
        eyez += 10;
        cofz += 10;
        break;
      case RIGHT: 
        lane = CENTER; 
        eyez += 10;
        cofz += 10;
        break;
      default: 
        break;
    }
  }
}

void moveCameraRight(){
  if (camera == FIRST_PERSON){
    switch (lane){
    case CENTER:
      lane = RIGHT;
      eyez -= 10;
      cofz -= 10;
      break;
    case LEFT:
      lane = CENTER;
      eyez -= 10;
      cofz -= 10;
      break;
    default:
      break;
    }
  }
}
//7.5 + 5 --> for obstacle collision  (make el hagat el 3izah yjump f range el 5 in its height)

void moveCameraUp(){
  if (camera == FIRST_PERSON && verticalPos != JUMP){
    verticalPos = JUMP;
    eyey += 5;
    cofy += 5;
    glutTimerFunc(900, resetCameraTimed, 0);
  }
}

//rocket (makes him duck) max height = 4.5 *2 = 9 --> coyote's height 
//rocket law geh f range  7 --> 9  --> coyote needs to duck --> otherwise collision
//draw rocket at height 8 : 
void moveCameraDown(){//duck
  if (camera == FIRST_PERSON &&  verticalPos != DUCK ){
    verticalPos = DUCK;
    eyey -= 2;
    cofy -= 2;
  }
}

void resetCamera(){
  if (camera == FIRST_PERSON){
    //initial cof values (taking in consideration coyote moving right or left)
    cofx = cofXFirst;
    cofy = cofYFirst;
    cofz = cofZFirst + eyez;
    //initial eye values (taking in consideration coyote moving right or left)
    eyez = eyeZFirst + eyez; 
    eyex = eyeXFirst;
    eyey = eyeYFirst;
    //reset angles of rotation 
    rotAngZ = initRotAngZ;
    rotAngY = 0;
    verticalPos = NONE;
  }
}

void resetCameraTimed(int value){
  resetCamera();
}

void oscillateCamera(){
  if (camera == FIRST_PERSON && verticalPos == NONE){
    if (eyey > eyeYFirst + amp){
      oscillateUp = false;
    }
    if (eyey < eyeYFirst){
      oscillateUp = true;
    }
    if (oscillateUp){
      eyey += amp / 50;
    } else {
      eyey -= amp / 50;
    }
  }
}