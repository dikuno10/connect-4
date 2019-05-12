/* ENGGEN131 Project - C Project - 2018 */
/* Connect Four */

#include "connect4.h"

/*
*** NAME: Di Kun Ong, ID: 534478094 ***
This is the file that you will be submitting for marking
Complete the definitions of the functions in this file
DO NOT REMOVE ANY FUNCTION DEFINITIONS - they all must be present when you submit this file
*/

int SecondPlacePrize(int prize1, int prize2, int prize3)
{
	// this tests each set of 6 possible arrangements of prize 1, 2, and 3
	// there are 2 possibilities for each value being in the middle
	if ((prize2 >= prize1 && prize1 >= prize3) || (prize3 >= prize1 && prize1 >= prize2)) {
		return prize1;
	} else if ((prize1 >= prize2 && prize2 >= prize3) || (prize3 >= prize2 && prize2 >= prize1)) {
		return prize2;
	} else if ((prize1 >= prize3 && prize3 >= prize2) || (prize2 >= prize3 && prize3 >= prize1)) {
		return prize3;
	} else {
		return 0;
	}
}

int FourInARow(int values[], int length)
{
	int i, j, identical;

	// we test a value and the 3 values following it, so don't need to test starting at the last 3
	for (i = 0; i < length - 3; i++) {
		identical = 0;

		// for each of the 3 numbers following i
		for (j = 1; j < 4; j++) {
			// if the first value and the current value are equal, iterate a count
			if (values[i] == values[i + j]) {
				identical++;
			}
		}

		// if all 4 values are equal, we wil have counted up 3 times (once for each pairing)
		if (identical == 3) {
			return i;
		}
	}

	// if the loop finishes without finding 4 identical values
	return -1;
}

int BinaryToDecimal(int binary)
{
	int binaryValues[100] = {0};
	int numValues = 0;
	int decimal = 0;
	int multiplier = 1;
	int i;

	// store the binary values from LSB --> MSB in an array
	// this is done by storing the remainder of binary / 10
	while (binary > 0) {
		binaryValues[numValues] = binary % 10;
		numValues++;
		binary /= 10;
	}

	// multiply each value in the array by 2^n and sum it into the decimal value
	// using a multiplier that starts at 1 (2^0) and increments *2 on each loop
	for (i = 0; i < numValues; i++) {
		decimal += binaryValues[i] * multiplier;
		multiplier *= 2;
	}
	
	return decimal;
}

// HELPER FUNCTION FOR MEDIANABILITY
// BubbleSort sorts an array in ascending order, from smallest value to largest value.
void BubbleSort(double abilities[], int length)
{
	int i, j;
	double temp;

	// Sort - bubble once for every value in the array
	for (i = 0; i < length; i++) {
		// Bubble - compare each pair of values in the array
		for (j = 0; j < length - 1; j++) {

			// Swap - take two values, if needed swap them so the higher one comes after the lower one
			if (abilities[j] > abilities[j+1]) {

				temp = abilities[j];
				abilities[j] = abilities[j+1];
				abilities[j+1] = temp;

			}

		}
	}
}

double MedianAbility(double abilities[], int length)
{
	// apply a bubble sort to the abilities array to get it in ascending order
	BubbleSort(abilities, length);

	// if our array has an even number of values, return the average of the 2 middle scores
	// otherwise it has an odd number, so return the 1 middle score
	if (length % 2 == 0) {
		return (abilities[length / 2 - 1] + abilities[length / 2])/2;
	} else {
		return abilities[length / 2];
	}

}

// HELPER FUNCTION FOR REMOVESPACES
// RemoveCharacter removes a single character from a given array at the location index 'pos',
// and shifts all of the rightmost characters to the left to fill the gap.
void RemoveCharacter(char *name, int pos)
{
	int i = 0;
	int trigger = 0;

	while (name[i] != '\0') {

		// trip the trigger once we encounter the position of the character for removal
		if (i == pos) {
			trigger = 1;
		}

		// once triggered, shift the rightmost value to the left by 1
		if (trigger == 1) {
			name[i] = name[i + 1];
		}

		i++;
	}
}

void RemoveSpaces(char *name)
{
	int i = 0;
	
	// step through each letter in the given array
	while (name[i] != '\0') {

		// if the current letter and previous letter are both spaces, delete the current letter
		// don't iterate i as we want to check the new current letter isn't also a space
		if (name[i] == ' ' && name[i-1] == ' ') {
			RemoveCharacter(name, i);
			continue;
		}

		i++;
	}
}

void InitialiseBoard(int board[MAX_SIZE][MAX_SIZE], int size)
{
	int i, j;

	// calculate the indices of the "centre" values in our board
	int end = size / 2;
	int start = end - 1;

	// set every value in the board to 0, up to size
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			board[i][j] = 0;
		}
	}

	// if the board is an even size, it has 4 centrepieces
	// else it's odd, and has 1 centrepieces
	if (size % 2 == 0) {

		for (i = start; i <= end; i++) {
			for (j = start; j <= end; j++) {
				board[i][j] = 3;
			}
		}

	} else {
		board[end][end] = 3;
	}
	
}

void AddMoveToBoard(int board[MAX_SIZE][MAX_SIZE], int size, char side, int move, int player, int *lastRow, int *lastCol)
{
	int i, j;

	// set our starting position based on the player's side and move
	if (side == 'N') {
		i = 0;
		j = move;
	} else if (side == 'S') {
		i = size - 1;
		j = move;
	} else if (side == 'W') {
		i = move;
		j = 0;
	} else {
		i = move;
		j = size - 1;
	}

	// check if the move is valid
	// if the first square isn't a 0, the player has wasted their move
	if (board[i][j] != 0) {
		*lastRow = -1;
		*lastCol = -1;
		return;
	}

	// check how far the token can move across the board
	// while the current position is 0, check if the next position is 0
	// AND if token isn't at edge of board
	// if it is, move along
	// if it isn't, set the final position of the token
	while (board[i][j] == 0) {
		if (side == 'N' && board[i+1][j] == 0 && i != size-1) {
			i++;
		} else if (side == 'S' && board[i-1][j] == 0 && i != 0) {
			i--;
		} else if (side == 'W' && board[i][j+1] == 0 && j != size-1) {
			j++;
		} else if (side == 'E' && board[i][j-1] == 0 && j != 0) {
			j--;
		} else {
			*lastRow = i;
			*lastCol = j;
			board[i][j] = player;
		}
	}
	
}


// HELPER FUNCTION FOR CHECKGAMEOVER
// CheckNtoSFour checks a column of board tokens from (0, col) to (size-1, col),
// while counting consecutive tokens that match the player's.
int CheckNtoSFour(int board[MAX_SIZE][MAX_SIZE], int size, int player, int col)
{
	int i;
	int count = 0;

	// step through each value in the column from top to bottom
	// if the player's token is found, increment count
	// if not, the streak is broken and the count is reset - unless the count is 4+
	// in which case it's made it
	for (i = 0; i < size; i++) {
		if (board[i][col] == player) {
			count++;
		} else if (count < 4) {
			count = 0;
		}
	}

	// if counted four in a row or more were counted, return true
	if (count >= 4) {
		return 1;
	} else {
		return 0;
	}
}

// HELPER FUNCTION FOR CHECKGAMEOVER
// CheckWtoEFour checks a row of board tokens from (row, 0) to (row, size-1),
// while counting consecutive tokens that match the player's.
int CheckWtoEFour(int board[MAX_SIZE][MAX_SIZE], int size, int player, int row)
{
	int j;
	int count = 0;

	// step through each value in the row from left to right
	// if the player's token is found, increment count
	// if not, the streak is broken and the count is reset - unless the count is 4+
	// in which case it's made it
	for (j = 0; j < size; j++) {
		if (board[row][j] == player) {
			count++;
		} else if (count < 4) {
			count = 0;
		}
	}

	// if four in a row or more were counted, return true
	if (count >= 4) {
		return 1;
	} else {
		return 0;
	}
}

// HELPER FUNCTION FOR CHECKGAMEOVER
// CheckNWtoSEFour checks a diagonal of tokens from the northwest to southeast,
// while counting consecutive tokens that match the player's.
int CheckNWtoSEFour(int board[MAX_SIZE][MAX_SIZE], int size, int player, int row, int col)
{
	int count = 0;

	// find our starting position by going diagonally towards the northwest corner
	// until a wall is encountered (a value = 0)
	while (row > 0 && col > 0) {
		row--;
		col--;
	}

	// step through each value diagonally until the southeast corner is reached
	// if the player's token is found, increment count
	// if not, the streak is broken and the count is reset - unless the count is 4+
	// in which case it's made it
	while (row < size && col < size) {
		if (board[row][col] == player) {
			count++;
		} else if (count < 4) {
			count = 0;
		}

		row++;
		col++;
	}

	// if four in a row or more were counted, return true
	if (count >= 4) {
		return 1;
	} else {
		return 0;
	}
}

// HELPER FUNCTION FOR CHECKGAMEOVER
// CheckSWtoNEFour checks a diagonal of tokens from the southwest to northeast,
// while counting consecutive tokens that match the player's.
int CheckSWtoNEFour(int board[MAX_SIZE][MAX_SIZE], int size, int player, int row, int col)
{
	int count = 0;

	// find our starting position by going diagonally towards the southwest corner
	// until a wall is encountered (a value = 0)
	while (row < size - 1 && col > 0) {
		row++;
		col--;
	}

	// step through each value diagonally until the northeast corner is reached
	// if the player's token is found, increment count
	// if not, the streak is broken and the count is reset
	// unless the count is 4+, in which case it's made it
	while (row >= 0 && col < size) {
		if (board[row][col] == player) {
			count++;
		} else if (count < 4) {
			count = 0;
		}

		row--;
		col++;
	}

	// if four in a row or more were counted, return true
	if (count >= 4) {
		return 1;
	} else {
		return 0;
	}
}

int CheckGameOver(int board[MAX_SIZE][MAX_SIZE], int size, int player, int row, int col)
{
	int i, j;
	int countOfFreeSpace = 0;
	int fourInARow = 0;

	// check if the EDGES OF THE board ARE completely full of tokens
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			if ((i == 0 || j == 0 || i == size-1 || j == size-1) && board[i][j] == 0) {
				countOfFreeSpace++;
			}
		}
	}

	// check each of the four directions surrounding the last placed token for a four-in-a-row
	fourInARow += CheckNtoSFour(board, size, player, col);
	fourInARow += CheckWtoEFour(board, size, player, row);
	fourInARow += CheckNWtoSEFour(board, size, player, row, col);
	fourInARow += CheckSWtoNEFour(board, size, player, row, col);

	// if the board has no free BORDERS left, game over
	// if the last move was invalid, keep going
	// if a four-in-arow was detected, game over
	// otherwise, keep going
	if (countOfFreeSpace == 0) {
		return player;
	} else if (row == -1 && col == -1) {
		return 0;
	} else if (fourInARow > 0) {
		return player;
	} else {
		return 0;
	}
	
}

// HELPER FUNCTION FOR GETDISPLAYBOARDSTRING
// BorderString generates the top or bottom borders of the Connect Four board, depending on
// the char side - "N" or "S", and appends it to boardString.
void BorderString(int size, char *boardString, char *side, char *indexNum)
{
	int i;

	// leftmost corner piece
	strcat(boardString, "--");

	// if on the northern side, letters are printed before numbers
	// if on the southern side, numbers are printed before letters
	if (strcmp(side, "N") == 0) {

		// append "N" border labels
		for (i = 0; i < size; i++) {
			strcat(boardString, side);
		}

		// corner pieces
		strcat(boardString, "--\n--");

		// append index numbers
		for (i = 0; i < size; i++) {
			sprintf(indexNum,"%d",i);
			strcat(boardString, indexNum);
		}
	} else {

		// append index numbers
		for (i = 0; i < size; i++) {
			sprintf(indexNum,"%d",i);
			strcat(boardString, indexNum);
		}
		// corner pieces
		strcat(boardString, "--\n--");

		// append "S" border labels
		for (i = 0; i < size; i++) {
			strcat(boardString, side);
		}
	}

	// rightmost corner piece
	strcat(boardString, "--\n");
}

void GetDisplayBoardString(int board[MAX_SIZE][MAX_SIZE], int size, char *boardString)
{
	int i, j;

	// indexNum is used in the conversion of index numbers from int to char
	char indexNum[2];

	// set the null character in boardString where strcat() will begin appending
	boardString[0] = '\0';

	// append the northern border
	BorderString(size, boardString, "N", indexNum);

	for (i = 0; i < size; i++) {

		// at the start of each row, append the western border
		strcat(boardString, "W");
		sprintf(indexNum,"%d",i);
		strcat(boardString, indexNum);

		// in the actual board area, append X, O, #, or . depending on the board
		for (j = 0; j < size; j++) {
			if (board[i][j] == 1) {
				strcat(boardString, "X");
			} else if (board[i][j] == 2) {
				strcat(boardString, "O");
			} else if (board[i][j] == 3) {
				strcat(boardString,"#");
			} else {
				strcat(boardString,".");
			}
		}

		// at the end of each row, append the eastern border
		strcat(boardString, indexNum);
		strcat(boardString, "E\n");
	}

	// append the southern border
	BorderString(size, boardString, "S", indexNum);

	// append null character to ensure string termination
	boardString[strlen(boardString)] = '\0';
}

// HELPER FUNCTION FOR GETMOVEBOT1
// PhotocopyBoard takes an array of a given size, and copies each value into
// an identical position in another array, creating a perfect copy.
void PhotocopyBoard(int board[MAX_SIZE][MAX_SIZE], int boardCopy[MAX_SIZE][MAX_SIZE], int size)
{
	int i, j;

	// photocopy the original board #RIPAcademicIntegrity
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			boardCopy[i][j] = board[i][j];
		}
	}
}

// HELPER FUNCTION FOR GETMOVEBOT1
// CheckValidMove takes the Connect Four board, makes a copy of it, and performs
// a specified move on this board to see if it is valid, returning this result.
int CheckValidMove(int board[MAX_SIZE][MAX_SIZE], int boardCopy[MAX_SIZE][MAX_SIZE], int size, char side, int move, int player)
{
	int rowPos, colPos;
	
	PhotocopyBoard(board, boardCopy, size);
	AddMoveToBoard(boardCopy, size, side, move, player, &rowPos, &colPos);

	if (rowPos == -1 || colPos == -1) {
		return 0;
	} else {
		return 1;
	}
}

void GetMoveBot1(int board[MAX_SIZE][MAX_SIZE], int size, int player, char *side, int *move)
{
	/*
	 * DKBOT v5.0.
	 * "It's not playing dirty it there's no rules against it."
	 * Attempts every move possible and checks to see if that wins the game, for it or for
	 * the opponent. If it's a winner, it submits that move. Should no such move exist, but
	 * the opponent is on the verge of victory, their parade will be halted.
	 * The bot then plays dirty and attempts to build a sequence of 3 tokens by the centrepiece.
	 * If it pulls this off successfully, victory is assured. But if it gets interrupted, the bot
	 * goes through each occurrence of its previously placed tokens and tries to place one
	 * consecutive to it. Should this fail, it reverts to random generation.
	 */

	int i, j, k, rowPos, colPos;
	char trialSide;
	int trialMove = 0;
	int result = 0;

	int enemyResult = 0;
	char enemySide = 'N';
	int enemyMove = -1;

	int randMove;
	char randSide;

	int boardCopy[MAX_SIZE][MAX_SIZE];
	char sides[4] = {'N','W','S','E'};

	// generate every single possible move on the board
	for (i = 0; i < 4; i++) {

		// this converts the for loop iterator into a side N/W/S/E
		trialSide = sides[i];

		for (j = 0; j < size; j++) {
			trialMove = j;

			// generate a copy of the existing board, perform the generated move on it
			// and check if this would end the game
			PhotocopyBoard(board, boardCopy, size);
			AddMoveToBoard(boardCopy, size, trialSide, trialMove, player, &rowPos, &colPos);
			result = CheckGameOver(boardCopy, size, player, rowPos, colPos);

			// generate a copy of the existing board, perform the generated move on it as the enemy
			// and check if this would win the game for them
			PhotocopyBoard(board, boardCopy, size);
			AddMoveToBoard(boardCopy, size, trialSide, trialMove, (3-player), &rowPos, &colPos);
			enemyResult = CheckGameOver(boardCopy, size, (3-player), rowPos, colPos);

			// if it's a game ending move, submit the move immediately
			// if it's a winning move for the enemy, save it for later
			if (result >= 1) {
				*side = trialSide;
				*move = trialMove;
				return;
			} else if (enemyResult >= 1) {
				enemySide = trialSide;
				enemyMove = trialMove;
				break;
			} else {
				continue;
			}
		}

	}

	// if an enemy 3-in-a-row was detected, submit a move that will block it
	if (enemyMove != -1) {
		*side = enemySide;
		*move = enemyMove;
		return;
	}

	// The following block code is poorly written and was written last-minute for the purposes of a bot competition.
	// It placed 12th in a pool of over 20 bots, which is a distinctly average result.
	// Was it worth it? Maybe.

	// attempt to build a sequence of 3-in-a-row using a pre-programmed check
	// check if the space by the centrepiece(s) is full and placing a token there would be valid - if so, make the move
	// if this space is full, place a token on one side, or if that's also full, the other
	// if the northern side is full, try the western, southern, and eastern sides
	// once these are in the place, the victory logic will take over
	// the move directions are predetermined but this will adapt to a board of any size

	int inARow1 = (size-1)/2 - 1;
	int inARow2 = (size-1)/2;
	int inARow3 = (size-1)/2 + 1;

	// NORTH SIDE
	if (board[inARow1][inARow2] == 0 && CheckValidMove(board, boardCopy, size, 'N', inARow2, player) == 1) {
		*side = 'N';
		*move = inARow2;
		return;
	} else if (board[inARow1][inARow3] == 0 && CheckValidMove(board, boardCopy, size, 'E', inARow1, player) == 1) {
		*side = 'E';
		*move = inARow1;
		return;
	} else if (board[inARow1][inARow1] == 0 && CheckValidMove(board, boardCopy, size, 'W', inARow1, player) == 1) {
		*side = 'W';
		*move = inARow1;
		return;
	}

	// WEST SIDE
	if (board[inARow2][inARow1] == 0 && CheckValidMove(board, boardCopy, size, 'W', inARow2, player) == 1) {
		*side = 'W';
		*move = inARow2;
		return;
	} else if (board[inARow1][inARow1] == 0 && CheckValidMove(board, boardCopy, size, 'N', inARow1, player) == 1) {
		*side = 'N';
		*move = inARow1;
		return;
	} else if (board[inARow3][inARow1] == 0 && CheckValidMove(board, boardCopy, size, 'S', inARow1, player) == 1) {
		*side = 'S';
		*move = inARow1;
		return;
	}

	// SOUTH SIDE
	if (board[inARow3][inARow2] == 0 && CheckValidMove(board, boardCopy, size, 'S', inARow2, player) == 1) {
		*side = 'S';
		*move = inARow2;
		return;
	} else if (board[inARow3][inARow3] == 0 && CheckValidMove(board, boardCopy, size, 'E', inARow3, player) == 1) {
		*side = 'E';
		*move = inARow3;
		return;
	} else if (board[inARow3][inARow1] == 0 && CheckValidMove(board, boardCopy, size, 'W', inARow3, player) == 1) {
		*side = 'W';
		*move = inARow3;
		return;
	}

	// EAST SIDE
	if (board[inARow2][inARow3] == 0 && CheckValidMove(board, boardCopy, size, 'E', inARow2, player) == 1) {
		*side = 'E';
		*move = inARow2;
		return;
	} else if (board[inARow1][inARow3] == 0 && CheckValidMove(board, boardCopy, size, 'N', inARow3, player) == 1) {
		*side = 'N';
		*move = inARow3;
		return;
	} else if (board[inARow3][inARow3] == 0 && CheckValidMove(board, boardCopy, size, 'S', inARow3, player) == 1) {
		*side = 'S';
		*move = inARow3;
		return;
	}

	// The ugly code ends here.

	// go through the board until a token that was previously played by the bot is found
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			if (board[i][j] == player) {

				// try each of the four sides of the board, in order of N, W, S, E
				for (k = 0; k < 4; k++) {
					trialSide = sides[k];

					// if k is even, it's N/S and the column should be used
					// otherwise, it's W/E and the row should be used
					if (k % 2 == 0) {
						trialMove = j;						
					} else {
						trialMove = i;
					}

					// generate a copy of the existing board, perform the generated move on it
					// and check if it's valid - if it is, submit it
					if (CheckValidMove(board, boardCopy, size, trialSide, trialMove, player) == 1) {
						*side = trialSide;
						*move = trialMove;
						return;
					}

				}
			} 
		}
	}

	// otherwise, revert to randomly generating a valid move
	while (!result) {

		// generate a random move and side
		randMove = rand() % size;
		randSide = sides[rand() % 4];

		// generate a copy of the existing board, perform the generated move on it
		// and check if it's valid - if it is, submit it
		if (CheckValidMove(board, boardCopy, size, randSide, randMove, player) == 1) {
			*side = randSide;
			*move = randMove;
			return;
		}
		
	}

}

void GetMoveBot2(int board[MAX_SIZE][MAX_SIZE], int size, int player, char *side, int *move)
{
	/*
	 * DKBOT v4.1
	 * "By building up towers, this bot actually helps with the progress of society."
	 * Attempts every move possible and checks to see if that wins the game, for it or for
	 * the opponent. If it's a winner, it submits that move. Should no such move exist, but
	 * the opponent is on the verge of victory, their parade will be halted. The bot then
	 * goes through each occurrence of its previously placed tokens and tries to place one
	 * consecutive to it. Should this fail, it reverts to random generation.
	 * v4.1 - uses a helper function to test moves to reduce code repetition.
	 */

	int i, j, k, rowPos, colPos;
	char trialSide;
	int trialMove = 0;
	int result = 0;

	int enemyResult = 0;
	char enemySide = 'N';
	int enemyMove = -1;

	int randMove;
	char randSide;

	int boardCopy[MAX_SIZE][MAX_SIZE];
	char sides[4] = {'N','W','S','E'};

	// generate every single possible move on the board
	for (i = 0; i < 4; i++) {

		// this converts the for loop iterator into a side N/W/S/E
		trialSide = sides[i];

		for (j = 0; j < size; j++) {
			trialMove = j;

			// generate a copy of the existing board, perform the generated move on it
			// and check if this would end the game
			PhotocopyBoard(board, boardCopy, size);
			AddMoveToBoard(boardCopy, size, trialSide, trialMove, player, &rowPos, &colPos);
			result = CheckGameOver(boardCopy, size, player, rowPos, colPos);

			// generate a copy of the existing board, perform the generated move on it as the enemy
			// and check if this would win the game for them
			PhotocopyBoard(board, boardCopy, size);
			AddMoveToBoard(boardCopy, size, trialSide, trialMove, (3-player), &rowPos, &colPos);
			enemyResult = CheckGameOver(boardCopy, size, (3-player), rowPos, colPos);

			// if it's a game ending move, submit the move immediately
			// if it's a winning move for the enemy, save it for later
			if (result >= 1) {
				*side = trialSide;
				*move = trialMove;
				return;
			} else if (enemyResult >= 1) {
				enemySide = trialSide;
				enemyMove = trialMove;
			} else {
				continue;
			}
		}

	}

	// if an enemy 3-in-a-row was detected, submit a move that will block it
	if (enemyMove != -1) {
		*side = enemySide;
		*move = enemyMove;
		return;
	}

	// go through the board until a token that was previously played by the bot is found
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			if (board[i][j] == player) {

				// try each of the four sides of the board, in order of N, W, S, E
				for (k = 0; k < 4; k++) {
					trialSide = sides[k];

					// if k is even, it's N/S and the column should be used
					// otherwise, it's W/E and the row should be used
					if (k % 2 == 0) {
						trialMove = j;						
					} else {
						trialMove = i;
					}

					// generate a copy of the existing board, perform the generated move on it
					// and check if it's valid - if it is, submit it
					if (CheckValidMove(board, boardCopy, size, trialSide, trialMove, player) == 1) {
						*side = trialSide;
						*move = trialMove;
						return;
					}

				}
			}
		}
	}

	// otherwise, revert to randomly generating a valid move
	while (!result) {

		// generate a random move and side
		randMove = rand() % size;
		randSide = sides[rand() % 4];

		// generate a copy of the existing board, perform the generated move on it
		// and check if it's valid - if it is, submit it
		if (CheckValidMove(board, boardCopy, size, randSide, randMove, player) == 1) {
			*side = randSide;
			*move = randMove;
			return;
		}
		
	}

}

