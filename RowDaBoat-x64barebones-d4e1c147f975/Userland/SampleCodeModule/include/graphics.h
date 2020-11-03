#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <stdint.h>

void drawPixel(int x, int y, int color);

void drawPiece(int piece, int x, int y, int pieceColor, int bgColor);
void drawBoard(int matrix[][8],uint64_t color1, uint64_t color2);
void timer(uint32_t startx, uint32_t starty, uint32_t endx, uint32_t endy, uint64_t bg_color);

#endif