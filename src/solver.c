#include <stdio.h>
#include "solver.h"

Bool isSolved(Game *game) {
    Coordinate emptyCells[N * N * M * M];
    int emptyCellsCount;
    emptyCellsCount = getEmptyCells(game->user_matrix, emptyCells);
    return emptyCellsCount == 0;
}

void copyBoard(const Board sourceBoard, Board targetBoard) {
    int i, j;
    for (i = 0; i < N * M; ++i) {
        for (j = 0; j < N * M; ++j) {
            targetBoard[i][j] = sourceBoard[i][j];
        }
    }
}

int getEmptyCells(const Board board, Coordinate *emptyCells) {
    int i, j, emptyCount = 0;
    for (i = 0; i < N * M; ++i) {
        for (j = 0; j < N * M; ++j) {
            if (board[i][j] == 0) {
                emptyCells[emptyCount] = createCoordinate(i, j);
                emptyCount++;
            }
        }
    }
    return emptyCount;
}

void clearBoard(Board board) {
    int i, j;
    for (i = 0; i < N * M; ++i) {
        for (j = 0; j < N * M; ++j) {
            board[i][j] = 0;
        }
    }
}

void coordinateNeighbours(Board board, Coordinate coordinate, Coordinate neighbours[3 * N * M - N - M + 1]) {
    int i, j, k, neighboursCreated = 0;
    Coordinate leftMostBlockCoordinate = createCoordinate(
            coordinate.i - coordinate.i % N,
            coordinate.j - coordinate.j % M
    );

    for (i = leftMostBlockCoordinate.i + 0; i < leftMostBlockCoordinate.i + N; ++i) {
        for (j = leftMostBlockCoordinate.j + 0; j < leftMostBlockCoordinate.j + M; ++j) {
            if (i != coordinate.i && j != coordinate.j) {
                neighbours[neighboursCreated] = createCoordinate(i, j);
                neighboursCreated++;
            }
        }
    }

    for (k = 0; k < N * M; ++k) {
        if (coordinate.i != k) {
            neighbours[neighboursCreated] = createCoordinate(k, coordinate.j);
            neighboursCreated++;
        }

        if (coordinate.j != k) {
            neighbours[neighboursCreated] = createCoordinate(coordinate.i, k);
            neighboursCreated++;
        }
    }

}

int getPossibleValues(Board board, Coordinate coordinate, int *possibleValues) {
    int i, possibleValuesCount = 0;
    Coordinate neighbours[3 * N * M - N - M - 1];
    for (i = 0; i < N * M; ++i) {
        possibleValues[i] = i + 1;
    }

    coordinateNeighbours(board, coordinate, neighbours);

    for (i = 0; i < 3 * N * M - N - M - 1; ++i) {
        int neighbourValue = board[neighbours[i].i][neighbours[i].j];
        if (neighbourValue != 0) {
            possibleValues[neighbourValue - 1] = 0;
        }
    }

    for (i = 0; i < N * M; ++i) {
        if (possibleValues[i] != 0) {
            possibleValues[possibleValuesCount] = possibleValues[i];
            possibleValues[i] = i + 1;
            possibleValuesCount++;
        }
    }

    for (i = possibleValuesCount; i < N * M; ++i) {
        possibleValues[i] = 0;
    }

    return possibleValuesCount;
}

/* return the removed value */
int removeArrayIndex(int *arr, int arrLength, int removeI) {
    int i, removedValue = arr[removeI];

    for (i = removeI; i < arrLength - 1; ++i) {
        arr[i] = arr[i + 1];
    }

    return removedValue;
}

/* return the removed value randomly*/
int randomRemoveArrayIndex(int *arr, int arrLength) {
    return removeArrayIndex(arr, arrLength, randLimit(arrLength));
}

Bool
solveBoardRec(Board board, Bool isDeterministic, Coordinate *emptyCells, int emptyCellsCount,
              int start) {
    int possibleValuesCount;
    int possibleValues[N * M];
    Coordinate currentCoordinate = emptyCells[start];
    possibleValuesCount = getPossibleValues(board, currentCoordinate, possibleValues);
    if (possibleValuesCount == 0) {
        return false;
    }

    if (start == emptyCellsCount - 1) {
        board[currentCoordinate.i][currentCoordinate.j] = possibleValues[0];
        return true;
    }

    while (possibleValuesCount > 0) {
        int nextValue;

        if (possibleValuesCount == 1 || isDeterministic) {
            nextValue = removeArrayIndex(possibleValues,possibleValuesCount, 0);
        } else {
            nextValue = randomRemoveArrayIndex(possibleValues, possibleValuesCount);
        }


        board[currentCoordinate.i][currentCoordinate.j] = nextValue;
        if (solveBoardRec(board, isDeterministic, emptyCells, emptyCellsCount, start + 1)) {
            return true;
        }

        board[currentCoordinate.i][currentCoordinate.j] = 0;
        possibleValuesCount--;
    }

    return false;
}


Bool solveBoard(const Board board, Board solvedBoard, Bool isDeterministic) {
    Coordinate emptyCells[N * N * M * M];
    int emptyCellsCount;
    copyBoard(board, solvedBoard);
    emptyCellsCount = getEmptyCells(board, emptyCells);

    return solveBoardRec(solvedBoard, isDeterministic, emptyCells, emptyCellsCount, 0);
}

void generateFixedBoard(const BoolBoard board, int fixedAmount) {
    int i, j, randN, fixedCellsFound = 0;
    clearBoard((Board) board);

    while (fixedCellsFound < fixedAmount) {
        randN = randLimit(N * N * M * M);
        j = randN % (N * M);
        i = (randN - j) / (N * M);
        if (board[i][j] == 0) {
            board[i][j] = 1;
            fixedCellsFound++;
        }
    }
}


void generateGame(Game *game, int fixedAmount) {
    int i, j;
    clearBoard(game->user_matrix);
    solveBoard(game->user_matrix, game->solved_matrix, false);
    generateFixedBoard(game->fixed_matrix, fixedAmount);
    for (i = 0; i < N * M; ++i) {
        for (j = 0; j < N * M; ++j) {
            if (game->fixed_matrix[i][j]) {
                game->user_matrix[i][j] = game->solved_matrix[i][j];
            }
        }
    }
}
