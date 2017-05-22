
#include "main.h"
#include "Draw_request.h"
#include "stm32_ub_vga_screen.h"
#include <math.h>
#include "uitvoer.h"

static int i;
short EllipseXPosArray[100];
short EllipseYPosArray[100];



//void Draw_Line(unsigned short xp, unsigned short yp, unsigned short angle_deg, unsigned short len, unsigned short thickness, unsigned short colour)
//{
//
//}

void DrawHorLine(uint16_t xp, uint16_t yp, uint8_t length, uint8_t color, uint8_t width_y) // x-coordinaat
{
	int i;
	int j;
	for(i=0; i<length; i++,xp++)
		for(j=0; j<width_y; j++)
		UB_VGA_SetPixel(xp, yp+j, color);
}

void DrawVerLine(uint16_t xp, uint16_t yp, uint8_t length, uint8_t color, uint8_t width_x)
{
	int t;
	for(t=0; t<length; t++,yp++)
		for(i=0; i<width_x; i++)
		UB_VGA_SetPixel(xp+i, yp, color);
}

void DrawEmptySquare(uint16_t xp, uint16_t yp, uint8_t width, uint8_t hight, uint8_t color, uint8_t width_x, uint8_t width_y)
{
	DrawHorLine(xp,yp,width,color, width_y);
	DrawVerLine(xp+width,yp,hight,color, width_x);
	DrawHorLine(xp,yp+hight,width,color, width_y);
	DrawVerLine(xp,yp,hight,color, width_x);
}

void DrawFullSquare(uint16_t xp, uint16_t yp, uint8_t width, uint8_t hight, uint8_t color, uint8_t width_y)
{
	int r;
	for(r=0;r<hight;r++,yp++)
		DrawHorLine(xp,yp,width, color, width_y);
}

void Write_Text(unsigned short xp, unsigned short yp, unsigned short string, char *font, unsigned short size, unsigned short colour)
{

}


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
void Bitmap_to_VGA(uint8_t xp, uint8_t yp, uint8_t repeat)
{
	int y_counter=0;
	int x_counter=0;
	int i=0;
	int j=0;
	int k=0;


    for (y_counter=yp; y_counter<IMAGE_HEIGHT+yp; y_counter++)   //for loop for vertical pixels of image
	{
		for (x_counter=xp; x_counter<IMAGE_WIDTH+xp; x_counter++)  //for loop for horizontal pixels of image
		{
//			UB_VGA_SetPixel(x_counter, y_counter, image[i]);
				i++; // i loopt tot Image_heigth*Image_width

				if (i==IMAGE_HEIGHT*IMAGE_WIDTH)	// Print duplicate of image next to it
//					UB_VGA_FillScreen(VGA_COL_BLACK);
					for(j=0; j<5000; j++)
					{
						//delay
					}
					for(k=0; k<repeat; k++)
						UB_VGA_SetPixel(x_counter+IMAGE_WIDTH*k, y_counter, image[i]);


				if (image[i] > 255 || image[i] < 0)   //The image may only have 256 colors
					printf ("error, your image contains more than 256 colors");
				if (IMAGE_HEIGHT > 240)
					printf("Your image height must be shorter than 240 pixels");
				if (IMAGE_WIDTH > 320)
					printf("Your image width must be shorter than 320 pixels");
				if (xp>320 || xp < 0)
					printf("x-coordinate must be an integer value between 0 and 320");
				if (yp>240 || yp < 0)
					printf("y-coordinate must be an integer value between 0 and 240");
		}
	}

}

