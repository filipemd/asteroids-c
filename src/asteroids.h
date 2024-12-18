#ifndef ASTEROIDS_H
#define ASTEROIDS_H

#include <stdint.h>
#include "spaceship.h"

extern unsigned asteroid_amount;
extern uint8_t level;

void reset_asteroids(void);
void create_asteroids(Spaceship* spaceship);
void update_asteroids(float delta);
void draw_asteroids(void);
void destroy_asteroids(void);

#endif
