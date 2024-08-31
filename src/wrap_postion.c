#include "wrap_position.h"

void wrap_position(Sprite* sprite) {
    const float halfWidth = sprite->rect.width / 2;
    const float halfHeight = sprite->rect.height / 2;

    if (sprite->rect.x < -halfWidth) {
        sprite->rect.x = swidth + halfWidth;
    } else if (sprite->rect.x > swidth + halfWidth) {
        sprite->rect.x = -halfWidth;
    }

    if (sprite->rect.y < -halfHeight) {
        sprite->rect.y = sheight + halfHeight;
    } else if (sprite->rect.y > sheight + halfHeight) {
        sprite->rect.y = -halfHeight;
    }
}
