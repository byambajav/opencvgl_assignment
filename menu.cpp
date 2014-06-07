#include <GL/glut.h>

#include "common.hpp"
#include "menu.hpp"
#include "rendering.hpp"

void select_menu(int command){
  switch (command)
    {
    case MENU_SHAKE:
      shake_enabled = shake_enabled ? false : true;
      glutChangeToMenuEntry(1, shake_enabled ? "Stop Harlem Shake!\n" : "Do Harlem Shake\n", MENU_SHAKE);
      reset_video_texture();
      break;
    case MENU_3DMODE:
      threedmode_enabled = threedmode_enabled ? false : true;
      glutChangeToMenuEntry(2, threedmode_enabled ? "Disable 3D Mode\n" : "Enable 3D Mode\n", MENU_3DMODE);
      break;
    }
  
  glutPostRedisplay();
}
