#ifndef MAIN_H
#define MAIN_H

#ifdef __EMSCRIPTEN__
#include "raylib.h"
#else
#include <raylib.h>
#endif
#include <stdint.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

extern uint16_t swidth;
extern uint16_t sheight;

extern bool close_window;

#define SPEED 600
#define ACCELERATION 2400
#define LIVES_AMOUNT 5

#define ASTEROID_AMOUNT 1
#define SMALL_ASTEROID_AMOUNT 2
#define ASTEROID_SPEED 75

#define SHOOT_SPEED 2000
#define SHOOT_DELAY .4f // (Em segundos).

#define STAR_AMOUNT 650

#endif
