/****************************************************************************
*                                                                           *
* Copyright (c) 2013, Iseatech Software. All rights reserved.				*
* Internet: http://www.iseasoft.com/bitfontcreator.htm						*
* Support:  support@iseatech.com										    *
*                                                                           *
*****************************************************************************
*																			*
* @file      bfc_latin_font.h												*
* @version   0.3.0.0														*
* @date      Oct-15-2013													*
* @brief     BitFontCreator (Latin Version) font header include file		*
*																			*
*****************************************************************************/

#ifndef __BFC_LATIN_FONT_H_

#if defined(__cplusplus)
extern "C" {     /* Make sure we have C-declarations in C++ programs */
#endif

#define __BFC_LATIN_FONT_H_

#define UCHAR	unsigned char 		// 255 (2^8-1, 8 bits) or greater*
#define USHORT	unsigned short		// 65535 (2^16-1, 16 bits ) or greater*
#define UINT	unsigned int 		// 65535 (2^16-1, 16 bits) or greater*
#define ULONG	unsigned long 		// 4294967295 (2^32-1, 32 bits, ) or greater*
#define ULLNG	unsigned long long  // (2^64-1,  64 bits )

/* font flags */
#define FONT_PACK_BITORDER 0x01
#define FONT_PACK_BITORDER_BIGEND 0
#define FONT_PACK_BITORDER_LITTLEEND 0x01

#define FONT_PACK_SCANBASED 0x02
#define FONT_PACK_SCANBASED_ROW 0
#define FONT_PACK_SCANBASED_COLUMN 0x02

#define FONT_PACK_SCANPREFERRED 0x04
#define FONT_PACK_SCANPREFERRED_ROW 0
#define FONT_PACK_SCANPREFERRED_COLUMN 0x04

#define FONT_PACK_COMPRESSED 0x08
#define FONT_PACK_COMPRESSED_OFF 0
#define FONT_PACK_COMPRESSED_ON 0x08

#define FONT_PACK_DATA_LEN 0x030
#define FONT_PACK_DATA_LEN_8B 0x00
#define FONT_PACK_DATA_LEN_16B 0x10
#define FONT_PACK_DATA_LEN_32B 0x20


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
	const  UCHAR	*data_table;	/* pointer to the imagebits data table */
	const  ULONG	*offset_table;	/* pointer to the offsets of the first byte of each character. 0 if this table is not needed */
	const  UCHAR	*width_table;	/* pointer to the width of each character. 0 if this table does not needed */
	const  UCHAR	*index_table;	/* used to find the index of an ascii character[0-255]. 0 if this table does not needed */
} BFCLATIN_FONT;


/*********************************************************************
*       Binary font structures (BIN)
**********************************************************************/
typedef struct
{
	USHORT		Magic;			/* magic number = 0xBFCA, created by BitFontCreator Latin version */
	USHORT		Flags;			/* font flags: FONT_PACK_BITORDER_BIGEND | FONT_PACK_SCANBASED_ROW | ... */
	USHORT		Width;			/* font width in pixels. 0 for proportional font */	
	USHORT		Height;			/* font height in pixels */	
	USHORT		Baseline;		/* font ascent (baseline) in pixels */
	USHORT		FirstChar;		/* first character */
	USHORT		LastChar;		/* last character */
	USHORT		Reversed;		/* reversed, = 0 */
} BFCLATIN_BIN_FONT;

typedef struct 
{
	USHORT		Width;			/* character width in pixels */
	USHORT		Size;			/* # bytes of the character imagebits data */
	ULONG		Offset;			/* Offset to the character imagebits data */	
} BFCLATIN_BIN_CHARINFO;

#ifdef __cplusplus
}
#endif

#endif /* #ifndef __BFC_LATIN_FONT_H_ */
