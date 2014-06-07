#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

#include "common.hpp"

typedef struct 
{
  double X;
  double Y;
  double Z;
  double U;
  double V;
} Vertices;

const int space = 6;
const int vertex_count = (90 / space) * (360 / space) * 4;
Vertices Vertex[vertex_count];

void display_sphere (double R, GLuint texture, int angle){
  int i;
  glEnable(GL_TEXTURE_2D);
  glColor3f(1, 1, 1);
  glScalef (R, R, R);
  glRotatef(angle, 0, 1, 0);
  glRotatef (90, 1, 0, 0);
  glBindTexture (GL_TEXTURE_2D, texture);
  glBegin(GL_TRIANGLE_STRIP);
  
  for (i = 0; i <= vertex_count; i++){
    glTexCoord2f (Vertex[i].U, Vertex[i].V);
    glVertex3f (Vertex[i].X, Vertex[i].Y, -Vertex[i].Z);
  }
  
  for (i = 0; i <= vertex_count; i++){
    glTexCoord2f (Vertex[i].U, -Vertex[i].V);
    glVertex3f (Vertex[i].X, Vertex[i].Y, Vertex[i].Z);
  }
  glEnd();
  glDisable(GL_TEXTURE_2D);
}

void create_sphere (double R, double H, double K, double Z) {
  int n = 0;
  double a;
  double b;
  
  for( b = 0; b <= 90 - space; b+=space){
    for( a = 0; a <= 360 - space; a+=space){
      Vertex[n].X = R * sin((a) / 180 * PI) * sin((b) / 180 * PI) - H;
      Vertex[n].Y = R * cos((a) / 180 * PI) * sin((b) / 180 * PI) + K;
      Vertex[n].Z = R * cos((b) / 180 * PI) - Z;
      Vertex[n].V = (2 * b) / 360;
      Vertex[n].U = (a) / 360;
      n++;
      
      Vertex[n].X = R * sin((a) / 180 * PI) * sin((b + space) / 180 * PI) - H;
      Vertex[n].Y = R * cos((a) / 180 * PI) * sin((b + space) / 180 * PI) + K;
      Vertex[n].Z = R * cos((b + space) / 180 * PI) - Z;
      Vertex[n].V = (2 * (b + space)) / 360;
      Vertex[n].U = (a) / 360;
      n++;
      
      Vertex[n].X = R * sin((a + space) / 180 * PI) * sin((b) / 180 * PI) - H;
      Vertex[n].Y = R * cos((a + space) / 180 * PI) * sin((b) / 180 * PI) + K;
      Vertex[n].Z = R * cos((b) / 180 * PI) - Z;
      Vertex[n].V = (2 * b) / 360;
      Vertex[n].U = (a + space) / 360;
      n++;
      
      Vertex[n].X = R * sin((a + space) / 180 * PI) * sin((b + space) / 180 * PI) - H;
      Vertex[n].Y = R * cos((a + space) / 180 * PI) * sin((b + space) / 180 * PI) + K;
      Vertex[n].Z = R * cos((b + space) / 180 * PI) - Z;
      Vertex[n].V = (2 * (b + space)) / 360;
      Vertex[n].U = (a + space) / 360;
      n++;
    }
  }
}

GLuint init_sphere_texture(const char* filename)
{
  GLuint texture;
  int width, height;
  unsigned char * data;
  FILE * file;
  file = fopen(filename, "rb");
  
  if ( file == NULL ) return 0;
  width = 1024;
  height = 512;
  data = (unsigned char *)malloc( width * height * 3 );
  fread(data, width * height * 3, 1, file);
  fclose(file);
  glGenTextures(1, &texture); 
  glBindTexture(GL_TEXTURE_2D, texture);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); 
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  
  gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
  free(data);
  
  create_sphere(1, 0, 0, 0);
  return texture;
}
