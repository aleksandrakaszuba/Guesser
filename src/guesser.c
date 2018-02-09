/*
 ============================================================================
 Name        : guesser.c
 Author      : Aleksandra Kaszuba
 Class       : CCPS305
 Description :
 A game in which a user is given a pointer (address) of some random item in the 2-D array.
 User must guess the corresponding INDEX of the array (i and j values).
 This guessing game repeats for various addresses in the array, until the
 user Quits.
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>

#define ROWS 2
#define COLS 20
#define NDEFAULT 5;

//Main Matrix complex M variables;
typedef struct {
	int real_part;
	int imag_part;
} complex;

complex **M;
unsigned int N;
char code[100];
int iguess;
int jguess;
int i;
int j;

//User input variables
char userinput[ROWS][COLS];
int play;

//Stats variables
int gamescount;
int hintscount;
int goodguess;
int badguessescount;
int games_total, games_allcorrect_nohints, games_nohints,
		games_allcorrect_1hint, games_1hint;
struct Game {
	int number;
	int badguesses;
	int hints;
	struct Game *next;
};
struct StatisticsList {
	struct Game *head;
};
struct StatisticsList *listPointer;

///// Functions for game start //////////////
void displayFirstPointer() {
	printf("\n");
	printf(">>>>>>>>>>>>>>>>>>>>>>   START   >>>>>>>>>>>>>>>>>>>>>> \n");
	printf("\n");
	printf("M[%d][%d] = %p \n", 0, 0, &M[0][0]);
}

void displayRandomPointer(int i, int j) {
	printf("M[i][j] = %p \n", &M[i][j]);
	printf("\n");
	printf("What's i and j? (or Q or H or HH or HHH)\n");
	printf("--------------------------------------------------------\n");
}

void playgame(int i, int j) {
	displayFirstPointer();
	displayRandomPointer(i, j);
	scanf(" %100[^\n]", code);
}

////// Hints ///////
void simpleHint() {
	printf("\n");
	printf("Simple hint \n");
	hintscount++;
	for (i = 0; i < N; i++) {
		for (j = 0; j <= 0; j++) {
			printf("M[%d][%d] = %p \n", i, j, &M[i][j]);
		}
	}

}
//moderate hint
void moderateHint() {
	hintscount++;
	printf("\n");
	printf("Moderate hint \n");
	for (i = 0; i < 1; i++) {
		for (j = 0; j < N; j++) {
			printf("M[%d][%d] %p ", i, j, &M[i][j]);
		}
		printf("\n");
	}
	for (i = 1; i < N; i++) {
		for (j = 0; j <= 0; j++) {
			printf("M[%d][%d] %p \n", i, j, &M[i][j]);
		}
	}
}
//strong hint
void strongHint() {
	hintscount++;
	printf("\n");
	printf("Strong hint \n");
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			printf("M[%d][%d] %p ", i, j, &M[i][j]);
		}
		printf("\n");
	}
}

//////Stats functions ///////
//// storing stats
void addItem(struct StatisticsList *listPointer, int gamescount, int badguessescount, int hintscount) {
	struct Game *tempItem;
	tempItem = malloc(sizeof(struct Game));
	tempItem->number = gamescount;
	tempItem->badguesses = badguessescount;
	tempItem->hints = hintscount;

	if (listPointer->head == NULL) {
		tempItem->next = NULL;
		listPointer->head = tempItem;
	} else {
		tempItem->next = listPointer->head;
		listPointer->head = tempItem;
	}
}
//// display stats

void displayStat(struct StatisticsList *listPointer, int gamescount) {
	games_total = 0;
	games_allcorrect_nohints = 0;
	games_nohints = 0;
	games_allcorrect_1hint = 0;
	games_1hint = 0;

	struct Game *listIterrator = listPointer->head;
	while (listIterrator != NULL) {

		if (listIterrator->badguesses == 0 & listIterrator->hints == 0) {
			games_allcorrect_nohints++;
		}
		if (listIterrator->badguesses >= 2 & listIterrator->hints == 0) {
			games_nohints++;
		}
		if (listIterrator->badguesses == 0 & listIterrator->hints >= 1) {
			games_allcorrect_1hint++;
		}
		if (listIterrator->hints >= 1) {
			games_1hint++;
		}
		listIterrator = listIterrator->next;
	}
	games_total = gamescount;
	printf("\n");
	printf("<<<<<<<<<<<<<<<<<<<<<<< STATISTICS <<<<<<<<<<<<<<<<<<<<<<< \n");
	if(games_total>0){
	printf("Total number of games %d \n", games_total);
	printf("%d%% Guessed first time after 0 hints\n",
			((games_allcorrect_nohints) * 100 / games_total));
	printf("%d%% Guessed after 2 or more guesses, 0 hints\n",
			((games_nohints) * 100 / games_total));
	printf("%d%% Guessed first time after 1 or more hints\n",
			((games_allcorrect_1hint) * 100 / games_total));
	printf("%d%% Guessed after after 1 or more hints\n",
			((games_1hint) * 100 / games_total));
	printf("--------------------------------------------------------:\n");
	printf("%d No of games guessed first time after 0 hints \n", games_allcorrect_nohints);
	printf("%d No of games guessed after 2 or more guesses, 0 hints\n", games_nohints);
	printf("%d No of games guessed after after 1 or more hints\n \n", games_1hint);
	}
	else{
		printf("Total number of games %d \n", games_total);
		printf("There are no statistics for your games.\n");
	}
}
////// Handling user input ///////
void hintsinput(char *userinput){

	if (strcmp(userinput, "H") == 0 || strcmp(userinput, "h") == 0) {
		simpleHint();
	}
	if (strcmp(userinput, "HH") == 0 || strcmp(userinput, "hh") == 0) {
		moderateHint();
	}
	if (strcmp(userinput, "HHH") == 0 || strcmp(userinput, "hhh") == 0) {
		strongHint();
	}
}

void quitProgram(struct StatisticsList *listPointer, char *userinput, int *play, int gamescount){
	if (strcmp(userinput, "Q") == 0 || strcmp(userinput, "q") == 0) {
		displayStat(listPointer, gamescount);
		*play = 1;
	}
}
void badGuess(int *badguesscount) {
	printf("\n");
	printf("Incorrect guess, try again \n");

}
void goodGuess(struct StatisticsList *listPointer, int guesscount, int badguesscount, int hintcount, char *userinput) {
	printf("\n");
	printf("Good guess. Congratulation! \n");
	addItem(listPointer, gamescount, badguessescount, hintscount);
	displayStat(listPointer, gamescount);

}

int main(int argc, char **argv) {

	////INIT/////
	iguess = 0;
	jguess = 0;
	play = 0;
	int endgame;

	gamescount = 0;
	games_total = 0;
	games_allcorrect_nohints = 0;
	games_nohints = 0;
	games_allcorrect_1hint = 0;
	games_1hint = 0;

	struct StatisticsList list;
	struct StatisticsList *listPointer = &list;
	listPointer->head = NULL;

	unsigned int i, j;
	srand((unsigned) time(NULL));

	////PROGRAM////

	// Commadline: prompt user for matrix size, if not given are below 2, matrix size equals NDEFAULT
	if (argc < 2) {
		N = NDEFAULT;
	} else {
		N = atoi(argv[1]);
		if (N <= 1) {
			N = NDEFAULT;
		}
	}
	printf("Matrix size N = %d \n", N);

	//Dynamically allocate a square, 2-D array of complex numbers
	M = (complex **) malloc(sizeof(complex) * N);
	for (i = 0; i < N; i++)
		M[i] = (complex *) malloc(sizeof(complex) * N);

	//LOOP1: loop until user press "Q|q" to quit
	do {
		badguessescount = 0;
		hintscount = 0;
		goodguess = 0;
		endgame = 0;

		// generate random i, j - indices for the random matrix pointer
		i = rand() % N;
		j = rand() % N;
		//printf("random i= %d j= %d \n", i, j);

		// assign complex values to the matrix
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				M[i][j].real_part = i;
				M[i][j].imag_part = j;
			}
		}
		// LOOP2: loop as appropriate
		do {
			//start the game
			playgame(i, j);

			//translate the user input into variables
			int d = 0;
			int word = 0;
			int character = 0;
			int space_count = 0;
			int wasAnyCharacter = 0;

			while (d < strlen(code) + 1) {
				if (!isspace(code[d])) {
					wasAnyCharacter = 1;
					userinput[word][character] = code[d];
					character++;
					space_count = 0;
				}
				if ((isspace(code[d]) || code[d] == '\0') && wasAnyCharacter
						&& space_count == 0) {
					word++;
					character = 0;
				}
				d++;
			}

			//user input evaluation
			//if there is more than 1 argument passed by the user
			if (strcmp(userinput[1], "\0")) {
				// atoi converts user input into numbers, if input NaN then jguess and iguess are equal zero
				iguess = atoi(userinput);
				jguess = atoi((userinput + 1));

				//good guess
				if (i == iguess & j == jguess) {
					gamescount++; //count number of guessses
					goodGuess(listPointer, gamescount, badguessescount, hintscount, *userinput);
					endgame=1;
				//bad guess
				} else {
					badGuess(&badguessescount);
					badguessescount++;
				}

			}
			//if there is only one argument passed by the user
			else {
				hintsinput(userinput);
			}

			//quits the program after pressing "Q || q"
			quitProgram(listPointer, *userinput, &play, gamescount);
			if (play == 1){break;}

			// resets memory, sets strings in "userinput" array to zero length
			for (int d = 0; d < word; d++) {
				memset(*(userinput + d), '\0', strlen(*(userinput + d)));
			}

		} while (endgame == 0);
	} while (play == 0);
	printf("Good Bye! \n");

	return EXIT_SUCCESS;
}
