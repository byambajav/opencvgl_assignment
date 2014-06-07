#ifndef DRAWING_H
#define DRAWING_H

void draw_walls();
void draw_lamp(GLfloat color[4]);
void draw_tv(GLuint textureHandle);
void draw_builtin_shapes();
void draw_line(double z, GLfloat color[3] = NULL);

#endif
