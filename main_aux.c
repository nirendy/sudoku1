#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main_aux.h"
#include "solver.h"


void printError(Error2 err, Command command) {
    switch (err) {
        case EInvalidNumberOfCells:
            printf("Error2: invalid number of cells to fill (should be between 0 and %d)\n", N * M - 1);
            break;
        case ECellIsFixed:
            printf("Error2: cell is fixed\n");
            break;
        case EValueIsInvalid:
            printf("Error2: value is invalid\n");
            break;
        case EInvalidCommand:
            printf("Error2: invalid command\n");
            break;
        case EFunctionFailed:
            /* TODO: fill command*/
            printf("Error2: <%d> has failed\n", command);
            break;
    }
}

void printPrompt(Prompt prompt, int num1) {
    switch (prompt) {
        case PEnterFixedAmount:
            printf("Please enter the number of cells to fill [0-%d]:\n", N * M - 1);
            break;
        case PExit:
            printf("Exiting…\n");
            break;
        case PSuccess:
            printf("Puzzle solved successfully\n");
            break;
        case PHint:
            printf("Hint: set cell to %d\n", num1);
            break;
        case PValidateFailed:
            printf("Validation failed: board is unsolvable\n");
            break;
        case PValidateSuccess:
            printf("Validation passed: board is solvable\n");
            break;
    }
}

Coordinate createCoordinate(int i, int j) {
    Coordinate result;
    result.i = i;
    result.j = j;
    return result;
}

int randLimit(int limit) {
    return rand() % limit;
}

int askUserForHintsAmount() {
    return 0;
}

Game *createGame(int fixedAmount) {
    Game *game = malloc(sizeof(Game));
    int pInt[9][9] = *(int) malloc(N * N * M * M * sizeof(int));
    game->user_matrix = *pInt;
    return game;
}

void deterministicSolve(Game *game) {

}

Coordinate *getEmptyCells(Game *game) {
    return NULL;
}

Input askUserForNextTurn() {
    Input result;
    return result;
}

