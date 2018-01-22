#include "TextureBuilder.h"
#include "GLTexture.h"
#include "Model_3DS.h"
#include <glut.h>
#include <math.h>
#include "sceneModels.h"

#define PI 3.14159
bool zEven = false;
GLuint tex_tunnel;
Model_3DS model_cactus, model_mountain;

void loadSceneModelsAssets(){
  loadBMP(&tex_tunnel, "textures/tunnel.bmp", true); 
  model_cactus.Load("models/cactus/cactus.3ds");
  model_mountain.Load("models/rock/rock.3ds");
}

void drawCactii(float minX, float maxX, float tx, float zLength, float laneSize){
  //position of scene models
  float dz = ((zLength / 2) - (laneSize * 1.5 ));
  float positionZ = (zLength / 2) - dz ;
  float xStep = (maxX - minX) / 10;
  glPushMatrix();
    for (float i = minX; i<maxX; i += xStep){//5 times
      glPushMatrix();
        if (zEven){
            glTranslated(i + tx, 0, positionZ + 5);
          zEven = false; 
        } else {
            glTranslated(i + tx, 0, -positionZ - 5);
          zEven = true; 
        }
        glScaled(0.1, 0.06, 0.1);
        drawCactus();
      glPopMatrix();
    }
  glPopMatrix();
}

void drawMountains(float minX, float maxX, float tx, float zLength, float laneSize){
 //position of scene models

  float dz = ((zLength / 2) - (laneSize * 1.5));
  float positionZ = (zLength / 2) - dz + 5;
  float xStep = (maxX - minX) / 10;
  glPushMatrix();
  for (float i = minX; i<maxX; i += xStep){//5 times
    glPushMatrix();
      if (zEven){
          glTranslated(i + tx, 0, positionZ);
          zEven = false;
      }
      else {
          glScaled(1, 1, -1);
          glTranslated(i + tx, 0, positionZ);
          zEven = true;
      }
      glScaled(0.01, 0.01, 0.01);
      drawMountain();
    glPopMatrix();
  }
  glPopMatrix();

}

void drawSceneModels(char scene, float tx, float minX, float maxX, float zLength, float laneSize){
  switch (scene){
  case '1':
      drawCactii(minX, maxX, tx, zLength, laneSize);
      break;
  case 'a':
      drawCactii(minX, (maxX-minX)/2, tx, zLength, laneSize);
      drawCactii((maxX - minX) / 2, maxX, tx, zLength, laneSize);
      break;
  case '2':
      drawTunnel(minX, maxX, tx, laneSize);
      break;
  case 'b':
      drawMountains(minX, maxX, tx, zLength, laneSize);
      break;
  case '3':
      drawMountains(minX, maxX, tx, zLength, laneSize);
      break;
  default: 
      break;
  }
}

void drawTunnel(float minX, float maxX, float tx, float laneSize){
  GLdouble eqn[4] = { 0.0, 1.0, 0.0, 0.0 };//crop the -ve y half of the cylinder
  float tunnelRadius = laneSize * 1.5; 
  GLUquadricObj * qobj;
  qobj = gluNewQuadric();
  glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, tex_tunnel);
    glPushMatrix(); 
      glClipPlane(GL_CLIP_PLANE0, eqn);
      glEnable(GL_CLIP_PLANE0);
      gluQuadricTexture(qobj, true);
      gluQuadricNormals(qobj, GL_SMOOTH);
      glTranslated(tx+minX-2*maxX, 0, 0);
      glRotatef(90.0, 0, 1, 0); // two bases lie on the x-axis
      gluCylinder(qobj, 20, 20, maxX-minX, 20, 10);
    glPopMatrix();
    gluDeleteQuadric(qobj);
  glPopMatrix();
  glDisable(GL_CLIP_PLANE0);
  glColor3f(1, 1, 1);
}

void drawCactus(){
   model_cactus.Draw();
}

void drawMountain(){
  model_mountain.Draw();
}