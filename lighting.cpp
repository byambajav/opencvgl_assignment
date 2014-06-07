#include <math.h>
#include <GL/glut.h>

#include "common.hpp"
#include "drawing.hpp"

void set_lights(int time_counter){
  GLfloat lightpos0[] = {8.0f + 2.0f * (float)sin(time_counter / 10.0), 8.0, -8.0f + 2.0f * (float)cos(time_counter / 10.0), 1.0f};
  GLfloat diffuse0[] = {1.0, 1.0, 1.0, 1.0};
  
  GLfloat lightpos1[] = {5.0, 5.0, -10.0, 1.0};
  GLfloat diffuse1[] = {1.0, 0.0, 0.0, 1.0};
  GLfloat dirVector1[]={(float)sin(time_counter / 5.0), (float)cos(time_counter / 5.0), 0.0, 0.0};
  
  GLfloat lightpos2[] = {7.0, 7.0, -8.0, 1.0};
  GLfloat diffuse2[] = {0.0, 1.0, 0.0, 1.0};
  GLfloat dirVector2[]={(float)sin(time_counter / 7.0), (float)cos(time_counter / 7.0), 0.0, 0.0};

  GLfloat lightpos3[] = {9.0, 5.0, -13.0, 1.0};
  GLfloat diffuse3[] = {0.0, 0.0, 1.0, 1.0};
  GLfloat dirVector3[]={(float)sin(time_counter / 9.0), (float)cos(time_counter / 9.0), 0.0, 0.0};
  
  GLfloat lightpos4[] = {8.0, 6.0, 300.0, 1.0};
  
  glLightfv(GL_LIGHT0, GL_POSITION, lightpos0);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse0);
  
  glLightfv(GL_LIGHT1, GL_POSITION, lightpos1);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse1);
  glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 30.0);
  glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, dirVector1); 
  glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 1);
  
  glLightfv(GL_LIGHT2, GL_POSITION, lightpos2);
  glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse2);
  glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 30.0);
  glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, dirVector2); 
  glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 1);
  
  glLightfv(GL_LIGHT3, GL_POSITION, lightpos3);
  glLightfv(GL_LIGHT3, GL_DIFFUSE, diffuse3);
  glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 30.0);
  glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, dirVector3); 
  glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, 1);
  
  
  glLightfv(GL_LIGHT4, GL_POSITION, lightpos4);
  glLightfv(GL_LIGHT4, GL_DIFFUSE, diffuse0);
  
  glPushMatrix();
  glColor3d(1.0, 1.0, 1.0);
  glTranslatef(lightpos0[0], lightpos0[1], lightpos0[2]);
  glutSolidSphere(0.3, 50, 50);
  glPopMatrix();
  
  GLfloat brown[3] = {0.647, 0.164, 0.164};
  GLfloat darkOliveGreen[3] = {0.333, 0.420, 0.184};
  GLfloat midnightBlue[3] = {0.098, 0.098, 0.439};
  
  glPushMatrix();
  glTranslatef(lightpos1[0], lightpos1[1], lightpos1[2]);
  draw_line(lightpos1[2], brown);
  glRotatef(-(time_counter / 5.0) / PI * 180, 0, 0, 1);
  glRotatef(90, 1, 0, 0);
  glTranslatef(0.0, 0.5, 0.0);
  draw_lamp(brown);
  glPopMatrix();
  
  glPushMatrix();
  glTranslatef(lightpos2[0], lightpos2[1], lightpos2[2]);
  draw_line(lightpos2[2], darkOliveGreen);
  glRotatef(-(time_counter / 7.0) / PI * 180, 0, 0, 1);
  glRotatef(90, 1, 0, 0);
  glTranslatef(0.0, 0.5, 0.0);
  draw_lamp(darkOliveGreen);
  glPopMatrix();
  
  glPushMatrix();
  glTranslatef(lightpos3[0], lightpos3[1], lightpos3[2]);
  draw_line(lightpos3[2], midnightBlue);
  glRotatef(-(time_counter / 9.0) / PI * 180, 0, 0, 1);
  glRotatef(90, 1, 0, 0);
  glTranslatef(0.0, 0.5, 0.0);
  draw_lamp(midnightBlue);
  glPopMatrix();
}
