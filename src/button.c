#include <stdint.h>

#include "button.h"

#define FONT_SIZE 48

bool Button(Rectangle rect, const char* text, bool centered) {
    Rectangle button_rect;

    if(centered) {
        button_rect = (Rectangle){rect.x-rect.width/2, rect.y-rect.height/2, rect.width, rect.height};
    } else {
        button_rect = rect;
    }

    const bool hover = CheckCollisionPointRec(GetMousePosition(), button_rect);
    const bool clicked = hover && IsMouseButtonDown(0);

    Color gray;
    if (hover) {
        gray = (Color){148, 148, 148, 255};
    } else {
        gray = GRAY;
    }

    if (clicked) {
        DrawRectangle(button_rect.x, button_rect.y, button_rect.width+5, button_rect.height+5, WHITE);
    } else {
        DrawRectangle(button_rect.x-5, button_rect.y-5, button_rect.width+5, button_rect.height+5, WHITE);
    }
    DrawRectangleRec(button_rect, gray);

    if (!centered)
        DrawText(text, rect.x+10, button_rect.y+FONT_SIZE/4, FONT_SIZE, BLACK);
    else
        DrawText(text, rect.x-MeasureText(text, FONT_SIZE)/2, rect.y-FONT_SIZE/2, FONT_SIZE, BLACK);

    return clicked;
}
