#include "includes.h"
#include "draw_char.h"
#include "bfc_latin_font.h"

uint16_t draw_character(uint16_t xp, uint16_t yp, int c, uint8_t color, f_name font_name, f_type font_type, uint8_t font_size, uint8_t bg)
{
    uint8_t  i, j , k, bit = 0 ;
	UCHAR  	pTemp ;
	UCHAR  *pData ;
  	USHORT 	char_height;
	UCHAR  	char_index;
	UCHAR  	char_width;
	ULONG  	char_offset;

	USHORT quotient  = 1 ;
	USHORT divisor   = 8 ;
    USHORT remainder = 0 ;

    extern const BFCLATIN_FONT fontTimes_New_Roman_bold_size8;		//take all font structs
   	extern const BFCLATIN_FONT fontTimes_New_Roman_bold_size12;
   	extern const BFCLATIN_FONT fontTimes_New_Roman_bold_size20;
   	extern const BFCLATIN_FONT fontTimes_New_Roman_reg_size8;
   	extern const BFCLATIN_FONT fontTimes_New_Roman_reg_size12;
   	extern const BFCLATIN_FONT fontTimes_New_Roman_reg_size20;
   	extern const BFCLATIN_FONT fontComic_Sans_bold_size8;
   	extern const BFCLATIN_FONT fontComic_Sans_bold_size12;
   	extern const BFCLATIN_FONT fontComic_Sans_bold_size20;
   	extern const BFCLATIN_FONT fontComic_Sans_reg_size8;
   	extern const BFCLATIN_FONT fontComic_Sans_reg_size12;
   	extern const BFCLATIN_FONT fontComic_Sans_reg_size20;


   	if (font_name == Times_New_Roman && font_type == bold && font_size == 8 )
	{
		//UART_puts("  Detected: fontTimes_New_Roman_bold_size8 \n") ;
	  	 char_height 	=  fontTimes_New_Roman_bold_size8.Height;
	   	 char_index 	=  fontTimes_New_Roman_bold_size8.index_table[c];
	   	 char_width  	=  fontTimes_New_Roman_bold_size8.width_table[char_index];
	   	 char_offset 	=  fontTimes_New_Roman_bold_size8.offset_table[char_index];
	   	 pData     	= &fontTimes_New_Roman_bold_size8.data_table[char_offset];
	}
	else if (font_name == Times_New_Roman && font_type == bold && font_size == 12  )
	{
		//UART_puts("  Detected: fontTimes_New_Roman_bold_size12 \n") ;
	  	 char_height 	=  fontTimes_New_Roman_bold_size12.Height;
	   	 char_index 	=  fontTimes_New_Roman_bold_size12.index_table[c];
	   	 char_width  	=  fontTimes_New_Roman_bold_size12.width_table[char_index];
	   	 char_offset 	=  fontTimes_New_Roman_bold_size12.offset_table[char_index];
	   	 pData     	= &fontTimes_New_Roman_bold_size12.data_table[char_offset];
	}
	else if (font_name == Times_New_Roman && font_type == bold && font_size == 20 )
	{
		//UART_puts("  Detected: fontTimes_New_Roman_bold_size20 \n") ;
	  	 char_height 	=  fontTimes_New_Roman_bold_size20.Height;
	   	 char_index 	=  fontTimes_New_Roman_bold_size20.index_table[c];
	   	 char_width  	=  fontTimes_New_Roman_bold_size20.width_table[char_index];
	   	 char_offset 	=  fontTimes_New_Roman_bold_size20.offset_table[char_index];
	   	 pData     	= &fontTimes_New_Roman_bold_size20.data_table[char_offset];
	}
	else if (font_name == Times_New_Roman && font_type == regular && font_size == 8 )
	{
		//UART_puts("  Detected: fontTimes_New_Roman_reg_size8 \n") ;
	  	 char_height 	=  fontTimes_New_Roman_reg_size8.Height;
	   	 char_index 	=  fontTimes_New_Roman_reg_size8.index_table[c];
	   	 char_width  	=  fontTimes_New_Roman_reg_size8.width_table[char_index];
	   	 char_offset 	=  fontTimes_New_Roman_reg_size8.offset_table[char_index];
	   	 pData     	= &fontTimes_New_Roman_reg_size8.data_table[char_offset];
	}
	else if (font_name == Times_New_Roman && font_type == regular && font_size == 12 )
	{
		//UART_puts("  Detected: fontTimes_New_Roman_reg_size12 \n") ;
	  	 char_height 	=  fontTimes_New_Roman_reg_size12.Height;
	   	 char_index 	=  fontTimes_New_Roman_reg_size12.index_table[c];
	   	 char_width  	=  fontTimes_New_Roman_reg_size12.width_table[char_index];
	   	 char_offset 	=  fontTimes_New_Roman_reg_size12.offset_table[char_index];
	   	 pData     	= &fontTimes_New_Roman_reg_size12.data_table[char_offset];
	}
	else if ( font_name == Times_New_Roman && font_type == regular && font_size == 20 )
	{
		//UART_puts("  Detected: fontTimes_New_Roman_bold_size20 \n") ;
	  	 char_height 	=  fontTimes_New_Roman_reg_size20.Height;
	   	 char_index 	=  fontTimes_New_Roman_reg_size20.index_table[c];
	   	 char_width  	=  fontTimes_New_Roman_reg_size20.width_table[char_index];
	   	 char_offset 	=  fontTimes_New_Roman_reg_size20.offset_table[char_index];
	   	 pData     	= &fontTimes_New_Roman_reg_size20.data_table[char_offset];
	}



	else if (font_name == Comic_sans && font_type == bold && font_size == 8 )
	{
		//UART_puts("  Detected: fontComic_Sans_bold_size8 \n") ;
	  	 char_height 	=  fontComic_Sans_bold_size8.Height;
	   	 char_index 	=  fontComic_Sans_bold_size8.index_table[c];
	   	 char_width  	=  fontComic_Sans_bold_size8.width_table[char_index];
	   	 char_offset 	=  fontComic_Sans_bold_size8.offset_table[char_index];
	   	 pData     	= &fontComic_Sans_bold_size8.data_table[char_offset];
	}
	else if (font_name == Comic_sans && font_type == bold && font_size == 12 )
	{
		//UART_puts("  Detected: fontComic_Sans_bold_size12 \n") ;
	  	 char_height 	=  fontComic_Sans_bold_size12.Height;
	   	 char_index 	=  fontComic_Sans_bold_size12.index_table[c];
	   	 char_width  	=  fontComic_Sans_bold_size12.width_table[char_index];
	   	 char_offset 	=  fontComic_Sans_bold_size12.offset_table[char_index];
	   	 pData     	= &fontComic_Sans_bold_size12.data_table[char_offset];
	}
	else if (font_name == Comic_sans && font_type == bold && font_size == 20 )
	{
		//UART_puts("  Detected: fontComic_Sans_bold_size20 \n") ;
	  	 char_height 	=  fontComic_Sans_bold_size20.Height;
	   	 char_index 	=  fontComic_Sans_bold_size20.index_table[c];
	   	 char_width  	=  fontComic_Sans_bold_size20.width_table[char_index];
	   	 char_offset 	=  fontComic_Sans_bold_size20.offset_table[char_index];
	   	 pData     	= &fontComic_Sans_bold_size20.data_table[char_offset];
	}
	else if (font_name == Comic_sans && font_type == regular && font_size == 8 )
	{
		//UART_puts("  Detected: fontComic_Sans_reg_size20 \n") ;
	  	 char_height 	=  fontComic_Sans_reg_size8.Height;
	   	 char_index 	=  fontComic_Sans_reg_size8.index_table[c];
	   	 char_width  	=  fontComic_Sans_reg_size8.width_table[char_index];
	   	 char_offset 	=  fontComic_Sans_reg_size8.offset_table[char_index];
	   	 pData     	= &fontComic_Sans_reg_size8.data_table[char_offset];
	}
	else if (font_name == Comic_sans && font_type == regular && font_size == 12 )
	{
		//UART_puts("  Detected: fontComic_Sans_reg_size12 \n") ;
	  	 char_height 	=  fontComic_Sans_reg_size12.Height;
	   	 char_index 	=  fontComic_Sans_reg_size12.index_table[c];
	   	 char_width  	=  fontComic_Sans_reg_size12.width_table[char_index];
	   	 char_offset 	=  fontComic_Sans_reg_size12.offset_table[char_index];
	   	 pData     	= &fontComic_Sans_reg_size12.data_table[char_offset];
	}
	else if (font_name == Comic_sans && font_type == regular && font_size == 20 )
	{
		//UART_puts("  Detected: fontComic_Sans_reg_size20 \n") ;
	  	 char_height 	=  fontComic_Sans_reg_size20.Height;
	   	 char_index 	=  fontComic_Sans_reg_size20.index_table[c];
	   	 char_width  	=  fontComic_Sans_reg_size20.width_table[char_index];
	   	 char_offset 	=  fontComic_Sans_reg_size20.offset_table[char_index];
	   	 pData     	= &fontComic_Sans_reg_size20.data_table[char_offset];
	}

	quotient  = char_width / divisor ;
	remainder = char_width % divisor ;

	if ( remainder > 0 ) quotient += 1 ;


	for ( i=0 ; i < char_height ; i++)		//ypos
	{

		for ( j = 0 ; j < quotient ; j++ ) // per byte per character line(height)
		{
			pTemp = *(pData + (i * quotient) + j ) ; //inhoud juiste byte
			for ( k = 0  ; k < divisor ; k++ ) // per aantal bits per data
			{
				bit = (pTemp >> (divisor-(k+1))) & 0b1;	//get hex font character val to separated bits.
				if ((j*divisor)+k >= char_width) break;
				if (bit == 1)	{									// if true fill screen else put in background.
					UB_VGA_SetPixel((xp+(j*divisor)+k),(yp+i), color);
				}
				else	{
					UB_VGA_SetPixel((xp+(j*divisor)+k),(yp+i), bg);
				}
			}
		}
	}
	return (uint16_t)char_width;
}



void draw_sentence( uint16_t xp, uint16_t yp, char *sent, uint8_t color, f_name font_name, f_type font_type, uint8_t font_size, uint8_t bg)
{
	int j = 0;
	UCHAR old_charW = 0;
	uint16_t new_charW;
	int sent_length = strlen(sent);

	for ( j=0 ; j <= sent_length ; j++)
	{
		new_charW = draw_character(xp+=old_charW, yp, *(sent+j), color, font_name, font_type, font_size,  bg);
		old_charW = new_charW;
	}
}
