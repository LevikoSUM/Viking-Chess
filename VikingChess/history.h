#ifndef HISTORY_H
#define HISTORY_H

#include <iostream>

void changeBoardToPreviousFromHistory(char** board, char*** history, int moveCounter, int size);
void undoMove(char** board, char*** history, int& moveCounter, int size);
void addCurrentBoardToHistory(char** board, char*** history, int moveCounter, int size);

#endif
