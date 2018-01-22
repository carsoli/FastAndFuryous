#ifndef CAMERA_H    
#define CAMERA_H

void setupCamera(int w, int h);
void updateCamera();
void lookUp();
void lookDown();
void lookRight();
void lookLeft();
void moveCameraLeft();
void moveCameraRight();
char switchCamera(float cy, float cz); 
char switchCamera(int perspective, float cy, float cz);
void resetCamera();
void resetCameraTimed(int value);
void moveCameraDown();
void moveCameraUp();

void oscillateCamera();
#endif