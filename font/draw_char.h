#include "includes.h"
#include "bfc_latin_font.h"


typedef enum
 {
 	Times_New_Roman, Comic_sans, Georgia, Mistral					// 4
 } f_name ;

typedef enum
 {
 	bold, regular					// 2
 } f_type ;


 uint16_t draw_character(uint16_t xp, uint16_t yp, int char_input, uint8_t color, f_name font_name, f_type font_type, uint8_t font_size, uint8_t bg);
 void 	  draw_sentence( uint16_t xp, uint16_t yp, char *sent,     uint8_t color, f_name font_name, f_type font_type, uint8_t font_size, uint8_t bg);

