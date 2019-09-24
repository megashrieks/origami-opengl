#include<stdio.h>
#include<GL/glut.h>

typedef struct{
    int width, height;
} window;
window wh;


void printCharacters(float x, float y, const unsigned char* str){
    int characters_width = glutBitmapLength(GLUT_BITMAP_TIMES_ROMAN_24,str);
    glRasterPos2f(x - characters_width / 2, y);
    for(int i = 0;str[i];++i)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,str[i]);

}

void displayText(){
    int left_half  = wh.width / 4,
        right_half = wh.width * 3 / 4;
    int header_y = wh.height * 3 / 4;
    int offset = 20, line_height = 30;
    glColor3f(1, 0, 0);


    printCharacters(left_half, header_y, (unsigned char*)"Name");
    printCharacters(right_half, header_y, (unsigned char*)"USN");
    
    glColor3f(1, 1, 0);
    
    printCharacters(left_half, header_y-line_height-offset, (unsigned char*)"Shreya Shirva");
    printCharacters(right_half, header_y-line_height-offset, (unsigned char*)"4nm16cs142");

    printCharacters(left_half, header_y-line_height*2-offset, (unsigned char*)"Shrikantha budya");
    printCharacters(right_half, header_y-line_height*2-offset, (unsigned char*)"4nm16cs143");


    printCharacters(left_half, header_y-line_height*3-offset, (unsigned char*)"Shrilatha ballal");
    printCharacters(right_half, header_y-line_height*3-offset, (unsigned char*)"4nm16cs144");
    
    glColor3f(0, 0, 1);
    printCharacters(wh.width / 2, header_y-line_height*6-offset, (unsigned char*)"ORIGAMI");
    
}

void sequential(){
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, wh.width, 0, wh.height);
    displayText();
    glFlush();
}

int main(int argc, char** argv){

    //set window dimensions

    wh.width  = 500;
    wh.height = 500;
    


    glutInit(&argc, argv);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(wh.width,wh.height);
    glutCreateWindow("Origami");
    glutDisplayFunc(sequential);
    glutMainLoop();
    return 0;
}