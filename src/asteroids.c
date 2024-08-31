#include <raylib.h>

#include <stdint.h>
#include <stdlib.h>
#include <math.h>

#include "main.h"
#include "asteroids.h"

#include "shoot.h"
#include "spaceship.h"
#include "sprite.h"
#include "wrap_position.h"

enum asteroid_type {
    ASTEROID_BIG,
    ASTEROID_SMALL
};

typedef struct asteroid {
    Sprite sprite;
    enum asteroid_type type;

    unsigned speed;
} Asteroid;

static Asteroid* asteroids;

static Spaceship* spaceship;

static Texture2D asteroid_texture;
static Texture2D small_asteroid_texture;

unsigned asteroid_amount = ASTEROID_AMOUNT;
uint8_t level = 0;

static void movement(Asteroid* asteroid, float delta) {
    const float radians = asteroid->sprite.rotation * DEG2RAD;
    const float offset_x = sinf(radians) * asteroid->speed * delta;
    const float offset_y = cosf(radians) * asteroid->speed * delta;
    asteroid->sprite.rect.x += offset_x;
    asteroid->sprite.rect.y += offset_y;
}

static void remove_asteroid(uint8_t i) {
    for(unsigned j = i; j < asteroid_amount-1; j++) {
        asteroids[j] = asteroids[j+1];
    }
}

void reset_asteroids(void) {
    free(asteroids);
    asteroids = calloc(asteroid_amount, sizeof(Asteroid));
    for(uint8_t i = 0; i < asteroid_amount; i++) {
        create_sprite(&asteroids[i].sprite, NULL, (Vector2){GetRandomValue(0, swidth), GetRandomValue(0, sheight)}, 1.5, GetRandomValue(0, 360));
        set_sprite_texture(&asteroids[i].sprite, asteroid_texture);
        asteroids[i].type = ASTEROID_BIG;
        asteroids[i].speed = ASTEROID_SPEED;

        // Verifica se o asteroide está longe da nave:
        while(sqrtf(powf(asteroids[i].sprite.rect.x - spaceship->sprite.rect.x, 2) + powf(asteroids[i].sprite.rect.y - spaceship->sprite.rect.y, 2)) < 350) {
            asteroids[i].sprite.rect.x = GetRandomValue(0, swidth);
            asteroids[i].sprite.rect.y = GetRandomValue(0, sheight);
        }
    }
}

void create_asteroids(Spaceship* spaceship_pointer) {
    spaceship = spaceship_pointer;

    asteroid_texture = LoadTexture("assets/textures/asteroid.png");
    small_asteroid_texture = LoadTexture("assets/textures/small_asteroid.png");

    reset_asteroids();
}

void update_asteroids(float delta) {
    for(uint8_t i = 0; i < asteroid_amount; i++) {
        if (!asteroids[i].sprite.hide) {
            movement(&asteroids[i], delta);
            wrap_position(&asteroids[i].sprite);

            if (sprite_collide(&asteroids[i].sprite, &spaceship->sprite)) {
                hit_spaceship();
            }
            if (shoot_collide(&asteroids[i].sprite)) {
                if(asteroids[i].type == ASTEROID_SMALL) {
                    remove_asteroid(i);
                    asteroids = realloc(asteroids, --asteroid_amount*sizeof(Asteroid));
                    if (asteroid_amount == 0) {
                        asteroid_amount = ASTEROID_AMOUNT+(++level);

                        reset_asteroids();
                    }
                } else {
                    const Asteroid destroyed_asteroid = asteroids[i];
                    remove_asteroid(i);

                    asteroid_amount += SMALL_ASTEROID_AMOUNT;
                    asteroids = realloc(asteroids, asteroid_amount*sizeof(Asteroid));
                    for(unsigned j = asteroid_amount-SMALL_ASTEROID_AMOUNT-1; j < asteroid_amount; j++) {
                        asteroids[j].sprite.scale = 6;
                        asteroids[j].type = ASTEROID_SMALL;

                        asteroids[j].sprite.rect.x = destroyed_asteroid.sprite.rect.x + GetRandomValue(-20, 20);
                        asteroids[j].sprite.rect.y = destroyed_asteroid.sprite.rect.y + GetRandomValue(-20, 20);
                        asteroids[j].sprite.rotation = destroyed_asteroid.sprite.rotation + GetRandomValue(-90, 90);

                        asteroids[j].speed = ASTEROID_SPEED*2;

                        set_sprite_texture(&asteroids[j].sprite, small_asteroid_texture);
                    }
                }
            }
        }
    }
}

void draw_asteroids(void) {
    for(uint8_t i = 0; i < asteroid_amount; i++) {
        draw_sprite(&asteroids[i].sprite);
    }
}

void destroy_asteroids(void) {
    for(uint8_t i = 0; i < asteroid_amount; i++) {
        destroy_sprite(&asteroids[i].sprite);
    }
    free(asteroids);
}
