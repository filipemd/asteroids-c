#ifndef MAIN_LOOP_H
#define MAIN_LOOP_H

enum scenes {
    TITLE_SCREEN,
    GAME
};

extern enum scenes scene;

void start(void);
void main_loop(float delta);
void main_draw(void);
void end(void);

#endif
