#include<stdio.h>
#include<GL/glut.h>

typedef struct{
    int width, height;
    int state;
} window;
window wh;

typedef struct{
    float x, y;
} vert;

int min(int a, int b){ return a < b ? a : b;}
int max(int a, int b){ return a > b ? a : b;}

void stateChange(unsigned char key, int x, int y){
    if(key == ' ') wh.state += 1;
    glutPostRedisplay();
}

void draw_square(float startx, float starty, int width, int height){
    glColor3f(1, 1, .5);
    glBegin(GL_POLYGON);
        glVertex2f(startx, starty);
        glVertex2f(startx+width, starty);
        glVertex2f(startx+width, starty+height);
        glVertex2f(startx, starty+height);
    glEnd();
    glColor3f(0, 0, 1);
    glBegin(GL_LINE_LOOP);
        glVertex2f(startx, starty);
        glVertex2f(startx+width, starty);
        glVertex2f(startx+width, starty+height);
        glVertex2f(startx, starty+height);
    glEnd();
}

void displayOrigami(){
    int box_size = 100;
    float mid_start_x = wh.width / 2 - box_size / 2,
        mid_start_y = wh.height * 3 / 4;
    float left_start_x = mid_start_x - box_size,
        left_start_y = mid_start_y - box_size;
    vert v[] = {
        {mid_start_x,mid_start_y - box_size},
        {mid_start_x, mid_start_y},
        {mid_start_x,mid_start_y - box_size*2},
        {mid_start_x,mid_start_y - box_size*3},
        {left_start_x,left_start_y},
        {left_start_x+2*box_size,left_start_y-box_size}
    };
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    for(int i = 0;i < max(6 - wh.state + 1, 1);++i){
            draw_square(v[i].x,v[i].y,box_size,box_size);
    }
}

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


    printCharacters(left_half, header_y-line_height*3-offset, (unsigned char*)"Shrilatha");
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
    if(!wh.state)
        displayText();
    else if(wh.state)
        displayOrigami();
    glFlush();
}

int main(int argc, char** argv){

    //set window dimensions

    wh.width  = 500;
    wh.height = 500;
    wh.state = 0;


    glutInit(&argc, argv);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(wh.width,wh.height);
    glutCreateWindow("Origami");
    glutKeyboardFunc(stateChange);
    glutDisplayFunc(sequential);
    glutMainLoop();
    return 0;
}