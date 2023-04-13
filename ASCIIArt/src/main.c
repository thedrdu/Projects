//Author(s): thedrdu
//Year of Creation: 2022

//todo: input custom width and height output size, different shading styles, width:height ratio processing
//todo: check this out: https://stackoverflow.com/questions/32987103/image-to-ascii-art-conversion
//todo: make this a webapp

#define WIDTH 1024
#define HEIGHT 1024

#include "../include/main.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define STB_IMAGE_IMPLEMENTATION
#include "../lib/stb/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../lib/stb/stb_image_write.h"
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "../lib/stb/stb_image_resize.h"

// char outputChars[69] = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`\'.";
char outputChars[69] = ".\'`^\",:;Il!i><~+_-?][}{1)(|\\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$"; //replace this with actual computed values later

//Takes in RGB values and returns the character with the corresponding brightness level
char getChar(int r, int g, int b){
  int brightness = ((r + g + b) / 3) / (3.7); //Find a way to not have this final divisor hardcoded
  return outputChars[brightness];
}


//args: {source image file} {font} [output text file name]
int main(int argc, char** argv){
  if(argc < 2){
    printf("Please enter a filename!\n");
    exit(1);
  }

  int width, height, channels;
  char image_filepath[200] = "../images/";
  strcat(image_filepath, argv[1]);
  unsigned char *img = stbi_load(image_filepath, &width, &height, &channels, 3);
  if(img == NULL){
    printf("Error in loading the image\n");
    exit(1);
  }
  printf("Loaded image with a width of %dpx, a height of %dpx and %d channels\n", width, height, channels);

  stbir_resize_uint8(img, width, height, 0, img, WIDTH, HEIGHT, 0, 3);
  width = WIDTH;
  height = HEIGHT;
  printf("Resized image to a width of %dpx, and a height of %dpx\n", WIDTH, HEIGHT);


  computeBrightness(argv[2]);


  char *output_directory = "../output/";
  char fullpath[100];

  FILE *fp = NULL;
  if(argc == 4){
    char* filename = argv[3];
    snprintf(fullpath, sizeof(fullpath), "%s%s", output_directory, filename);
    fp = fopen(fullpath, "w");
  }
  else{
    snprintf(fullpath, sizeof(fullpath), "%s%s", output_directory, "textFile.txt");
    fp = fopen(fullpath, "w");
  }
  int bytePerPixel = 1;

  for(int i = 0; i < height; i++){
    for(int j = 0; j < width; j++){
      unsigned char *pixelOffset = img + (j + width * i) * 3;
      unsigned char r = pixelOffset[0];
      unsigned char g = pixelOffset[1];
      unsigned char b = pixelOffset[2];
      fprintf(fp, "%c", getChar(r,g,b));
    }
    fprintf(fp, "\n");
  }
  return 0;
}