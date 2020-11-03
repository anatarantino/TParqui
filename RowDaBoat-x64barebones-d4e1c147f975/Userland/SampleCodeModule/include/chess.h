#ifndef CHESS_H
#define CHESS_H

typedef enum{
    WPAWN = 1,
    WROOK = 2,
    WHORSE = 3,
    WBISHOP = 4,
    WQUEEN = 5,
    WKING = 6,
    BPAWN = -1,
    BROOK = -2,
    BHORSE = -3,
    BBISHOP = -4,
    BQUEEN = -5,
    BKING = -6
}Pieces;

void playChess();

#endif