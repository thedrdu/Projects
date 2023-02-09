//Author(s): thedrdu
//Year of Creation: 2022

//todo: input custom width and height output size, different shading styles, width:height ratio processing
//todo: check this out: https://stackoverflow.com/questions/32987103/image-to-ascii-art-conversion
//todo: make this a webapp

#define WIDTH 1024
#define HEIGHT 1024

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb/stb_image_resize.h"

//Shading styles: regular + inverted:
// char outputChars[69] = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`\'.";
char outputChars[69] = ".\'`^\",:;Il!i><~+_-?][}{1)(|\\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$";

//Takes in RGB values and returns the character with the corresponding brightness level
char getChar(int r, int g, int b){
  int brightness = ((r + g + b) / 3) / (3.7); //Find a way to not have this final divisor hardcoded
  return outputChars[brightness];
}


//args: {source image file} [output text file]
int main(int argc, char** argv){
  if(argc < 2){
    printf("Please enter a filename!\n");
    exit(1);
  }

  int width, height, channels;
  unsigned char *img = stbi_load(argv[1], &width, &height, &channels, 3);
  printf("Loaded image with a width of %dpx, a height of %dpx and %d channels\n", width, height, channels);
  // stbir_resize_uint8(img, width, height, 0, img, 1024, 1024, 0, 3);

  if(img == NULL){
    printf("Error in loading the image\n");
    exit(1);
  }

  
  // width = WIDTH;
  // height = HEIGHT;
  // printf("Resized image to a width of %dpx, and a height of %dpx", width, height);

  // size_t img_size = width * height * channels;
  // int gray_channels = channels == 4 ? 2 : 1;
  // size_t gray_img_size = width * height * gray_channels;
  // unsigned char *gray_img = malloc(gray_img_size);

  // if(gray_img == NULL){
  //   printf("Unable to allocate memory for the gray image.\n");
  //   exit(1);
  // }

  // for(unsigned char *p = img, *pg = gray_img; p != img + img_size; p += channels, pg += gray_channels){
  //   *pg = (uint8_t)((*p + *(p + 1) + *(p + 2))/3.0);
  // }

  // stbi_write_jpg("pardo.jpg", width, height, gray_channels, gray_img, 100);

  FILE *fp = NULL;
  if(argc == 3){
    fp = fopen(argv[2], "w");
  }
  else{
    fp = fopen("textFile.txt" , "w");
  }
  int bytePerPixel = 1;

  for(int i = 0; i < height; i++){
    for(int j = 0; j < width; j++){
      unsigned char *pixelOffset = img + (j + width * i) * 3;
      unsigned char r = pixelOffset[0];
      unsigned char g = pixelOffset[1];
      unsigned char b = pixelOffset[2];
      // unsigned char a = channels >= 4 ? pixelOffset[3] : 0xff;
      //fprintf(fp, "[%d %d %d] ", r, g, b);
      fprintf(fp, "%c", getChar(r,g,b));
    }
    fprintf(fp, "\n");
  }
  

  return 0;
}
