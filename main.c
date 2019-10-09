#include<stdio.h>
#include<GL/glut.h>


#include"types.h"
#include"splash.h"
#include"utils.h"
#include"statemanager.h"


window wh;




void init(){
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
   glClearDepth(1.0f);                   // Set background depth to farthest
   glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
   glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
   glShadeModel(GL_SMOOTH);   // Enable smooth shading
   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
}


void displayOrigami(){
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    int box_size = 100;
    float mid_start_x = wh.width / 2 - box_size / 2,
        mid_start_y = wh.height * 3 / 4;
    float left_start_x = mid_start_x - box_size,
        left_start_y = mid_start_y - box_size;




    //vertices of the cube
    vert v[] = {
        {mid_start_x,mid_start_y - box_size, 0}, //2nd from top
        {mid_start_x, mid_start_y, 0}, //1st from top
        {mid_start_x,mid_start_y - box_size*2, 0},//3rd from top
        {mid_start_x,mid_start_y - box_size*3, 0},//4th from top
        {left_start_x,left_start_y, 0}, // left
        {left_start_x+2*box_size,left_start_y-box_size, 0} //right
    };

    //squares
    square s[] = {
        {
            v[0],
            {v[0].x+box_size,v[0].y,v[0].z},
            {v[0].x,v[0].y+box_size,v[0].z},
            {v[0].x+box_size,v[0].y+box_size,v[0].z}
        },{
            v[1],
            {v[1].x+box_size,v[1].y,v[1].z},
            {v[1].x,v[1].y+box_size,v[1].z},
            {v[1].x+box_size,v[1].y+box_size,v[1].z}
        },{
            v[2],
            {v[2].x+box_size,v[2].y,v[2].z},
            {v[2].x,v[2].y+box_size,v[2].z},
            {v[2].x+box_size,v[2].y+box_size,v[2].z}
        },{
            v[3],
            {v[3].x+box_size,v[3].y,v[3].z},
            {v[3].x,v[3].y+box_size,v[3].z},
            {v[3].x+box_size,v[3].y+box_size,v[3].z}
        },{
            v[4],
            {v[4].x+box_size,v[4].y,v[4].z},
            {v[4].x,v[4].y+box_size,v[4].z},
            {v[4].x+box_size,v[4].y+box_size,v[4].z}
        },{
            v[5],
            {v[5].x+box_size,v[5].y,v[5].z},
            {v[5].x,v[5].y+box_size,v[5].z},
            {v[5].x+box_size,v[5].y+box_size,v[5].z}
        }
    };


    //the transitions for the transformation
    transitions t;

    square s1 = {{s[0].bl.x,s[0].bl.y,1},{s[0].br.x,s[0].br.y,1},s[0].bl,s[0].br};
    square s2 = {s[2].tr,{s[2].tr.x,s[2].tr.y,1},s[2].br,{s[2].br.x,s[2].br.y,1}};
    square s3 = {{s[0].tl.x,s[0].tl.y,1},s[0].tl,{s[0].bl.x,s[0].bl.y,1},s[0].bl};
    square s4 = {{s[2].tl.x,s[2].tl.y,1},{s[2].tr.x,s[2].tr.y,1},s[2].tl,s[2].tr};
    square s5 = {{s[0].tl.x,s[0].tl.y,1},{s[0].tr.x,s[0].tr.y,1},s[0].tl,s[0].tr};
    square s6 = {{s[0].tr.x,s[0].tr.y,1},{s[0].br.x,s[0].br.y,1},s[0].tr,s[0].br};

    transition_step tts0,tts1,tts2,tts3,tts4;
    tts0.steps = 1;
    tts0.index_array[0] = 1;
    tts0.squares[0] = s1;

    tts1.steps = 1;
    tts1.index_array[0] = 5;
    tts1.squares[0] = s2;

    tts2.steps = 1;
    tts2.index_array[0] = 4;
    tts2.squares[0] = s3;

    tts3.steps = 1;
    tts3.index_array[0] = 3;
    tts3.squares[0] = s4;

    tts4.steps = 3;
    tts4.index_array[0] = 2;
    tts4.index_array[1] = 3;
    tts4.index_array[2] = 5;
    tts4.squares[0] = s5;
    tts4.squares[1] = s5;
    tts4.squares[2] = s6;


    t.total_transitions = 5  ;
    t.ts[0] = tts0;
    t.ts[1] = tts1;
    t.ts[2] = tts2;
    t.ts[3] = tts3;
    t.ts[4] = tts4;




    int step_pointer = 0;
    for(int i = 0;i < 6;++i){


        //preserve the transitions from the previous steps
        int flag = 0;
        for(int j = wh.state - 2;j >= 0; --j){
            for(int k = 0;k < t.ts[j].steps;++k){
                if(t.ts[j].index_array[k] == i){
                    s[i] = t.ts[j].squares[k];
                    flag = 1;
                    break;
                }
            }
            if(flag) break;
        }



        //current transitions for linear interpolation
        transition_step current = t.ts[min(wh.state - 1,t.total_transitions-1)];
        if(step_pointer < current.steps && current.index_array[step_pointer] == i){
            draw_square(
                lerp_square(wh.global_interpolation, s[i],current.squares[step_pointer])
            );
            step_pointer += 1;
        }else
            draw_square(s[i]);
    }


    //TODO : use glutTimerFunc to replace the static interpolation parameter with ID based one
    if(wh.global_interpolation <= 1){
        wh.global_interpolation += 0.0001;
        glutPostRedisplay();
    }

    //glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix
    //glLoadIdentity();
    //gluLookAt ( 0.0, 0.0, 10.0, 0,0,0.0, 0.0, 1.0, 0.0 );
    //glRotatef(-.1,1,0,0);
    //glutPostRedisplay();
}



int main(int argc, char** argv){
    //set window dimensions
    wh.width  = 500;
    wh.height = 500;
    wh.state = 0;
    wh.global_interpolation = 0;

    glutInit(&argc, argv);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(wh.width,wh.height);
    glutCreateWindow("Origami");
    glutKeyboardFunc(stateChange);
    glutDisplayFunc(sequential);
    glutReshapeFunc(reshape);
    init();
    glutMainLoop();
    return 0;
}
