#ifndef SHOOT_H
#define SHOOT_H

#include <raylib.h>
#include "sprite.h"

typedef struct shoot {
    Vector2 position;
    float rotation;

    bool active;
} Shoot;

void create_shoot(void);

void reset_shoot(Sprite* sprite);
void launch_shoot(void);

void update_shoot(float delta);
void draw_shoot(void);

bool shoot_collide(Sprite* sprite);

#endif
