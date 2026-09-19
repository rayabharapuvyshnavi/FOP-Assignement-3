#include "barcode.h"

static const char *digit_patterns[] = {
    "1110010", "1100110", "1101100", "1010000", "1011100",
    "1001110", "1000010", "1000100", "1001000", "1110100"
};

static void set_column(struct image *img, int x, int height, int white) {
    int value = white ? 255 : 0;
    struct pixel pixel = { value, value, value };

    for (int y = 0; y < height; y++) {
        img->pixels[y * img->width + x] = pixel;
    }
}

static void set_pattern(struct image *img, int *x, const char *pattern,
                        int invert) {
    for (int i = 0; pattern[i] != '\0'; i++) {
        int white = pattern[i] == '1';
        if (invert) {
            white = !white;
        }
        set_column(img, *x, img->height, white);
        (*x)++;
    }
}

struct image* barcode(char* data, int width, int height) {
    struct image *img = malloc(sizeof(struct image));
    img->pixels = malloc(sizeof(struct pixel) * width * height);
    img->width = width;
    img->height = height;

    int x = 0;
    set_pattern(img, &x, "111111111", 0);
    set_pattern(img, &x, "010", 0);

    for (int i = 0; i < 6; i++) {
        set_pattern(img, &x, digit_patterns[data[i] - '0'], 0);
    }

    set_pattern(img, &x, "10101", 0);

    for (int i = 6; i < 12; i++) {
        set_pattern(img, &x, digit_patterns[data[i] - '0'], 1);
    }

    set_pattern(img, &x, "010", 0);
    set_pattern(img, &x, "111111111", 0);

    return img;
}

