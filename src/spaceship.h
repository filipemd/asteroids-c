#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <stdint.h>

#include "sprite.h"
#include "shoot.h"

typedef struct spaceship {
    Sprite sprite;
    uint8_t lives;

    Shoot shoot;
} Spaceship;

Spaceship* get_spaceship(void);

void reset_spaceship(void);
void create_spaceship(void);
void update_spaceship(float delta);
void draw_spaceship(void);
void destroy_spaceship(void);

void hit_spaceship(void);

#endif
