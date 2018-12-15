#include "parser.h"
#include <stdio.h>
#include <string.h>
#include "SPBufferset.h"

int isFixed(int i, int j){
	return 1;
}

void printMat(){

	int i=0,j=0,k=1;
	int matrix [9][9]={0};
	char sep[35] = "----------------------------------\n";

	for (i=0; i<9 ; i++){
		for (j=0 ; j<9 ; j++){
			matrix[i][j] = 1;
			k++;
		}

	}

	for (i=0; i<9 ; i++){
		if (i%3==0)
			printf("%s",sep);
		for (j=0 ; j<9 ; j++){
			if (j%3==0)
				printf("| ");
			if (isFixed(i,j))
				printf(".");
			else
				printf(" ");

			if (matrix[i][j]!=0)
				printf("%d",matrix[i][j]);
			else
				printf(" ");
			printf(" ");
		}
		printf("|");
		printf("\n");
	}

}

int parseCommand(){

	char str[1024];
	char *token ,command[10];
	int numOfVars= -1;
	int X=0,Y=0,Z=0;
	int index=0;

	SP_BUFF_SET();
	printf("input: ");
	fgets(str,1024,stdin);
	token = strtok(str, " \t\r\n");

	if (!strcmp(token,"set"))
		numOfVars = 3;

	if (!strcmp(token,"hint"))
		numOfVars = 2;

	if (!strcmp(token,"validate") || !strcmp(token,"restart") || !strcmp(token,"exit") )
		numOfVars = 0;

	if (numOfVars ==-1)
		return (0); /*printf("error");*/

	strcpy(command, token);

	token = strtok(NULL, " \t\r\n");
	index =1;

	while (token!=NULL && index<=numOfVars) {

		switch (index){
			case 1:
				X = token[0] - '0';
				break;
			case 2:
				Y = token[0] - '0';
				break;
			case 3:
				Z = token[0] - '0';
				break;

		}

		index++;
		token = strtok(NULL, " \t\r\n");
	}

	printf("command: %s\n",command);
	if (numOfVars>=2)
		printf("cords: %d %d\n",X,Y);
	if (numOfVars==3)
		printf("value: %d\n",Z);

	return (0);
}

