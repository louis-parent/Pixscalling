# Pixscalling

3rd Semester project aiming to apply Pixel Scalling filters on images or any other sources!

## Compilation

### Linux

use `make` in the project folder to compile all the necessary files in one "pixscalling" executable file.

### Window

use `gcc -o pixscalling.exe main.c sources/ppm.c sources/timer.c sources/pixel.c sources/matrix.c sources/filter.c headers/ppm.h headers/timer.h headers/pixel.h headers/matrix.h headers/filter.h` in the project folder to compile all the necessary files in one "pixscalling.exe" executable file.

## Usage

Launch the pixscalling (`./pixscalling [Scale]`) executable file of the project root folder to transform the file "in.ppm" in a file called "out.ppm".
