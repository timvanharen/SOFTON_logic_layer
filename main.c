//--------------------------------------------------------------
// File     : main.c
// Datum    : 30.03.2016
// Version  : 1.0
// Autor    : UB
// mods by	: J.F. van der Bent
// CPU      : STM32F4
// IDE      : CooCox CoIDE 1.7.x
// Module   : CMSIS_BOOT, M4_CMSIS_CORE
// Function : VGA_core DMA LIB 320x240, 8bit color
//--------------------------------------------------------------

#include "main.h"
#include "stm32_ub_vga_screen.h"
#include <math.h>
#include "Draw_request.h"

int main(void)
{

	//  uint32_t n;

	SystemInit(); // System speed to 168MHz

	UB_VGA_Screen_Init(); // Init VGA-Screen

	UB_VGA_FillScreen(VGA_COL_BLACK);
	UB_VGA_SetPixel(10,10,10);

  	//Fill_BitMap();
	int i,j;
	i=0;
  while(1)
  {
	  //cmd prompt is openend
	  //wait for rs232 string
	  Draw_Ellipse(160, 120, 100, 10, 1, 1, VGA_COL_RED);
	  //Put_Bitmap();
	  i++;
	  for(j=0; j<19992999; j++);
  }
}

