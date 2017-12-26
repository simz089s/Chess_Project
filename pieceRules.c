#include "chess.h"
#ifndef BOOLS
    #define BOOLS
    #define TRUE 1
    #define FALSE 0
#endif

// To check if code compiles we add this (normally would use extern/modular programming so this will be removed):
static const char B = 'B';
static const char W = 'W';
Cell board[8][8];
void main() {
}

/* TO DO:
    0.5: Update failure states for all 'move' functions
    1. Incoperate 'strange' rules:
        https://en.wikipedia.org/wiki/En_passant
        https://en.wikipedia.org/wiki/Castling
    2. Add captured pieces to their respective arrays
    3. Whenever a move is made, record it in a text-file (with game ID?)
    4. Update return codes to explain to user better why their move wasn't valid (?)
*/


// Arrays to record the number of captured X pieces to be used later; max is 17 as King can't be captured
Cell capturedBlack[17];
Cell capturedWhite[17];

// Function to turn given cell, board[x][y], to a 'blank' cell
void blank(int x, int y) {
    board[x][y].id = ' ';
    board[x][y].color = ' ';
}

// Function to check if (x1, y1) can capture a piece at (x2, y2)
int canCapture(int x1, int y1, int x2, int y2) { 
    if ( ( board[x1][y1].color == B && board[x2][y2].color == W ) || ( board[x1][y1].color == W && board[x2][y2].color == B ) ) return TRUE;
    else return FALSE;
}

/*  Function to be called whenever a piece moves successfully to it's destination;
    will replace the dest. cell with info @ source cell and 'wipe' source cell */
void moveSuccess(int x1, int y1, int x2, int y2) {
    board[x2][y2] = board[x1][y1];
    blank(x1, y1); // Set board[x1][y2] to a 'blank cell'
}

// Returns -1 if for ANY reason move is invalid
int movePawn(int x1, int y1, int x2, int y2) {
    // Pawns can only ever move up/down one row so these act as global checks:
    if ( ( board[x1][y1].color == W && y2 != (y1 + 1) ) || ( board[x1][y1].color == B && y2 != (y1 - 1) ) ) return -1;
    // Without capture pawn can only move (progressively) within it's rank:
    else if ( x1 == x2 && board[x2][y2].id == ' ') {
        moveSuccess(x1,y1, x2, y2);
    }
    // Check if capture is possible and capture if so:
    else if ( (x2 == (x1 + 1) || x2 == (x1 - 1) ) ) {
        if ( canCapture(x1, y1, x2, y2) == TRUE ) {
            moveSuccess(x1, y1, x2, y2);
        }
        else return -1;
    }
    else return -1;

    // No errors were found while the move was processed
    return 0;
}


// TO DO: add the rest of the pieces' move functions


// Format: (x1, y1) is the current position while (x2, y2) is the requested destination; nb: x <--> columns/letters, y <--> rows/numbers
int movePiece(int x1, int y1, int x2, int y2) {
    // Check if dest. is invalid (due to the board's dimensions):
    if (y2 >= 8 || x2 >= 8 || y2 < 0 || x2 < 0) return -1;
    
    // UPDATE feedback from calling movePawn()
    if( board[x1][y1].id == 'P') {
        // Success:
        if( movePawn(x1, y1, x2, y2) == 0 ) return 0;
        // Failure:
        else return -1;
    }

    return 0;
}


