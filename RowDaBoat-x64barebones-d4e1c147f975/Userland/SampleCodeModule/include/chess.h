#ifndef CHESS_H
#define CHESS_H

typedef enum{
    WROOK = 2,
    WHORSE = 3,
    WBISHOP = 4,
    WQUEEN = 5,
    WKING = 6,
    BROOK = -2,
    BHORSE = -3,
    BBISHOP = -4,
    BQUEEN = -5,
    BKING = -6
}Pieces;

enum game_state{new_game=0,game_started};

void playChess(enum game_state state);

#endif