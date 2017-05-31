/****************************************************************************
*                                                                           *
* Copyright (c) 2013, Iseatech Software. All rights reserved.				*
* Internet: http://www.iseasoft.com/bitfontcreator.htm						*
* Support:  support@iseatech.com										    *
*                                                                           *
*****************************************************************************
*																			*
* @file      BFC_LATIN_font.h												*
* @version   0.3.0.1														*
* @date      Mar-29-2016													*
* @brief     BitFontCreator (Latin Version) font header include file		*
*																			*
*****************************************************************************/

#ifndef __BFC_LATIN_FONT_H_

#define __BFC_LATIN_FONT_H_

#define UCHAR	unsigned char 
#define USHORT	unsigned short
#define ULONG	unsigned long

/*********************************************************************
*       C font structures
**********************************************************************/
typedef struct
{
	ULONG		Flags;			/* font flags: FONT_PACK_BITORDER_BIGEND | FONT_PACK_SCANBASED_ROW | ... */
	USHORT		Width;			/* font width in pixels. 0 for proportional font */
	USHORT		Height;			/* font height in pixels */
	USHORT		Baseline;		/* font ascent (baseline) in pixels */
	UCHAR		FirstChar;		/* first character */
	UCHAR		LastChar;		/* last character */
	const UCHAR	 *data_table;	/* pointer to the imagebits data table */
	const ULONG	 *offset_table;	/* pointer to the offsets of the first byte of each character. 0 if this table does not needed */
	const UCHAR  *width_table;	/* pointer to the width of each character. 0 if this table does not needed */
	const UCHAR	 *index_table;	/* used to find the index of an ascii character[0-255]. 0 if this table does not needed */
} BFCLATIN_FONT;



#endif /* #ifndef __BFC_LATIN_FONT_H_ */
