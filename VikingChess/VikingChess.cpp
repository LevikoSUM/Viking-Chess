// VikingChess.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "constants.h"
#include "utility.h"
#include "board.h"
#include "pieces.h"
#include "history.h"
using namespace std;

void printBoardSelectionScreen()
{
	cout << "Choose the size of the board\n";
	cout << "1. Small (7x7)\n";
	cout << "2. Medium (9x9)\n";
	cout << "3. Large (11x11)\n";
	cout << "4. Huge (13x13)\n";
}

void selectBoard(int& size)
{
	int option;
	cin >> option;
	if (option == 1)
	{
		size = 7;
		return;
	}
	if (option == 2)
	{
		size = 9;
		return;
	}
	if (option == 3)
	{
		size = 11;
		return;
	}
	if (option == 4)
	{
		size = 13;
		return;
	}
	else
	{
		cout << "Invalid input\n";
		clearInputBuffer();
		selectBoard(size);
	}
}

void printMenu()
{
	cout << "Welcome to Tafl!\n";
	cout << "Choose an option:\n";
	cout << "1. Start Game.\n";
	cout << "2. Quit\n";
}

void selectMenuOption(int &size)
{
	int option;
	cin >> option;
	if (option == 1)
	{
		printBoardSelectionScreen();
		selectBoard(size);
	}
	else if (option == 2)
	{
		exit(0);
	}
	else
	{
		cout << "Invalid input\n";
		clearInputBuffer();
		selectMenuOption(size);
	}
}

char** createBoard(int size) 
{
	char** board = new char*[size];
	for (int i = 0; i < size; i++) 
	{
		board[i] = new char[size];
	}
	return board;
}

char*** createHistory(int size)
{
	char*** history = new char**[1024];
	for (int i = 0; i < 1024; i++)
	{
		history[i] = new char* [size];
		for (int j = 0; j < size; j++)
		{
			history[i][j] = new char[size];
		}
	}
	return history;
}

int findAttackersPiecesCount(char** board, int size)
{
	int count = 0;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (board[i][j] == ATTACKER_PIECE)
			{
				count++;
			}
		}
	}
	return count;
}

int findDefendersPiecesCount(char** board, int size)
{
	int count = 0;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (board[i][j] == DEFENDER_PIECE || board[i][j] == KING)
			{
				count++;
			}
		}
	}
	return count;
}

void printInfo(int moveCounter, char** board, int size, int defendersPiecesCountMax, int attackersPiecesCountMax)
{
	int defendersPiecesCount = findDefendersPiecesCount(board, size);
	int attackersPiecesCount = findAttackersPiecesCount(board, size);
	int capturedDefendersPieces = defendersPiecesCountMax - defendersPiecesCount;
	int capturedAttackersPieces = attackersPiecesCountMax - attackersPiecesCount;

	cout << "The current turn is " << moveCounter + 1 << endl;
	cout << (moveCounter % 2 == 1 ? "It's defenders turn" : "It's attackers turn") << endl;
	cout << "Defenders pieces: " << defendersPiecesCount << endl;
	cout << "The defenders have captured " << capturedAttackersPieces << " pieces" << endl;
	cout << "Attackers pieces: " << attackersPiecesCount << endl;
	cout << "The attackers have captured " << capturedDefendersPieces << " pieces" << endl;
}

void printHelp()
{
	cout << "move <number1> <number2> <number3> <number4> : move a piece  from (number1,number2) to (number3,number4) if possible.\n";
	cout << "back : undo the last turn made.\n";
	cout << "info : get information about the current board state.\n";
}

bool compareCommand(const char command[], const char expected[]) 
{
	for (int i = 0; i < 4; i++) 
	{
		if (command[i] != expected[i]) 
		{
			return false; 
		}
	}
	return command[4] == '\0';
}

int main()
{
	printMenu();
	int size;
	selectMenuOption(size);

	char** board = createBoard(size);
	char*** history = createHistory(size);

	initializeBoard(size, board);
	printBoard(size, board);

	int moveCounter = 0;
	addCurrentBoardToHistory(board, history, moveCounter, size);

	int defendersPiecesCountMax= findDefendersPiecesCount(board, size);
	int attackersPiecesCountMax = findAttackersPiecesCount(board, size);

	char command[4];
	while (true)
	{
		cout << "> ";
		cin >> command;

		if (compareCommand(command, "move"))
		{
			int startX, startY, endX, endY;
			if (cin >> startX >> startY >> endX >> endY)
			{
				makeMove(startX - 1, startY - 1, endX - 1, endY - 1, moveCounter, size, board, history);
				addCurrentBoardToHistory(board, history, moveCounter, size);
				printBoard(size, board);
			}
			else
			{
				cout << "Invalid input. Please enter four numbers for the move command.\n";
				clearInputBuffer();
			}
		}
		else if (compareCommand(command, "back"))
		{
			undoMove(board, history, moveCounter, size);
			printBoard(size, board);
		}
		else if (compareCommand(command, "info"))
		{
			printInfo(moveCounter, board, size, defendersPiecesCountMax, attackersPiecesCountMax);
		}
		else if (compareCommand(command, "help"))
		{
			printHelp();
		}
		else
		{
			cout << "Invalid command. You can write \"help\" to see available commands\n";
			clearInputBuffer();
		}
	}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
