#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

#include "common.hpp"

GLfloat white[4] = {1.0, 1.0, 1.0, 0.8};
GLfloat black[4] = {0.0, 0.0, 0.0, 0.8};
GLfloat silver[4] = {0.753, 0.753, 0.753, 0.8};
GLfloat midnightBlue[4] = {0.098, 0.098, 0.439, 0.8};
GLfloat brown[4] = {0.647, 0.164, 0.164, 0.8};
GLfloat darkOliveGreen[4] = {0.333, 0.420, 0.184, 0.8};

//-----------------------------------------------------------------------------
//-> draw_line:
//-> -> Draws line from a object to wall in given color.
//-> -> z: the object's z axis coordinate.
//-----------------------------------------------------------------------------
void draw_line(double z, GLfloat color[3] = NULL){
  if (color != NULL){
    glColor3fv(color);
  }
  for (double u = 0; u > -16.0 - z; u -= 1.5){
    glPushMatrix();
    glTranslatef(0.0, 0.0, u);
    glutSolidSphere(0.06, 50, 50);
    glPopMatrix();
  }
}


//-----------------------------------------------------------------------------
//-> draw_builtin_shapes:
//-> -> Draws Icosahedron, Teapot, Dodecahedron
//-----------------------------------------------------------------------------
void draw_builtin_shapes(){
  glMaterialfv(GL_FRONT, GL_DIFFUSE, darkOliveGreen);
  
  glPushMatrix();
  glTranslatef(5.0, 2.0, 8.0);
  draw_line(8.0);
  glScalef(0.5, 0.5, 0.5);
  glRotatef(time_counter * 3.0, 0, 1, 1);
  glutSolidIcosahedron();
  glPopMatrix();
  
  glPushMatrix();
  glTranslatef(4.0, 3.0, 3.0);
  draw_line(3.0);
  glutSolidTeapot(fabs(sin(time_counter / 16.0 + 0.8)) / 1.5 + 0.2);
  glPopMatrix();
  
  glMaterialfv(GL_FRONT, GL_DIFFUSE, brown);
  glPushMatrix();
  glTranslatef(14.0, 7.0, 6.0);
  draw_line(6.0);
  glScalef(0.2, 0.2, 0.2);
  glRotatef(time_counter * 4.0, 1, 0.2, 1);
  glutSolidDodecahedron();
  glPopMatrix();
}

void draw_cube(double x, double y, double z, double size, GLfloat color[4], GLfloat sticker[4] = NULL){
  GLfloat points[8][3];
  
  // Make vertexes
  for (int i = 0; i < 8; ++i){
    points[i][0] = (i & 1) * size + x;
    points[i][1] = ((i >> 1) & 1) * size + y;
    points[i][2] = ((i >> 2) & 1) * size + z;
  }
  
  // Draw each side
  glBegin(GL_QUADS);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, color);
  
  // far
  glNormal3d(0.0, 0.0, -1.0);
  glVertex3fv(points[0]);
  glVertex3fv(points[1]);
  glVertex3fv(points[3]);
  glVertex3fv(points[2]);
  
  // near
  glNormal3d(0.0, 0.0, 1.0);
  glVertex3fv(points[4]);
  glVertex3fv(points[5]);
  glVertex3fv(points[7]);
  glVertex3fv(points[6]);
  
  // top
  glNormal3d(0.0, 1.0, 0.0);
  glVertex3fv(points[2]);
  glVertex3fv(points[3]);
  glVertex3fv(points[7]);
  glVertex3fv(points[6]);
  
  // bottom
  glNormal3d(0.0, -1.0, 0.0);
  glVertex3fv(points[0]);
  glVertex3fv(points[1]);
  glVertex3fv(points[5]);
  glVertex3fv(points[4]);
  
  // right
  glNormal3d(1.0, 0.0, 0.0);
  glVertex3fv(points[1]);
  glVertex3fv(points[3]);
  glVertex3fv(points[7]);
  glVertex3fv(points[5]);
  
  // left
  glNormal3d(-1.0, 0.0, 0.0);
  glVertex3fv(points[0]);
  glVertex3fv(points[2]);
  glVertex3fv(points[6]);
  glVertex3fv(points[4]);
  
  if (sticker != NULL){
    glMaterialfv(GL_FRONT, GL_DIFFUSE, sticker);
    // near
    glNormal3d(0.0, 0.0, 1.0);
    double width = 0.03;
    points[4][0] += width;
    points[5][0] -= width;
    points[6][0] += width;
    points[7][0] -= width;
    points[4][1] += width;
    points[5][1] += width;
    points[6][1] -= width;
    points[7][1] -= width;
    points[4][2] += width;
    points[5][2] += width;
    points[6][2] += width;
    points[7][2] += width;
    
    glVertex3fv(points[4]);
    glVertex3fv(points[5]);
    glVertex3fv(points[7]);
    glVertex3fv(points[6]);
  }
  
  glEnd();
}

inline double cube_offset(){
  return sin((time_counter) / 15.0);
}

//-----------------------------------------------------------------------------
//-> draw_walls:
//-> -> Draws 5 walls of the room.
//-----------------------------------------------------------------------------
void draw_walls(){
  static bool started = false;
  const int width = 16, height = 9;
  const double cube_size = 1;
  static double offset[width][height];
  
  if (!started){
    for (int i = 0; i < height; ++i){
      for (int j = 0; j < width; ++j){
	offset[j][i] = (double)rand() / RAND_MAX;
      }
    }
    
    started = true;
  }
  
  // far wall
  for (int i = 0; i < height; ++i){
    for (int j = 0; j < width; ++j){
      draw_cube(j * cube_size, i * cube_size, -width * cube_size, cube_size, brown, silver);
    }
  }
  
  // left wall
  for (int i = 0; i < height; ++i){
    for (int j = 0; j < width; ++j){
      if (isPrimeNumber(i * width + 17 * j)){
	draw_cube((cube_offset() * offset[j][i] * offset[j][i] * 4.0  - 1.1) * cube_size, i * cube_size, -j * cube_size, cube_size, brown);
      }
      else {
	draw_cube(-cube_size, i * cube_size, -j * cube_size, cube_size, silver);
      }
    }
  }
  
  // right wall
  for (int i = 0; i < height; ++i){
    for (int j = 0; j < width; ++j){
      if (isPrimeNumber(i * width + j)){
	draw_cube((-cube_offset() * offset[j][i] + width - 0.3) * cube_size, i * cube_size, -j * cube_size, cube_size, midnightBlue);
      }
      else {
	draw_cube(width * cube_size, i * cube_size, -j * cube_size, cube_size, silver);
      }
    }
  }
  
  // floor
  for (int i = 0; i < width; ++i){
    for (int j = 0; j < width; ++j){
      draw_cube(j * cube_size, (sin(min(min(i, width - i - 1), (min(j, width - j - 1))) * PI / width) * sin(time_counter / 8.0) - 1.0) * cube_size, -i * cube_size, cube_size, (i + j) % 2 ? black : white);
    }
  }
  
  // ceiling
  for (int i = 0; i < width; ++i){
    for (int j = 0; j < width; ++j){
      draw_cube(j * cube_size, height * cube_size, -i * cube_size, cube_size, silver);
    }
  }
}

void draw_lamp(GLfloat color[3]){
  glColor3fv(color);
  glutSolidCone(0.3, 1, 50, 50);
}

void draw_tv(GLuint textureHandle){
  GLdouble pointA[] = {0.0, 0.0, 0.0};
  GLdouble pointB[] = {0.0, 1.0, 0.0};
  GLdouble pointC[] = {1.0, 1.0, 0.0};
  GLdouble pointD[] = {1.0, 0.0, 0.0};
  
  glEnable(GL_TEXTURE_2D);
  
  glBindTexture(GL_TEXTURE_2D, textureHandle);
  glColor3d(1.0, 1.0, 1.0);
  glBegin(GL_QUADS);
  glTexCoord2d(0.0, 0.0);
  glVertex3dv(pointA);
  glTexCoord2d(0.0, 1.0);
  glVertex3dv(pointB);
  glTexCoord2d(1.0, 1.0);
  glVertex3dv(pointC);
  glTexCoord2d(1.0, 0.0);
  glVertex3dv(pointD);
  glEnd();
  
  glDisable(GL_TEXTURE_2D);
}
