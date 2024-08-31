#include <raylib.h>
#include <stddef.h>

#include "sprite.h"

void create_sprite(Sprite* sprite, const char* file_path, Vector2 position, float scale, int rotation) {
    if (file_path) {
        sprite->texture = LoadTexture(file_path);
    }

    sprite->scale = scale;

    sprite->rotation = rotation;

    sprite->rect = (Rectangle){position.x, position.y, sprite->texture.width*sprite->scale, sprite->texture.height*sprite->scale};

    sprite->hide = false;
}

void draw_sprite(Sprite *sprite) {
    if (!sprite->hide) DrawTexturePro(sprite->texture, (Rectangle){0, 0, sprite->texture.width, sprite->texture.height}, sprite->rect, (Vector2){sprite->rect.width/2, sprite->rect.height/2}, sprite->rotation, WHITE);
}

void destroy_sprite(Sprite *sprite) {
    UnloadTexture(sprite->texture);
}

bool sprite_collide(Sprite* sprite1, Sprite* sprite2) {
   return CheckCollisionRecs(sprite1->rect, sprite2->rect) && !sprite1->hide && !sprite2->hide;
}

void set_sprite_texture(Sprite* sprite, Texture2D texture) {
    sprite->texture = texture;
    sprite->rect = (Rectangle){sprite->rect.x, sprite->rect.y, sprite->texture.width*sprite->scale, sprite->texture.height*sprite->scale};
}
