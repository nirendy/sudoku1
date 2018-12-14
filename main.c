/*
 * defines
 * */

#define START_TURN USER

/*
 * includes
 * */
#include <stdio.h>
#include <stdlib.h>
#include "main_aux.h"
#include "parser.h"
#include "game.h"
#include "solver.h"
#include "SPBufferset.h"

int main(int argc, char **argv) {
    /*
     * init
     * */
    Input input;
    Bool shouldRestart, isGameOver = false;
    Game game;
    int fixedAmount;

    srand((unsigned int) strtol(*(argv + 1), (char **) NULL, 10));

    while (!isGameOver) {
        fixedAmount = askUserForHintsAmount();
        /*
         * puzzle generation:
         * */
        game = *createGame(fixedAmount);
        shouldRestart = false;

        while (isFinished(&game) && !shouldRestart) {
            input = askUserForNextTurn();

            switch (input.command) {
                case SET:
                    setCoordinate(&game, input);
                    break;
                case HINT:
                    hint(&game, input.coordinate);
                    break;
                case VALIDATE:
                    deterministicSolve(&game);
                    break;
                case RESTART:
                    shouldRestart = true;
                    break;
                case EXIT:
                    isGameOver = true;
            }
        }

        /* TODO: destroy matrix?*/
    }

    exit(1);
}
