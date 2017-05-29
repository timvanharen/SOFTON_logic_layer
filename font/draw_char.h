#include "includes.h"
#include "bfclatin_font.h"

uint16_t draw_character(int char_input, int font_name, int font_type, uint8_t out_size, uint16_t xp, uint16_t yp, uint8_t color, uint8_t bg);
void draw_sentence(char *sent, int fname, int ftype, int font_size, uint16_t xp, uint16_t yp, uint8_t color, uint8_t bg);
