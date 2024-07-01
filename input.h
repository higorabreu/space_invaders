#ifndef INPUT_H
#define INPUT_H

#include "game.h"
#include "tower.h"

typedef struct {
    GameState *game;
    Tower *tower;
} input_args;

void *capture_input(void *arg);

#endif
