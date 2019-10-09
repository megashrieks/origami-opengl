#include"statemanager.h"
#include"types.h"
#include<GL/glut.h>
extern window wh;
void stateChange(unsigned char key, int x, int y){
    if(key == ' ') wh.state += 1;
    wh.global_interpolation = 0;
    glutPostRedisplay();
}


void sequential(){
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, wh.width, 0, wh.height);
    if(!wh.state)
        displayText();
    else if(wh.state)
        displayOrigami();
    glFlush();
}
