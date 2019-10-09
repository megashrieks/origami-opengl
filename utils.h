#include "types.h"

#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

void stateChange(unsigned char, int, int);

void draw_square(square);
vert lerp_vert(float, vert, vert);
square lerp_square(float, square, square);

int min(int, int);
int max(int, int);
float lerp(float, float, float);
void reshape(GLsizei, GLsizei);


#endif // UTILS_H_INCLUDED
