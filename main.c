/****************************************************************
 * File     : main.c
 * Datum    : Mei 2017
 * Version  : 1.0
 * Autor    : SOFTON groep 9, Irisjka, Tim, Alessandro en Mansur
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

void put_usage()
{
	UART_puts("*****USAGE GUIDE*****\r\n"
		 "This program translates user draw request to draw function which drive the VGA display.\r\n"
		 "The user has a certain selection of commands which can be inserted, these commands are:\r\n"
		 "write text: this command puts text on position x/y, the font, size, text color and background color can be chosen\r\n "
		 "		example: tekst,[xposition],[yposition],[sentence],[text color],[font name],[font type],[font size],[background color]\r\n"
		 "		argument ranges: \r\n"
		 "		xposition: 0 -> 320\r\n"
		 "		yposition: 0 -> 240\r\n"
		 "		sentence : depends on font size\r\n"
		 "		text color: 0->256(all posible colors) or zwart,blauw,lichtblauw,groen,lichtgroen,cyaan,lichtcyaan,rood,lichtrood,magenta,lichtmagenta,bruin,geel,grijs,wit"
		 "		font name(insert the exact representation): Times New Roman, Comic sans"
		 "		font type(insert the exact representation): Bold, regular"
		 "		font size: 8, 12 & 20"
		 "		background color: same as text color"
		 "Draw line: this command draws a line on position x/y, the font, size, text color and background color can be chosen\r\n "
		 "		example: tekst,[xposition],[yposition],[xposition2],[yposition2],[Line thickness], [color]\r\n"
		 "		argument ranges: \r\n"
		 "		xposition: 0 -> 320"
		 "		yposition: 0 -> 240"
		 "		xposition2: 0 -> 320"
		 "		yposition2: 0 -> 240"
		 "		width : 0 -> 30(thicker than this will ruin the figure"
		 "		color: 0->256(all posible colors) or zwart,blauw,lichtblauw,groen,lichtgroen,cyaan,lichtcyaan,rood,lichtrood,magenta,lichtmagenta,bruin,geel,grijs,wit"
		 "Draw ellipse: this command draws a ellipe on position x/y with a horizontal radius r1 and vertical radius r2. "
		 "		Wheter the ellipse is filled or not is determined by fill, thickness is determined bij thickness\r\n "
		 "		example: tekst,[xposition],[yposition],[xposition2],[yposition2],[Line thickness], [color]\r\n"
		 "		argument ranges: \r\n"
		 "		xposition: 0 -> 320"
		 "		yposition: 0 -> 240"
		 "		xposition2: 0 -> 320"
		 "		yposition2: 0 -> 240"
		 "		width : 0 -> 30(thicker than this will ruin the figure"
		 "		color: 0->256(all posible colors) or zwart,blauw,lichtblauw,groen,lichtgroen,cyaan,lichtcyaan,rood,lichtrood,magenta,lichtmagenta,bruin,geel,grijs,wit");
}

int main()
{
	SystemInit(); // System speed to 168MHz
	UB_VGA_Screen_Init(); // Init VGA-Screen
	delay_init();
	TIMER3_Initialize();
	UART_init();

	UART_puts("love\r");
	while(1)
	{

	}
}

