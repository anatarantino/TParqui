#ifndef CHESS_BITMAPS_H
#define CHESS_BITMAPS_H

#include <chess_piece.h>

static unsigned char * __chess_bitmap__[]={
	"________,"
     "________,"
     "__XXXX__,"
    "_XX__XX_,"
    "XX____X_,"
    "XX______,"
    "XX______,"
    "XX______,"
    "XX______,"
    "XX____X_,"
    "_XX__XX_,"
    "__XXXX__,"
    "________,"
    "________,"
    "________,"
    "________"

};

unsigned char * chess_bitMap(int c){
	return (__chess_bitmap__[c]);
    
}

#endif