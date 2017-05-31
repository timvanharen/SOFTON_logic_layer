
#include "main.h"
#include "Draw_request.h"
#include "stm32_ub_vga_screen.h"
#include <math.h>
#include "apllication.h"
#include "stm32f4xx_rcc.h"
#include "uitvoer.h"

static int i=0;
short EllipseXPosArray[1000];
short EllipseYPosArray[1000];


void TIMER3_Initialize() //delay timer
{
	int G_CLK;
	RCC_ClocksTypeDef Clocks;
	RCC_GetClocksFreq(&Clocks);
	G_CLK = Clocks.SYSCLK_Frequency;	// Read the systemclock

	uint16_t PrescalerValue;
	//prescaler aan de hand van freq instellen
	PrescalerValue = (uint16_t)(G_CLK / (TIMER_FREQ));

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	TIM_TimeBaseInitTypeDef timerInitStructure;
	timerInitStructure.TIM_Prescaler = PrescalerValue;
	timerInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	timerInitStructure.TIM_Period = 24000; //timer tot 24000 ms laten tellen
	timerInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	timerInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM3, &timerInitStructure);
	TIM_Cmd(TIM3, ENABLE);
}

void wait_msec(unsigned int msec)
{
	TIM_SetCounter(TIM3, 0);
	while(TIM_GetCounter(TIM3)<msec);
}

signed int Draw_Line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t width, uint8_t color)
{
	signed int dx,dy,px,py,dxabs,dyabs,i,j;
	float slope;

	dx=x2-x1;		// the horizontal distance of the line
	dy=y2-y1;		// the vertical distance of the line
	dxabs=fabs(dx);		//abs(dx); betekent de absolute waarde van
	dyabs=fabs(dy);		//abs(dy); same

	if (dxabs>=dyabs)	// the line is more horizontal than vertical
	{
		slope=(float)dy / (float)dx;
		if(dx<0x80000000)	// x is positive
		{
			for(i=0;i!=dx;i++)
			{
				px=i+x1;
				for(j=0;j<width;j++)
				{
					py=slope*i+y1+j;
					UB_VGA_SetPixel(px,py,color);
				}
			}
		}
		else			// x is negative
		{
			for(i=0;i!=dxabs;i++)
			{
				px=x1-i;
				for(j=0;j<width;j++)
				{
					py=j+y1-slope*i;
					UB_VGA_SetPixel(px,py,color);
				}
			}
		}
		return dxabs;
	}
	else 			// the line is more vertical than horizontal
	{
//		UART_puts("more ver than hor\r");
		slope=(float)dx / (float)dy;
		if(dy<0x80000000)	// y is positive
		{
			for(i=0;i!=dy;i++)
			{
				py=y1+i;
				for(j=0;j<width;j++)
				{
					px=slope*i+x1+j;
					UB_VGA_SetPixel(px,py,color);
				}
			}
		}else			// y is negative
		{
			for(i=0;i!=dyabs;i++)
			{
				py=y1-i;
				for(j=0;j<width;j++)
				{
					px=j+x1-slope*i;
					UB_VGA_SetPixel(px,py,color);
				}
			}
		}
		return dyabs;
	}
}

void Draw_HorLine(uint16_t xp, uint16_t yp, uint8_t length, uint8_t color) // x-coordinaat
{
	int i;
	for(i=0; i<length; i++,xp++)
		UB_VGA_SetPixel(xp, yp, color);
}

void Draw_VerLine(uint16_t xp, uint16_t yp, uint8_t length, uint8_t color)
{
	int t;
	for(t=0; t<length; t++,yp++)
		UB_VGA_SetPixel(xp+i, yp, color);
}

void Draw_EmptySquare(uint16_t xp, uint16_t yp, uint8_t width, uint8_t hight, uint8_t color, uint8_t width_x, uint8_t width_y)
{
	Draw_HorLine(xp,yp,width,color);
	Draw_VerLine(xp+width,yp,hight,color);
	Draw_HorLine(xp,yp+hight,width,color);
	Draw_VerLine(xp,yp,hight,color);
}

void Draw_FullSquare(uint16_t xp, uint16_t yp, uint8_t width, uint8_t hight, uint8_t color, uint8_t width_y)
{
	int r;
	for(r=0;r<hight;r++,yp++)
		Draw_HorLine(xp,yp,width,color);
}

void Draw_Triangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, int fill, uint8_t color)
{
	uint16_t mpx = (x1+x2+x3)/3;
	uint16_t mpy = (y1+y2+y3)/3;

	Draw_Line(x1,y1,x2,y2,1,color);
	Draw_Line(x2,y2,x3,y3,1,color);
	Draw_Line(x3,y3,x1,y1,1,color);

	UB_VGA_SetPixel(mpx,mpy,color);

	if(fill==1)
	{
		signed int x,y,dx,dy,px,py,dxabs,dyabs,i,j;
		float slope;
		for(j=0;j<3;j++)
		{
			if(j==0)
			{
				dx=x2-x1;		/* the horizontal distance of the line */
				dy=y2-y1;		/* the vertical distance of the line */
				x=x1; y=y1;
			}
			else if(j==1)
			{
				dx=x3-x2;		/* the horizontal distance of the line */
				dy=y3-y2;		/* the vertical distance of the line */
				x=x2; y=y2;
			}
			else if(j==2)
			{
				dx=x1-x3;		/* the horizontal distance of the line */
				dy=y1-y3;		/* the vertical distance of the line */
				x=x3; y=y3;
			}
			dxabs=fabs(dx);		//abs(dx); betekent de absolute waarde van
			dyabs=fabs(dy);		//abs(dy); same

			if (dxabs>=dyabs) /* the line is more horizontal than vertical */
			{
				slope=(float)dy / (float)dx;
				if(dx<0x80000000)	/*x is positive*/
				{
					for(i=0;i!=dx;i++)
					{
						px=i+x;
						py=slope*i+y;
						Draw_Line(mpx,mpy,px,py,1,color);
					}
				}
				else				/*x is negative*/
				{
					for(i=0;i!=dxabs;i++)
					{
						px=x-i;
						py=y-slope*i;
						Draw_Line(mpx,mpy,px,py,1,color);
					}
				}
			}
			else /* the line is more vertical than horizontal */
			{
				slope=(float)dx / (float)dy;
				if(dy<0x80000000)	/*y is positive*/
				{
					for(i=0;i!=dy;i++)
					{
						px=slope*i+x;
						py=y+i;
						Draw_Line(mpx,mpy,px,py,1,color);
					}
				}else				/*y is negative*/
				{
					for(i=0;i!=dyabs;i++)
					{
						px=x-slope*i;
						py=y-i;
						Draw_Line(mpx,mpy,px,py,1,color);
					}
				}
			}
		}
	}
}

void Draw_Ellipse(unsigned short xp, unsigned short yp, unsigned short r1, unsigned short r2, short fill, unsigned short thickness, unsigned short colour)
{
	unsigned int len = 0;
	for(i=0; i<=r1; i++) {
		EllipseXPosArray[i] = xp - i;
		EllipseXPosArray[i + r1] = xp + r1 - i;
		EllipseXPosArray[i + r1*2] = xp + i;
		EllipseXPosArray[i + r1*3] = xp - r1 + i;
	}

	for(i=0; i <= r1; i++) {
		EllipseYPosArray[i] = yp - sqrt((r2*r2) - ((r2*r2)*(i*i))/(r1*r1));
		EllipseYPosArray[r1*2-i] = yp - sqrt((r2*r2) - ((r2*r2)*(i*i))/(r1*r1));
		EllipseYPosArray[r1*2+i] = yp + sqrt((r2*r2) - ((r2*r2)*(i*i))/(r1*r1));
		EllipseYPosArray[r1*4-i] = yp + sqrt((r2*r2) - ((r2*r2)*(i*i))/(r1*r1));
	}

	if(fill==0) {
		if(thickness>1) {
			for(i=0; i < r1*2; i++)
				Draw_VerLine(EllipseXPosArray[i], EllipseYPosArray[i]+(thickness/2), thickness, colour);

			for(i=r1*2; i < r1*4; i++)
				Draw_VerLine(EllipseXPosArray[i], EllipseYPosArray[i]-(thickness/2), thickness, colour);
		} else {
			for(i=0; i < r1*4; i++)
				UB_VGA_SetPixel(EllipseXPosArray[i], EllipseYPosArray[i], colour);
		}
	} else {
		for(i=0; i < r1*2; i++) {
			len = yp-EllipseYPosArray[i];
			Draw_VerLine(EllipseXPosArray[i], EllipseYPosArray[i], len, colour);
		}

		for(i=r1*2; i <= r1*4; i++) {
			len = EllipseYPosArray[i]-yp;
			Draw_VerLine(EllipseXPosArray[i], yp, len, colour);
		}
	}
}

void Set_Single_Pixel(unsigned short xp, unsigned short yp, unsigned short colour )
{
	UB_VGA_SetPixel(xp,yp,colour);
}

void Clear_screen(unsigned short color)
{
	UB_VGA_FillScreen(color);
}

/*
 * The function Bitmap_to_VGA receives 2 parameters that define the begin position of the image on the screen (left top corner).
 * A third parameter defines how many times the image is printed on the screen
 */
void Bitmap_to_VGA(uint8_t xp, uint8_t yp, uint8_t repeat)
{
	int y_counter=0;
	int x_counter=0;
	int i=0;
	int j=0;
	int k=0;

	//errormessages
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

    for (y_counter=yp; y_counter<IMAGE_HEIGHT+yp; y_counter++)   //for loop for vertical pixels of image
	{
		for (x_counter=xp; x_counter<IMAGE_WIDTH+xp; x_counter++)  //for loop for horizontal pixels of image
		{
//				UB_VGA_SetPixel(x_counter, y_counter);
			i++; // i loopt tot Image_heigth*Image_width

			if (i==IMAGE_HEIGHT*IMAGE_WIDTH)	// Print duplicate of image next to it

				for(j=0; j<5000; j++)
				{
					//delay
				}
				for(k=0; k<repeat; k++)
					UB_VGA_SetPixel(x_counter+IMAGE_WIDTH*k, y_counter, image[i]);

		}
	}

}

