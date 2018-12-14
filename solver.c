#include "solver.h"

Bool isFinished(Game *game) {
    Coordinate *arr = getEmptyCells(game);
    return arr == 0;
}

/*
Coordinate getEmptyCells(Game *game) {
    int i, j;
    */
/*Coordinate tempCoordinate;*//*

    Coordinate *arr[N * N * M * M] = {0};

    for (i = 0; i < N * M; ++i) {
        for (j = 0; j < N * M; ++j) {
            if (game->user_matrix[i][j] ==0){

            }
        }

    }
    while ((arr + i) == 0) {

        i++;
    }

    return arr;
}
*/
