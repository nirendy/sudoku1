#include "game.h"
#include "solver.h"
#include "parser.h"

Bool isCoordinateFixed(Game *game, Coordinate coordinate) {
    return game->fixed_matrix[coordinate.i][coordinate.j] == true;
}

Bool isValueInNeighbours(Game *game, Coordinate coordinate, int value) {
    int possibleValues[N * M];
    int i, possibleValuesCount;
    possibleValuesCount = getPossibleValues(game->user_matrix, coordinate, possibleValues);

    for (i = 0; i < possibleValuesCount; ++i) {
        if (possibleValues[i] == value) {
            return false;
        }
    }

    return true;
}

void setCoordinate(Game *game, Input input) {
    if (isCoordinateFixed(game, input.coordinate)) {
        printError(ECellIsFixed, INVALID);
    } else if (input.value != 0 && isValueInNeighbours(game, input.coordinate, input.value)) {
        printError(EValueIsInvalid, INVALID);
    } else {
        game->user_matrix[input.coordinate.i][input.coordinate.j] = input.value;
        printBoard(game->user_matrix, game->fixed_matrix);
        if (isSolved(game)) {
            printPrompt(PSuccess, 0);
        }
    }
}

void hint(Game *game, Coordinate coordinate) {
    printPrompt(PHint, game->solved_matrix[coordinate.i][coordinate.j]);
}

void validate(Game *game) {
    if (solveBoard(game->user_matrix, game->solved_matrix, true)) {
        printPrompt(PValidateSuccess, 0);
    } else {
        printPrompt(PValidateFailed, 0);
    }
}
