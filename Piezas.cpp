#include "Piezas.h"
#include <vector>
using namespace std;

#define BOARD_ROWS 3
#define BOARD_COLUMNS 4

/** CLASS Piezas
 * Class for representing a Piezas vertical board, which is roughly based
 * on the game "Connect Four" where pieces are placed in a column and 
 * fall to the bottom of the column, or on top of other pieces already in
 * that column. For an illustration of the board, see:
 *  https://en.wikipedia.org/wiki/Connect_Four
 *
 * Board coordinates [row,col] should match with:
 * [2,0][2,1][2,2][2,3]
 * [1,0][1,1][1,2][1,3]
 * [0,0][0,1][0,2][0,3]
 * So that a piece dropped in column 2 should take [0,2] and the next one
 * dropped in column 2 should take [1,2].
**/


/**
 * Constructor sets an empty board (default 3 rows, 4 columns) and 
 * specifies it is X's turn first
**/
Piezas::Piezas()
{
	turn = X;
	for (int i = 0; i < BOARD_ROWS; i ++) {
		vector<Piece>* row = new vector<Piece>();
		for (int j = 0; j < BOARD_COLUMNS; j ++) {
			row->push_back(Blank);
		}
		board.push_back(*row);
	}
}

/**
 * Resets each board location to the Blank Piece value, with a board of the
 * same size as previously specified
**/
void Piezas::reset()
{
}

/**
 * Places a piece of the current turn on the board, returns what
 * piece is placed, and toggles which Piece's turn it is. dropPiece does 
 * NOT allow to place a piece in a location where a column is full.
 * In that case, placePiece returns Piece Blank value 
 * Out of bounds coordinates return the Piece Invalid value
 * Trying to drop a piece where it cannot be placed loses the player's turn
**/ 
Piece Piezas::dropPiece(int column)
{
	//Keep track of the piece that is to be placed
	Piece cur = turn;
	
	//Toggle whose turn it is
	if (turn == X)
		turn = O;
	else if (turn == O)
		turn = X;
	
	//Check for out-of-bounds moves
    if (column < 0 || column >= BOARD_COLUMNS) {
		return Invalid;
	}
	
	//Place the piece
	for (int i = 0; i < BOARD_ROWS; i ++) {
		if (board[i][column] == Blank) {
			board[i][column] = cur;
			break;
		}
		//Check for a full column
		if (i == BOARD_ROWS-1) {
			return Blank;
		}
	}
	
    return cur;
}

/**
 * Returns what piece is at the provided coordinates, or Blank if there
 * are no pieces there, or Invalid if the coordinates are out of bounds
**/
Piece Piezas::pieceAt(int row, int column)
{
	if (row < 0 || row >= BOARD_ROWS || column < 0 || column >= BOARD_COLUMNS) {
		return Invalid;
	}
    return board[row][column];
}

/**
 * Returns which Piece has won, if there is a winner, Invalid if the game
 * is not over, or Blank if the board is filled and no one has won ("tie").
 * For a game to be over, all locations on the board must be filled with X's 
 * and O's (i.e. no remaining Blank spaces). The winner is which player has
 * the most adjacent pieces in a single line. Lines can go either vertically
 * or horizontally. If both X's and O's have the same max number of pieces in a
 * line, it is a tie.
**/
Piece Piezas::gameState()
{
	//Ensure the game has actually ended
	for (int i = 0; i < BOARD_ROWS; i ++) {
		for (int j = 0; j < BOARD_COLUMNS; j ++) {
			if (board[i][j] == Blank) {
				return Invalid;
			}
		}
	}
	
	//Store each player's current largest row or column
	int X_score = 0;
	int O_score = 0;
	
    //Check rows
	for (int i = 0; i < BOARD_ROWS; i ++) {
		Piece cur_piece = Blank;
		int cur_score = 0;
		for (int j = 0; j < BOARD_COLUMNS; j ++) {
			//Check if the type of piece has changed
			if (board[i][j] != cur_piece) {
				cur_piece = board[i][j];
				cur_score = 0;
			}
			
			//Increase the count
			cur_score ++;
			
			//Update the scores accordingly
			if (cur_piece == X && cur_score > X_score) {
				X_score = cur_score;
			}
			if (cur_piece == O && cur_score > O_score) {
				O_score = cur_score;
			}
		}
	}
	
	//Return the result
	if (X_score > O_score)
		return X;
	if (O_score > X_score)
		return O;
	return Blank;
}