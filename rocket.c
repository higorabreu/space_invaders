#include "rocket.h"
#include <pthread.h>
#include <unistd.h>
#include "game.h"

void tower_fire(GameState *game, Tower *tower) {
    pthread_mutex_lock(&game->mutex);

    if (game->rockets_available > 0) {
        for (int i = 0; i < game->num_rockets; i++) {
            if (!game->rockets[i].active) {
                game->rockets[i].x = tower->x;
                game->rockets[i].y = tower->y - 1;
                game->rockets[i].direction = tower->direction;
                game->rockets[i].active = 1;

                pthread_t rocket_thread;
                pthread_create(&rocket_thread, NULL, move_tower_rocket, (void *)game);
                pthread_detach(rocket_thread);
                game->rockets_available--;
                break;
            }
        }
    }

    pthread_mutex_unlock(&game->mutex);
}

void *move_tower_rocket(void *arg) {
    GameState *game = (GameState *)arg;

    while (1) {
        for (int i = 0; i < game->num_rockets; i++) {
            Rocket *rocket = &game->rockets[i];

            pthread_mutex_lock(&game->mutex);
            if (rocket->active) {
                rocket->y--;
                if (rocket->y < 0) {
                    rocket->active = 0;
                }
            }
            pthread_mutex_unlock(&game->mutex);

            usleep(ROCKET_SPEED);
        }
    }

    return NULL;
}



void *check_collision(void *arg) {
  GameState *game = (GameState *)arg;
  while (1) {
    for (int i = 0; i < game->num_ships; i++) {
      pthread_mutex_lock(&game->mutex);
      Ship ship = game->ships[i];
      pthread_mutex_unlock(&game->mutex);

      if (!ship.active) {
        continue;
      }

      for (int j = 0; j < game->num_rockets; j++) {
        pthread_mutex_lock(&game->mutex);
        Rocket rocket = game->rockets[j];
        pthread_mutex_unlock(&game->mutex);

        if (!rocket.active) {
          continue;
        }

        if (rocket.x >= ship.x && rocket.x <= ship.x + 6 &&
            rocket.y == ship.y) {
          pthread_mutex_lock(&game->mutex);
          game->ships[i].active = 0;
          game->rockets[j].active = 0;
          game->ships_destroyed++;
          pthread_mutex_unlock(&game->mutex);
        }
      }
    }

    usleep(8000);
  }
}

