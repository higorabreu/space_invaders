#ifndef GAME_H
#define GAME_H

#include <pthread.h>

typedef struct {
    int x, y;
    int active;
} Ship;

typedef struct {
    int x, y;
    int direction;
    int active;
} Rocket;

typedef struct {
    Ship *ships;
    Rocket *rockets;
    int num_ships;
    int num_rockets;
    int rockets_available;
    int ships_destroyed;
    int ships_hit;
    pthread_mutex_t mutex;
} GameState;

typedef struct {
    int x, y;
    int direction;
} Tower;

extern int NUM_SHIPS;
extern int NUM_ROCKETS;
extern int SHIP_SPEED;
extern int ROCKET_SPEED;
extern int screen_height, screen_width;

void initialize_game(GameState *game, Tower *tower);
void check_game_over(GameState *game);
int all_ships_destroyed(GameState *game);
int verify_position(GameState *game, int x, int y);

#endif