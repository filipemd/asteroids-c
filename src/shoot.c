#include <math.h>

#include "shoot.h"
#include "main.h"
#include "paths.h"

static Shoot shoot;

static Sound shoot_sound;
static Sound explosion_sound;

void create_shoot(void) {
    shoot_sound = LoadSound(SHOOT_SOUND);
    explosion_sound = LoadSound(EXPLOSION_SOUND);

    SetSoundVolume(explosion_sound, .75f);
}

void reset_shoot(Sprite* sprite) {
    shoot.position.x = sprite->rect.x;
    shoot.position.y = sprite->rect.y;

    shoot.rotation = sprite->rotation * DEG2RAD;

    shoot.active = false;
}

void launch_shoot(void) {
    PlaySound(shoot_sound);
    shoot.active = true;
}

void update_shoot(float delta) {
    if (shoot.active) {
        shoot.position.x += sinf(shoot.rotation) * SHOOT_SPEED * delta;
        shoot.position.y -= cosf(shoot.rotation) * SHOOT_SPEED * delta;
    }
}

void draw_shoot(void) {
    if (shoot.active)
        DrawRectanglePro((Rectangle){shoot.position.x, shoot.position.y, 10, 10}, (Vector2){5, 5}, shoot.rotation*RAD2DEG, WHITE);
}

bool shoot_collide(Sprite* sprite) {
    const bool value = shoot.active && CheckCollisionPointRec(shoot.position, sprite->rect);
    if (value) {
        PlaySound(explosion_sound);
        shoot.active = false;
    }
    return value;
}
