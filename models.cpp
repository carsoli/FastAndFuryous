#include "TextureBuilder.h"
#include <glut.h>
#include <math.h>
#include "models.h"

#define PI 3.14159
#define rgbD 1/255.0 

//GLuint tex_grass;
float innerEarR, innerEarG, innerEarB, outerEarR, outerEarG, outerEarB, headR, headG, headB, noseR, noseG, noseB;
float scleraR=1, scleraG=1, scleraB=1; //default is whitef 
float roadRunnerLegsRot = 0;
float coyoteLegsAng = 0;
bool coyoteLegsBackwards = true;

void loadModelAssets(){
}

void drawCoyoteEars(){//ears
  glPushMatrix();
  glTranslated(0, 1, 0);
  glPushMatrix();
  glColor3f(0.627, 0.322, 0.176);
  glRotated(-90.0, 1, 0, 0);
  glTranslated(0.4, 0, 2.3);
  glScaled(0.1, 0.2, 0.9);
  glutSolidSphere(1, 15, 15);
  glPopMatrix();

  glPushMatrix();
  glColor3f(0.627, 0.322, 0.176);
  glRotated(-90.0, 1, 0, 0);
  glTranslated(-0.4, 0, 2.3);
  glScaled(0.1, 0.2, 0.9);
  glutSolidSphere(1, 15, 15);
  glPopMatrix();
  glPopMatrix();
}

void drawCoyoteEyes(){//eyes
  scleraR = 1;
  scleraG = 1;
  scleraB = 0;
  glPushMatrix();
    glTranslated(0, 2.4, 0.5);
    glScaled(1, 1.5, 0.8);
    glRotatef(-90, 0, 1, 0);
    drawEyes();
  glPopMatrix();
}

void drawCoyoteSnout(){//snout
  glPushMatrix();
  glColor3f(0.961, 0.871, 0.702);
  glTranslated(0, 1.7, 0.9);
  glScaled(0.4, 0.4, 0.8);
  glutSolidSphere(1, 15, 15);
  glPopMatrix();

  glPushMatrix();
  //glColor3f(1, 0, 0);
  glColor3f(0.961, 0.871, 0.702);
  glRotated(-90, 0, 1, 0);
  glTranslated(0.2, 1.7, 0.35);
  glScaled(0.4, 0.5, 0.7);
  glutSolidSphere(1, 15, 15);
  glPopMatrix();

  glPushMatrix();
  glColor3f(0.961, 0.871, 0.702);
  glRotated(90, 0, 1, 0);
  glTranslated(-0.2, 1.7, 0.35);
  glScaled(0.4, 0.5, 0.7);
  glutSolidSphere(1, 15, 15);
  glPopMatrix();
  //snout
}

void drawCoyoteFullHead(bool redNose){
  //Full head
  glPushMatrix();

  glScaled(1, 0.85, 1);

  drawCoyoteSnout();
  //nose
  glPushMatrix();
  if (redNose){
    glColor3f(1, 0, 0);
  }
  else {
    glColor3f(0, 0, 0);
  }
  glTranslated(0, 1.8, 1.8);
  glScaled(1, 0.8, 1);
  glutSolidSphere(0.2, 15, 15);
  glPopMatrix();

  //head
  glPushMatrix();
  glColor3f(0.627, 0.322, 0.176);
  glRotated(-90.0, 1, 0, 0);
  glScaled(0.8, 0.7, 1.5);
  glTranslated(0, 0, 1.4);
  glutSolidSphere(0.8, 15, 15);
  glPopMatrix();

  drawCoyoteEyes();
  drawCoyoteEars();
  glPopMatrix();
  //full head end
  glColor3f(1, 1, 1);

}

void drawCoyoteBody(){//full body
  glPushMatrix();
  glColor3f(0.627, 0.322, 0.176);
  glTranslated(0, -0.2, 0);
  glRotated(-90.0, 1, 0, 0);
  glScaled(0.7, 0.7, 1.5);
  glutSolidCone(0.7, 1.8, 15, 15);
  glPopMatrix();

  glPushMatrix();
  glTranslated(0, -0.5, 0);
  glRotated(-90.0, 1, 0, 0);
  glScaled(0.95, 0.95, 1.4);
  glutSolidSphere(0.55, 15, 15);
  glPopMatrix();
  glColor3f(1, 1, 1);
}

void drawCoyoteLegs(){//legs+feet
  glColor3f(0.627, 0.322, 0.176);
  if (coyoteLegsBackwards){
    coyoteLegsAng += 2;
    if (coyoteLegsAng > 50){
      coyoteLegsBackwards = false;
    }
  }
  else{
    coyoteLegsAng -= 4;
    if (coyoteLegsAng < -45){
      coyoteLegsBackwards = true;
    }
  }

  glPushMatrix(); 
    //LEFT
    glPushMatrix();
      glPushMatrix();
        glTranslated(0.3, -1.5, 0);
        glRotated(coyoteLegsAng, 1, 0, 0);
        glRotated(-90.0, 1, 0, 0);
        glScaled(0.2, 0.2, 0.7);
        glutSolidSphere(1, 15, 15);
      glPopMatrix();
      
      glPushMatrix();
        glRotated(coyoteLegsAng/8, 1, 0, 0);
        glTranslated(0.3, -2, 0.1);
        glScaled(1, 0.7, 1);
        glutSolidSphere(0.35, 15, 15);
      glPopMatrix();
    glPopMatrix();
    
    //RIGHT
    glPushMatrix();
      glPushMatrix();
        glTranslated(-0.3, -1.5, 0);
        glRotated(-coyoteLegsAng, 1, 0, 0);
        glRotated(-90.0, 1, 0, 0);
        glScaled(0.2, 0.2, 0.7);
        glutSolidSphere(1, 15, 15);
      glPopMatrix();
      
      glPushMatrix();
        glRotated(-coyoteLegsAng / 8, 1, 0, 0);
        glTranslated(-0.3, -2, 0.1);
        glScaled(1, 0.7, 1);
        glutSolidSphere(0.35, 15, 15);
      glPopMatrix();
    glPopMatrix();
  glPopMatrix();
  
  glColor3f(1, 1, 1);
}

void drawCoyoteArms(){//arms
  glPushMatrix();
  glColor3f(0.627, 0.322, 0.176);
  glTranslated(0.5, -0.3, 0);
  glRotated(10.0, 0, 0, 1);
  glRotated(-90.0, 1, 0, 0);
  glScaled(1, 1, 1.5);
  glutSolidCone(0.2, 0.7, 15, 15);
  glPopMatrix();

  glPushMatrix();
  glColor3f(0.627, 0.322, 0.176);
  glTranslated(-0.5, -0.3, 0);
  glRotated(-10.0, 0, 0, 1);
  glRotated(-90.0, 1, 0, 0);
  glScaled(1, 1, 1.5);
  glutSolidCone(0.2, 0.7, 15, 15);
  glPopMatrix();

  //hands
  glPushMatrix();
  glColor3f(0.627, 0.322, 0.176);
  glTranslated(0.5, -0.3, 0);
  glRotated(-90.0, 1, 0, 0);
  glScaled(1, 1, 1.5);
  glutSolidSphere(0.2, 15, 15);
  glPopMatrix();

  glPushMatrix();
  glColor3f(0.627, 0.322, 0.176);
  glTranslated(-0.5, -0.3, 0);
  glRotated(-90.0, 1, 0, 0);
  glScaled(1, 1, 1.5);
  glutSolidSphere(0.2, 15, 15);
  glPopMatrix();
  //hands end

  glColor3f(1, 1, 1);
}

void drawCoyoteTail(){
  glPushMatrix();
  glRotated(-20.0, 1, 0, 0);

  glPushMatrix();//wide then narrow then wide then narrow
  glColor3f(0.627, 0.322, 0.176);
  glRotated(180, 0, 1, 0);
  glRotated(90, 1, 0, 0);
  glTranslated(0, 0.8, 0.8);
  int cones = 3;
  for (int i = 0; i < cones; i++){
      glPushMatrix();
      glTranslated(0, 0.2*i, 0);
      glRotated(90, 1, 0, 0);
      glutSolidCone(0.3, 0.5, 10, 10);
      glPopMatrix();
  }
  glPopMatrix();

  glPushMatrix();
  glRotated(180, 1, 0, 0);
  glTranslated(0, 0.8, 0.45 + cones*0.2);
  glutSolidCone(0.2, 0.6, 10, 10);
  glPopMatrix();

  glPopMatrix();

  glColor3f(1, 1, 1);
}

void drawCoyote(float coyoteY, float coyoteZ, float coyoteSideAng, float coyoteUpAng, float oscillateY, bool thirdCam, bool redNose){
    glPushMatrix();
    if (!thirdCam){
        oscillateY = 0;
    }
    else {
        glTranslated(0, oscillateY,0);
    }
    if (coyoteY >= 0){//jumping
      glTranslated(41.6, 4.5 + coyoteY, coyoteZ);//coyote's height is 4.5
      glRotatef(-90+coyoteSideAng, 0, 1, 0);
      glRotatef(-coyoteUpAng, 1, 0, 0);
      glScaled(2, 1.95, 2);
      glRotatef(-coyoteSideAng, 0, 1, 0);
      glRotatef(coyoteUpAng, 1, 0, 0);
      glPushMatrix();
        glRotatef(-coyoteUpAng, 1, 0, 0);
        glRotatef(coyoteSideAng, 0, 1, 0);
        drawCoyoteFullHead(redNose);
      glPopMatrix();
      drawCoyoteBody();
      drawCoyoteArms();
      drawCoyoteTail();
      drawCoyoteLegs();
    } else { //ducking
        glPushMatrix();
          glTranslated(41.6, 4.5 + coyoteY , coyoteZ);//coyote's height is 4.5
          glRotatef(-90, 0, 1, 0);
          glScaled(2, 1.95, 2);
          drawCoyoteFullHead(redNose);
          drawCoyoteBody();
          drawCoyoteArms();
          drawCoyoteTail();
        glPopMatrix();
        //legs 
        glPushMatrix();
          glTranslated(41.6, 4.5, coyoteZ);//coyote's height is 4.5
          glRotatef(-90, 0, 1, 0);
          glScaled(2, 1.95, 2);
        drawCoyoteLegs();
        glPopMatrix();
    }


    glPopMatrix();

    glColor3f(1, 1, 1);
}

void drawCircle(float r, float steps){//on the x-z plane
  float theta, x, z, delta = (2 * PI) / steps;
  glBegin(GL_POINTS);
  glPointSize(1.0);
  for (theta = 0.0; theta < 2 * PI; theta += delta){
      x = r*cos(theta);
      z = r*sin(theta);
      glVertex3f(x, 0, z);
  }
  glEnd();
}

void drawEyes(){
  double irisRad = 0.15;
  double scleraRad = 0.2;
  double pupilRad = 0.1;

  //==right eye
  glPushMatrix();
  glTranslated(0, 0, scleraRad);
  //sclera
  glPushMatrix();
  glColor3f(scleraR, scleraG, scleraB);
  glScaled(1.0, 1.25, 1.0);
  glutSolidSphere(scleraRad, 100, 100);
  glPopMatrix();
  //iris
  glPushMatrix();
  glColor3f(51*rgbD, 25*rgbD, 0);
  glTranslated(scleraRad, 0, 0);
  glutSolidSphere(irisRad, 100, 100);
  glPopMatrix();
  //pupil
  glPushMatrix();
  glColor3f(0, 0, 0);
  glTranslated(scleraRad + 0.5*irisRad, 0, 0);
  glutSolidSphere(pupilRad, 100, 100);
  glPopMatrix();
  glPopMatrix();

  //==left eye
  glPushMatrix();
  glTranslated(0, 0, - scleraRad);
  //sclera
  glPushMatrix();
  glColor3f(255 * rgbD, 250 * rgbD, 35 * rgbD);
  glScaled(1.0, 1.25, 1.0);
  glutSolidSphere(scleraRad, 100, 100);
  glPopMatrix();
  //iris
  glPushMatrix();
  glColor3f(51 * rgbD, 25 * rgbD, 0);
  glTranslated(scleraRad, 0, 0);
  glutSolidSphere(irisRad, 100, 100);
  glPopMatrix();
  //pupil
  glPushMatrix();
  glColor3f(0, 0, 0);
  glTranslated(scleraRad + 0.5*irisRad, 0, 0);
  glutSolidSphere(pupilRad, 100, 100);
  glPopMatrix();
  glPopMatrix();
}

void drawEars(float headRadius){
    //y-z plane equation, x = 0
    GLdouble eqn[4] = { -1.0, 0.0, 0.0, 0.0 };
    //left ear
    glPushMatrix();
    glTranslated(headRadius*0.5, 0, headRadius + 0.5);
    glRotatef(-30.0, 1, 0, 0);
    //spherical part    
    glPushMatrix();
    glColor3f(innerEarR, innerEarG, innerEarB);
    glClipPlane(GL_CLIP_PLANE0, eqn);
    glEnable(GL_CLIP_PLANE0);
    glScaled(0.8, 1.8, 2.2);
    glutWireSphere(0.1, 250, 250);
    glDisable(GL_CLIP_PLANE0);
    glPopMatrix();
    //outer cartiladge
    glPushMatrix();
    glColor3f(outerEarR, outerEarG, outerEarB);
    glScaled(0.8, 1.8, 2.5);
    glRotatef(90.0, 0, 1, 0);
    glutSolidTorus(0.02, 0.1, 100, 100);
    glPopMatrix();
    glPopMatrix();

    //right ear
    glPushMatrix();
    glTranslated(headRadius*0.5, 0, -headRadius - 0.5);
    glRotatef(30.0, 1, 0, 0);
    //spherical part    
    glPushMatrix();
    glColor3f(innerEarR, innerEarG, innerEarB);
    glClipPlane(GL_CLIP_PLANE0, eqn);
    glEnable(GL_CLIP_PLANE0);
    glScaled(0.8, 1.8, 2.2);
    glutWireSphere(0.1, 250, 250);
    glDisable(GL_CLIP_PLANE0);
    glPopMatrix();
    //outer cartiladge
    glPushMatrix();
    glColor3f(outerEarR, outerEarG, outerEarB);
    glScaled(0.8, 1.8, 2.5);
    glRotatef(90.0, 0, 1, 0);
    glutSolidTorus(0.02, 0.1, 100, 100);
    glPopMatrix();
    glPopMatrix();
}


void drawRREyes(){
    double irisRad = 1;
    double scleraRad = 1;
    double pupilRad = 1;

    //==right eye
    glPushMatrix();
    glTranslated(0, 0, scleraRad);

    //iris
    glPushMatrix();
    glColor3f(1, 1, 1);
    glTranslated(scleraRad, 0, 0);
    glutSolidSphere(irisRad, 100, 100);
    glPopMatrix();
    //pupil
    glPushMatrix();
    glColor3f(0, 0, 0);
    glTranslated(scleraRad + 0.5*irisRad, 0, 0);
    glutSolidSphere(pupilRad, 100, 100);
    glPopMatrix();
    glPopMatrix();

    //==left eye
    glPushMatrix();
    glTranslated(0, 0, -scleraRad);
    //iris
    glPushMatrix();
    glColor3f(1, 1, 1);
    glTranslated(scleraRad, 0, 0);
    glutSolidSphere(irisRad, 100, 100);
    glPopMatrix();
    //pupil
    glPushMatrix();
    glColor3f(0, 0, 0);
    glTranslated(scleraRad + 0.5*irisRad, 0, 0);
    glutSolidSphere(pupilRad, 100, 100);
    glPopMatrix();
    glPopMatrix();

}
void drawRRHead(){
    glPushMatrix();

    glColor3f(0, 0.5, 1);
    glPushMatrix();
    glScaled(0.02, 0.02, 0.02);
    glutSolidSphere(1, 15, 15);
    glPopMatrix();

    glColor3f(1, 1, 0);
    glPushMatrix();
    glTranslated(-0.015, 0, 0);
    glRotated(-90, 0, 1, 0);
    glutSolidCone(0.012, 0.02, 15, 15);
    glPopMatrix();

    glColor3f(0, 0, 1);
    glPushMatrix();
    glTranslated(0.01, 0.07, 0);
    glRotated(90, 1, 0, 0);
    glutSolidCone(0.01, 0.08, 15, 15);
    glPopMatrix();

    glPushMatrix();
    glScaled(0.01, 0.01, 0.01);
    glTranslated(0.01, 0.7, 0);
    glRotated(180, 0, 1, 0);
    drawRREyes();
    glPopMatrix();

    glPopMatrix();

}

void drawRRNeck(){
    glPushMatrix();
    glColor3f(0, 0.5, 1);
    glTranslated(0, -0.07, 0);
    glRotated(90, 1, 0, 0);
    glScaled(1, 1, 8);
    glutSolidTorus(0.01, 0, 15, 15);
    glPopMatrix();
}
void drawRRBody(){
    glColor3f(0, 0.5, 1);
    glPushMatrix();
    glTranslated(0.03, -0.13, 0);
    glScaled(0.05, 0.03, 0.05);
    glutSolidSphere(1, 15, 15);
    glPopMatrix();
}

void drawRRLegs(bool roadRunnerAvoiding){
  glPushMatrix();
    if (!roadRunnerAvoiding){
      if (roadRunnerLegsRot >= 50){//(ranges from -5 to 50)
        roadRunnerLegsRot = -5; //reset to -5  
      }
      roadRunnerLegsRot += 2.5;
    }
    glPushMatrix();
      //right
      if (roadRunnerAvoiding){
        roadRunnerLegsRot = -5; //reset to -5  
        glTranslated(0.02, -0.17, -0.02);
        glRotatef(50, 1, 0, 0); //avoid obstacle rot angle
        glTranslated(-0.02, 0.17, 0.02);
      
      }
      glPushMatrix();
        glColor3f(1, 1, 0);
        glTranslated(0.02, -0.17, -0.02);
        glRotatef(roadRunnerLegsRot, 0, 0, 1);//as if running
        glRotated(90, 1, 0, 0);
        glScaled(0.005, 0.005, 6 * 0.005);
        glutSolidTorus(1, 0, 15, 15);
      glPopMatrix();
      
      glPushMatrix(); //foot
        glRotatef(roadRunnerLegsRot/8, 0, 0,1); //as if running
        glTranslated(0.02, -0.2, -0.02);
        glScaled((1 * 0.015), (0.2*0.015), (1 * 0.015));
        glRotated(90, 1, 0, 0);
        glutSolidSphere(1, 15, 15);
      glPopMatrix();
    glPopMatrix();
    
    glPushMatrix();
      //left
      if (roadRunnerAvoiding){
        glTranslated(0.02, -0.17, 0.02);
        glRotatef(-50, 1, 0, 0); //avoid obstacle rot angle
        glTranslated(-0.02, 0.17, -0.02);
      }
      glPushMatrix();
        glColor3f(1, 1, 0);
        glTranslated(0.02, -0.17, 0.02);
        glRotatef(roadRunnerLegsRot, 0, 0, 1);//as if running
        glRotated(90 , 1, 0, 0);
        glScaled(1, 1, 6);
        glutSolidTorus(0.005, 0, 15, 15);
      glPopMatrix();
      
      glPushMatrix();//foot
        glRotatef(roadRunnerLegsRot / 8, 0, 0, 1); //as if running
        glTranslated(0.02, -0.2, 0.02);
        glScaled((1 * 0.015), (0.2*0.015), (1 * 0.015));
        glRotated(90, 1, 0, 0);
        glutSolidSphere(1, 15, 15);
      glPopMatrix();
    glPopMatrix();

  glPopMatrix();
}

void drawRRTail(){
  glColor3f(0, 0, 1);
  glPushMatrix();
  glTranslated(0.07, -0.02, 0);
  glRotated(90, 1, 0, 0);
  glutSolidCone(0.02, 0.1, 15, 15);
  glPopMatrix();
}

void drawRoadRunner(float roadRunnerOscillate, bool roadRunnerAvoiding, bool roadRunnerJump){
  glPushMatrix();
  if (roadRunnerAvoiding){
      if (roadRunnerJump){//else: case of rocket 
        glTranslated(0, 3, 0);
      }
  }
  glTranslated(0, 4 + roadRunnerOscillate, 0);
  glScaled(20,20,20);
  drawRRHead();
  drawRRNeck();
  drawRRBody();
  drawRRLegs(roadRunnerAvoiding);
  drawRRTail();
  glPopMatrix();
}