/*
 **************************************************************************************
 *!	\file		presentation.c
 *	\brief		Gets commands from the terminal and interpret them to the screen(API).
 *	\author		SOFTON groep 9.
 *	\date		Mei 2017.
 *	\version	0.1.
 *
 *	CPU			STM32F4;
 *	IDE			CooCox CoIDE 1.7.x;
 *	Module
 **************************************************************************************
 */

#include "includes.h"

int line_split(char *str, char separator, char ***array, int *length)
{
	char *p;
	char **res;		//result
	int count=0;
	int k=0;

	p = str;

	// Count occurance of separator in string
	//This returns a pointer to the first occurrence of the character c in the string str,
	//or NULL if the character is not found.
	while( ( p = strchr(p, separator)) != NULL ) {
		*p = 0 ;   // Null terminate the separator.
		p++ ;      // Skip past our new null
		count++;
	}

	// allocate dynamic array
	res = calloc( 1, ( count + 1 ) * sizeof(char *));
	if( !res ) return -1;

	p = str;
	for( k=0; k<=count; k++ ){
		if( *p ) res[k] = p;  // Copy start of string
		p = strchr(p, 0 );    // Look for next null
		p++; // Start of next string
	}

	*array = res;
	*length = count;

	return 0;
}

static void Text_Request(char** res)
{
	uint16_t xpos,ypos;
	uint8_t kleur, background, font_size;
	f_name font_name;
	f_type font_type;

	if ( strcmp( res[0], "tekst") == 0 )
	{
		UART_puts("Userinput --> tekst request \r\n");
		xpos = atoi( res[1] ) ; UART_putint(xpos);UART_puts(" ");
		ypos = atoi( res[2] ) ; UART_putint(ypos);UART_puts(" ");
		if ( strcmp( res[4],"zwart") 		== 0 ) 	kleur = VGA_COL_BLACK ;
		else if ( strcmp( res[4],"blauw") 		== 0 )  kleur = VGA_COL_BLUE ;
		else if ( strcmp( res[4],"lichtblauw") 	== 0 ) 	kleur = VGA_COL_LIGHTBLUE ;
		else if ( strcmp( res[4],"groen") 		== 0 )  kleur = VGA_COL_GREEN ;
		else if ( strcmp( res[4],"lichtgroen") 	== 0 )  kleur = VGA_COL_LIGHTGREEN ;
		else if ( strcmp( res[4],"cyaan") 		== 0 )  kleur = VGA_COL_CYAN ;
		else if ( strcmp( res[4],"lichtcyaan") 	== 0 )  kleur = VGA_COL_LIGHTCYAN ;
		else if ( strcmp( res[4],"rood") 		== 0 )  kleur = VGA_COL_RED ;
		else if ( strcmp( res[4],"lichtrood") 	== 0 )  kleur = VGA_COL_LIGHTRED ;
		else if ( strcmp( res[4],"magenta")	 	== 0 ) 	kleur = VGA_COL_MAGENTA ;
		else if ( strcmp( res[4],"lichtmagenta")== 0 )  kleur = VGA_COL_LIGHTMAGENTA ;
		else if ( strcmp( res[4],"bruin") 		== 0 )  kleur = VGA_COL_BROWN ;
		else if ( strcmp( res[4],"geel") 		== 0 )  kleur = VGA_COL_YELLOW ;
		else if ( strcmp( res[4],"grijs") 		== 0 )  kleur = VGA_COL_GRAY ;
		else if ( strcmp( res[4],"wit") 		== 0 )  kleur = VGA_COL_WHITE ;
		else kleur = atoi( res[4] );
		UART_puts(res[6]); UART_puts(" ");

		if ( strcmp( res[5], "Times New Roman" ) == 0 ) font_name = Times_New_Roman ;
		else if ( strcmp( res[5], "Georgia" ) == 0 )	font_name = Georgia ;
		if ( strcmp( res[6], "bold" ) 			 == 0 )	font_type = bold ;
		else if ( strcmp( res[6], "regular" ) 	 == 0 )	font_type = regular ;

		if ( strcmp( res[7], "8" ) 				 == 0 )	font_size = atoi(res[7]) ;
		else if ( strcmp( res[7], "12" ) 		 == 0 )	font_size = atoi(res[7]) ;
		else if ( strcmp( res[7], "20" ) 		 == 0 )	font_size = atoi(res[7]) ;

		if ( strcmp( res[8],"zwart" ) 			== 0 )	background = VGA_COL_BLACK ;
		else if ( strcmp( res[8],"blauw") 		== 0 )  background = VGA_COL_BLUE ;
		else if ( strcmp( res[8],"lichtblauw") 	== 0 ) 	background = VGA_COL_LIGHTBLUE ;
		else if ( strcmp( res[8],"groen") 		== 0 )  background = VGA_COL_GREEN ;
		else if ( strcmp( res[8],"lichtgroen") 	== 0 )  background = VGA_COL_LIGHTGREEN ;
		else if ( strcmp( res[8],"cyaan") 		== 0 )  background = VGA_COL_CYAN ;
		else if ( strcmp( res[8],"lichtcyaan") 	== 0 )  background = VGA_COL_LIGHTCYAN ;
		else if ( strcmp( res[8],"rood") 		== 0 )  background = VGA_COL_RED ;
		else if ( strcmp( res[8],"lichtrood") 	== 0 )  background = VGA_COL_LIGHTRED ;
		else if ( strcmp( res[8],"magenta")	 	== 0 ) 	background = VGA_COL_MAGENTA ;
		else if ( strcmp( res[8],"lichtmagenta")== 0 )  background = VGA_COL_GREEN ;
		else if ( strcmp( res[8],"bruin") 		== 0 )  background = VGA_COL_BROWN ;
		else if ( strcmp( res[8],"geel") 		== 0 )  background = VGA_COL_YELLOW ;
		else if ( strcmp( res[8],"grijs") 		== 0 )  background = VGA_COL_WHITE ;
		else if ( strcmp( res[8],"wit") 		== 0 )  background = VGA_COL_WHITE ;
		else background = atoi( res[4] );

		UART_puts(res[8]); UART_puts("\n\r");

		char *sentence = res[3];
		draw_sentence(xpos, ypos, sentence, kleur, font_name, font_type, font_size, background);
	}
}

static void Ellipse_Request(char** res)
{
	uint8_t kleur = VGA_COL_RED;
	uint16_t fill = 1;
	uint16_t thickness = 2;
	UART_puts("Userinput --> ellipse request \r\n");
	uint16_t xpos = atoi( res[1] ) ; 	UART_putint(xpos);UART_puts(" ");
	uint16_t ypos = atoi( res[2] ) ; 	UART_putint(ypos);UART_puts(" ");
	uint16_t r1 = atoi( res[3] ) ; 		UART_putint(r1);UART_puts(" ");
	uint16_t r2 = atoi( res[4] ) ; 		UART_putint(r2);UART_puts(" ");
	fill = atoi( res[5] ) ; 	UART_putint(fill);UART_puts(" ");
	thickness = atoi( res[6] ); UART_putint(thickness); UART_puts(" ");

	if ( strcmp( res[7],"zwart") 			== 0 ) 	kleur = VGA_COL_BLACK ;
	else if ( strcmp( res[7],"blauw") 		== 0 )  kleur = VGA_COL_BLUE ;
	else if ( strcmp( res[7],"lichtblauw") 	== 0 ) 	kleur = VGA_COL_LIGHTBLUE ;
	else if ( strcmp( res[7],"groen") 		== 0 )  kleur = VGA_COL_GREEN ;
	else if ( strcmp( res[7],"lichtgroen") 	== 0 )  kleur = VGA_COL_LIGHTGREEN ;
	else if ( strcmp( res[7],"cyaan") 		== 0 )  kleur = VGA_COL_CYAN ;
	else if ( strcmp( res[7],"lichtcyaan") 	== 0 )  kleur = VGA_COL_LIGHTCYAN ;
	else if ( strcmp( res[7],"rood") 		== 0 )  kleur = VGA_COL_RED ;
	else if ( strcmp( res[7],"lichtrood") 	== 0 )  kleur = VGA_COL_LIGHTRED ;
	else if ( strcmp( res[7],"magenta")	 	== 0 ) 	kleur = VGA_COL_MAGENTA ;
	else if ( strcmp( res[7],"lichtmagenta")== 0 )  kleur = VGA_COL_LIGHTMAGENTA ;
	else if ( strcmp( res[7],"bruin") 		== 0 )  kleur = VGA_COL_BROWN ;
	else if ( strcmp( res[7],"geel") 		== 0 )  kleur = VGA_COL_YELLOW ;
	else if ( strcmp( res[7],"grijs") 		== 0 )  kleur = VGA_COL_GRAY ;
	else if ( strcmp( res[7],"wit") 		== 0 )  kleur = VGA_COL_WHITE ;
	else kleur = atoi( res[7] );
	UART_puts(res[7]); UART_puts("\n\r");

	Draw_Ellipse(xpos, ypos, r1, r2, fill, thickness, kleur);
}

static void Line_Request(char** res)
{
	uint8_t kleur = VGA_COL_RED;
	uint8_t thickness = 1;
	UART_puts("Userinput --> line request \r\n");
	uint16_t x = atoi( res[1] ) ; UART_putint(x);UART_puts(" ");
	uint16_t y = atoi( res[2] ) ; UART_putint(y);UART_puts(" ");
	uint16_t x2 = atoi( res[3] ) ; UART_putint(x2);UART_puts(" ");
	uint16_t y2 = atoi( res[4] ) ; UART_putint(y2);UART_puts(" ");
	thickness = atoi( res[5] ) ; UART_putint(thickness);UART_puts(" ");

	if ( strcmp( res[6],"zwart") 			== 0 ) 	kleur = VGA_COL_BLACK ;
	else if ( strcmp( res[6],"blauw") 		== 0 )  kleur = VGA_COL_BLUE ;
	else if ( strcmp( res[6],"lichtblauw") 	== 0 ) 	kleur = VGA_COL_LIGHTBLUE ;
	else if ( strcmp( res[6],"groen") 		== 0 )  kleur = VGA_COL_GREEN ;
	else if ( strcmp( res[6],"lichtgroen") 	== 0 )  kleur = VGA_COL_LIGHTGREEN ;
	else if ( strcmp( res[6],"cyaan") 		== 0 )  kleur = VGA_COL_CYAN ;
	else if ( strcmp( res[6],"lichtcyaan") 	== 0 )  kleur = VGA_COL_LIGHTCYAN ;
	else if ( strcmp( res[6],"rood") 		== 0 )  kleur = VGA_COL_RED ;
	else if ( strcmp( res[6],"lichtrood") 	== 0 )  kleur = VGA_COL_LIGHTRED ;
	else if ( strcmp( res[6],"magenta")	 	== 0 ) 	kleur = VGA_COL_MAGENTA ;
	else if ( strcmp( res[6],"lichtmagenta")== 0 )  kleur = VGA_COL_LIGHTMAGENTA ;
	else if ( strcmp( res[6],"bruin") 		== 0 )  kleur = VGA_COL_BROWN ;
	else if ( strcmp( res[6],"geel") 		== 0 )  kleur = VGA_COL_YELLOW ;
	else if ( strcmp( res[6],"grijs") 		== 0 )  kleur = VGA_COL_GRAY ;
	else if ( strcmp( res[6],"wit") 		== 0 )  kleur = VGA_COL_WHITE ;
	else kleur = atoi( res[6] );
	UART_puts(res[6]); UART_puts("\n\r");

	Draw_Line(x, y, x2, y2, thickness, kleur);
}

static void Rectangle_Request(char** res)
{
	uint8_t kleur = VGA_COL_RED;
	uint8_t fill = 1;
	uint8_t line_width = 1;
	UART_puts("Userinput --> Empty rectangle request \r\n");
	uint16_t xpos = atoi( res[1] ) ; UART_putint(xpos);UART_puts(" ");
	uint16_t ypos = atoi( res[2] ) ; UART_putint(ypos);UART_puts(" ");
	uint8_t width = atoi( res[3] ) ; UART_putint(width);UART_puts(" ");
	uint8_t height = atoi( res[4] ) ; UART_putint(height);UART_puts(" ");
	line_width = atoi( res[5] ) ; UART_putint(height);UART_puts(" ");
	fill = atoi( res[6] ) ; UART_putint(height);UART_puts(" ");

	if ( strcmp( res[7],"zwart") 			== 0 ) 	kleur = VGA_COL_BLACK ;
	else if ( strcmp( res[7],"blauw") 		== 0 )  kleur = VGA_COL_BLUE ;
	else if ( strcmp( res[7],"lichtblauw") 	== 0 ) 	kleur = VGA_COL_LIGHTBLUE ;
	else if ( strcmp( res[7],"groen") 		== 0 )  kleur = VGA_COL_GREEN ;
	else if ( strcmp( res[7],"lichtgroen") 	== 0 )  kleur = VGA_COL_LIGHTGREEN ;
	else if ( strcmp( res[7],"cyaan") 		== 0 )  kleur = VGA_COL_CYAN ;
	else if ( strcmp( res[7],"lichtcyaan") 	== 0 )  kleur = VGA_COL_LIGHTCYAN ;
	else if ( strcmp( res[7],"rood") 		== 0 )  kleur = VGA_COL_RED ;
	else if ( strcmp( res[7],"lichtrood") 	== 0 )  kleur = VGA_COL_LIGHTRED ;
	else if ( strcmp( res[7],"magenta")	 	== 0 ) 	kleur = VGA_COL_MAGENTA ;
	else if ( strcmp( res[7],"lichtmagenta")== 0 )  kleur = VGA_COL_LIGHTMAGENTA ;
	else if ( strcmp( res[7],"bruin") 		== 0 )  kleur = VGA_COL_BROWN ;
	else if ( strcmp( res[7],"geel") 		== 0 )  kleur = VGA_COL_YELLOW ;
	else if ( strcmp( res[7],"grijs") 		== 0 )  kleur = VGA_COL_GRAY ;
	else if ( strcmp( res[7],"wit") 		== 0 )  kleur = VGA_COL_WHITE ;
	else kleur = atoi( res[7] );
	UART_puts(res[7]); UART_puts("\n\r");

	Draw_Rectangle(xpos, ypos, width, height, line_width, fill, kleur);
	//Draw_Rectangle(xpos, ypos, width, height, fill, thickness, kleur);
}

static void Triangle_Request(char** res)
{
	uint8_t kleur = VGA_COL_RED;
	uint8_t fill = 1;
	uint8_t line_width = 1;
	UART_puts("Userinput --> triangle request \r\n");
	uint16_t x = atoi( res[1] ) ; UART_putint(x);UART_puts(" ");
	uint16_t y = atoi( res[2] ) ; UART_putint(y);UART_puts(" ");
	uint16_t x2 = atoi( res[3] ) ; UART_putint(x2);UART_puts(" ");
	uint16_t y2 = atoi( res[4] ) ; UART_putint(y2);UART_puts(" ");
	uint16_t x3 = atoi( res[5] ) ; UART_putint(x3);UART_puts(" ");
	uint16_t y3 = atoi( res[6] ) ; UART_putint(y3); UART_puts(" ");
	fill = atoi( res[7] ) ; UART_putint(fill);UART_puts(" ");
	line_width = atoi( res[8] ) ; UART_putint(fill);UART_puts(" ");

	if ( strcmp( res[9],"zwart") 			== 0 ) 	kleur = VGA_COL_BLACK ;
	else if ( strcmp( res[9],"blauw") 		== 0 )  kleur = VGA_COL_BLUE ;
	else if ( strcmp( res[9],"lichtblauw") 	== 0 ) 	kleur = VGA_COL_LIGHTBLUE ;
	else if ( strcmp( res[9],"groen") 		== 0 )  kleur = VGA_COL_GREEN ;
	else if ( strcmp( res[9],"lichtgroen") 	== 0 )  kleur = VGA_COL_LIGHTGREEN ;
	else if ( strcmp( res[9],"cyaan") 		== 0 )  kleur = VGA_COL_CYAN ;
	else if ( strcmp( res[9],"lichtcyaan") 	== 0 )  kleur = VGA_COL_LIGHTCYAN ;
	else if ( strcmp( res[9],"rood") 		== 0 )  kleur = VGA_COL_RED ;
	else if ( strcmp( res[9],"lichtrood") 	== 0 )  kleur = VGA_COL_LIGHTRED ;
	else if ( strcmp( res[9],"magenta")	 	== 0 ) 	kleur = VGA_COL_MAGENTA ;
	else if ( strcmp( res[9],"lichtmagenta")== 0 )  kleur = VGA_COL_LIGHTMAGENTA ;
	else if ( strcmp( res[9],"bruin") 		== 0 )  kleur = VGA_COL_BROWN ;
	else if ( strcmp( res[9],"geel") 		== 0 )  kleur = VGA_COL_YELLOW ;
	else if ( strcmp( res[9],"grijs") 		== 0 )  kleur = VGA_COL_GRAY ;
	else if ( strcmp( res[9],"wit") 		== 0 )  kleur = VGA_COL_WHITE ;
	else kleur = atoi( res[9] );
	UART_puts(res[9]); UART_puts("\n\r");

	Draw_Triangle(x, y, x2, y2, x3, y3, fill, line_width, kleur);
}

static void Wait_request(char** res)
{
	UART_puts("Userinput --> wait request \r\n");
	int msec = atoi( res[1] ) ; UART_putint(msec);UART_puts(" ");
	UART_puts("\r\n");
	wait_msec(msec);
}

static void Clear_Request(char** res)
{
	uint8_t kleur;
	UART_puts("Userinput --> clear screen request \r\n");
	if ( strcmp( res[1],"zwart") 			== 0 ) 	kleur = VGA_COL_BLACK ;
	else if ( strcmp( res[1],"blauw") 		== 0 )  kleur = VGA_COL_BLUE ;
	else if ( strcmp( res[1],"lichtblauw") 	== 0 ) 	kleur = VGA_COL_LIGHTBLUE ;
	else if ( strcmp( res[1],"groen") 		== 0 )  kleur = VGA_COL_GREEN ;
	else if ( strcmp( res[1],"lichtgroen") 	== 0 )  kleur = VGA_COL_LIGHTGREEN ;
	else if ( strcmp( res[1],"cyaan") 		== 0 )  kleur = VGA_COL_CYAN ;
	else if ( strcmp( res[1],"lichtcyaan") 	== 0 )  kleur = VGA_COL_LIGHTCYAN ;
	else if ( strcmp( res[1],"rood") 		== 0 )  kleur = VGA_COL_RED ;
	else if ( strcmp( res[1],"lichtrood") 	== 0 )  kleur = VGA_COL_LIGHTRED ;
	else if ( strcmp( res[1],"magenta")	 	== 0 ) 	kleur = VGA_COL_MAGENTA ;
	else if ( strcmp( res[1],"lichtmagenta")== 0 )  kleur = VGA_COL_LIGHTMAGENTA ;
	else if ( strcmp( res[1],"bruin") 		== 0 )  kleur = VGA_COL_BROWN ;
	else if ( strcmp( res[1],"geel") 		== 0 )  kleur = VGA_COL_YELLOW ;
	else if ( strcmp( res[1],"grijs") 		== 0 )  kleur = VGA_COL_GRAY ;
	else if ( strcmp( res[1],"wit") 		== 0 )  kleur = VGA_COL_WHITE ;
	else kleur = atoi( res[1] );
	UART_puts(res[1]); UART_puts("\n\r");

	Clear_screen(kleur);
}

static void Bitmap_Request(char** res)
{
	UART_puts("Userinput --> bitmap request \r\n");
	uint16_t image_nr = atoi( res[1] ) ; UART_putint(image_nr);UART_puts(" ");
	uint8_t x = atoi( res[2] ) ; UART_putint(x);UART_puts(" ");
	uint16_t y = atoi( res[3] ) ; UART_putint(x);UART_puts(" ");
	UART_puts("\r\n");

	Bitmap_to_VGA(image_nr, x, y);
}

void put_usage()
{
	UART_puts("*****USAGE GUIDE*****\r\n"
				"This program translates user draw request to output on the a VGA screen.\r\n"
				"\r\n"
				"The user has a certain selection of commands which can be inserted:\r\n"
				"write text: this command puts text on position x/y, the font, size, text color and background color can be chosen\r\n "
				"	example: tekst,[xposition],[yposition],[sentence],[text color],[font name],[font type],[font size],[background color]\r\n"
				"	argument ranges: \r\n"
				"	x position: 0 -> 320\r\n"
				"	y position: 0 -> 240\r\n"
				"	sentence : depends on font size\r\n"
				"	text color*\r\n"
				"	font name(insert the exact representation): Times New Roman, Comic sans\r\n"
				"	font type(insert the exact representation): Bold, regular\r\n"
				"	font size: 8, 12 & 20\r\n"
				"	background color: same as text color\r\n"
				"Draw line: this command draws a line on position x/y, the font, size, text color and background color can be chosen\r\n "
				"	example: tekst,[xposition],[yposition],[xposition2],[yposition2],[Line thickness], [color]\r\n"
				"	argument ranges: \r\n"
				"	x position 1: 0 -> 320\r\n"
				"	y position 1: 0 -> 240\r\n"
				"	x position 2: 0 -> 320\r\n"
				"	y position 2: 0 -> 240\r\n"
				"	width : 0 -> 30(thicker than this will ruin the figure\r\n"
				"	color*\r\n"
				"Draw ellipse: this command draws a ellipe on position x/y with a horizontal radius r1 and vertical radius r2.\r\n"
				"	Wheter the ellipse is filled or not is determined by fill, thickness is determined bij thickness\r\n "
				"	example: tekst,[xposition],[yposition],[xposition2],[yposition2],[Line thickness], [color]\r\n"
				"	argument ranges: \r\n"
				"	xposition: 0 -> 320\r\n"
				"	yposition: 0 -> 240\r\n"
				"	xposition2: 0 -> 320\r\n"
				"	yposition2: 0 -> 240\r\n"
				"	width : 0 -> 30(thicker than this will ruin the figure)\r\n"
				"	color*\r\n"
				"Draw rectangle:\r\n"
				"	example: rechthoek,[xposition],[yposition],[lengte_x],[lengte_y],[Line thickness],[filled or not filled],[color]\r\n"
				"	xposition: 0 -> 320\r\n"
				"	yposition: 0 -> 240\r\n"
				"	lengte_x: 0 -> 320-xposition\r\n"
				"	lengte_y: 0 -> 240-yposition\r\n"
				"	Line thicknes: 0 -> lengte x of y\r\n"
				"	fill: vol || leeg\r\n"
				"	color*\r\n"
				"Draw triangle: this command draws a triangle with corners on which ever coordinate you want.\r\n"
				"	example: driehoek,[xposition],[yposition],[xposition2],[yposition2],[xposition3],[yposition3],[filled or not filled],[color]\r\n"
				"	xposition1,2,3: 0 -> 320\r\n"
				"	yposition1,2,3: 0 -> 240\r\n"
				"	fill: vol || leeg\r\n"
				"	color*\r\n"
				"Draw bitmap: puts a image on the screen.\r\n"
				"	example: bitmap,[image],[xposition],[yposition]\r\n"
				"	image: let's you choose which number image you want\r\n"
				"	xposition: 0 -> 320\r\n"
				"	yposition: 0 -> 240\r\n"
				"Wait: this command is a delay function."
				"	example: wacht,[amount ms]\r\n"
				"	amount: how many miliseconds you want to wait\r\n"
				"Clearscherm: Wipe all text and figures from the screen\r\n"
				"	example: clearscherm,[color]\r\n"
				"	color*\r\n"
				"\r\n"
				"*color = 0->256(all posible colors) or zwart,blauw,lichtblauw,groen,lichtgroen,cyaan,lichtcyaan,rood,lichtrood,magenta,lichtmagenta,bruin,geel,grijs,wit\r\n");
}

void Request_Handling(char** res)
{
	if (strcmp( res[0], "tekst") == 0)
	{
		Text_Request(res);
	} else if (strcmp( res[0], "ellips") == 0) {
		Ellipse_Request(res);
	} else if (strcmp( res[0], "rechthoek") == 0) {
		Rectangle_Request(res);
	} else if (strcmp( res[0], "driehoek") == 0) {
		Triangle_Request(res);
	} else if (strcmp( res[0], "lijn") == 0) {
		Line_Request(res);
	} else if (strcmp( res[0], "wacht") == 0) {
		Wait_request(res);
	} else if (strcmp( res[0], "clearscherm") == 0) {
		Clear_Request(res);
	} else if (strcmp( res[0], "bitmap") == 0) {
		Bitmap_Request(res);
	} else if (strcmp( res[0], "NULL") == 0) {
		UART_puts("no command is inserted");
	} else {
		UART_puts("request command is invalid\r\n\n\n\n");
		//put_usage();
	}
	res = 0 ;		//empty the array
}

