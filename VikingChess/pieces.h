#ifndef PIECES_H
#define PIECES_H

#include <iostream>

bool isCorner(int row, int col, int size);
bool isEdge(int row, int col, int size);
bool isThrone(int row, int col, int size);
bool isKingCaptured(int targetRow, int targetCol, int size, char** board);
void checkCaptureForAttackers(int targetRow, int targetCol, int size, char** board, char*** history);
void checkCaptureForDefenders(int targetRow, int targetCol, int size, char** board);
void checkCapture(int targetRow, int targetCol, char pieceMoved, int size, char** board, char*** history);
bool isValidMove(int startX, int startY, int endX, int endY, int& moveCounter, int size, char** board);
void makeMove(int startX, int startY, int endX, int endY, int& moveCounter, int size, char** board, char*** history);

#endif
