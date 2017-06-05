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
#include "includes.h"

void put_usage()
{
	UART_puts("*****USAGE GUIDE*****\r\n"
			"This program translates user draw request to output on the a VGA screen.\r\n"
			"\r\n"
			"The user has a certain selection of commands which can be inserted:\r\n"
			"write text: this command puts text on position x/y, the font, size, text color and background color can be chosen\r\n "
			"	example: tekst,[xposition],[yposition],[sentence],[text color],[font name],[font type],[font size],[background color]\r\n"
			"	argument ranges: \r\n"
			"	x position: 0 -> 320\r\n"
			"	y position: 0 -> 240\r\n"
			"	sentence : depends on font size\r\n"
			"	text color*\r\n"
			"	font name(insert the exact representation): Times New Roman, Comic sans\r\n"
			"	font type(insert the exact representation): Bold, regular\r\n"
			"	font size: 8, 12 & 20\r\n"
			"	background color: same as text color\r\n"
			"Draw line: this command draws a line on position x/y, the font, size, text color and background color can be chosen\r\n "
			"	example: tekst,[xposition],[yposition],[xposition2],[yposition2],[Line thickness], [color]\r\n"
			"	argument ranges: \r\n"
			"	x position 1: 0 -> 320\r\n"
			"	y position 1: 0 -> 240\r\n"
			"	x position 2: 0 -> 320\r\n"
			"	y position 2: 0 -> 240\r\n"
			"	width : 0 -> 30(thicker than this will ruin the figure\r\n"
			"	color*\r\n"
			"Draw ellipse: this command draws a ellipe on position x/y with a horizontal radius r1 and vertical radius r2.\r\n"
			"	Wheter the ellipse is filled or not is determined by fill, thickness is determined bij thickness\r\n "
			"	example: tekst,[xposition],[yposition],[xposition2],[yposition2],[Line thickness], [color]\r\n"
			"	argument ranges: \r\n"
			"	xposition: 0 -> 320\r\n"
			"	yposition: 0 -> 240\r\n"
			"	xposition2: 0 -> 320\r\n"
			"	yposition2: 0 -> 240\r\n"
			"	width : 0 -> 30(thicker than this will ruin the figure)\r\n"
			"	color*\r\n"
			"Draw rectangle:\r\n"
			"	example: rechthoek,[xposition],[yposition],[lengte_x],[lengte_y],[Line thickness],[filled or not filled],[color]\r\n"
			"	xposition: 0 -> 320\r\n"
			"	yposition: 0 -> 240\r\n"
			"	lengte_x: 0 -> 320-xposition\r\n"
			"	lengte_y: 0 -> 240-yposition\r\n"
			"	Line thicknes: 0 -> lengte x of y\r\n"
			"	fill: vol || leeg\r\n"
			"	color*\r\n"
			"Draw triangle: this command draws a triangle with corners on which ever coordinate you want.\r\n"
			"	example: driehoek,[xposition],[yposition],[xposition2],[yposition2],[xposition3],[yposition3],[filled or not filled],[color]\r\n"
			"	xposition1,2,3: 0 -> 320\r\n"
			"	yposition1,2,3: 0 -> 240\r\n"
			"	fill: vol || leeg\r\n"
			"	color*\r\n"
			"Draw bitmap: puts a image on the screen.\r\n"
			"	example: bitmap,[image],[xposition],[yposition]\r\n"
			"	image: let's you choose which number image you want\r\n"
			"	xposition: 0 -> 320\r\n"
			"	yposition: 0 -> 240\r\n"
			"Wait: this command is a delay function."
			"	example: wacht,[amount ms]\r\n"
			"	amount: how many miliseconds you want to wait\r\n"
			"Clearscherm: Wipe all text and figures from the screen\r\n"
			"	example: clearscherm,[color]\r\n"
			"	color*\r\n"
			"\r\n"
			"*color = 0->256(all posible colors) or zwart,blauw,lichtblauw,groen,lichtgroen,cyaan,lichtcyaan,rood,lichtrood,magenta,lichtmagenta,bruin,geel,grijs,wit\r\n"
			);
}

int main()
{
	SystemInit(); // System speed to 168MHz
	UB_VGA_Screen_Init(); // Init VGA-Screen
	delay_init();
	TIMER3_Initialize();
	UART_init();

	put_usage();
	while(1)
	{

	}
}

