#ifndef COMMON_H
#define COMMON_H

#include <GL/glut.h>
extern GLfloat midnightBlue[4];

extern double ShiftX; // Head shift from center in x coordinate
extern double ShiftY; // Head shift from center in y coordinate
extern double Distance; // Determined head distance from display
extern bool shake_enabled; // If shake mode is enabled by user by clicking on menu
extern bool threedmode_enabled; // If 3D mode is enabled by user by clicking on menu
extern int time_counter; // Increments in each glut_idle() call if shake mode is enable

// For playing audio
#define LENGTH 0.5 // number of seconds
#define RATE 44100 // sampling rate
#define SIZE 2 // size of sample in bytes
#define CHANNELS 1 // number of channels

#define PI 3.1415926535897

inline bool isPrimeNumber(int num){
  if (num == 1 || num == 4 || num == 0) return false;
  for (int i = 2; i < (num / 2); ++i){
    if ((num % i) == 0) return false;
  }
  
  return true;
}

inline int min(int a, int b){
  return a > b ? b : a;
}

#endif
