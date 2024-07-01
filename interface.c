#include "interface.h"
#include <ncurses.h>
#include <unistd.h>
#include "input.h"

void *update_interface(void *arg) {
    input_args *args = (input_args *)arg;
    GameState *game = args->game;
    Tower *tower = args->tower;

    while (1) {
        usleep(50000);
        clear();

        pthread_mutex_lock(&game->mutex);

        // Draw ships
        for (int i = 0; i < game->num_ships; i++) {
            if (game->ships[i].active) {
                mvprintw(game->ships[i].y, game->ships[i].x, " /+\\ ");
                mvprintw(game->ships[i].y + 1, game->ships[i].x, "|-O-|");
                mvprintw(game->ships[i].y + 2, game->ships[i].x, " \\+/ ");
            }
        }

        // Draw rockets
        for (int i = 0; i < game->num_rockets; i++) {
            if (game->rockets[i].active) {
                mvprintw(game->rockets[i].y, game->rockets[i].x, "|");
            }
        }

        // Draw the tower
        mvprintw(tower->y, tower->x, "  ^  ");
        mvprintw(tower->y + 1, tower->x, " /|\\ ");
        mvprintw(tower->y + 2, tower->x, "|-o-|");

        // Game information
        mvprintw(0, 0, "Rockets: %d/%d", game->rockets_available, game->num_rockets);
        mvprintw(1, 0, "Ships Destroyed: %d", game->ships_destroyed);
        mvprintw(2, 0, "Ships Hit: %d", game->ships_hit);

        pthread_mutex_unlock(&game->mutex);

        refresh();
    }

    return NULL;
}
