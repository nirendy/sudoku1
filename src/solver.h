#ifndef HW2_SOLVER_H
#define HW2_SOLVER_H

#include "game.h"
#include "main_aux.h"


void clearBoard(Board board);

int getEmptyCells(const Board board, Coordinate *emptyCells);

/*int getPossibleValues(Game *game, Coordinate coordinate, int possibleValues[N * M]);*/

void generateGame(Game *game, int fixedAmount);

Bool solveBoard(const Board board, Board solvedBoard, Bool isDeterministic);

/*void coordinateNeighbours(Game *game, Coordinate coordinate, Coordinate neighbours[2* N * M - N - M + 1]);*/


Bool isFinished(Game *game);


#endif

