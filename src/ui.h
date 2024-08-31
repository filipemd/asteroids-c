#ifndef UI_H
#define UI_H

#include <stdint.h>

void create_ui(void);
void draw_ui(uint8_t lives, uint8_t level, void (*reset)(void), bool* paused);
void destroy_ui(void);

#endif
