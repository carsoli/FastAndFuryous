#include <TextureBuilder.h>
#include <math.h>
#include <glut.h>
#include <obstacles.h>

GLuint bomb_sphere, rope;
void loadObstaclesAssets(){
  loadBMP(&bomb_sphere, "textures/bomb.bmp", true);
  //loadBMP(&rope, "textures/rope.bmp", true);
}


void drawBomb(float tx, float ty, float tz){
  glColor3f(1.0f, 1.0f, 1.0f);
  glEnable(GL_TEXTURE_2D);
  GLUquadricObj * qobj;
  qobj = gluNewQuadric();
  glLineWidth(1);
  glPushMatrix();
    glTranslated(tx, ty, tz);
    glRotated(-90.0, 1, 0, 0);
    glPushMatrix();
      glBindTexture(GL_TEXTURE_2D, bomb_sphere);
      gluQuadricTexture(qobj, true);
      gluQuadricNormals(qobj, GL_SMOOTH);
      gluSphere(qobj, 1, 15, 15);
    glPopMatrix();
    
    gluDeleteQuadric(qobj);
    glDisable(GL_TEXTURE_2D);


    glPushMatrix();
      glTranslated(0, 1, 0);
      glRotatef(90, 1, 0, 0);
      glColor3f(0.0f, 0.0f, 0.0f);
      glScaled(1, 1, 2);
      glutWireTorus(0.1, 0.15, 10, 10);
    glPopMatrix();

    glPushMatrix();
      glColor3f(1.0f, 1.0f, 1.0f);
      glLineWidth(10);
      glTranslated(0, 1, 0);
      glBegin(GL_LINE_STRIP);
      glVertex3f(0, 0, 0);
      glVertex3f(0, 0.5, 0);
      glEnd();
      
      glColor3f(1.0f, 0.0f, 0.0f);
      glBegin(GL_LINE_STRIP);
      glVertex3f(0, 0.5, 0);
      glVertex3f(0, 0.55, 0);
      glEnd();
      
      glColor3f(1.0f, 0.64f, 0.0f);
      glBegin(GL_LINE_STRIP);
      glVertex3f(0, 0.55, 0);
      glVertex3f(0, 0.59, 0);
      glEnd();
      
      glColor3f(1.0f, 1.0f, 0.0f);
      glBegin(GL_LINE_STRIP);
      glVertex3f(0, 0.59, 0);
      glVertex3f(0, 0.62, 0);
      glEnd();
    glPopMatrix();

  glPopMatrix();
  
  glLineWidth(1);
  glColor3f(1, 1, 1);
}

void draw1Dynamite(float tx, float ty, float tz){
  glPushMatrix();
    glTranslated(tx, ty, tz);
    glPushMatrix();
      glScaled(1, 1, 7);
      glutSolidTorus(0.09, 0.09, 15, 15);
    glPopMatrix();

    glPushMatrix();
      glColor3f(0, 0, 0);
      glLineWidth(4);
      glTranslated(0, 0, 0);
      glBegin(GL_LINE_STRIP);
      glVertex3f(0, 0, 0.7);
      glVertex3f(0, 0, 0);
      glEnd();
      glLineWidth(1);
    glPopMatrix();
  glPopMatrix();
  glColor3f(1, 1, 1);
}

void drawDynamite(float tx, float ty, float tz){
glPushMatrix();
glTranslated(tx, ty, tz);
glScaled(2, 1, 1);
glRotatef(90,0,1,0);
  glPushMatrix();
  draw1Dynamite(0, 0, 0);
  glPopMatrix();

  glPushMatrix();
  glTranslated(0.3, 0, 0);
  draw1Dynamite(0, 0, 0);
  glPopMatrix();

  glPushMatrix();
  glTranslated(-0.3, 0, 0);
  draw1Dynamite(0, 0, 0);
  glPopMatrix();

  glPushMatrix();
  glTranslated(-0.15, 0.2, 0);
  draw1Dynamite(0, 0, 0);
  glPopMatrix();

  glPushMatrix();
  glTranslated(0.15, 0.2, 0);
  draw1Dynamite(0, 0, 0);
  glPopMatrix();
glPopMatrix();
}

void drawRocket(float tx, float ty, float tz){
  glPushMatrix();
    glTranslated(tx, ty, tz);
    glPushMatrix();
    glScaled(2, 1, 1);
    glRotated(-90, 0, 1, 0);
    glPushMatrix();
    draw1Dynamite(0, 0, 0);
    glPopMatrix();
    
    glPushMatrix();
    glRotated(180, 1, 0, 0);
    glutSolidCone(0.42, 0.5, 15, 15);
    glPopMatrix();
    glColor3f(1, 1, 1);
    glPopMatrix();
  glPopMatrix();
}

void renderObstacles(float rocketTx, float rocketTy, float rocketTz){
    drawRocket(rocketTx, rocketTy, rocketTz);
}