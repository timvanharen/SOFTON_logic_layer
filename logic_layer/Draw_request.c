
#include "main.h"
#include "Draw_request.h"
#include "stm32_ub_vga_screen.h"
#include <math.h>

static int i;
short EllipseXPosArray[100];
short EllipseYPosArray[100];

//static BitMapImage image[VGA_DISPLAY_Y*VGA_DISPLAY_X];

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

//void Fill_BitMap()
//{
//	image[0].ypos = 0;
//	image[0].xpos = 0;
//	for(i=0;i<sizeof(*image);i++)	{
//		image[i].colour = VGA_COL_MAGENTA;
//			if(image[i].xpos < 320)
//				image[i].xpos++;
//			else
//				image[i].xpos = 0;
//				image[i].ypos++;
//	}
//}
