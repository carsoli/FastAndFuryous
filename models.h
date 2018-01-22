#ifndef MODELS_H 
#define MODELS_H

void loadModelAssets();
//help
void drawEars(float headRad);
void drawEyes();
void drawCircle(float r, float steps);

//coyote
void drawCoyote(float coyoteY, float coyoteZ, float coyoteSideAng, float coyoteUpAng, float oscillateY, bool thirdCam, bool redNose);

void drawCoyoteEyes();
void drawCoyoteFullHead(bool redNose);
void drawCoyoteBody();
void drawCoyoteLegs();
void drawCoyoteArms();
void drawCoyoteTail();
void drawCoyoteSnout();

//road runner
void drawRoadRunner(float roadRunnerOscillate, bool roadRunnerAvoiding, bool roadRunnerJump);
void drawRRTail();
void drawRRLegs(bool roadRunnerAvoiding);
void drawRRBody(); 
void drawRRNeck();
void drawRRHead();
void drawRREyes();


#endif