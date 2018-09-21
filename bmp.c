#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *in;
    FILE *out;

    in = fopen("in.bmp", "rb");
    out = fopen("out.bmp", "wb");

    fseek(in, 0L, SEEK_END);
    int size = ftell(in);
    fseek(in, 0L, SEEK_SET);

   for(int i = 0; i < size; i++){
       if(i < 34){
           fputc(fgetc(in), out);
       }else{
           fputc(fgetc(in)+19000000, out);
       }
    }

    fclose(in);
    fclose(out);
}
