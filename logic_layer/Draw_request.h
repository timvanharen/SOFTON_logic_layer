//--------------------------------------------------------------
// File     : Draw_request.h
//--------------------------------------------------------------

//--------------------------------------------------------------
#ifndef DRAW_REQUEST_H
#define DRAW_REQUEST_H


//--------------------------------------------------------------
// Includes
//--------------------------------------------------------------
#include "stm32f4xx.h"

//--------------------------------------------------------------
// typedefs
//--------------------------------------------------------------
#define PI 3.14159265359


void Draw_Ellipse(unsigned short xp, unsigned short yp, unsigned short r1, unsigned short r2, short fill, unsigned short thickness, unsigned short colour);
void Fill_BitMap();
void Put_Bitmap();
#endif // DRAW_REQUEST_H
