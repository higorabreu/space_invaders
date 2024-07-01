#include "game.h"
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>
#include <time.h>

int NUM_SHIPS = 8;
int NUM_ROCKETS = 6;
int SHIP_SPEED = 450000;
int ROCKET_SPEED = 15000;

int screen_height, screen_width;

void initialize_game(GameState *game, Tower *tower) {
    game->ships = (Ship *)malloc(NUM_SHIPS * sizeof(Ship));
    game->rockets = (Rocket *)malloc(NUM_ROCKETS * sizeof(Rocket));
    game->num_ships = NUM_SHIPS;
    game->num_rockets = NUM_ROCKETS;
    game->rockets_available = NUM_ROCKETS;
    game->ships_destroyed = 0;
    game->ships_hit = 0;
    pthread_mutex_init(&game->mutex, NULL);

    for (int i = 0; i < NUM_SHIPS; i++) {
        int x, y;
        do {
            x = rand() % (screen_width - 6);
            y = 0;
        } while (!is_position_free(game, x, y));

        game->ships[i].x = x;
        game->ships[i].y = y;
        game->ships[i].active = 1;
    }

    for (int i = 0; i < NUM_ROCKETS; i++) {
        game->rockets[i].active = 0;
    }

    tower->x = screen_width / 2;
    tower->y = screen_height - 5;
}

int all_ships_destroyed(GameState *game) {
    pthread_mutex_lock(&game->mutex);
    int all_dead = 1;
    for (int i = 0; i < game->num_ships; i++) {
        if (game->ships[i].active) {
            all_dead = 0;
            break;
        }
    }
    pthread_mutex_unlock(&game->mutex);
    return all_dead;
}

void check_game_over(GameState *game) {
    pthread_mutex_lock(&game->mutex);
    int ships_destroyed = game->ships_destroyed;
    int ships_hit = game->ships_hit;
    int total_ships = game->num_ships;
    pthread_mutex_unlock(&game->mutex);

    if (ships_destroyed >= total_ships / 2 && all_ships_destroyed(game)) {
        clear();
        mvprintw(screen_height / 2, screen_width / 2 - 5, "You win!");
        refresh();
        usleep(1500000);
        endwin();
        exit(0);
    } else if (ships_hit >= total_ships / 2) {
        clear();
        mvprintw(screen_height / 2, screen_width / 2 - 5, "You Lose!");
        refresh();
        usleep(1500000);
        endwin();
        exit(0);
    }
}

int is_position_free(GameState *game, int x, int y) {
    for (int i = 0; i < game->num_ships; i++) {
        if (game->ships[i].active && game->ships[i].x >= x && game->ships[i].x <= x + 6) {
            return 0;
        }
    }
    return 1;
}
