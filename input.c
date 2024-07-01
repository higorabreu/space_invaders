#include "input.h"
#include <ncurses.h>
#include "game.h"
#include "tower.h"
#include "rocket.h"

void *capture_input(void *arg) {
    input_args *args = (input_args *)arg;
    GameState *game = args->game;
    Tower *tower = args->tower;

    while (1) {
        int ch = getch();
        switch (ch) {
            case KEY_LEFT:
                move_tower(game, tower, KEY_LEFT);
                break;
            case KEY_RIGHT:
                move_tower(game, tower, KEY_RIGHT);
                break;
            case ' ':
                tower_fire(game, tower);
                break;
            case 'r':
                reload_tower(game);
                break;
        }
    }

    return NULL;
}
