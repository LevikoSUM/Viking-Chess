/*
Solution to course project # 7
Introduction to programming course
Faculty of Mathematics and Informatics of Sofia University
Winter semester 2024/2025

@author Kosta Ilev
@idnumber 4MI0600514
@compiler VC
<cpp file with helper functions>
*/
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