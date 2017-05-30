/****************************************************************
 * File     : main.c
 * Datum    : Mei 2017
 * Version  : 1.0
 * Autor    : SOFTON groep 9
 * CPU      : STM32F4
 * IDE      : CooCox CoIDE 1.7.x
 * Module   : CMSIS_BOOT, M4_CMSIS_CORE
 * Function :
 ****************************************************************/

#include "main.h"
#include "stm32_ub_vga_screen.h"
#include <math.h>
#include "Draw_request.h"
#include "apllication.h"

int i,j=0;
char c;

int main()
{
	SystemInit(); // System speed to 168MHz
	UB_VGA_Screen_Init(); // Init VGA-Screen
	delay_init();
	TIMER3_Initialize();
	UART_init();

	Bitmap_to_VGA(0,0,5);
  while(1)
  {
//	  UART_puts("hello world");
//	  UART_putchar(c);
//	  Draw_Ellipse(80, 120, 50, 50, 0, 2, VGA_COL_BLUE);
//	  wait_msec(1000);
//	  Draw_Ellipse(240, 120, 70, 30, 1, 0, VGA_COL_RED);
//	  wait_msec(5000);
//	  Clear_screen(VGA_COL_BLACK);
  }
}

