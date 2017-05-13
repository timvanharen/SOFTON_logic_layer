//--------------------------------------------------------------
// File     : main.c
// Datum    : 30.03.2016
// Version  : 1.0
// Autor    : UB
// mods by	: J.F. van der Bent
// CPU      : STM32F4
// IDE      : CooCox CoIDE 1.7.x
// Module   : CMSIS_BOOT, M4_CMSIS_CORE
// Function : VGA_core DMA LIB 320x240, 8bit color
//--------------------------------------------------------------

#include "main.h"
#include "stm32_ub_vga_screen.h"
#include <math.h>
#include "Draw_request.h"

int Bitmap_to_VGA(){
	int i=0, w=0, h=0, a=0, k=0;
	int rgb = 0;
	int byte_color;
	int red=0;    // red is een 3 bits getal
	int green=0;
	int blue=0;
	char buf[256];
//	int array_2d[320][240];

	FILE *fp;
//	FILE *fh;

	if ( (fp = fopen("mangekyou.ppm", "r")) == NULL){
	printf("error: couldn't find or open file");
	return 1;
	}

//	if ( (fh = fopen("uitvoer.h", "w")) == NULL){
//		printf("error: couldn't find or open file");
//		return 1;
//	}

	fgets(buf, 255, fp);
	fgets(buf, 255, fp);
	fgets(buf, 255, fp);
	sscanf(buf, "%d %d", &w, &h);
	fgets(buf, 255, fp);

//	fprintf(fh, "%s %d\n", "#define IMAGE_WIDTH", w);
//	fprintf(fh, "%s %d\n", "#define IMAGE_HEIGHT", h);
//	fprintf(fh, "%s %d\n", "#define IMAGE_type", 1);
//	fprintf(fh, "%s", "\n");
//	fprintf(fh, "%s", "const uint8_t image[] PROGMEM = {\n");

    for (k=0; k<h; k++)
	{
		for (a=0; a<w; a++)
		{
			fscanf(fp, "%d", &i);

			if (rgb == 0){
				red = i & 0xE0; //0xE00 = 0b11100000
			} else
			if (rgb == 1){
				green = i & 0xE0;
			}else
			if (rgb == 2){
				blue = i & 0xC0; //0xC00 = 0b11000000
			}
			byte_color=red+green+blue;

	    // 	byte_color = (red <<5+ green <<2+ blue);
//			fprintf(fh, "%d%s%x,", 0, "x", i);  //printing hexadecimal values
			rgb++;
			if (rgb==3){
				UB_VGA_SetPixel(a, k, byte_color);
//				fprintf(fh, "%d,", byte_color);
//				fprintf(fh," ");
				rgb=0;
			}

//			array_2d[k][a] = byte_color;
//			printf("%d", array_2d);


		}
//		fprintf(fh, "\n");
	}

//	fprintf(fh, "};\n");
	fclose (fp);
//	fclose (fh);
	return 0;
}

int main(void)
{

	//  uint32_t n;

	SystemInit(); // System speed to 168MHz

	UB_VGA_Screen_Init(); // Init VGA-Screen

	UB_VGA_FillScreen(VGA_COL_BLACK);
	UB_VGA_SetPixel(10,10,10);

  	//Fill_BitMap();
	int i,j;
	i=0;
  while(1)
  {
	  Bitmap_to_VGA();
	  //cmd prompt is openend
	  //wait for rs232 string
//	  Draw_Ellipse(160, 120, 100, 10, 1, 1, VGA_COL_RED);
//	  i++;
//	  for(j=0; j<19992999; j++);
  }
}

