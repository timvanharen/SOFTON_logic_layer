/*
*********************************************************************************************************
*
*                                           MASTER INCLUDES
*
*                                     ST Microelectronics STM32
*                                              with the
*
*                                           STM3240G-EVAL
*                                         Evaluation Board
*
* Filename      : includes.h
* Version       : V1.00
* Programmer(s) : van der Bent
* 				: COOcox
*
*  07-07-2014 toevoeging van false en true defines
*********************************************************************************************************
*/

#ifndef  INCLUDES_PRESENT
#define  INCLUDES_PRESENT
#define OS_MASTER_FILE
/*
*********************************************************************************************************
*                                         STANDARD LIBRARIES
*********************************************************************************************************
*/

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <bfc_latin_font.h>

/*
*********************************************************************************************************
*                                                 OS
*********************************************************************************************************
*/

#include "misc.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_usart.h"
#include "stm32_ub_vga_screen.h"
#include "uart.h"
#include "delay.h"
#include "Draw_request.h"
#include "presentation.h"

/*
*********************************************************************************************************
*                                            INCLUDES END
*********************************************************************************************************
*/

#define MAX_LINE_SIZE 64

#define TRUE		1
#define FALSE		0


#endif

