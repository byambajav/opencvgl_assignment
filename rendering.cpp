#include <stdio.h>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <GL/glut.h>

#include "common.hpp"
#include "detection.hpp"
#include "drawing.hpp"
#include "lighting.hpp"
#include "rendering.hpp"
#include "sphere.hpp"

#define TEXHEIGHT 680
#define TEXWIDTH 680
#define TEXNUMBER 3

double ShiftX = 0.0;
double ShiftY = 0.0;
double Distance = 30.0;

int time_counter = 0;

bool LeftButtonOn = false;
bool RightButtonOn = false;

GLuint TextureHandle[TEXNUMBER];

void init_camera_capture(void);
void init_video_capture(void);
void update_video_texture(void);
void init_tv_texture(void);

void init(void){
  glClearColor(0.0, 0.0, 0.0, 0.0);
  init_tv_texture();
  init_video_capture();
  init_camera_capture();
  TextureHandle[1] = init_sphere_texture("earth.raw");
  TextureHandle[2] = init_sphere_texture("moon.bmp");
}

void glut_keyboard(unsigned char key, int x, int y){
  switch(key){ 
  case 'q':
  case 'Q':
  case '\033':
    exit(0);
    break;
  }
  
  glutPostRedisplay(); // refreshes displayed image
}

void glut_display(void){
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  const double k = 8.0;
  double zNear = Distance / k, zFar = 100.0;
  double x = 8.0, y = 4.5;
  glFrustum((-x + ShiftX)/k, (x + ShiftX)/k, (-y + ShiftY)/k, (y + ShiftY)/k, zNear, zFar);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(x - ShiftX, y - ShiftY, Distance, x - ShiftX, y - ShiftY, 0.0, 0.0, 1.0, 0.0);
  
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glShadeModel(GL_SMOOTH);
  glEnable(GL_DEPTH_TEST);
  
  // Draws earth and moon
  static int angle = 0;
  glPushMatrix();
  glTranslatef(3.0, 5.0, -3.0);
  glColor3fv(midnightBlue);
  draw_line(-3.0);
  display_sphere(1.0, TextureHandle[1], angle+=10); // earth
  glPopMatrix();
  
  glPushMatrix();
  glTranslatef(3.0 + 2 * sin(angle * (PI / 180) / 28.0), 5.0, -3.0 + 2 * cos(angle * (PI / 180) / 28.0));
  display_sphere(0.3, TextureHandle[2], 0); // moon
  glPopMatrix();
  
  set_lights(time_counter);
  
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHT1);
  glEnable(GL_LIGHT2);
  glEnable(GL_LIGHT3);
  glEnable(GL_LIGHT4);
  
  // Draws video output
  glPushMatrix();
  glTranslatef(14.0, 6.0, -13.0);
  glScalef(-4.0, -3.0, 1.0);
  draw_tv(TextureHandle[0]);
  glPopMatrix();
  
  draw_builtin_shapes();
  
  glPushMatrix();
  glTranslatef(0.0, 0.0, -1.0);
  draw_walls();
  glPopMatrix();
  
  glFlush();
  
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_LIGHT0);
  glDisable(GL_LIGHT1);
  glDisable(GL_LIGHT2);
  glDisable(GL_LIGHT3);
  glDisable(GL_LIGHT4);
  glDisable(GL_LIGHTING);
  
  glutSwapBuffers();
}

void glut_idle(void){
  update_video_texture();
  if (shake_enabled){
    time_counter++;
  }
  
  glutPostRedisplay();
}

cv::VideoCapture camera;
cv::VideoCapture video;

void init_camera_capture(void){
  camera.open(1);
  if (!camera.isOpened()){
    camera.open("harlemshake.mp4");
  }
}

void init_video_capture(void){
  video.open("harlemshake.mp4");
  if (!video.isOpened()){
    exit(1);
  }
}

void init_tv_texture(){  
  glGenTextures(TEXNUMBER, TextureHandle);
  for (int i = 0; i < TEXNUMBER; i++){
    glBindTexture(GL_TEXTURE_2D, TextureHandle[i]);
    
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TEXWIDTH, TEXHEIGHT,
		 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  }
}

void update_video_texture(){
  cv::Mat input;
  if (!shake_enabled){
    camera >> input;
  }
  else {
    video >> input;
    if (input.empty()){
      init_video_capture();
      video >> input;
    }
  }
  
  glBindTexture(GL_TEXTURE_2D, TextureHandle[0]);
  glTexSubImage2D(GL_TEXTURE_2D, 0,
		  (TEXWIDTH - input.cols) / 2,
		  (TEXHEIGHT - input.rows) / 2,
		  input.cols, input.rows,
		  GL_RGB, GL_UNSIGNED_BYTE, input.data);
}

void reset_video_texture(void){
  cv::Mat black = cv::Mat::zeros(TEXHEIGHT, TEXWIDTH, CV_32F);
  glBindTexture(GL_TEXTURE_2D, TextureHandle[0]);
  glTexSubImage2D(GL_TEXTURE_2D, 0,
		  (TEXWIDTH - black.cols) / 2,
		  (TEXHEIGHT - black.rows) / 2,
		  black.cols, black.rows,
		  GL_RGB, GL_UNSIGNED_BYTE, black.data);
}
