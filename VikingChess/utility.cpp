#include "utility.h"
#include "constants.h"
#include <iostream>
using namespace std;

void clearInputBuffer()
{
	cin.clear();
	while (cin.get() != '\n');
}

void deleteBoard(char** board, int size)
{
	for (int i = 0; i < size; i++)
	{
		delete[] board[i];
	}
	delete[] board;
}

void deleteHistory(char*** history, int size)
{
	for (int i = 0; i < MAX_HISTORY_SIZE; i++)
	{
		for (int j = 0; j < size; j++)
		{
			delete[] history[i][j];
		}
		delete[] history[i];
	}
	delete[] history;
}
void quitGame(int size, char** board, char*** history)
{
	deleteBoard(board, size);
	deleteHistory(history, size);
	exit(0);
}