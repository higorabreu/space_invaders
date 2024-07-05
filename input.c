#include "input.h"
#include <ncurses.h>
#include "game.h"
#include "tower.h"
#include "rocket.h"
#include <unistd.h>

void *capture_input(void *arg) {
    input_args *args = (input_args *)arg;
    GameState *game = args->game;
    Tower *tower = args->tower;

    while (1) {
        int ch = getch();
        switch (ch) {
            case 'a':
                // mira para a esquerda
                if (tower->direction > 0) {
                    tower->direction--;
                }
                break;
            case 'd':
                // mira para a direita
                if (tower->direction < 4) {
                    tower->direction++;
                }
                break;
            case KEY_LEFT:
                // move para a esquerda
                move_tower(game, tower, KEY_LEFT);
                break;
            case KEY_RIGHT:
                // move para a direita
                move_tower(game, tower, KEY_RIGHT);
                break;
            case ' ':
                // atira
                tower_fire(game, tower);
                break;
            case 'r':
                // recarrega
                reload_tower(game);
                break;
        }
        usleep(100000);
    }

    return NULL;
}
