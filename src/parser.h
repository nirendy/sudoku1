#ifndef HW2_PARSER_H
#define HW2_PARSER_H

#include <stdio.h>
#include <string.h>
#include "SPBufferset.h"
#include "main_aux.h"


void printBoard(const Board matrix, const BoolBoard fixed_matrix);

int parseHintsAmount();

Input parseCommand();


#endif

