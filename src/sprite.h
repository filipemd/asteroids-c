#ifndef SPRITE_H
#define SPRITE_H

#include <raylib.h>

typedef struct sprite {
    Texture2D texture;

    float scale;
    int rotation;

    Rectangle rect;

    bool hide;
} Sprite;

void create_sprite(Sprite* sprite, const char* file_path, Vector2 position, float scale, int rotation);
void draw_sprite(Sprite *sprite);
void destroy_sprite(Sprite* sprite);

bool sprite_collide(Sprite* sprite1, Sprite* sprite2);
void set_sprite_texture(Sprite* sprite, Texture2D texture);

#endif
