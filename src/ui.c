#include <raylib.h>

#include <stdint.h>
#include <stdio.h>

#include "main.h"
#include "ui.h"

#include "button.h"

#include "paths.h"

static Texture2D hearts;

void create_ui(void) {
    hearts = LoadTexture(HEART_PATH);
}

void draw_ui(uint8_t lives, uint8_t level, void (*reset)(void), bool* paused) {
    if (IsKeyPressed(KEY_ESCAPE) && lives != 0) {
        *paused = !*paused;
    }

    for(uint8_t i = 0; i < lives; i++) {
        const unsigned scaled_width = hearts.width*10;
        const unsigned scaled_height = hearts.height*10;

        DrawTexturePro(hearts, (Rectangle){0, 0, hearts.width, hearts.height}, (Rectangle){i*(scaled_width+10), 0, scaled_width, scaled_height}, (Vector2){0, 0}, 0, WHITE);
    }
    DrawText(TextFormat("Level: %d", level), swidth/2, 0, 48, WHITE);
    if(IsKeyDown(KEY_F)) {
        DrawFPS(0, sheight/2);
    }

    if (*paused) {
        DrawRectangle(0, 0, swidth, sheight, (Color){0, 0, 0, 128});

        if (Button((Rectangle){swidth/2, sheight/2-90, 300, 75}, "Continue", true))
            *paused = false;
        if (Button((Rectangle){swidth/2, sheight/2, 300, 75}, "Reset", true)) {
            reset();
            *paused = false;
        }

        // Não tem como fechar uma janela em um navegador.
        #ifndef PLATFORM_WEB
        if (Button((Rectangle){swidth/2, sheight/2+90, 300, 75}, "Exit", true))
            close_window = true;
        #endif
    }
    if (lives == 0) {
        if(Button((Rectangle){swidth/2, sheight/2, 300, 75}, "Play Again", true))
            reset();
    }
}

void destroy_ui(void) {
    UnloadTexture(hearts);
}
