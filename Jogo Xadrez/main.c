#include <stdio.h>
#include <stdlib.h>
#include "chess.h"

int main() {
    Piece board[BOARD_SIZE][BOARD_SIZE];
    initializeBoard(board);
    Color turn = WHITE;

    while (1) {
        printBoard(board);
        printf("%s > Informe o movimento (ex: e2 e4): ", turn == WHITE ? "Branco" : "Preto");

        char src[3], dst[3];
        scanf("%s %s", src, dst);

        int sx = 8 - (src[1] - '0');
        int sy = src[0] - 'a';
        int dx = 8 - (dst[1] - '0');
        int dy = dst[0] - 'a';

        if (!movePiece(board, sx, sy, dx, dy, turn)) {
            printf("Movimento inválido!\n");
            continue;
        }

        turn = (turn == WHITE) ? BLACK : WHITE;
    }

    return 0;
}
