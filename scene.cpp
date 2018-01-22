#include "TextureBuilder.h"
#include <glut.h>
#include "scene.h"
#include "sceneModels.h"
#define PI 3.14159

GLuint tex_sky, tex_ground, tex_rails, tex_grass, tex_blend1, tex_blend2;
float  sSky = 50, sGround = sSky; //sGround >= sSky
float tGround = 0, rSky; 
char const SCENE1 = '1', BLEND1 = 'a', SCENE2 = '2', BLEND2 = 'b', SCENE3 = '3'; //5 states, 5 pictures
char scene = SCENE1;
bool gameOver = false; 

void loadSceneAssets(){//called in main, once
  loadBMP(&tex_sky, "textures/sky.bmp", true);
  loadBMP(&tex_ground, "textures/road.bmp", true);  
  loadBMP(&tex_blend1, "textures/blend1.bmp", true);
  loadBMP(&tex_grass, "textures/grass.bmp", true); //scene 2 
  loadBMP(&tex_blend2, "textures/blend2.bmp", true);
  loadBMP(&tex_rails, "textures/rails.bmp", true);//scene 3
  loadSceneModelsAssets();
}

void renderScene(){
  glClear(GL_COLOR_BUFFER_BIT);
  glEnable(GL_TEXTURE_2D);
    renderSky();
    renderGround();
    //lane size is decided by the camera
    drawSceneModels(scene, tGround, -7*sGround, sGround, 2*sGround, 10);
  glDisable(GL_TEXTURE_2D);

}

void renderSky(){
  GLUquadricObj *qobj;
  qobj = gluNewQuadric();
  GLdouble eqn[4] = { 0.0, 1.0, 0.0, 0};
 
  glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, tex_sky);
    glClipPlane(GL_CLIP_PLANE0, eqn);
    glEnable(GL_CLIP_PLANE0);
    gluQuadricTexture(qobj, true); 
    gluQuadricNormals(qobj, GL_SMOOTH);
    glScaled(sSky, sSky, sSky);
    glRotatef(rSky, 0, 1, 0);
    glRotatef(-90, 1, 0, 0);
    gluSphere(qobj, 1, 50, 50);
    glDisable(GL_CLIP_PLANE0);
  glPopMatrix();
  gluDeleteQuadric(qobj);
}

void rotateSky(){
  if (rSky > 360){
    rSky = 0; 
  }
  rSky += 0.01;
}

void renderGround(){
  glBindTexture(GL_TEXTURE_2D, tex_ground);
  GLUquadricObj * qobj;
  qobj = gluNewQuadric();
  float rep = 1;
  glPushMatrix();
  //translate
    glTranslated(tGround, 0, 0);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);			
    glVertex3f(-7*sGround, 0, -sGround);
    glTexCoord2f(1, 0);
    glVertex3f(-7*sGround, 0, sGround);
    glTexCoord2f(1, rep);	
    glVertex3f(sGround, 0, sGround);
    glTexCoord2f(0, rep);		
    glVertex3f(sGround, 0, -sGround);
    glEnd();
  glPopMatrix();
}

bool translateGround(){
  //width quad = maxX - minX = 1*sGround - -2*sGround = 3*sGround
  //diameter sky = 2*sSky
  float sceneTransition = 7*sGround - sSky; 
  if (tGround >= sceneTransition){
    tGround = 0; //reset
    switch (scene){
    case SCENE1:
        scene = BLEND1;
        tex_ground = tex_blend1;
        break;
    case BLEND1:
        scene = SCENE2;
        tex_ground = tex_grass;
        break;
    case SCENE2:
        scene = BLEND2;
        tex_ground = tex_blend2;
        break;
    case BLEND2: 
        scene = SCENE3;
        tex_ground = tex_rails;
        break;
    case SCENE3: 
        gameOver = true; 
        break;
    default:
        break;
    }
  }
  if (!gameOver){
    tGround += 0.35;
  }
  return gameOver;
}

