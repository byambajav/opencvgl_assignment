#include <GL/glut.h>
#include <omp.h>
#include <unistd.h>
#include <iostream>
#include <fstream>

#include "common.hpp"
#include "detection.hpp"
#include "menu.hpp"
#include "playsound.hpp"
#include "rendering.hpp"

#define AUDIO_ARRAYSIZE (LENGTH * RATE * CHANNELS)

bool shake_enabled = false;
bool threedmode_enabled = true;

int main(int argc, char *argv[])
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
  //glutGameModeString("1024x768:32@60");
  glutGameModeString("1366x768:32@60");
  glutEnterGameMode();
  init();
  
  glutCreateMenu(select_menu);
  glutAddMenuEntry("Do Harlem Shake\n", MENU_SHAKE);
  glutAddMenuEntry("Disable 3D Mode\n", MENU_3DMODE);
  glutAttachMenu(GLUT_RIGHT_BUTTON);
  
  glutDisplayFunc(glut_display);
  glutKeyboardFunc(glut_keyboard);
  glutIdleFunc(glut_idle);
  
#pragma omp parallel num_threads(3)
  {
    if (omp_get_thread_num() == 0){
      // This thread runs glutMainLoop
      glutMainLoop();
    }
    
    if (omp_get_thread_num() == 1){
      // This thread updates head position using OpenCV
      detection_init();
      while(1){
	if (threedmode_enabled){
	  detection(); // Update head position
	}
	else {
	  usleep(300);
	}
      }
    }
    
    if (omp_get_thread_num() == 2){
      // This thread plays audio
      short audio[(int)AUDIO_ARRAYSIZE];
      std::ifstream audio_file("harlemshake.wav");
      int output = init_audio_output();
      if (output >=0){ // If playing audio is supported
	while (1){
	  if (shake_enabled){
	    audio_file.read((char *)audio, sizeof(short) * AUDIO_ARRAYSIZE);
	    if (!audio_file){
	      audio_file.seekg(0, std::ios::beg); // play from start again
	    }
	    else {
	      write_output(audio, output);
	    }
	  }
	  else {
	    usleep(300);
	  }
	}
      }
    }
  }
  
  return 0;
}
