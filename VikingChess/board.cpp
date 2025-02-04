/*
Solution to course project # 7
Introduction to programming course
Faculty of Mathematics and Informatics of Sofia University
Winter semester 2024/2025

@author Kosta Ilev
@idnumber 4MI0600514
@compiler VC
<cpp file with functions related to the board>
*/
#include "board.h"
#include "constants.h"
#include <iostream>
using namespace std;

void initializeBoard(int size, char** board)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			board[i][j] = EMPTY;
		}
	}

	board[0][0] = CORNER;
	board[0][size - 1] = CORNER;
	board[size - 1][0] = CORNER;
	board[size - 1][size - 1] = CORNER;

	board[size / 2][size / 2] = KING;
	if (size == 7)
	{
		board[3][2] = DEFENDER_PIECE;
		board[3][4] = DEFENDER_PIECE;
		board[2][3] = DEFENDER_PIECE;
		board[4][3] = DEFENDER_PIECE;

		board[3][0] = ATTACKER_PIECE;
		board[3][1] = ATTACKER_PIECE;
		board[3][5] = ATTACKER_PIECE;
		board[3][6] = ATTACKER_PIECE;
		board[0][3] = ATTACKER_PIECE;
		board[1][3] = ATTACKER_PIECE;
		board[5][3] = ATTACKER_PIECE;
		board[6][3] = ATTACKER_PIECE;
	}
	else if (size == 9)
	{
		board[4][3] = DEFENDER_PIECE;
		board[4][5] = DEFENDER_PIECE;
		board[3][4] = DEFENDER_PIECE;
		board[5][4] = DEFENDER_PIECE;
		board[4][2] = DEFENDER_PIECE;
		board[4][6] = DEFENDER_PIECE;
		board[2][4] = DEFENDER_PIECE;
		board[6][4] = DEFENDER_PIECE;

		for (int i = 3; i < 6; i++)
		{
			board[i][0] = ATTACKER_PIECE;
			board[0][i] = ATTACKER_PIECE;
			board[i][8] = ATTACKER_PIECE;
			board[8][i] = ATTACKER_PIECE;
		}
		board[4][1] = ATTACKER_PIECE;
		board[4][7] = ATTACKER_PIECE;
		board[7][4] = ATTACKER_PIECE;
		board[1][4] = ATTACKER_PIECE;

	}
	else if (size == 11)
	{
		for (int i = 3; i < 8; i++)
		{
			if (i == 5) continue;
			board[5][i] = DEFENDER_PIECE;
			board[i][5] = DEFENDER_PIECE;
		}

		board[4][4] = DEFENDER_PIECE;
		board[6][4] = DEFENDER_PIECE;
		board[4][6] = DEFENDER_PIECE;
		board[6][6] = DEFENDER_PIECE;

		for (int i = 3; i < 8; i++)
		{
			board[0][i] = ATTACKER_PIECE;
			board[10][i] = ATTACKER_PIECE;
			board[i][0] = ATTACKER_PIECE;
			board[i][10] = ATTACKER_PIECE;
		}

		board[5][1] = ATTACKER_PIECE;
		board[1][5] = ATTACKER_PIECE;
		board[5][9] = ATTACKER_PIECE;
		board[9][5] = ATTACKER_PIECE;
	}
	else if (size == 13)
	{
		for (int i = 3; i < 10; i++)
		{
			if (i == 6) continue;
			board[6][i] = DEFENDER_PIECE;
			board[i][6] = DEFENDER_PIECE;
		}
		board[5][5] = DEFENDER_PIECE;
		board[7][5] = DEFENDER_PIECE;
		board[5][7] = DEFENDER_PIECE;
		board[7][7] = DEFENDER_PIECE;
		for (int i = 3; i < 10; i++)
		{
			board[0][i] = ATTACKER_PIECE;
			board[12][i] = ATTACKER_PIECE;
			board[i][0] = ATTACKER_PIECE;
			board[i][12] = ATTACKER_PIECE;
		}
		board[6][1] = ATTACKER_PIECE;
		board[1][6] = ATTACKER_PIECE;
		board[6][11] = ATTACKER_PIECE;
		board[11][6] = ATTACKER_PIECE;
	}

}

void printBoard(int size, char** board)
{
	for (int i = 0; i < size; i++)
	{
		cout << "    ";
		for (int j = 0; j < size; j++)
		{
			cout << "+-------";
		}
		cout << "+" << endl;

		for (int rowPart = 0; rowPart < 3; rowPart++)
		{
			if (rowPart == 1)
			{

				if (i + 1 < 10)
				{
					cout << "   " << i + 1;
				}
				else
				{
					cout << "  " << i + 1;
				}
			}
			else
			{
				cout << "    ";
			}

			for (int j = 0; j < size; j++)
			{
				if (rowPart == 1 && board[i][j] != EMPTY)
				{

					cout << "|   " << board[i][j] << "   ";
				}
				else
				{

					cout << "|       ";
				}
			}
			cout << "|" << endl;
		}
	}


	cout << "    ";
	for (int i = 0; i < size; i++)
	{
		cout << "+-------";
	}
	cout << "+" << endl;


	cout << "    ";
	for (int i = 0; i < size; i++)
	{
		char letter = 'A' + i;
		cout << "    " << letter << "   ";
	}
	cout << endl;
}