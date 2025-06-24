#include <stdio.h>
#include "chess.h"

void initializeBoard(Piece board[BOARD_SIZE][BOARD_SIZE]) {
    // Limpa o tabuleiro
    for (int i = 0; i < BOARD_SIZE; i++)
        for (int j = 0; j < BOARD_SIZE; j++)
            board[i][j] = (Piece){EMPTY, NONE};

    // Peões
    for (int i = 0; i < BOARD_SIZE; i++) {
        board[1][i] = (Piece){PAWN, BLACK};
        board[6][i] = (Piece){PAWN, WHITE};
    }

    // Demais peças
    PieceType backRow[] = {ROOK, KNIGHT, BISHOP, QUEEN, KING, BISHOP, KNIGHT, ROOK};
    for (int i = 0; i < BOARD_SIZE; i++) {
        board[0][i] = (Piece){backRow[i], BLACK};
        board[7][i] = (Piece){backRow[i], WHITE};
    }
}

void printBoard(Piece board[BOARD_SIZE][BOARD_SIZE]) {
    printf("  a b c d e f g h\n");
    for (int i = 0; i < BOARD_SIZE; i++) {
        printf("%d ", 8 - i);
        for (int j = 0; j < BOARD_SIZE; j++) {
            Piece p = board[i][j];
            char c = '.';
            if (p.type != EMPTY) {
                switch (p.type) {
                    case PAWN:   c = 'P'; break;
                    case ROOK:   c = 'R'; break;
                    case KNIGHT: c = 'N'; break;
                    case BISHOP: c = 'B'; break;
                    case QUEEN:  c = 'Q'; break;
                    case KING:   c = 'K'; break;
                    default: break;
                }
                if (p.color == BLACK) c += 32; // minúsculo para pretas
            }
            printf("%c ", c);
        }
        printf("%d\n", 8 - i);
    }
    printf("  a b c d e f g h\n");
}

int movePiece(Piece board[BOARD_SIZE][BOARD_SIZE], int sx, int sy, int dx, int dy, Color turn) {
    if (!isValidMove(board, sx, sy, dx, dy))
        return 0;

    Piece src = board[sx][sy];
    if (src.color != turn) return 0;

    board[dx][dy] = src;
    board[sx][sy] = (Piece){EMPTY, NONE};
    return 1;
}

int isValidMove(Piece board[BOARD_SIZE][BOARD_SIZE], int sx, int sy, int dx, int dy) {
    if (sx < 0 || sx >= BOARD_SIZE || sy < 0 || sy >= BOARD_SIZE ||
        dx < 0 || dx >= BOARD_SIZE || dy < 0 || dy >= BOARD_SIZE)
        return 0;

    Piece src = board[sx][sy];
    Piece dst = board[dx][dy];
    if (src.type == EMPTY) return 0;
    if (dst.color == src.color) return 0;

    // Movimentos básicos de peão (sem captura diagonal ou promoção)
    if (src.type == PAWN) {
        int dir = (src.color == WHITE) ? -1 : 1;
        if (sy == dy && dst.type == EMPTY && dx == sx + dir)
            return 1;
        if (sy == dy && dst.type == EMPTY && dx == sx + 2*dir &&
            ((src.color == WHITE && sx == 6) || (src.color == BLACK && sx == 1)))
            return 1;
        if ((dy == sy + 1 || dy == sy - 1) && dx == sx + dir && dst.type != EMPTY && dst.color != src.color)
            return 1;
        return 0;
    }

    // Simples: apenas movimento da torre
    if (src.type == ROOK) {
        if (sx == dx || sy == dy) return 1;
        return 0;
    }

    return 1; // Demais peças: liberar tudo por enquanto
}
