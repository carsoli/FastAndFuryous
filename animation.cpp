#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <glut.h>
#include "animation.h"
#include "models.h"
#include "scene.h"
#include "sceneModels.h"
#include "camera.h"
#include "obstacles.h"

//this file controls all animations of scene/ obstacles / camera 
//bool obstacleLock[4] = {false, false, false, true}; //if true, there is an obstacle currently in scene
//int obstacleZ[4] = {0, 0, 0, -1 };  //ranges from -1 to 1
//int obstacleX[4] = { 0, 0, 0, 0 };//x value of all obstacles at any pt in time
//float rocketY=7.5;//4 constant y's 

bool animateScene(){ //animates scene and all obstacles
  rotateSky(); 
  return translateGround();
}

void animateCamera(){
  oscillateCamera();
}
