#include <ncurses.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "game.h"
#include "interface.h"
#include "input.h"
#include "rocket.h"
#include "ship.h"

int main() {
    srand(time(NULL));
    GameState game; // armazena o estado do jogo

    // inicializa a tela do ncurses
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    printw("============================\n");
    printw("Select the difficulty level:\n");
    printw("1 - Easy\n");
    printw("2 - Medium\n");
    printw("3 - Hard\n");
    printw("============================\n");
    int input = getch();
    switch (input) {
        case '1':
            NUM_SHIPS = 5;
            NUM_ROCKETS = 10;
            SHIP_SPEED = 1000000;
            break;
        case '2':
            NUM_SHIPS = 10;
            NUM_ROCKETS = 5;
            SHIP_SPEED = 500000;
            break;
        case '3':
            NUM_SHIPS = 15;
            NUM_ROCKETS = 3;
            SHIP_SPEED = 200000;
            break;
        default:
            printw("Select a value between 1 and 3.\n");
            endwin();
            return 1;
    }

    getmaxyx(stdscr, screen_height, screen_width);
    endwin();

    Tower tower = {screen_width / 2, screen_height - 4, 2};

    initialize_game(&game, &tower);

    pthread_t thread_ships, thread_interface, thread_input, thread_collision;


    input_args args = {&game, &tower};
    // threads para movimentar as naves, atualizar a interface, capturar entrada e verificar colisões
    pthread_create(&thread_ships, NULL, move_ships, (void *)&game);
    pthread_create(&thread_interface, NULL, update_interface, (void *)&args);
    pthread_create(&thread_input, NULL, capture_input, (void *)&args);
    pthread_create(&thread_collision, NULL, check_collision, (void *)&game);

    // espera todas as threads terminarem
    pthread_join(thread_ships, NULL);
    pthread_join(thread_interface, NULL);
    pthread_join(thread_input, NULL);
    pthread_join(thread_collision, NULL);

    // destroi o mutex e libera a memória alocada
    pthread_mutex_destroy(&game.mutex);
    free(game.ships);
    free(game.rockets);

    return 0;
}
