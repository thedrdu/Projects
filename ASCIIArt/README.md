# ASCIIArt

A C program to analyze .ttf and .otf font files, and convert common image file formats into text files containing ASCII artwork. You can find example outputs labeled in the format of `example_.txt`
<br><br>
## Running this project

There are two programs in use here. 

The first is `bitmapreader.c`, which analyzes a font file and exports the "brightness" value for each ASCII character.

First, place any fonts you want analyzed inside the `fonts` directory.

To compile `bitmapreader.c`, cd to the ASCIIArt directory and run the following command: ```{finish later}```.

This will provide a `bitmapreader` executable. You can invoke this with `./bitmapreader {your_font_filename}`. The resultant brightness values will be printed in the console.
<br><br><br>
The second program is `main.c`, which analyzes an image file and exports a resulting text file.

finish later