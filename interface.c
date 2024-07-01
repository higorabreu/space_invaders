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

        for (int i = 0; i < game->num_ships; i++) {
            if (game->ships[i].active) {
                mvprintw(game->ships[i].y, game->ships[i].x, " /+\\ ");
                mvprintw(game->ships[i].y + 1, game->ships[i].x, "|-O-|");
                mvprintw(game->ships[i].y + 2, game->ships[i].x, " \\+/ ");
            }
        }

        for (int i = 0; i < game->num_rockets; i++) {
            if (game->rockets[i].active) {
                mvprintw(game->rockets[i].y, game->rockets[i].x, "|");
            }
        }

        for (int i = 0; i < game->num_rockets; i++) {
            Rocket *rocket = &game->rockets[i];

            if (rocket->active) {
                int x = rocket->x;
                int y = rocket->y;
                int direction = rocket->direction;

                if (direction == 0 || direction == 4) {
                    mvprintw(y, x, "__");
                } else if (direction == 1) {
                    mvprintw(y, x, "\\");
                } else if (direction == 2) {
                    mvprintw(y, x, "|");
                } else if (direction == 3) {
                    mvprintw(y, x, "/");
                }
            }
        }

        int tower_x = tower->x;
        int tower_y = tower->y;
        switch (tower->direction) {
            case 0:
                mvprintw(tower_y - 1, tower_x - 2, "__");
                break;
            case 1:
                mvprintw(tower_y - 1, tower_x - 1, "\\");
                break;
            case 2:
                mvprintw(tower_y - 1, tower_x - 1, " | ");
                break;
            case 3:
                mvprintw(tower_y - 1, tower_x + 1, "/");
                break;
            case 4:
                mvprintw(tower_y - 1, tower_x + 1, "__");
                break;
            default:
                mvprintw(tower_y - 1, tower_x, " | ");
                break;
        }

        mvprintw(tower_y, tower_x - 2, "  ^  ");
        mvprintw(tower_y + 1, tower_x -2, " /|\\ ");
        mvprintw(tower_y + 2, tower_x -2, "|-o-|");

        mvprintw(0, 0, "Rockets: %d/%d", game->rockets_available, game->num_rockets);
        mvprintw(1, 0, "Ships Destroyed: %d", game->ships_destroyed);
        mvprintw(2, 0, "Ships Hit: %d", game->ships_hit);

        pthread_mutex_unlock(&game->mutex);

        refresh();

        check_game_over(game);

        usleep(150000);
    }

    endwin();
    return NULL;
}
