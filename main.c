/*
 ******************************************************************
 *! \file		main.c
 *	\brief		the main function for softon practical
 *	\datum		Mei 2017
 *	\version	1.0
 *	\author		SOFTON groep 9, Irisjka, Tim, Alessandro en Mansur
 *
 *	CPU			STM32F4
 *	IDE			CooCox CoIDE 1.7.x
 *	Module		CMSIS_BOOT, M4_CMSIS_CORE
 ******************************************************************
 */

#include "includes.h"
#include "main.h"

int main()
{
	SystemInit(); 							// System speed to 168MHz
	UB_VGA_Screen_Init(); 					// Init VGA-Screen
	UB_VGA_FillScreen(VGA_COL_BLACK);
	TIMER3_Initialize();
	UART_init();

	put_usage();

	char input_line[MAX_LINE_SIZE] = "" ;	// malloc(buffer_size * sizeof(char));
    int count,k=0;
    char separator=',';
	char **res;								//  res is a pointer to a string pointer

    while(TRUE)
    {
    	UART_gets(input_line, 0);							//get single request
    	line_split( input_line, separator, &res, &count );	//split into array res. get nr of elements count

    	for( k=0; k<=count; k++ )
    	{
    		UART_putint(k); UART_puts(": ");
    		if ( res[k] != NULL )
    		{
    			UART_puts(res[k]); UART_puts("   ");
    		}
    		else UART_puts("NULL");
    	}
    	UART_puts("\r\n");

    	Request_Handling(res);
    }
}
