#include <raylib.h>

#include "main.h"
#include "stars.h"

static int* x;
static int* y;

void create_stars(void) {
    x = LoadRandomSequence(STAR_AMOUNT, 0, swidth);
    y = LoadRandomSequence(STAR_AMOUNT, 0, sheight);
}

void draw_stars(void) {
    for(unsigned i=0; i < STAR_AMOUNT; i++)
        DrawRectangle(x[i], y[i], 2, 2, WHITE);
}

void destroy_stars(void) {
    UnloadRandomSequence(x);
    UnloadRandomSequence(y);
}
