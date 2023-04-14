//Author(s): thedrdu
//Year of Creation: 2022

#include "../include/main.h"
#include "../lib/freetype-2.13.0/include/ft2build.h"

#include FT_FREETYPE_H

int compare_characters(const void* a, const void* b){
    CharacterBrightness* char_a = (CharacterBrightness*)a;
    CharacterBrightness* char_b = (CharacterBrightness*)b;
    if(char_a->brightness != char_b->brightness){
        return char_a->brightness - char_b->brightness;
    }
    return char_a->character - char_b->character;
}


int* computeBrightness(char* font_file, ErrorCode* errorCode){
    CharacterBrightness brightness_values[96];

    FT_Library library;
    FT_Error error = FT_Init_FreeType(&library);
    if(error){
        // fprintf(stderr, "Error initializing FreeType library\n");
        *errorCode = ERROR_INIT_FREETYPE;
        return NULL;
    }
    // printf("[%s]\n", font_file);

    // //Open the TTF file
    FT_Face face;
    char font_filepath[200] = "../fonts/";
    font_filepath[11] = '\0';
    strcat(font_filepath, font_file);
    error = FT_New_Face(library, font_filepath, 0, &face);
    if(error){
        // fprintf(stderr, "Error loading TTF file\n");
        *errorCode = ERROR_LOAD_TTF;
        return NULL;
    }

    //Set the font size(64 in this case).
    error = FT_Set_Char_Size(face, 0, 16 * 64, 0, 0);
    if(error){
        // fprintf(stderr, "Error setting font size\n");
        *errorCode = ERROR_SET_FONT_SIZE;
        return NULL;
    }

    //Iterate through all ASCII characters
    int max_black_pixels = 0;
    for(int i = 32; i < 127; i++){
        //Render the character
        error = FT_Load_Char(face, i, FT_LOAD_RENDER);
        if(error){
            // fprintf(stderr, "Error rendering character '%c'\n", i);
            *errorCode = ERROR_RENDER_CHAR;
            return NULL;
        }

        //Calculate the number of black pixels in the character bitmap
        FT_Bitmap bitmap = face->glyph->bitmap;
        int black_pixels = 0;
        for(unsigned int y = 0; y < bitmap.rows; y++){
            for(unsigned int x = 0; x < bitmap.width; x++){
                if (bitmap.buffer[y * bitmap.width + x] > 0){
                    black_pixels++;
                }
            }
        }

        //Update the maximum number of black pixels if necessary
        //edit: I have to figure out the max black pixels early on. this can't be changing during the program
        if(black_pixels > max_black_pixels){
            max_black_pixels = black_pixels;
        }

        //Calculate the brightness value for the character
        int brightness = (int)((float)black_pixels / max_black_pixels * 100);
        CharacterBrightness c = {i, brightness};
        brightness_values[i - 32] = c;
        // printf("Character '%c': %d%% brightness\n", i, brightness);
    }
    qsort(brightness_values, 96, sizeof(CharacterBrightness), compare_characters);

    for(int i = 0; i < 96; i++){
        int brightness = brightness_values[i].brightness;
        char c = brightness_values[i].character; // Convert index back to character code
        printf("Character '%c': %d%% brightness\n", c, brightness);
    }

    //Cleanup
    FT_Done_Face(face);
    FT_Done_FreeType(library);
    return brightness_values;
}