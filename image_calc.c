#include "barcode.h"
#include "loader.h"
#include <stdlib.h>
#include <string.h>



int main(int argc, char** argv){
    if(argc != 5) {
        printf("Incorrect number of arguments. Expected: ./build/image_calc <barcode_value> <width> <height> <output_image_path>\n");
        return -1;
    }

    char *data = argv[1];
    int width = atoi(argv[2]);
    int height = atoi(argv[3]);
    char *filename = argv[4];

    struct image *img = barcode(data, width, height);

    int result = saveimage(filename, img);
    free(img->pixels);
    free(img);
    return result;
}


