#include "tower.h"
#include <ncurses.h>

void move_tower(GameState *game, Tower *tower, int direction) {
    pthread_mutex_lock(&game->mutex);
    if (direction == KEY_LEFT) {
        if (tower->x > 0) {
            tower->x--;
        }
    } else if (direction == KEY_RIGHT) {
        if (tower->x < screen_width - 1) {
            tower->x++;
        }
    }
    pthread_mutex_unlock(&game->mutex);
}


void reload_tower(GameState *game) {
    pthread_mutex_lock(&game->mutex);
    game->rockets_available = game->num_rockets;
    pthread_mutex_unlock(&game->mutex);
}
