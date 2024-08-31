#include "main.h"
#include "main_loop.h"

int main(void) {
    swidth = SCREEN_WIDTH;
    sheight = SCREEN_HEIGHT;

    InitWindow(swidth, sheight, "Game");
    InitAudioDevice();

    SetTargetFPS(60);
    SetExitKey(KEY_NULL);

    start();

    close_window = false;
    while (!close_window) {
        close_window = WindowShouldClose();
        main_loop(GetFrameTime());

        BeginDrawing();
            main_draw();
        EndDrawing();
    }
    end();

    CloseWindow();

    return 0;
}
