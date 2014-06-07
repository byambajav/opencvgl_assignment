#ifndef RENDER_H
#define RENDER_H

void init(void);
void glut_display(void);
void glut_keyboard(unsigned char key, int x, int y);
void glut_mouse(int button, int state, int x, int y);
void glut_idle(void);
void reset_video_texture(void);

#endif
