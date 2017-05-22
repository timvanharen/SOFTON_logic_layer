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
#define	TIMER_FREQ 1000 //freq van 1 MHz
#define SYS_CLK 168000000

void TIMER3_Initialize();
void Draw_Ellipse(unsigned short xp, unsigned short yp, unsigned short r1, unsigned short r2, short fill, unsigned short thickness, unsigned short colour);
void Draw_Ellipse_2(unsigned short xp, unsigned short yp, unsigned short r1, unsigned short r2, short fill, unsigned short thickness, unsigned short colour);
void Draw_Ellipse_3(unsigned short xp, unsigned short yp, unsigned short r1, unsigned short r2, short fill, unsigned short thickness, unsigned short colour);
void wait_msec(unsigned int msec);
void Fill_BitMap();
void Put_Bitmap();
void Clear_screen(unsigned short color);
void Bitmap_to_VGA();
#endif // DRAW_REQUEST_H
