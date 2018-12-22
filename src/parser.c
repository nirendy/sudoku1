#include "parser.h"

int isFixed(BoolBoard fixed_matrix, int i, int j) {
    return fixed_matrix[i][j];
}

int parseHintsAmount() {
    int hintsAmount;
    printPrompt(PEnterFixedAmount, 0);

    /*
     * read input
     * */
    if (scanf("%d", &hintsAmount) != 1) {
        char isEOF;
        if (scanf("%c", &isEOF) != EOF) {
            /* This part is just that the programs works as the example program*/
            printf("Error: not a number\n");
        }
        printPrompt(PExit, 0);
        exit(1);
    }

    /*
     * Validate input
     * */
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
        if (i % 3 == 0) {
            printf("%s", sep);
        }
        for (j = 0; j < 9; j++) {
            if (j % 3 == 0) {
                printf("| ");
            }
            if (isFixed(fixed_matrix, i, j)) {
                printf(".");
            } else {
                printf(" ");
            }

            if (matrix[i][j] != 0) {
                printf("%d", matrix[i][j]);
            } else {
                printf(" ");
            }
            printf(" ");
        }
        printf("|");
        printf("\n");
    }
    printf("%s", sep);
}

Input parseCommand() {
    char str[1024];
    char *token, command[10];
    int numOfVars = -1;
    int x = 0, y = 0, value = -1;
    int index = 0;
    Input returnedInput;
    returnedInput.command = INVALID;

    /*
     * Do until a non empty line received
     * */
    do {
        if (fgets(str, 1024, stdin) == NULL) {
            printPrompt(PExit, 0);
            exit(1);
        }
        token = strtok(str, " \t\r\n");
    } while (token == NULL);

    /*
     * Categorize token to commands
     * */
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

    /*
     *
     * */
    strcpy(command, token);

    token = strtok(NULL, " \t\r\n");
    index = 1;

    /*
     * while not all expected parameters has been interpreted
     * */
    while (token != NULL && index <= numOfVars) {

        switch (index) {
            case 1:
                x = token[0] - '0';
                break;
            case 2:
                y = token[0] - '0';
                break;
            case 3:
                value = token[0] - '0';
                break;
            default:
                printf("Unreachable Code Error");
                exit(0);
        }

        index++;
        token = strtok(NULL, " \t\r\n");
    }

    /*
     * if X,Y in needed for command make the values changed
     * if VALUE in needed for command make the values changed
     * */
    if (
            (numOfVars >= 2 && (x == 0 || y == 0))
            || (numOfVars == 3 && value == -1)
            ) {
        returnedInput.command = INVALID;
        printError(EInvalidCommand, INVALID);
        return returnedInput;
    }

    returnedInput.coordinate = createCoordinate(y - 1, x - 1);
    returnedInput.value = value;

    return returnedInput;
}

