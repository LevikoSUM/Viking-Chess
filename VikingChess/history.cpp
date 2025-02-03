#include "history.h"
#include <iostream>
using namespace std;

void changeBoardToPreviousFromHistory(char** board, char*** history, int moveCounter, int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			board[i][j] = history[moveCounter][i][j];
		}
	}
}

void undoMove(char** board, char*** history, int& moveCounter, int size)
{
	if (moveCounter < 1)
	{
		cout << "No move to undo!\n";
	}
	else
	{
		moveCounter--;
		changeBoardToPreviousFromHistory(board, history, moveCounter, size);
	}
}

void addCurrentBoardToHistory(char** board, char*** history, int moveCounter, int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			history[moveCounter][i][j] = board[i][j];
		}
	}
}
