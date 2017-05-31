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
#include "bfc_latin_font.h"

//--------------------------------------------------------------
// typedefs
//--------------------------------------------------------------
#define PI 3.14159265359
#define	TIMER_FREQ 1000 //freq van 1 MHz
#define SYS_CLK 168000000

//Function prototypes
void TIMER3_Initialize();
void Draw_Ellipse(unsigned short xp, unsigned short yp, unsigned short r1, unsigned short r2, short fill, unsigned short thickness, unsigned short colour);
void wait_msec(unsigned int msec);
void Draw_Rectangle(uint16_t xp, uint16_t yp, uint8_t x_length, uint8_t y_length, uint8_t line_width, uint8_t fill, uint8_t color);
void Clear_screen(unsigned short color);
void Bitmap_to_VGA(uint8_t xp, uint8_t yp, uint8_t repeat);
signed int Draw_Line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t width, uint8_t color);
void Draw_Triangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, int fill, uint8_t color);
void Set_Single_Pixel(unsigned short xp, unsigned short yp, unsigned short colour);

typedef enum
 {
 	Times_New_Roman, Comic_sans, Georgia, Mistral					// 4
 } f_name ;

typedef enum
 {
 	bold, regular					// 2
 } f_type ;


 uint16_t draw_character(uint16_t xp, uint16_t yp, int char_input, uint8_t color, f_name font_name, f_type font_type, uint8_t font_size, uint8_t bg);
 void 	  draw_sentence( uint16_t xp, uint16_t yp, char *sent,     uint8_t color, f_name font_name, f_type font_type, uint8_t font_size, uint8_t bg);




#endif // DRAW_REQUEST_H
