#include "game.h"
#include "main_aux.h"


Coordinate *getEmptyCells(Game *game);

int *getPossibleValues(Game *game, Coordinate *coordinate);

Game *createGame(int fixedAmount);

void deterministicSolve(Game *game);

Bool isFinished(Game *game);



