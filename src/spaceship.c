#include <raylib.h>
#include <math.h>

#include "paths.h"
#include "main.h"

#include "spaceship.h"

#include "wrap_position.h"
#include "timer.h"

static Spaceship spaceship;

static Timer hit_delay;
static Timer blink_delay;
static Timer shoot_delay;

static int speed = 0;
static void movement(float delta) {
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
        spaceship.sprite.rotation -= delta * SPEED / 3;
    }
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
        spaceship.sprite.rotation += delta * SPEED / 3;
    }

    const float radians = spaceship.sprite.rotation * DEG2RAD;
    const Vector2 accel = { sinf(radians) * speed, -cosf(radians) * speed };

    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) {
        if(speed < SPEED) speed+=ACCELERATION*delta; else speed=SPEED;
    } else if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) {
        if(-speed < SPEED/2) speed-=ACCELERATION*delta; else speed=-SPEED/2;
    } else {
        if(speed > 0) speed-=ACCELERATION*delta; else speed = 0;
    }

    spaceship.sprite.rect.x += accel.x * delta;
    spaceship.sprite.rect.y += accel.y * delta;
}

Spaceship* get_spaceship(void) {
    return &spaceship;
}

void reset_spaceship(void) {
    spaceship.sprite.hide = false;
    spaceship.lives = LIVES_AMOUNT;
    stop_timer(&hit_delay);
}

void create_spaceship(void) {
    create_sprite(&spaceship.sprite, SPACESHIP_PATH, (Vector2){swidth/2, sheight/2}, 7, 0);
    create_shoot();

    spaceship.lives = LIVES_AMOUNT;
}

void update_spaceship(float delta) {
    if (!spaceship.sprite.hide) {
        movement(delta);
        wrap_position(&spaceship.sprite);

        if (IsKeyPressed(KEY_SPACE) && timer_done(&shoot_delay)) {
            start_timer(&shoot_delay, SHOOT_DELAY);
            reset_shoot(&spaceship.sprite);
            launch_shoot();
        }

        update_shoot(delta);
    }
}

void draw_spaceship(void) {
    draw_shoot();

    if (!timer_done(&hit_delay) && timer_done(&blink_delay)) {
        start_timer(&blink_delay, .1f);
    } else {
        draw_sprite(&spaceship.sprite);
    }
}

void destroy_spaceship(void) {
    destroy_sprite(&spaceship.sprite);
}

void hit_spaceship(void) {
    if (timer_done(&hit_delay) && spaceship.lives > 0) {
        start_timer(&hit_delay, 3);

        spaceship.lives--;
        if (spaceship.lives == 0) {
            spaceship.sprite.hide = true;
            reset_shoot(&spaceship.sprite);
        }
    }
}
