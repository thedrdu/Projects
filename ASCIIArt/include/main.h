#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WIDTH 256
#define HEIGHT 256

typedef enum {
    SUCCESS = 0,
    ERROR_INIT_FREETYPE,
    ERROR_LOAD_TTF,
    ERROR_SET_FONT_SIZE,
    ERROR_RENDER_CHAR
} ErrorCode;

typedef struct {
    char character;
    int brightness;
} CharacterBrightness;

void concatenate_string(char* s, char* s1);
int* computeBrightness(char* font_file, ErrorCode* error);
int compare_brightness(const void* a, const void* b);