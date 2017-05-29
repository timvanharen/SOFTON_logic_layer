#include "includes.h"

uint16_t draw_character(int char_input, int font_name, int font_type, uint8_t out_size, uint16_t xp, uint16_t yp, uint8_t color, uint8_t bg)
{
	#include "bfclatin_font.h"

	typedef enum {  debug_off, debug_lvl1, debug_lvl2, debug_lvl3	  }  Debugs_Def ;
	Debugs_Def  debug_lvl  = debug_lvl3 ;
	const UCHAR  *pData_In  ;
//	const UCHAR  *pData_Out ;
	UCHAR   pTemp_In  ;
//	UCHAR	pTemp_Out ;
  	USHORT 	char_height;
	UCHAR  	char_index;
	UCHAR  	char_width;
	ULONG  	char_offset;

	USHORT quotient  = 1 ;
	USHORT divisor   = 8 ;
    USHORT remainder = 0 ;

	//   set some enumerations
	// char char_input[MAX_LINE_SIZE] = "" ;
    UINT  i, j , k, q = 0 ;

	// UINT debug_info =  0 ;
	UINT  in_size 	= 72 ;
//	UINT  out_size 	= 16 ;

	UINT  bits_size =  8 ;
	UINT  leveling 	=  100 ;


    extern const BFCLATIN_FONT font_Arial_regular_s72;		//take all font structs
   	extern const BFCLATIN_FONT font_Arial_bold_s72;
   	extern const BFCLATIN_FONT font_Arial_italic_s72;
   	extern const BFCLATIN_FONT font_Times_New_Roman_regular_s72;
   	extern const BFCLATIN_FONT font_Times_New_Roman_bold_s72;
   	extern const BFCLATIN_FONT font_Times_New_Roman_italic_s72;
   	extern const BFCLATIN_FONT font_Rockwell_regular_s72;
   	extern const BFCLATIN_FONT font_Rockwell_bold_s72;
   	extern const BFCLATIN_FONT font_Rockwell_italic_s72;
   	extern const BFCLATIN_FONT font_Georgia_regular_s72;
   	extern const BFCLATIN_FONT font_Georgia_bold_s72;
   	extern const BFCLATIN_FONT font_Georgia_italic_s72;
   	extern const BFCLATIN_FONT font_Mistral_bold_s72;
   	extern const BFCLATIN_FONT font_Mistral_regular_s72;


	if 		(font_name == 0 && font_type == 0)
	{
		if ( debug_lvl > debug_off ) UART_puts("    Detect font_Arial_regular_s72 \n") ;
		char_height =  font_Arial_regular_s72.Height;
		char_index  =  font_Arial_regular_s72.index_table[char_input];
		char_width  =  font_Arial_regular_s72.width_table[char_index];
		char_offset =  font_Arial_regular_s72.offset_table[char_index];
		pData_In    = &font_Arial_regular_s72.data_table[char_offset];
	}
	else if (font_name == 0 && font_type == 1)
	{
		if ( debug_lvl > debug_off ) UART_puts("    Detect font_Arial_bold_s72 \n") ;
		char_height =  font_Arial_bold_s72.Height;
		char_index  =  font_Arial_bold_s72.index_table[char_input];
		char_width  =  font_Arial_bold_s72.width_table[char_index];
		char_offset =  font_Arial_bold_s72.offset_table[char_index];
		pData_In    = &font_Arial_bold_s72.data_table[char_offset];
	}
	else if (font_name == 0 && font_type == 2)
	{
		if ( debug_lvl > debug_off ) UART_puts("    Detect font_Arial_italic_s72 \n") ;
		char_height =  font_Arial_italic_s72.Height;
		char_index  =  font_Arial_italic_s72.index_table[char_input];
		char_width  =  font_Arial_italic_s72.width_table[char_index];
		char_offset =  font_Arial_italic_s72.offset_table[char_index];
		pData_In    = &font_Arial_italic_s72.data_table[char_offset];
	}


	//  Times_New_Roman

	else if (font_name == 1 && font_type == 0)
	{
		if ( debug_lvl > debug_off ) UART_puts("Detect font_Times_New_Roman_regular_s72 \n") ;
		char_height =  font_Times_New_Roman_regular_s72.Height;
		char_index  =  font_Times_New_Roman_regular_s72.index_table[char_input];
		char_width  =  font_Times_New_Roman_regular_s72.width_table[char_index];
		char_offset =  font_Times_New_Roman_regular_s72.offset_table[char_index];
		pData_In    = &font_Times_New_Roman_regular_s72.data_table[char_offset];
	}

	else if (font_name == 1 && font_type == 1)
	{
		if ( debug_lvl > debug_off ) UART_puts("Detect font_Times_New_Roman_bold_s72 \n") ;
		char_height =  font_Times_New_Roman_bold_s72.Height;
		char_index  =  font_Times_New_Roman_bold_s72.index_table[char_input];
		char_width  =  font_Times_New_Roman_bold_s72.width_table[char_index];
		char_offset =  font_Times_New_Roman_bold_s72.offset_table[char_index];
		pData_In    = &font_Times_New_Roman_bold_s72.data_table[char_offset];
	}
	else if (font_name == 1 && font_type == 2)
	{
		if ( debug_lvl > debug_off ) UART_puts("Detect font_Times_New_Roman_italic_s72 \n") ;
		char_height =  font_Times_New_Roman_italic_s72.Height;
		char_index  =  font_Times_New_Roman_italic_s72.index_table[char_input];
		char_width  =  font_Times_New_Roman_italic_s72.width_table[char_index];
		char_offset =  font_Times_New_Roman_italic_s72.offset_table[char_index];
		pData_In    = &font_Times_New_Roman_italic_s72.data_table[char_offset];
	}

	// Rockwell

	else if (font_name == 2 && font_type == 0)
	{
		if ( debug_lvl > debug_off ) UART_puts("Detect font_Rockwell_regular_s72 \n") ;
		char_height =  font_Rockwell_regular_s72.Height;
		char_index  =  font_Rockwell_regular_s72.index_table[char_input];
		char_width  =  font_Rockwell_regular_s72.width_table[char_index];
		char_offset =  font_Rockwell_regular_s72.offset_table[char_index];
		pData_In    = &font_Rockwell_regular_s72.data_table[char_offset];
	}

	else if (font_name == 2 && font_type == 1)
	{
		if ( debug_lvl > debug_off ) UART_puts("Detect font_Rockwell_bold_s72 \n") ;
		char_height =  font_Rockwell_bold_s72.Height;
		char_index  =  font_Rockwell_bold_s72.index_table[char_input];
		char_width  =  font_Rockwell_bold_s72.width_table[char_index];
		char_offset =  font_Rockwell_bold_s72.offset_table[char_index];
		pData_In    = &font_Rockwell_bold_s72.data_table[char_offset];
	}

	else if (font_name == 2 && font_type == 2)
	{
		if ( debug_lvl > debug_off ) UART_puts("Detect font_Rockwell_italic_s72 \n") ;
		char_height =  font_Rockwell_italic_s72.Height;
		char_index  =  font_Rockwell_italic_s72.index_table[char_input];
		char_width  =  font_Rockwell_italic_s72.width_table[char_index];
		char_offset =  font_Rockwell_italic_s72.offset_table[char_index];
		pData_In    = &font_Rockwell_italic_s72.data_table[char_offset];
	}


	//  Georgia

	else if (font_name == 3 && font_type == 0)
	{
		if ( debug_lvl > debug_off ) UART_puts("Detect font_Georgia_regular_s72 \n") ;
		char_height =  font_Georgia_regular_s72.Height;
		char_index  =  font_Georgia_regular_s72.index_table[char_input];
		char_width  =  font_Georgia_regular_s72.width_table[char_index];
		char_offset =  font_Georgia_regular_s72.offset_table[char_index];
		pData_In    = &font_Georgia_regular_s72.data_table[char_offset];
	}

	else if (font_name == 3 && font_type == 1)
	{
		if ( debug_lvl > debug_off ) UART_puts("Detect font_Georgia_bold_s72 \n") ;
		char_height =  font_Georgia_bold_s72.Height;
		char_index  =  font_Georgia_bold_s72.index_table[char_input];
		char_width  =  font_Georgia_bold_s72.width_table[char_index];
		char_offset =  font_Georgia_bold_s72.offset_table[char_index];
		pData_In    = &font_Georgia_bold_s72.data_table[char_offset];
	}

	else if (font_name == 3 && font_type == 2)
	{
		if ( debug_lvl > debug_off ) UART_puts("Detect font_Georgia_italic_s72 \n") ;
		char_height =  font_Georgia_italic_s72.Height;
		char_index  =  font_Georgia_italic_s72.index_table[char_input];
		char_width  =  font_Georgia_italic_s72.width_table[char_index];
		char_offset =  font_Georgia_italic_s72.offset_table[char_index];
		pData_In    = &font_Georgia_italic_s72.data_table[char_offset];
	}

	//  Mistral

	else if ( font_name == 4 && ( font_type == 0 || font_type == 2 )  )
	{
		if ( debug_lvl > debug_off ) UART_puts("Detect font_Mistral_regular_s72 \n") ;
		char_height =  font_Mistral_regular_s72.Height;
		char_index  =  font_Mistral_regular_s72.index_table[char_input];
		char_width  =  font_Mistral_regular_s72.width_table[char_index];
		char_offset =  font_Mistral_regular_s72.offset_table[char_index];
		pData_In    = &font_Mistral_regular_s72.data_table[char_offset];
	}

	else if (font_name == 4 && font_type == 1)
	{
		if ( debug_lvl > debug_off ) UART_puts("Detect font_Mistral_bold_s72 \n") ;
		char_height =  font_Mistral_bold_s72.Height;
		char_index  =  font_Mistral_bold_s72.index_table[char_input];
		char_width  =  font_Mistral_bold_s72.width_table[char_index];
		char_offset =  font_Mistral_bold_s72.offset_table[char_index];
		pData_In    = &font_Mistral_bold_s72.data_table[char_offset];
	}
	else
	{
		if ( debug_lvl > debug_off ) UART_puts("Invallid Font \n") ;
		return(-1);
	}


	quotient  = char_width / divisor ;
	remainder = char_width % divisor ;
	if ( remainder > 0 ) quotient += 1 ;

	UINT sf_f_div = in_size / out_size ;  	//  scale factor (sf) for font size divider
	UINT sf_f_rem = in_size % out_size ;  	//  scale factor (sf) for font size reminder

	UINT ss_f = sf_f_div ;
	if ( sf_f_rem > 0 ) ss_f =  ss_f + 1 ;		//  sample size  (ss) for font (global)

	UINT sf_w_div = char_width / ss_f  ;  		//  scale factor (sf) for font width divider
	UINT sf_w_rem = char_width % ss_f  ;  		//  scale factor (sf) for font width reminder
	UINT sa_w = sf_w_div ;
	if ( sf_w_rem > 0 ) sa_w =  sa_w + 1 ;		//  number of samples in width (sa_w) for font (width)

	int nbr_w_jump = sa_w * ss_f - char_width ;			//  number of -1 jump backs required.
	int mod_w_jump = char_width / ( nbr_w_jump + 1 ) ; 	//  jump -1 back every modulo mod_w_jump bits

	UINT sf_h_div = char_height / ss_f ;  		//  scale factor (sf) for font height divider
	UINT sf_h_rem = char_height % ss_f ; 		//  scale factor (sf) for font height reminder

	UINT sa_h = sf_h_div ;
	if ( sf_h_rem > 0 ) sa_h =  sa_h + 1 ;		//  number of samples in height (sa_h) for font (height)

	UINT nbr_h_jump = sa_h * ss_f - char_height ;			//  number of -1 jump backs required.
	UINT mod_h_jump = char_height / ( nbr_h_jump + 1 ) ; 	//  jump -1 back every modulo mod_w_jump bits


	UINT h_in  = char_height ;
	UINT h_out = sa_h ;
	UINT w_in  = char_width ;
	UINT w_out = sa_w ;
	UINT r, s = 0;

// First: Initialize a boolean array representing the sample  character
	//        for allowing samping over de edges, add the sample size in
	//        both the width and height directions
	///
	// bool B_Array_Source[ h_in + ss_f ][ w_in + ss_f ];
	UINT I_Array_Source[ h_in + ss_f ][ w_in + ss_f ];

// Second: initialize all cells with false
	for( i = 0; i < h_in + ss_f; i++)
	{
		// printf("%d, ", i );
		for( j = 0; j < w_in + ss_f; j++)
		{
		  	// B_Array_Source[i][j] = false ;
		   	I_Array_Source[i][j] = 0 ;
		}
 	}

	if ( debug_lvl > debug_off ) UART_puts("	Initialisation of Source Array done\n");

// Third: fill all cells with 'true' where the actual character has a bit set to '1'
	for ( i  = 0 ; i < h_in ; i++)
	{
		for ( q = 0 ; q < quotient ; q++ )
		{
			pTemp_In = *( pData_In + i * quotient + q ) ;
			for ( k = bits_size - 1  ; k >= 0 ; k-- )
			{
				r += 1 ;
				j = bits_size * q + ( bits_size - k ) ;
				if ( j <= char_width )
				{
					if ( 1 & ( pTemp_In >> k ) )
					{
						// B_Array_Source[i][j] = true ;
						I_Array_Source[i][j] = 1 ;
					}
				}
				if ( k <= 0 ) break ;
			}
		}
	}


	// Initialize an integer array representing the resulting character (# = 1 )
	UINT I_Array_Result[h_out][w_out];
	// Now initialize all cells with false

	for( i = 0; i < h_out; i++)
	   	for( j = 0; j < w_out; j++)
	   	{
		   	//B_Array_Result[i][j] = false;
    		I_Array_Result[i][j] = 0;
		}


 	/*
	 *                              s = 1 2 3 4 5
	 *                                  |       |
	 *                                  v       v
	 *				1 1 1 1 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
	 *				1 1 1 1 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0      i
	 *				1 1 1 1 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0      =
	 *		r		1 1 1 1 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
	 *		=		1 1 1 1 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0      0
	 *		1 ->	0 0 0 0 0 0 0 0 0 0 1 1 1 1 1 0 0 0 0 0 0 0 0 0 0      -
	 *		2		0 0 0 0 0 0 0 0 0 0 1 1 1 1 1 0 0 0 0 0 0 0 0 0 0     24
	 *		3		0 0 0 0 0 0 0 0 0 0 1 1 1 1 1 0 0 0 0 0 0 0 0 0 0
	 *		4		0 0 0 0 0 0 0 0 0 0 1 1 1 1 1 0 0 0 0 0 0 0 0 0 0    ( source
	 *		5 -> 	0 0 0 0 0 0 0 0 0 0 1 1 1 1 1 0 0 0 0 0 0 0 0 0 0      array )
	 *				0 0 0 0 0 0 0 0 0 0 0 0 0 0 0   THIS    0 0 0 0 0
	 *				0 0 0 0 0 0 0 0 0 0 0 0 0 0 0   IS A    0 0 0 0 0
	 *				0 0 0 0 0 0 0 0 0 0 0 0 0 0 0  SAMPLER  0 0 0 0 0
	 *				0 0 0 0 0 0 0 0 0 0 0 0 0 0 0  WINDOW   0 0 0 0 0
	 *				0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
	 *				0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
	 *				0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
	 *				0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
	 *
	 *              j =>  0 - 24 (source array)
	 *
	 *              ss_f = sampler size font = 5
	 */

	for( i = 0; i < h_out; i++)   				//	Loop in vertical direction ( Height )
	{
		for( j = 0; j < w_out; j++)  			//	loop in horizontal direction ( Width )
    	{
			for ( r = 0 ; r < ss_f ; r++)		//	Loop through the sampler window ( Height )
			{
				for ( s = 0 ; s < ss_f ; s++ )	//	Loop through the sampler window ( Width )
					{
					//if ( debug_lvl > debug_lvl2 ) printf("Result[i=%3d,j=%3d] with Source[r=%3d,s=%3d] - Start.\n", i, j , r, s) ;

					//  provide a warning if the sampler window runs out of the source array
					//
					if ( (i*ss_f+r >= h_in + ss_f )  || (j*ss_f+s >= w_in + ss_f ) )
					{
//						fprintf(stderr, "Warning, overflow of index for Source[ i=%3d, j=%3d ] ", i*ss_f+r, j*ss_f+s )	;
//						fprintf(stderr, "         where max = Source[ i=%3d, j=%3d ]\n", h_in - 1, w_in - 1 )	;
					}
		   			if ( I_Array_Source[i*ss_f+r][j*ss_f+s] == 1 ) I_Array_Result[i][j] += 1;
				}
			}

			I_Array_Result[i][j] /= ( ss_f * ss_f * 25 / leveling );

			if ( debug_lvl > debug_lvl1 )
			{
//				printf("Result[i=%3d,j=%3d]=%3d ", i, j, I_Array_Result[i][j] ) ;
//				printf(" / %f = %d \n", ( ss_f * ss_f * 25 / leveling ) , I_Array_Result[i][j] ) ;
//				if ( debug_lvl > debug_lvl2 )
//				{
//					printf("Result[i=%3d,j=%3d] with Source[r=%3d,s=%3d] - Done. \n\n", i, j , r, s) ;
//				}
			}
		}
	}



	// and finaly, display the character by plotting all array elements.
	for( i = 0; i < h_out; i++)
	{
		for( j = 0; j < w_out; j++)
	  	{
		   	if ( I_Array_Result[i][j] >= 1 ) {
		   		UB_VGA_SetPixel((xp+j),(yp+i), color);
		   	}
		   	else 	{
		   	UB_VGA_SetPixel((xp+j),(yp+i), bg);
		   	}
		}
	}


	return (uint16_t)w_out;
}



void draw_sentence(char *sent, int fname, int ftype, int font_size, uint16_t xp, uint16_t yp, uint8_t color, uint8_t bg)
{
	int i, j = 0;
	UCHAR old_charW = 0;
	uint16_t new_charW;
	int sent_length = strlen(sent);

	int char_input[sent_length];

	for ( i=0 ; i <= sent_length ; i++)
	{
		char_input[i] = sent[i];
	}

	for ( j=0 ; j <= sent_length ; j++)
	{
		new_charW = draw_character(char_input[j], fname, ftype, font_size, xp+=old_charW, yp, color, bg);
		old_charW = new_charW;
	}
}
