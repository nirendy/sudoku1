#include <stdio.h>
#include <stdlib.h>
#include "main_aux.h"
#include "parser.h"
#include "game.h"
#include "solver.h"
#include "SPBufferset.h"

int main(int argc, char *argv[]) {
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
        printBoard(game.user_matrix, game.fixed_matrix);

        printBoard(game.solved_matrix, game.fixed_matrix);

        while (!isFinished(&game) && !shouldRestart) {
            input = askUserForNextTurn();

            switch (input.command) {
                case SET:
                    setCoordinate(&game, input);
                    break;
                case HINT:
                    hint(&game, input.coordinate);
                    break;
                case VALIDATE:
                    validate(&game);
                    break;
                case RESTART:
                    shouldRestart = true;
                    break;
                case EXIT:
                    isGameOver = true;
                    break;
                case INVALID:
                    printf("Unreachable Code Error");
                    exit(0);
            }
        }
    }
    destroyGame(&game);

    exit(1);
}
