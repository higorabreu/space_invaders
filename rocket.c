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

                // cria uma thread para movimentar o foguete
                pthread_t rocket_thread;
                pthread_create(&rocket_thread, NULL, move_tower_rocket, (void *)game);
                pthread_detach(rocket_thread);
                game->rockets_available--; // numero de foguetes disponiveis
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
                int direction = rocket->direction;

                switch (direction) {
                    case 0: rocket->x--; break; // 180 graus
                    case 1: rocket->y--; rocket->x -= 2; break; // 45 graus
                    case 2: rocket->y--; break; // 90 graus
                    case 3: rocket->y--; rocket->x += 2; break; // 45 graus
                    case 4: rocket->x++; break; // 180 graus
                    default: break;
                }

                if (rocket->y < 0 || rocket->x < 0 || rocket->x >= screen_width) {
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
                continue; // pula para a próxima nave se esta estiver inativa
            }

            for (int j = 0; j < game->num_rockets; j++) {
                pthread_mutex_lock(&game->mutex);
                Rocket rocket = game->rockets[j];
                pthread_mutex_unlock(&game->mutex);

                if (!rocket.active) {
                    continue; // pula para o próximo foguete se este estiver inativo
                }

                // verifica se o foguete colidiu com a nave
                if (rocket.x >= ship.x && rocket.x <= ship.x + 6 &&
                    rocket.y == ship.y) {
                    pthread_mutex_lock(&game->mutex);
                    game->ships[i].active = 0; // desativa a nave
                    game->rockets[j].active = 0; // desativa o foguete
                    game->ships_destroyed++;
                    pthread_mutex_unlock(&game->mutex);
                }
            }
        }

        usleep(8000);
    }
}
