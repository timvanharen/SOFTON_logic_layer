/*
 *****************************************************************
 *!	\file		presentation.h
 *	\brief		Header file of presentation.c.
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
#ifndef PRESENTATION_H
#define PRESENTATION_H

/*
 *****************************************************************
 *	Includes
 *****************************************************************
 */
#include "stm32f4xx.h"

/*
 *****************************************************************
 *	Typedefs
 *****************************************************************
 */
typedef enum
 {
	tekst, ellips, rechthoek, driehoek, lijn, wacht, bitmap
 } request ;

/*
 *****************************************************************
 *	Function prototypes & documentation
 *****************************************************************
 */

/*!	\fn 	int line_split(char *str, char separator, char ***array, int *length)
 *	\brief 	.
 *	\param 	*str
 *	\param 	separator
 *	\param	***array
 *	\param	*length
 *	\return	0
 *	\remark \b Memory
 *	\remark \b Milestone
 */
int line_split(char *str, char separator, char ***array, int *length);
/*!	\fn 	void Request_Handling(char** res)
 *	\brief 	.
 *	\param 	**res
 *	\remark \b Memory
 *	\remark \b Milestone
 */
void Request_Handling(char** res);
/*!	\fn 	void put_usage()
 *	\brief 	The instructions of how you should use the software with the terminal, to be printed in the terminal.
 *	\param 	**res
 *	\remark \b Memory
 *	\remark \b Milestone
 */
void put_usage();

/*
 ********************************************************************************************************************
 * There are no prototypes of the following functions, because they are static. They are only used in the related .c
 * file and not outside of it.
 ********************************************************************************************************************
 */

/*!	\fn 	static void Text_Request(char** res)
 *	\brief 	.
 *	\param 	**res
 *	\remark \b Memory
 *	\remark \b Milestone
 */
/*!	\fn 	static void Ellipse_Request(char** res)
 *	\brief 	.
 *	\param 	**res
 *	\remark \b Memory
 *	\remark \b Milestone
 */
/*!	\fn 	static void Line_Request(char** res)
 *	\brief 	.
 *	\param 	**res
 *	\remark \b Memory
 *	\remark \b Milestone
 */
/*!	\fn 	static void Rectangle_Request(char** res)
 *	\brief 	.
 *	\param 	**res
 *	\remark \b Memory
 *	\remark \b Milestone
 */
/*!	\fn 	static void Triangle_Request(char** res)
 *	\brief 	.
 *	\param 	**res
 *	\remark \b Memory
 *	\remark \b Milestone
 */
/*!	\fn 	static void Wait_request(char** res)
 *	\brief 	.
 *	\param 	**res
 *	\remark \b Memory
 *	\remark \b Milestone
 */
/*!	\fn 	static void Clear_Request(char** res)
 *	\brief 	.
 *	\param 	**res
 *	\remark \b Memory
 *	\remark \b Milestone
 */
/*!	\fn 	static void Bitmap_Request(char** res)
 *	\brief 	.
 *	\param 	**res
 *	\remark \b Memory
 *	\remark \b Milestone
 */

#endif // PRESENTATIONs_H
