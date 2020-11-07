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

// Piezas con sus posiciones iniciales y finales
int rook(int x0, int y0, int xf, int yf);		// 2 o -2
int knight(int x0, int y0, int xf, int yf);		// 3 o -3
int bishop(int x0, int y0, int xf, int yf);		// 4 o -4
int queen(int x0, int y0, int xf, int yf);		// 5 o -5
int king(int x0, int y0, int xf, int yf);		// 6 o -6
int pawn(int x0, int y0, int xf, int yf);		// 1 o -1

int gameover();
void noPiece();
char changePiece(int x, int y);
int checkFinalPos(int xf,int yf);
void check();
void makeMove();
void addPieceChar(int number);
void initNewGame();
char obtainChar();
int squareUnderAttack(int x, int y, int value);
void blankPawnMoves();
void exit();
void userGuide();
#endif