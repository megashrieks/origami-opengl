#ifndef TYPES_H_INCLUDED
#define TYPES_H_INCLUDED


typedef struct{
    int width, height;
    int state;
    float global_interpolation;
} window;

typedef struct{
    float x, y, z;
} vert;

typedef struct{
    vert tl, tr, bl, br;
} square;

typedef struct{
    int steps;
    int index_array[10];
    square squares[10];
} transition_step;

typedef struct{
    int total_transitions;
    transition_step ts[10];
} transitions;

#endif // TYPES_H_INCLUDED
