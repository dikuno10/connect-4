/* ENGGEN131 Project - C Project - 2018 */
/* Connect Four - The Garage */

#include "connect4.h"

/*
 * THIS FILE CONTAINS ALL OF MY OLD BOTS
 * May they rest peacefully in this garage,
 * ...and maybe used for spare parts one day.
 */



// HELPER FUNCTIONS FOR BOTS

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

void GetMoveBot2(int board[MAX_SIZE][MAX_SIZE], int size, int player, char *side, int *move)
{
	/*
	 * DKBOT v4.0
	 * "By building up towers, this bot actually helps with the progress of society."
	 * Attempts every move possible and checks to see if that wins the game, for it or for
	 * the opponent. If it's a winner, it submits that move. Should no such move exist, but
	 * the opponent is on the verge of victory, their parade will be halted. The bot then
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
					PhotocopyBoard(board, boardCopy, size);
					AddMoveToBoard(boardCopy, size, trialSide, trialMove, player, &rowPos, &colPos);

					if (rowPos == -1 || colPos == -1) {
						continue;
					} else {
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
		// I have consciously repeated code here as I want to return immediately upon setting the pointers
		PhotocopyBoard(board, boardCopy, size);
		AddMoveToBoard(boardCopy, size, randSide, randMove, player, &rowPos, &colPos);

		if (rowPos == -1 || colPos == -1) {
			continue;
		} else {
			*side = randSide;
			*move = randMove;
			return;
		}
		
	}

}

void GetMoveBot2(int board[MAX_SIZE][MAX_SIZE], int size, int player, char *side, int *move)
{
	/*
	 * DKBOT v3.0
	 * "I promise it's like a noncompetitive inhibitor. It's just natural selection."
	 * Attempts every move possible and checks to see if that wins the game, for it or for
	 * the opponent. If it's a winner, it submits that move. Should no such move exist, but
	 * the opponent is on the verge of victory, their parade will be halted. Otherwise, it
	 * reverts to random generation.
	 * Also comes with simplified side letter selection logic, and actually working
	 * invalid move checking!
	 */

	int i, j, rowPos, colPos;
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

	// otherwise, revert to randomly generating a valid move
	while (!result) {

		// generate a random move and side
		randMove = rand() % size;
		randSide = sides[rand() % 4];

		// generate a copy of the existing board, perform the generated move on it
		// and check if it's valid - if it is, submit it
		PhotocopyBoard(board, boardCopy, size);
		AddMoveToBoard(boardCopy, size, randSide, randMove, player, &rowPos, &colPos);

		if (rowPos == -1 || colPos == -1) {
			continue;
		} else {
			*side = randSide;
			*move = randMove;
			return;
		}

	}

}

// NOTE: ALL BOTS BELOW THIS LINE HAVE BROKEN INVALID MOVE DETECTION IN THE RANDOM MOVE SECTION. THAT PART SHOULD NOT BE USED

void GetMoveBot2(int board[MAX_SIZE][MAX_SIZE], int size, int player, char *side, int *move)
{
	/*
	 * DKBOT v2.1
	 * "Slow and steady wins the race!"
	 * Attempts every move possible and checks to see if that wins the game. If it does,
	 * it submits that move. Otherwise, it reverts to random generation.
	 * v2.1 - Now with bug fixes so it actually works when the bot is Player 2!
	 */

	int i, j, rowPos, colPos;
	char trialSide;
	int trialMove = 0;
	int result = 0;
	int boardCopy[MAX_SIZE][MAX_SIZE];

	// generate every single possible move on the board
	for (i = 0; i < 4; i++) {
		if (i == 0) {
			trialSide = 'N';
		} else if (i == 1) {
			trialSide = 'W';
		} else if (i == 2) {
			trialSide = 'S';
		} else {
			trialSide = 'E';
		}

		for (j = 0; j < size; j++) {
			trialMove = j;

			// generate a copy of the existing board, perform the generated move on it
			// and check if this would end the game
			PhotocopyBoard(board, boardCopy, size);
			AddMoveToBoard(boardCopy, size, trialSide, trialMove, player, &rowPos, &colPos);
			result = CheckGameOver(boardCopy, size, player, rowPos, colPos);

			// if it's a game ending move, submit the move immediately
			if (result >= 1) {
				*side = trialSide;
				*move = trialMove;
				return;
			} else {
				continue;
			}
		}

	}

	// otherwise, revert to randomly generating a valid move
	int randMove;
	int randSide;

	while (!result) {

		// generate a random number between 0 and size-1 for *move
		randMove = rand() % size;
		// generate a random number between 0 and 3 for *side
		randSide = rand() % 4;

		// if the first space in the desired move isn't occupied, submit the move
		// otherwise, try again
		if (randSide == 0 && board[0][randMove] == 0) {
			*side = 'N';
			*move = randMove;
			return;
		} else if (randSide == 1 && board[randMove][0] == 0) {
			*side = 'W';
			*move = randMove;
			return;
		} else if (randSide == 2 && board[size-1][randMove] == 0) {
			*side = 'S';
			*move = randMove;
			return;
		} else if (randSide == 3 && board[randMove][size-1 == 0]){
			*side = 'E';
			*move = randMove;
			return;
		} else {
			continue;
		}
	}

}

void GetMoveBot2(int board[MAX_SIZE][MAX_SIZE], int size, int player, char *side, int *move)
{
	/*
	 * DKBOT v2.0
	 * "Slow and steady wins the race!"
	 * Attempts every move possible and checks to see if that wins the game. If it does,
	 * it submits that move. Otherwise, it reverts to random generation.
	 */

	int i, j, rowPos, colPos;
	char trialSide;
	int trialMove = 0;
	int result = 0;
	int boardCopy[MAX_SIZE][MAX_SIZE] = {-1};

	// generate every single possible move on the board
	for (i = 0; i < 4; i++) {
		if (i == 0) {
			trialSide = 'N';
		} else if (i == 1) {
			trialSide = 'W';
		} else if (i == 2) {
			trialSide = 'S';
		} else {
			trialSide = 'E';
		}

		for (j = 0; j < size; j++) {
			trialMove = j;

			// generate a copy of the existing board, perform the generated move on it
			// and check if this would end the game
			PhotocopyBoard(board, boardCopy, size);
			AddMoveToBoard(boardCopy, size, trialSide, trialMove, player, &rowPos, &colPos);
			result = CheckGameOver(boardCopy, size, player, rowPos, colPos);

			// if it's a game ending move, stop generating moves
			if (result == 1) {
				break;
			} else {
				continue;
			}
		}

		if (result == 1) {
			break;
		}
	}

	// if a game ending move was found, submit the move
	if (result == 1) {
		*side = trialSide;
		*move = trialMove;
		return;
	}

	// otherwise, revert to randomly generating a valid move
	int randMove;
	int randSide;

	while (!result) {

		// generate a random number between 0 and size-1 for *move
		randMove = rand() % size;
		// generate a random number between 0 and 3 for *side
		randSide = rand() % 4;

		// if the first space in the desired move isn't occupied, submit the move
		// otherwise, try again
		if (randSide == 0 && board[0][randMove] == 0) {
			*side = 'N';
			*move = randMove;
			return;
		} else if (randSide == 1 && board[randMove][0] == 0) {
			*side = 'W';
			*move = randMove;
			return;
		} else if (randSide == 2 && board[size-1][randMove] == 0) {
			*side = 'S';
			*move = randMove;
			return;
		} else if (randSide == 3 && board[randMove][size-1 == 0]){
			*side = 'E';
			*move = randMove;
			return;
		} else {
			continue;
		}
	}

}

void GetMoveBot2(int board[MAX_SIZE][MAX_SIZE], int size, int player, char *side, int *move)
{
	/*
	 * DKBOT v1.0
	 * "Slow, dumb, and as random as a spork!"
	 * Randomly generates moves until a valid one is made.
	 */

	int validMove = 0;
	int randMove;
	int randSide;

	// int player is unused in this bot as it is beyond the capabilities of its simple mind.
	// ...this is to shut up the compiler
	player = player;

	while (!validMove) {

		// generate a random number between 0 and size-1 for *move
		randMove = rand() % size;
		// generate a random number between 0 and 3 for *side
		randSide = rand() % 4;

		// if the first space in the desired move isn't occupied, set the pointers and end the function
		// otherwise, try again
		if (randSide == 0 && board[0][randMove] == 0) {
			*side = 'N';
			*move = randMove;
			return;
		} else if (randSide == 1 && board[randMove][0] == 0) {
			*side = 'W';
			*move = randMove;
			return;
		} else if (randSide == 2 && board[size-1][randMove] == 0) {
			*side = 'S';
			*move = randMove;
			return;
		} else if (randSide == 3 && board[randMove][size-1 == 0]){
			*side = 'E';
			*move = randMove;
			return;
		} else {
			continue;
		}
	}
}