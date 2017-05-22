
#include "main.h"
#include "Draw_request.h"
#include "stm32_ub_vga_screen.h"
#include <math.h>
#include "apllication.h"
#include "stm32f4xx_rcc.h"

static int i,j=0;
short EllipseXPosArray[1000];
short EllipseYPosArray[1000];

//static BitMapImage image[VGA_DISPLAY_Y*VGA_DISPLAY_X];
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
				DrawVerLine(EllipseXPosArray[i], EllipseYPosArray[i]+(thickness/2), thickness, colour);

			for(i=r1*2; i < r1*4; i++)
				DrawVerLine(EllipseXPosArray[i], EllipseYPosArray[i]-(thickness/2), thickness, colour);
		} else {
			for(i=0; i < r1*4; i++)
				UB_VGA_SetPixel(EllipseXPosArray[i], EllipseYPosArray[i], colour);
		}
	} else {
		for(i=0; i < r1*2; i++) {
			len = yp-EllipseYPosArray[i];
			DrawVerLine(EllipseXPosArray[i], EllipseYPosArray[i], len, colour);
		}

		for(i=r1*2; i <= r1*4; i++) {
			len = EllipseYPosArray[i]-yp;
			DrawVerLine(EllipseXPosArray[i], yp, len, colour);
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
