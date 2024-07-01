#include "ship.h"
#include <unistd.h>

void *move_ships(void *arg) {
    GameState *game = (GameState *)arg;

    while (1) {
        pthread_mutex_lock(&game->mutex);

        for (int i = 0; i < game->num_ships; i++) {
            if (game->ships[i].active) {
                game->ships[i].y++;

                if (game->ships[i].y >= screen_height - 1) {
                    game->ships[i].active = 0;
                    game->ships_hit++;
                }
            }
        }

        pthread_mutex_unlock(&game->mutex);

        check_game_over(game);
        usleep(SHIP_SPEED);
    }

    return NULL;
}
