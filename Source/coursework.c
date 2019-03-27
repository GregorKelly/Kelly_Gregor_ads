#include <stdio.h>
//initialise the locations of the board
char board[3][3] = {
	//initializers
	{'7','8','9'} ,
	{'4','5','6'} ,
	{'1','2','3'}
};

//prints the game board
void printBoard() {
	printf("      |      |      \n");
	printf("   %c  |  %c   |  %c   \n", board[0][0], board[0][1], board[0][2]);
	printf("______|______|______\n");
	printf("      |      |      \n");
	printf("   %c  |  %c   |  %c   \n", board[1][0], board[1][1], board[1][2]);
	printf("______|______|______\n");
	printf("      |      |      \n");
	printf("   %c  |  %c   |  %c   \n", board[2][0], board[2][1], board[2][2]);
	printf("      |      |      \n");
}

//creates pointers to indicate which boardspace is selected
int indexToCoord(int index, int *row, int *col) {
	if (index < 1 || index > 9) {
		return 1; // 1 = wrong index
	}
	if (index < 4) {
		*row = 2;
		*col = index - 1;
	}
	else if (index < 7) {
		*row = 1;
		*col = index - 4;
	}
	else if (index < 10) {
		*row = 0;
		*col = index - 7;
	}
	return 0;
}

void playerTurn(char playerPointer) {
	int input = -1;
	int row;
	int col;
	printf("\nPlayer %c, Enter a Number: ", playerPointer);
	//check if  input is within the limits of the board
	while (input < 1 || input > 9) {
		input = getchar() - '0';
		//checks if there is an error
		if (input < 1) {
			continue;
		}
		printf("\nInput = %d\n", input);
		//checks for invalid input
		if (indexToCoord(input, &row, &col)) {
			input = -1;
			printf("Location invalid, please select again: ");
		}
		//checks if space has already been typed in
		if (checkBox(row, col)) {
			input = -1;
			printf("Space already occupied, please select again: ");
		}
	}
	//set the game to the pointer
	board[row][col] = playerPointer;
}

int checkBox(int row, int col) {
	int t = 0;
	//check for player piece
	if (board[row][col] == 'X' || board[row][col] == 'O') {
		t = 1;
	}
	return t;
}

int winConditions[8][3] = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {1, 4, 7}, {2, 5, 8}, {3, 6, 9}, {1, 5, 9}, {3, 5, 7} };

int checkWin(char playerPointer) {
	int row;
	int col;
	int counter;

	for (int i = 0; i < 8; i++) {
		counter = 0;
		for (int j = 0; j < 3; j++) {
			//check for incorrect index
			if (indexToCoord(winConditions[i][j], &row, &col) == 1) {
				printf("No such index exists\n"); 
			}
			else {
				//check win conditions
				if (board[row][col] == playerPointer) {
					counter = counter + 1;
					if (counter == 3) {
						return 1; //1 = win
					}
				}
				else {
					break;
				}
			}
		}
	}
	return 0;
}

int main(int argc, char **argv) {
	printf("WELCOME TO TIC TAC TOE \n");
	printf("To begin playing use the number pad as your TTT board\n");
	printf("(e.g pressing no.7 will place the respectful players X or O in the top left corner of the board)\n\n");
	printf("Player X is to start...\n\n\n");
	printBoard();

	char playerPointer = 'O';

	for (int moves = 0; moves < 9; moves++) {
		//change player
		if (playerPointer == 'X') {
			playerPointer = 'O';
		}
		else {
			playerPointer = 'X';
		}
		//play turn
		playerTurn(playerPointer);
		printBoard();
		if (checkWin(playerPointer) == 1) {
			printf("Player %c WINS!", playerPointer);
			//break;
			return 0;
		}
	}
	printf("CATSGAME");
	
	return 0;
}
