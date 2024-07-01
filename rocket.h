#ifndef ROCKET_H
#define ROCKET_H

#include "game.h"

void tower_fire(GameState *game, Tower *tower);
void *move_tower_rocket(void *arg);
void *check_collision(void *arg);

#endif
