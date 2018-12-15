#include "parser.h"

int isFixed(BoolBoard fixed_matrix, int i, int j) {
    return fixed_matrix[i][j];
}

int parseHintsAmount() {
    int hintsAmount;
    char c;
    printPrompt(PEnterFixedAmount, 0);
    if (scanf("%d", &hintsAmount) != 1) {
        printError(EInvalidNumberOfCells, 0);
        scanf(" %c", &c);
        return -1;
    }

    if (!(0 <= hintsAmount && hintsAmount <= N * N * M * M - 1)) {
        printError(EInvalidNumberOfCells, 0);
        return -1;
    }

    return hintsAmount;
}


void printBoard(const Board matrix, const BoolBoard fixed_matrix) {
    int i = 0, j = 0;
    char sep[35] = "----------------------------------\n";

    for (i = 0; i < 9; i++) {
        if (i % 3 == 0)
            printf("%s", sep);
        for (j = 0; j < 9; j++) {
            if (j % 3 == 0)
                printf("| ");
            if (isFixed(fixed_matrix, i, j))
                printf(".");
            else
                printf(" ");

            if (matrix[i][j] != 0)
                printf("%d", matrix[i][j]);
            else
                printf(" ");
            printf(" ");
        }
        printf("|");
        printf("\n");
    }
    printf("%s", sep);
}

Input parseCommand() {
    /*TODO: get numOfVars from a function*/
    char str[1024];
    char *token, command[10];
    int numOfVars = -1;
    int x = 0, y = 0, z = -1;
    int index = 0;
    Input returnedInput;
    returnedInput.command = INVALID;

    do {
        fgets(str, 1024, stdin);
        token = strtok(str, " \t\r\n");
    } while (token == NULL);

    if (!strcmp(token, "set")) {
        numOfVars = 3;
        returnedInput.command = SET;
    }

    if (!strcmp(token, "hint")) {
        numOfVars = 2;
        returnedInput.command = HINT;
    }

    if (!strcmp(token, "validate") || !strcmp(token, "restart") || !strcmp(token, "exit")) {
        numOfVars = 0;
        if (!strcmp(token, "validate")) {
            returnedInput.command = VALIDATE;
        }
        if (!strcmp(token, "restart")) {
            returnedInput.command = RESTART;
        }
        if (!strcmp(token, "exit")) {
            returnedInput.command = EXIT;
        }
    }

    if (numOfVars == -1) {
        printError(EInvalidCommand, INVALID);
        return returnedInput;
    }

    strcpy(command, token);

    token = strtok(NULL, " \t\r\n");
    index = 1;

    while (token != NULL && index <= numOfVars) {

        switch (index) {
            case 1:
                x = token[0] - '0';
                break;
            case 2:
                y = token[0] - '0';
                break;
            case 3:
                z = token[0] - '0';
                break;
            default:
                printf("Unreachable Code Error");
                exit(0);
        }

        index++;
        token = strtok(NULL, " \t\r\n");
    }

    if (
            (numOfVars >= 2 && (x == 0 || y == 0))
            || (numOfVars == 3 && z == -1)
            ) {
        returnedInput.command = INVALID;
        printError(EInvalidCommand, INVALID);
        return returnedInput;
    }

    returnedInput.coordinate = createCoordinate(x - 1, y - 1);
    returnedInput.value = z;

    return returnedInput;
}

