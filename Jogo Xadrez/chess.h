#ifndef CHESS_H
#define CHESS_H

#define BOARD_SIZE 8

typedef enum { EMPTY, PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING } PieceType;
typedef enum { NONE, WHITE, BLACK } Color;

typedef struct {
    PieceType type;
    Color color;
} Piece;

void initializeBoard(Piece board[BOARD_SIZE][BOARD_SIZE]);
void printBoard(Piece board[BOARD_SIZE][BOARD_SIZE]);
int movePiece(Piece board[BOARD_SIZE][BOARD_SIZE], int sx, int sy, int dx, int dy, Color currentTurn);
int isValidMove(Piece board[BOARD_SIZE][BOARD_SIZE], int sx, int sy, int dx, int dy);

#endif
