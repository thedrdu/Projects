#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WIDTH 256
#define HEIGHT 256

typedef struct {
    char character;
    int brightness;
} CharacterBrightness;

void concatenate_string(char* s, char* s1);
int computeBrightness(char* font_file);