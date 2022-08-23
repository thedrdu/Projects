#include <stdio.h>
#include <stdlib.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"

int main(int argc, char** argv) {
  printf("Hello World\n");

  int width, height, channels;
  unsigned char *img = stbi_load("Pardo.png", &width, &height, &channels, 0);

  if(img == NULL){
    printf("Error in loading the image\n");
    exit(1);
  }
  printf("Loaded image with a width of %dpx, a height of %dpx and %d channels\n", width, height, channels);

  size_t img_size = width * height * channels;
  int gray_channels = channels == 4 ? 2 : 1;
  size_t gray_img_size = width * height * gray_channels;
  unsigned char *gray_img = malloc(gray_img_size);

  if(gray_img == NULL){
    printf("Unable to allocate memory for the gray image.\n");
    exit(1);
  }

  for(unsigned char *p = img, *pg = gray_img; p != img + img_size; p += channels, pg += gray_channels){
    *pg = (uint8_t)((*p + *(p + 1) + *(p + 2))/3.0);
  }

  stbi_write_jpg("pardo.jpg", width, height, gray_channels, gray_img, 100);
  return 0;
}