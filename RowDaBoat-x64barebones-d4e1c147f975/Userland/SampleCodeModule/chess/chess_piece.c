#ifndef CHESS_BITMAPS_H
#define CHESS_BITMAPS_H

#include <chess_piece.h>

static unsigned char * __chess_bitmap__[]={
"_______________________________________________________________________________________,"
"_______________________________________________________________________________________,"
"_______________________________________________________________________________________,"
"_______________________________________________________________________________________,"
"_______________________________________________________________________________________,"
"_______________________________________________________________________________________,"
"_______________________________________________________________________________________,"
"_______________________________________________________________________________________,"
"_______________________________________________________________________________________,"
"_______________________________________________________________________________________,"
"_______________________________________________________________________________________,"
"_______________xxxxxxxxxxxxxx__________________________________________________________,"
"_______________xxxxxxxxxxxxxx__________________________________________________________,"
"_______________xxxxxxxxxxxxxx__________________________________________________________,"
"_______________xxxxxxxxxxxxxx__________________________________________________________,"
"_______________xxxxxxxxxxxxxx__________________________________________________________,"
"_______________xxxxxxxxxxxxxx__________________________________________________________,"
"_______________xxxxxxxxxxxxxx__________________________________________________________,"
"_______________xxxxxxxxxxxxxx__________________________________________________________,"
"_______________xxxxxxxxxxxxxx__________________________________________________________,"
"_______________xxxxxxxxxxxxxx__________________________________________________________,"
"_______________xxxxxxxxxxxxxx__________________________________________________________,"
"_______________xxxxxxxxxxxxxx__________________________________________________________,"
"_______________xxxxxxxxxxxxxx__________________________________________________________,"
"_______________xxxxxxxxxxxxxx__________________________________________________________,"
"_______________xxxxxxxxxxxxxx__________________________________________________________,"
"_______________xxxxxxxxxxxxxx__________________________________________________________,"
"_______________xxxxxxxxxxxxxx__________________________________________________________,"
"_______________xxxxxxxxxxxxxx__________________________________________________________,"
"_______________xxxxxxxxxxxxxx__________________________________________________________,"
"_______________xxxxxxxxxxxxxx__________________________________________________________,"
"_______________xxxxxxxxxxxxxx__________________________________________________________,"
"_______________xxxxxxxxxxxxxx__________________________________________________________,"
"_______________xxxxxxxxxxxxxx__________________________________________________________,"
"_______________xxxxxxxxxxxxxx__________________________________________________________,"
"_______________xxxxxxxxxxxxxx__________________________________________________________,"
"_______________xxxxxxxxxxxxxx__________________________________________________________,"
"_______________xxxxxxxxxxxxxx__________________________________________________________,"
"_______________xxxxxxxxxxxxxx__________________________________________________________,"
"_______________xxxxxxxxxxxxxx__________________________________________________________,"
"_______________xxxxxxxxxxxxxx__________________________________________________________,"
"_______________xxxxxxxxxxxxxx__________________________________________________________,"
"_______________xxxxxxxxxxxxxx__________________________________________________________,"
"_______________xxxxxxxxxxxxxx__________________________________________________________,"
"_______________xxxxxxxxxxxxxx__________________________________________________________,"
"_______________xxxxxxxxxxxxxx__________________________________________________________,"
"_______________xxxxxxxxxxxxxx__________________________________________________________,"
"_______________xxxxxxxxxxxxxx__________________________________________________________,"
"_______________xxxxxxxxxxxxxx__________________________________________________________,"
"_______________xxxxxxxxxxxxxx__________________________________________________________,"
"_______________xxxxxxxxxxxxxx__________________________________________________________,"
"_______________xxxxxxxxxxxxxx__________________________________________________________,"
"_______________xxxxxxxxxxxxxx__________________________________________________________,"
"_______________xxxxxxxxxxxxxx__________________________________________________________,"
"_______________xxxxxxxxxxxxxx__________________________________________________________,"
"_______________xxxxxxxxxxxxxx__________________________________________________________,"
"_______________xxxxxxxxxxxxxx__________________________________________________________,"
"_______________xxxxxxxxxxxxxx__________________________________________________________,"
"_______________xxxxxxxxxxxxxx__________________________________________________________,"
"_______________xxxxxxxxxxxxxx__________________________________________________________,"
"_______________xxxxxxxxxxxxxx__________________________________________________________,"
"_______________xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx______________________,"
"_______________xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx______________________,"
"_______________xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx______________________,"
"_______________xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx______________________,"
"_______________xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx______________________,"
"_______________xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx______________________,"
"_______________xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx______________________,"
"_______________xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx______________________,"
"_______________xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx______________________,"
"_______________xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx______________________,"
"_______________xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx______________________,"
"_______________xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx______________________,"
"_______________________________________________________________________________________,"
"_______________________________________________________________________________________,"
"_______________________________________________________________________________________,"
"_______________________________________________________________________________________,"
"_______________________________________________________________________________________,"
"_______________________________________________________________________________________,"
"_______________________________________________________________________________________,"
"_______________________________________________________________________________________,"
"_______________________________________________________________________________________,"
"_______________________________________________________________________________________,"
"_______________________________________________________________________________________,"
"_______________________________________________________________________________________,"
"_______________________________________________________________________________________,"
"_______________________________________________________________________________________"

};

unsigned char * chess_bitMap(int c){
	return (__chess_bitmap__[c]);
    
}

#endif