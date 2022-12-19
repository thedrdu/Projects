//Author(s): thedrdu
//Year of Creation: 2022

#include <stdio.h>
#include <stdlib.h>
#include "freetype-2.12.1/include/ft2build.h"
#include FT_FREETYPE_H

#define PIXEL_SIZE 4

int main(int argc, char** argv){
    // Check for the correct number of command line arguments
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <ttf file>\n", argv[0]);
        return 1;
    }

    //Initialize the FreeType library
    FT_Library library;
    FT_Error error = FT_Init_FreeType(&library);
    if(error){
        fprintf(stderr, "Error initializing FreeType library\n");
        return -1;
    }

    //Open the TTF file
    FT_Face face;
    error = FT_New_Face(library, argv[1], 0, &face);
    if(error){
        fprintf(stderr, "Error loading TTF file\n");
        return -1;
    }

    //Set the font size(64 in this case).
    error = FT_Set_Char_Size(face, 0, 16 * 64, 0, 0);
    if(error){
        fprintf(stderr, "Error setting font size\n");
        return 1;
    }

    //Iterate through all ASCII characters
    int max_black_pixels = 0;
    for(int i = 32; i < 127; i++){
        //Render the character
        error = FT_Load_Char(face, i, FT_LOAD_RENDER);
        if(error){
            fprintf(stderr, "Error rendering character '%c'\n", i);
            continue;
        }

        //Calculate the number of black pixels in the character bitmap
        FT_Bitmap bitmap = face->glyph->bitmap;
        int black_pixels = 0;
        for (int y = 0; y < bitmap.rows; y++) {
            for (int x = 0; x < bitmap.width; x++) {
                if (bitmap.buffer[y * bitmap.width + x] > 0) {
                    black_pixels++;
                }
            }
        }

        //Update the maximum number of black pixels if necessary
        if(black_pixels > max_black_pixels){
            max_black_pixels = black_pixels;
        }

        //Calculate the brightness value for the character
        int brightness = (int)((float)black_pixels / max_black_pixels * 100);
        printf("Character '%c': %d%% brightness\n", i, brightness);
    }

    //Cleanup
    FT_Done_Face(face);
    FT_Done_FreeType(library);
    return 0;
}
