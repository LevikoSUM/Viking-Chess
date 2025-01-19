#ifndef UTILITY_H
#define UTILITY_H

#include <iostream>

void clearInputBuffer();
void deleteBoard(char** board, int size);
void deleteHistory(char*** history, int size);
void quitGame(int size, char** board, char*** history);

#endif