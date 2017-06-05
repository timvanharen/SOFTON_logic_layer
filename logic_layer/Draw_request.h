/*
 *****************************************************************
 *!	\file		Draw_request.h
 *	\brief		Header file for Draw_request.c.
 *	\author		SOFTON groep 9.
 *	\date		Mei 2017.
 *	\version	0.1.
 *
 *	CPU			STM32F4;
 *	IDE			CooCox CoIDE 1.7.x;
 *	Module
 *****************************************************************
 */

//****************************************************************
#ifndef DRAW_REQUEST_H
#define DRAW_REQUEST_H

/*
 *****************************************************************
 *	Includes
 *****************************************************************
 */
#include "stm32f4xx.h"
#include "bfc_latin_font.h"

/*
 *****************************************************************
 *	Defines
 *****************************************************************
 */
#define PI 3.14159265359
#define	TIMER_FREQ 1000 //freq van 1 MHz
#define SYS_CLK 168000000

/*
 *****************************************************************
 *	Typedefs
 *****************************************************************
 */
typedef enum
 {
 	Times_New_Roman, Georgia				// 4
 } f_name ;

typedef enum
 {
 	bold, regular					// 2
 } f_type ;

/*
 *****************************************************************
 *	Function prototypes & documentation
 *****************************************************************
 */

/*! \fn 	void TIMER3_Initialize()
 *	\brief 	Timer3 Initialization.
 */
void TIMER3_Initialize();
/*!	\fn 	void wait_msec(unsigned int msec)
 *	\brief
 *	\param 	msec
 *	\remark Memory:
 *	\remark Wat kan er beter?
 */
void wait_msec(unsigned int msec);
/*!	\fn 	void Draw_Ellipse(uint16_t xp, uint16_t yp, uint16_t r1, uint16_t r2, uint16_t fill, uint16_t thickness, uint8_t colour)
 *	\brief 	Draws a ellips on a VGA screen.
 *	\param 	xp x value of the start coordinate (0 to 320).
 *	\param 	yp y value of the start coordinate (0 to 240).
 *	\param	r2
 *	\param	fill
 *	\param 	thickness
 *	\param 	colour color of the line (0x00 to 0xFF).
 *	\remark \b Memory
 *	\remark \b Milestone
 */
void Draw_Ellipse(uint16_t xp, uint16_t yp, uint16_t r1, uint16_t r2, uint16_t fill, uint16_t thickness, uint8_t colour);
/*!	\fn 	void Clear_screen(uint8_t color)
 *	\brief 	Turns the whole vga screen into one color.
 *	\param 	color color of the screen(0x00 to 0xFF).
 *	\remark \b Memory
 *	\remark \b Milestone
 */
void Clear_screen(uint8_t color);
/*!	\fn 	void Bitmap_to_VGA(uint8_t image_nr, uint8_t xp, uint8_t yp)
 *	\brief 	Draws a the bitmap of a picture/image on a VGA screen.
 *	\param 	image_nr the number of the image that you want.
 *	\param 	xp x value of the start coordinate (0 to 320).
 *	\param 	yp y value of the start coordinate (0 to 240).
 *	\remark \b Memory
 *	\remark \b Milestone
 */
void Bitmap_to_VGA(uint8_t image_nr, uint8_t xp, uint8_t yp);
/*!	\fn 	signed int Draw_Line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t width, uint8_t color)
 *	\brief 	Draws a line on a VGA screen.
 *	\param 	x1 x value of the start coordinate (0 to 320).
 *	\param 	y1 y value of the start coordinate (0 to 240).
 *	\param 	x2 x value of the end coordinate (0 to 320).
 *	\param 	y2 y value of the end coordinate (0 to 240).
 *	\param 	width indicates the width of the line.
 *	\param 	color color of the line (0x00 to 0xFF).
 *	\remark \b Memory
 *	\remark \b Milestone It could be faster without all the mathematical stuff going on.
 */
signed int Draw_Line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t width, uint8_t color);
/*!	\fn 	void Draw_HorLine(uint16_t xp, uint16_t yp, uint8_t length, uint8_t color)
 *	\brief 	Draws a horizontal line on a VGA screen.
 *	\param 	xp x value of the start coordinate (0 to 320).
 *	\param 	yp y value of the start coordinate (0 to 240).
 *	\param 	length amount of pixels that makes the length of the line.
 *	\param 	color color of the line (0x00 to 0xFF).
 *	\remark \b Memory
 */
void Draw_HorLine(uint16_t xp, uint16_t yp, uint8_t length, uint8_t color);
/*!	\fn 	void Draw_VerLine(uint16_t xp, uint16_t yp, uint8_t length, uint8_t color)
 *	\brief 	Draws a vertical line on a VGA screen.
 *	\param 	xp x value of the start coordinate (0 to 320).
 *	\param 	yp y value of the start coordinate (0 to 240).
 *	\param 	length amount of pixels that makes the length of the line.
 *	\param 	color color of the line (0x00 to 0xFF).
 *	\remark \b Memory
 */
void Draw_VerLine(uint16_t xp, uint16_t yp, uint8_t length, uint8_t color);
/*!	\fn 	void Draw_Rectangle(uint16_t xp, uint16_t yp, uint8_t x_length, uint8_t y_length, uint8_t line_width, uint8_t fill, uint8_t color)
 *	\brief 	Draws a rectangle with any lengths you like on a VGA screen.
 *	\param 	xp x value of the start coordinate (0 to 320).
 *	\param 	yp y value of the start coordinate (0 to 240).
 *	\param	x_length the amount of pixels in the x direction (0 to 320 minus xp).
 *	\param 	y_length the amount of pixels in the y direction (0 to 240 minus yp).
 *	\param 	line_width the width of the drawn line (1 to half of the shortest length).
 *	\param	fill filled rectangle (1) or empty rectangle (0).
 *	\param	color color of the rectangle (0x00 to 0xFF).
 *	\remark \b Memory
 */
void Draw_Rectangle(uint16_t xp, uint16_t yp, uint8_t x_length, uint8_t y_length, uint8_t line_width, uint8_t fill, uint8_t color);
/*!	\fn 	void void Draw_Triangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, int fill, uint8_t line_width, uint8_t color)
 *	\brief 	Draws a triangle with the corners on which ever coordinate you choose.
 *	\param 	x1 x value of the first coordinate (0 to 320).
 *	\param 	y1 y value of the first coordinate (0 to 240).
 *	\param 	x2 x value of the second coordinate (0 to 320).
 *	\param 	y2 y value of the second coordinate (0 to 240).
 *	\param 	x3 x value of the third coordinate (0 to 320).
 *	\param 	y3 y value of the third coordinate (0 to 240).
 *	\param 	fill filled triangle (1) or empty triangle (0).
 *	\param 	color color of the triangle (0x00 to 0xFF).
 *	\remark \b Memory
 *	\remark \b Milestone It could be faster without all the mathematical stuff going on.
 */
void Draw_Triangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, int fill, uint8_t line_width, uint8_t color);
/*!	\fn 	void Set_Single_Pixel(uint16_t xp, uint16_t yp, uint8_t colour)
 *	\brief 	Colors a pixel on the coordinate of you desire with the color of your desire.
 *	\param 	xp x value of the pixel coordinate (0 to 320).
 *	\param 	yp y value of the pixel coordinate (0 to 240).
 *	\param 	color color of the pixel (0x00 to 0xFF).
 *	\remark \b Memory
 *	\remark \b Milestone
 */
void Set_Single_Pixel(uint16_t xp, uint16_t yp, uint8_t colour);
/*!	\fn 	uint16_t draw_character(uint16_t xp, uint16_t yp, int char_input, uint8_t color, f_name font_name, f_type font_type, uint8_t font_size, uint8_t bg)
 *	\brief 	Draw a character on the VGA screen.
 *	\param 	xp x value of the pixel coordinate (0 to 320).
 *	\param 	yp y value of the pixel coordinate (0 to 240).
 *	\param 	color color of the pixel (0x00 to 0xFF).
 *	\param	font_name
 *	\param	font_type
 *	\param	font_size
 *	\param	bg background color.
 *	\return	char_width
 *	\remark \b Memory
 *	\remark \b Milestone
 */
uint16_t draw_character(uint16_t xp, uint16_t yp, int char_input, uint8_t color, f_name font_name, f_type font_type, uint8_t font_size, uint8_t bg);
/*!	\fn 	void draw_sentence( uint16_t xp, uint16_t yp, char *sent,uint8_t color, f_name font_name, f_type font_type, uint8_t font_size, uint8_t bg)
 *	\brief 	Draw multiple characyers on the VGA screen.
 *	\param 	xp x value of the pixel coordinate (0 to 320).
 *	\param 	yp y value of the pixel coordinate (0 to 240).
 *	\param 	color color of the pixel (0x00 to 0xFF).
 *	\param	font_name
 *	\param	font_type
 *	\param	font_size
 *	\param	bg background color.
 *	\remark \b Memory
 *	\remark \b Milestone
 */
void draw_sentence( uint16_t xp, uint16_t yp, char *sent,uint8_t color, f_name font_name, f_type font_type, uint8_t font_size, uint8_t bg);

#endif // DRAW_REQUEST_H
