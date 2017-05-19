
#include "main.h"
#include "Draw_request.h"
#include "stm32_ub_vga_screen.h"
#include <math.h>
#include "uitvoer.h"

static int i;
short EllipseXPosArray[100];
short EllipseYPosArray[100];



void Draw_Line(unsigned short xp, unsigned short yp, unsigned short angle_deg, unsigned short len, unsigned short thickness, unsigned short colour)
{

}

void DrawHorLine(uint16_t xp, uint16_t yp, uint8_t length, uint8_t color)
{
	int i;
	for(i=0; i<length; i++,xp++)
		UB_VGA_SetPixel(xp, yp, color);
}

void DrawVerLine(uint16_t xp, uint16_t yp, uint8_t length, uint8_t color)
{
	int t;
	for(t=0; t<length; t++,yp++)
		UB_VGA_SetPixel(xp, yp, color);
}

void DrawEmptySquare(uint16_t xp, uint16_t yp, uint8_t width, uint8_t hight, uint8_t color)
{
	DrawHorLine(xp,yp,width,color);
	DrawVerLine(xp+width,yp,hight,color);
	DrawHorLine(xp,yp+hight,width,color);
	DrawVerLine(xp,yp,hight,color);
}

void DrawFullSquare(uint16_t xp, uint16_t yp, uint8_t width, uint8_t hight, uint8_t color)
{
	int r;
	for(r=0;r<hight;r++,yp++)
		DrawHorLine(xp,yp,width, color);
}

void Write_Text(unsigned short xp, unsigned short yp, unsigned short string, char *font, unsigned short size, unsigned short colour)
{

}

//void Put_Bitmap()
//{
//	for(i=0;i<sizeof(*image);i++)
//		UB_VGA_SetPixel(image[i].xpos, image[i].ypos, image[i].colour);
//}

void Draw_Ellipse(unsigned short xp, unsigned short yp, unsigned short r1, unsigned short r2, short fill, unsigned short thickness, unsigned short colour)
{
	//int EllipsePerimeter = 2*PI*sqrtf((r1*r1 + r2*r2)/ 2);
	for(i=0;i<r1;i++) {
		EllipseXPosArray[i] = xp - r1/2 + i;
		EllipseXPosArray[i + r1] = xp + r1/2 - i;
	}
	r2 = r2/ 2;
	for(i=0; i < r1; i++) {
			EllipseYPosArray[i] = yp + sqrtf((1 - ((i*i)/(r1*r1)))/(r2*r2));
			EllipseYPosArray[r1-i] = yp + sqrtf((1 - ((i*i)/(r1*r1)))/(r2*r2));
			EllipseYPosArray[i+r1] = yp - sqrtf((1 - ((i*i)/(r1*r1)))/(r2*r2));
			EllipseYPosArray[r1*2-i] = yp - sqrtf((1 - ((i*i)/(r1*r1)))/(r2*r2));
	}

	for(i=0; i < r1*2; i++)
		UB_VGA_SetPixel(EllipseXPosArray[i], EllipseYPosArray[i], colour);
}

void Draw_Rectangle(unsigned short xp, unsigned short yp, unsigned short width, unsigned short length, short fill, unsigned short thickness, unsigned short colour)
{

}

void Set_Single_Pixel(unsigned short xp, unsigned short yp, unsigned short colour )
{
	UB_VGA_SetPixel(xp,yp,colour);
}

void Clear_screen()
{
	UB_VGA_FillScreen(VGA_COL_WHITE);
}
/*
 * The function Bitmap_to_VGA receives 2 parameters that define the begin position of the image on the screen.
 * This position is the left top corner of the image.
 */
void Bitmap_to_VGA(uint8_t xp, uint8_t yp)
{
	int y_counter=0;
	int x_counter=0;
	int i=0;
	int j=0;

// for(y=0 y<30 y++)
    for (y_counter=yp; y_counter<IMAGE_HEIGHT; y_counter++)   //VGA_DISPLAY_Y must be maxheight of the image
	{
		for (x_counter=xp; x_counter<IMAGE_WIDTH; x_counter++)  //VGA_DISPLAY_Y must be maxwidth of the image
		{
			UB_VGA_SetPixel(x_counter, y_counter, image[i]); //image comes on left corner always
				i++;

//				for(j=0; j<5000; j++)
//				{
//					//delay
//				}
//				if (image[i] > 255)
//					printf ("error, your image contains more than 256 colors");
		}
	}

}

