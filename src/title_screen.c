#include <raylib.h>

#include "button.h"

#include "main.h"
#include "main_loop.h"

#include "title_screen.h"

void draw_title_screen(void) {
    DrawText("Asteroids", 16, 16, 96, WHITE);

    if(Button((Rectangle){16, 128, 256, 64}, "Play", false))
        scene = GAME;
    
    DrawText("License: "LICENSE"\nVersion "VERSION, 0, sheight-48, 24, WHITE);
}
