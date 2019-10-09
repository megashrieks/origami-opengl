#include"utils.h"
#include"types.h"
#include<GL/glut.h>
extern window wh;

int min(int a, int b){ return a < b ? a : b;}
int max(int a, int b){ return a > b ? a : b;}



float lerp(float interpolation, float source, float destination){
    return source*(1-interpolation) + destination * interpolation;
}

vert lerp_vert(float interpolation, vert source, vert destination){
    vert v={
        lerp(interpolation, source.x, destination.x),
        lerp(interpolation, source.y, destination.y),
        lerp(interpolation, source.z, destination.z),
    };
    return v;
}

square lerp_square(float interpolation, square source, square destination){
    square s={
        lerp_vert(interpolation, source.tl,destination.tl),
        lerp_vert(interpolation, source.tr, destination.tr),
        lerp_vert(interpolation, source.bl, destination.bl),
        lerp_vert(interpolation, source.br, destination.br)
    };
    return s;
}

void draw_square(square s){
    glColor3f(1, 1, .5);
    glBegin(GL_POLYGON);
        glVertex3f(s.tl.x, s.tl.y, s.tl.z);
        glVertex3f(s.tr.x, s.tr.y, s.tr.z);
        glVertex3f(s.br.x, s.br.y, s.br.z);
        glVertex3f(s.bl.x, s.bl.y, s.bl.z);
    glEnd();
    glColor3f(0, 0, 1);
    glBegin(GL_LINE_LOOP);
        glVertex3f(s.tl.x, s.tl.y, s.tl.z);
        glVertex3f(s.tr.x, s.tr.y, s.tr.z);
        glVertex3f(s.br.x, s.br.y, s.br.z);
        glVertex3f(s.bl.x, s.bl.y, s.bl.z);
    glEnd();
}





void reshape(GLsizei width, GLsizei height) {  // GLsizei for non-negative integer

    wh.width = width;
    wh.height = height;
   // Compute aspect ratio of the new window
   if (height == 0) height = 1;                // To prevent divide by 0
   GLfloat aspect = (GLfloat)width / (GLfloat)height;

   // Set the viewport to cover the new window
   glViewport(0, 0, width, height);

   // Set the aspect ratio of the clipping volume to match the viewport
   glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
   glLoadIdentity();             // Reset
   // Enable perspective projection with fovy, aspect, zNear and zFar
   gluPerspective(45.0f, aspect, 0.1f, 100.0f);
   glutPostRedisplay();
}
