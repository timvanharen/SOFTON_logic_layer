#include "main.h"
#include <stm32f4xx_rcc.h>

static int G_CLK;
static int D_uS; // static variable (us)
static int D_nS; // static variable (ns)

statusFlag Processing_input_request(char * inputString)
{
	// is request valid yes or no
	// yes translate string to draw command
	// no return ErrorFlag
	return CompleteFlag;
}

//void demo_apps()
//{
//	k = 160+50*sin(i/2);
//	m = 120+50*cos(i/2);
//	if (i%10==0) {
//		l++;
//	  }
//	Draw_Ellipse(k, m, 50, 50, 1, 1, l);
//}

void delay_init()
{
	RCC_ClocksTypeDef Clocks;
	RCC_GetClocksFreq(&Clocks);
	G_CLK = Clocks.SYSCLK_Frequency;	// Read the systemclock
	D_uS = (G_CLK*1.25)/90000000/2; // Number of instructions in one microsecond
	D_nS = (G_CLK*1.25)/90000000000/2; // Number of instructions in one nanosecond

}

void settlingTime(volatile unsigned int time, char dim) //wait msec
{
	switch (dim) {
	case 's'  : time *= 1000000000;
	case 'm' :	time *= 1000000;
	case 'u' : 	time *= 1000;
	case 'n' : break;
	}
    volatile unsigned int i;

    while(time>0)		// Run x times 1 millisecond
    {
        for(i=0;i<D_nS;i++);
        time--;
    }
}
