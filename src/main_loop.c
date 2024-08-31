#include <raylib.h>

#include "main.h"
#include "main_loop.h"

#include "spaceship.h"
#include "asteroids.h"
#include "stars.h"

#include "ui.h"

static Spaceship* spaceship;
static bool paused = false;

static void reset(void) {
    level = 0;
    asteroid_amount = ASTEROID_AMOUNT;

    reset_asteroids();
    reset_spaceship();
}

void start(void) {
    spaceship = get_spaceship();

    create_spaceship();
    create_asteroids(spaceship);

    create_stars();
    create_ui();
}

void main_loop(float delta) {
    if (!paused) {
        update_spaceship(delta);
        update_asteroids(delta);
    }
}

void main_draw(void) {
    ClearBackground(BLACK);

    draw_stars();

    draw_spaceship();
    draw_asteroids();

    draw_ui(spaceship->lives, level, reset, &paused);
}

void end(void) {
    destroy_stars();

    destroy_spaceship();
    destroy_asteroids();
    destroy_ui();
}
