/*
****************************************************************
*!	\file		Draw_request.c
*	\brief		Uses ub_lib to draw figures on a vga screen.
*	\author		SOFTON groep 9.
*	\date		Mei 2017.
*	\version	0.1.
*
*	CPU			STM32F4;
*	IDE			CooCox CoIDE 1.7.x;
*	Module
****************************************************************
*/

#include "includes.h"
#include "uitvoer.h"

static int i,j,k=0;

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
	signed int dx,dy,px,py,dxabs,dyabs;
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
		}
		else			// y is negative
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

void Draw_HorLine(uint16_t xp, uint16_t yp, uint8_t length, uint8_t color)
{
	for(k=0; k<length; k++,xp++)
		UB_VGA_SetPixel(xp, yp, color);
}

void Draw_VerLine(uint16_t xp, uint16_t yp, uint8_t length, uint8_t color)
{
	for(k=0; k<length; k++,yp++)
		UB_VGA_SetPixel(xp, yp, color);
}

void Draw_Rectangle(uint16_t xp, uint16_t yp, uint8_t x_length, uint8_t y_length, uint8_t line_width, uint8_t fill, uint8_t color)
{
	uint8_t x,y;
	int i,j;
	if(fill==0)
	{
		for(i=0;i<line_width;i++)
		{
			xp++; yp++;
			x=x_length-(i*2); y=y_length-(i*2);
			Draw_HorLine(xp,yp,x,color);
			Draw_VerLine(xp+x,yp,y,color);
			Draw_HorLine(xp,yp+y,x,color);
			Draw_VerLine(xp,yp,y,color);
		}
	}else
	{
		for(j=0;j<y_length;j++)
			Draw_HorLine(xp,yp+j,x_length,color);
	}
}

void Draw_Triangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, int fill, uint8_t line_width, uint8_t color)
{
	uint16_t mpx = (x1+x2+x3)/3;
	uint16_t mpy = (y1+y2+y3)/3;

	Draw_Line(x1,y1,x2,y2,line_width,color);
	Draw_Line(x2,y2,x3,y3,line_width,color);
	Draw_Line(x3,y3,x1,y1,line_width,color);

	//UB_VGA_SetPixel(mpx,mpy,color);

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

void Draw_Ellipse(uint16_t xp, uint16_t yp, uint16_t r1, uint16_t r2, uint16_t fill, uint16_t thickness, uint8_t colour)
{
unsigned short EllipseXPosArray[1000];
unsigned short EllipseYPosArray[1000];

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

void Set_Single_Pixel(uint16_t xp, uint16_t yp, uint8_t colour)
{
	UB_VGA_SetPixel(xp,yp,colour);
}

void Clear_screen(uint8_t color)
{
	UB_VGA_FillScreen(color);
}


uint16_t draw_character(uint16_t xp, uint16_t yp, int c, uint8_t color, f_name font_name, f_type font_type, uint8_t font_size, uint8_t bg)
{
    uint8_t  i, j , k, bit = 0 ;
    		UCHAR  	pTemp ;
	const 	UCHAR  *pData ;
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
	extern const BFCLATIN_FONT fontGeorgia_bold_size8;
  	extern const BFCLATIN_FONT fontGeorgia_bold_size12;
   	extern const BFCLATIN_FONT fontGeorgia_bold_size20;
   	extern const BFCLATIN_FONT fontGeorgia_reg_size8;
   	extern const BFCLATIN_FONT fontGeorgia_reg_size12;
   	extern const BFCLATIN_FONT fontGeorgia_reg_size20;


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
	else if (font_name == Georgia && font_type == bold && font_size == 8 )
	{
		//UART_puts("  Detected: fontComic_Sans_bold_size8 \n") ;
		 char_height 	=  fontGeorgia_bold_size8.Height;
		 char_index 	=  fontGeorgia_bold_size8.index_table[c];
		 char_width  	=  fontGeorgia_bold_size8.width_table[char_index];
		 char_offset 	=  fontGeorgia_bold_size8.offset_table[char_index];
		 pData     	= &fontGeorgia_bold_size8.data_table[char_offset];
	}
	else if (font_name == Georgia && font_type == bold && font_size == 12 )
	{
		//UART_puts("  Detected: fontComic_Sans_bold_size12 \n") ;
		 char_height 	=  fontGeorgia_bold_size12.Height;
		 char_index 	=  fontGeorgia_bold_size12.index_table[c];
		 char_width  	=  fontGeorgia_bold_size12.width_table[char_index];
		 char_offset 	=  fontGeorgia_bold_size12.offset_table[char_index];
		 pData     	= &fontGeorgia_bold_size12.data_table[char_offset];
	}
	else if (font_name == Georgia && font_type == bold && font_size == 20 )
	{
		//UART_puts("  Detected: fontComic_Sans_bold_size20 \n") ;
		 char_height 	=  fontGeorgia_bold_size20.Height;
		 char_index 	=  fontGeorgia_bold_size20.index_table[c];
		 char_width  	=  fontGeorgia_bold_size20.width_table[char_index];
		 char_offset 	=  fontGeorgia_bold_size20.offset_table[char_index];
		 pData     	= &fontGeorgia_bold_size20.data_table[char_offset];
	}
	else if (font_name == Georgia && font_type == regular && font_size == 8 )
	{
		//UART_puts("  Detected: fontComic_Sans_reg_size20 \n") ;
		 char_height 	=  fontGeorgia_reg_size8.Height;
		 char_index 	=  fontGeorgia_reg_size8.index_table[c];
		 char_width  	=  fontGeorgia_reg_size8.width_table[char_index];
		 char_offset 	=  fontGeorgia_reg_size8.offset_table[char_index];
		 pData     	= &fontGeorgia_reg_size8.data_table[char_offset];
	}
	else if (font_name == Georgia && font_type == regular && font_size == 12 )
	{
		//UART_puts("  Detected: fontComic_Sans_reg_size12 \n") ;
		 char_height 	=  fontGeorgia_reg_size12.Height;
		 char_index 	=  fontGeorgia_reg_size12.index_table[c];
		 char_width  	=  fontGeorgia_reg_size12.width_table[char_index];
		 char_offset 	=  fontGeorgia_reg_size12.offset_table[char_index];
		 pData     	= &fontGeorgia_reg_size12.data_table[char_offset];
	}
	else if (font_name == Georgia && font_type == regular && font_size == 20 )
	{
		//UART_puts("  Detected: fontComic_Sans_reg_size20 \n") ;
		 char_height 	=  fontGeorgia_reg_size20.Height;
		 char_index 	=  fontGeorgia_reg_size20.index_table[c];
		 char_width  	=  fontGeorgia_reg_size20.width_table[char_index];
		 char_offset 	=  fontGeorgia_reg_size20.offset_table[char_index];
		 pData     	= &fontGeorgia_reg_size20.data_table[char_offset];
	}

	quotient  = char_width / divisor ;
	remainder = char_width % divisor ;

	if ( remainder > 0 ) quotient += 1 ;

	for ( i=0 ; i < char_height ; i++)		     	 	//ypos
	{

		for ( j = 0 ; j < quotient ; j++ ) 		 	// per byte per character line(height)
		{
			pTemp = *(pData + (i * quotient) + j ) ; 		//content correct byte
			for ( k = 0  ; k < divisor ; k++ ) 			//Per number of bits per data
			{
				bit = (pTemp >> (divisor-(k+1))) & 0b1;		//get hex font character val to separated bits.
				if ((j*divisor)+k >= char_width) break;

				if (bit == 1)	{				//if true fill screen else put in background.

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
	int sent_length = strlen(sent);					//scrape all characters from sentence 

	for ( j=0 ; j <= sent_length ; j++)			//separate all characters from sentence string and put them one-by-one on screen
	{							//draw_character puts characters on screen
		new_charW = draw_character(xp+=old_charW, yp, *(sent+j), color, font_name, font_type, font_size,  bg);
		old_charW = new_charW;
	}
}

/*
 * The function Bitmap_to_VGA displays PPM (bitmap) images on a VGA screen.
 * The images are stored in uint8_t arrays in the library "uitvoer.h".
 * The function needs 4 parameters to display one or multiple images correctly.
 * The first parameter determines which of the 6 images will be displayed on the VGA screen.
 * The second parameter is the x-coordinate on the VGA screen and the starting point (x-axis) of the image.
 * The third parameter is the y-coordinate on the VGA screen and the starting point (y-axis) of the image.
 * The fourth parameter determines how many times the image will be displayed horizontally on the VGA screen.
 */
void Bitmap_to_VGA(uint8_t image_nr, uint8_t xp, uint8_t yp)
{
	unsigned short k=0;
	unsigned short y_counter=0;
	unsigned short x_counter=0;

	//errormessages
	if (IMAGE_HEIGHT > 240)
		printf("Your image height must be shorter than 240 pixels");
	if (IMAGE_WIDTH > 320)
		printf("Your image width must be shorter than 320 pixels");
	if (xp>320)
		printf("x-coordinate must be an integer value between 0 and 320");
	if (yp>240)
		printf("y-coordinate must be an integer value between 0 and 240");


switch (image_nr)
	 {
		case 1:
			i=0;
			for (y_counter=yp; y_counter<IMAGE_HEIGHT+yp; y_counter++)   //for loop for vertical pixels of image
			{
				for (x_counter=xp; x_counter<IMAGE_WIDTH+xp; x_counter++)  //for loop for horizontal pixels of image
				{
					UB_VGA_SetPixel(x_counter+IMAGE_WIDTH*k, y_counter, pijl_rechts[i]);
					i++; // i loopt tot Image_heigth*Image_width
				}
			}
		   break;

		case 2:
			i=0;
			for (y_counter=yp; y_counter<IMAGE_HEIGHT+yp; y_counter++)   //for loop for vertical pixels of image
			{
				for (x_counter=xp; x_counter<IMAGE_WIDTH+xp; x_counter++)  //for loop for horizontal pixels of image
				{
					UB_VGA_SetPixel(x_counter+IMAGE_WIDTH*k, y_counter, pijl_links[i]);
					i++;
				}
			}
			break;

		case 3:
			i=0;
			for (y_counter=yp; y_counter<IMAGE_HEIGHT+yp; y_counter++)   //for loop for vertical pixels of image
			{
				for (x_counter=xp; x_counter<IMAGE_WIDTH+xp; x_counter++)  //for loop for horizontal pixels of image
				{
					UB_VGA_SetPixel(x_counter+IMAGE_WIDTH*k, y_counter, pijl_omlaag[i]);
					i++;
				}
			}
		   break;

		case 4:
			i=0;
			for (y_counter=yp; y_counter<IMAGE_HEIGHT+yp; y_counter++)   //for loop for vertical pixels of image
			{
				for (x_counter=xp; x_counter<IMAGE_WIDTH+xp; x_counter++)  //for loop for horizontal pixels of image
				{
					UB_VGA_SetPixel(x_counter+IMAGE_WIDTH*k, y_counter, pijl_omhoog[i]);
					i++;
				}
			}
		   break;

		case 5:
			i=0;
			for (y_counter=yp; y_counter<IMAGE_HEIGHT+yp; y_counter++)   //for loop for vertical pixels of image
			{
				for (x_counter=xp; x_counter<IMAGE_WIDTH+xp; x_counter++)  //for loop for horizontal pixels of image
				{
					UB_VGA_SetPixel(x_counter+IMAGE_WIDTH*k, y_counter, smiley_cool[i]);
					i++;
				}
			}
		   break;

		case 6:
			i=0;
			for (y_counter=yp; y_counter<IMAGE_HEIGHT+yp; y_counter++)   //for loop for vertical pixels of image
			{
				for (x_counter=xp; x_counter<IMAGE_WIDTH+xp; x_counter++)  //for loop for horizontal pixels of image
				{
					UB_VGA_SetPixel(x_counter+IMAGE_WIDTH*k, y_counter, smiley_thumb[i]);
					i++;
				}
			}
			break;

		default:
		UART_puts("invalid bitmap selected");
		   break;
	 }
}

