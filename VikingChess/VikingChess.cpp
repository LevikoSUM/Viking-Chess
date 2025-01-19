// VikingChess.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "constants.h"
using namespace std;

//const char EMPTY = ' ', KING = 'K', DEFENDER_PIECE = 'D', ATTACKER_PIECE = 'A', CORNER = 'X';
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
	for (int i = 0; i < 1024; i++)
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
	for (int j = 0; j < size; j++)
	{
		cout << "+-------";
	}
	cout << "+" << endl;


	cout << "    ";
	for (int j = 0; j < size; j++)
	{
		if (j + 1 < 10)
		{
			cout << "    " << j + 1 << "   ";
		}
		else
		{
			cout << "   " << j + 1 << "   ";
		}
	}
	cout << endl;
}

bool isCorner(int row, int col, int size)
{
	return (row == 0 && col == 0) ||
		(row == 0 && col == size - 1) ||
		(row == size - 1 && col == 0) ||
		(row == size - 1 && col == size - 1);
}

bool isEdge(int row, int col, int size)
{
	return row == 0 || col == 0 || row == size - 1 || col == size - 1;
}

bool isThrone(int row, int col, int size)
{
	return row == size / 2 && col == size / 2;
}

bool isKingCaptured(int targetRow, int targetCol, int size, char** board)
{
	int sidesSurrounded = 0;
	int sidesToCapture;
	if (isEdge(targetRow, targetCol, size))
	{
		sidesToCapture = 3;
	}
	else
	{
		sidesToCapture = 4;
	}
	if (board[targetRow - 1][targetCol] == ATTACKER_PIECE ||
		isCorner(targetRow - 1, targetCol, size) ||
		isThrone(targetRow - 1, targetCol, size))
	{
		sidesSurrounded++;
	}
	if (board[targetRow][targetCol - 1] == ATTACKER_PIECE ||
		isCorner(targetRow, targetCol - 1, size) ||
		isThrone(targetRow, targetCol - 1, size))
	{
		sidesSurrounded++;
	}
	if (board[targetRow + 1][targetCol] == ATTACKER_PIECE ||
		isCorner(targetRow + 1, targetCol, size) ||
		isThrone(targetRow + 1, targetCol, size))
	{
		sidesSurrounded++;
		if (sidesSurrounded == sidesToCapture)
		{
			return true;
		}
	}
	if (board[targetRow][targetCol + 1] == ATTACKER_PIECE ||
		isCorner(targetRow, targetCol + 1, size) ||
		isThrone(targetRow, targetCol + 1, size))
	{
		sidesSurrounded++;
	}
	if (sidesSurrounded == sidesToCapture)
	{
		return true;
	}
	return false;
}

void checkCaptureForAttackers(int targetRow, int targetCol, int size, char** board, char*** history)
{
	// top
	if (targetRow > 1 && board[targetRow - 1][targetCol] == DEFENDER_PIECE &&
		(board[targetRow - 2][targetCol] == ATTACKER_PIECE ||
			isCorner(targetRow - 2, targetCol, size) ||
			isThrone(targetRow - 2, targetCol, size)))
	{
		board[targetRow - 1][targetCol] = EMPTY;
		cout << "Captured piece at (" << targetRow - 1 << ", " << targetCol << ")\n";
	}

	// left
	if (targetCol > 1 && board[targetRow][targetCol - 1] == DEFENDER_PIECE &&
		(board[targetRow][targetCol - 2] == ATTACKER_PIECE ||
			isCorner(targetRow, targetCol - 2, size) ||
			isThrone(targetRow, targetCol - 2, size)))
	{
		board[targetRow][targetCol - 1] = EMPTY;
		cout << "Captured piece at (" << targetRow << ", " << targetCol - 1 << ")\n";
	}

	// down
	if (targetRow < size - 2 && board[targetRow + 1][targetCol] == DEFENDER_PIECE &&
		(board[targetRow + 2][targetCol] == ATTACKER_PIECE ||
			isCorner(targetRow + 2, targetCol, size) ||
			isThrone(targetRow + 2, targetCol, size)))
	{
		board[targetRow + 1][targetCol] = EMPTY;
		cout << "Captured piece at (" << targetRow + 1 << ", " << targetCol << ")\n";
	}

	// right
	if (targetCol < size - 2 && board[targetRow][targetCol + 1] == DEFENDER_PIECE &&
		(board[targetRow][targetCol + 2] == ATTACKER_PIECE ||
			isCorner(targetRow, targetCol + 2, size) ||
			isThrone(targetRow, targetCol + 2, size)))
	{
		board[targetRow][targetCol + 1] = EMPTY;
		cout << "Captured piece at (" << targetRow << ", " << targetCol + 1 << ")\n";
	}

	if (targetRow > 0 &&board[targetRow - 1][targetCol] == KING && isKingCaptured(targetRow - 1, targetCol, size, board))
	{
		printBoard(size, board);
		cout << "The King was captured!" << endl << "Attackers Win!!!";
		quitGame(size, board, history);
	}
	else if (targetCol > 0 && board[targetRow][targetCol - 1] == KING && isKingCaptured(targetRow, targetCol - 1, size, board))
	{
		printBoard(size, board);
		cout << "The King was captured!" << endl << "Attackers Win!!!";
		quitGame(size, board, history);
	}
	else if (targetRow < size - 1 && board[targetRow + 1][targetCol] == KING && isKingCaptured(targetRow + 1, targetCol, size, board))
	{
		printBoard(size, board);
		cout << "The King was captured!" << endl << "Attackers Win!!!";
		quitGame(size, board, history);
	}
	else if (targetCol < size - 1 && board[targetRow][targetCol + 1] == KING && isKingCaptured(targetRow, targetCol + 1, size, board))
	{
		printBoard(size, board);
		cout << "The King was captured!" << endl << "Attackers Win!!!";
		quitGame(size, board, history);
	}
}

void checkCaptureForDefenders(int targetRow, int targetCol, int size, char** board)
{
	// top
	if (targetRow > 1 && board[targetRow - 1][targetCol] == ATTACKER_PIECE &&
		(board[targetRow - 2][targetCol] == DEFENDER_PIECE ||
			board[targetRow - 2][targetCol] == KING ||
			isCorner(targetRow - 2, targetCol, size) ||
			isThrone(targetRow - 2, targetCol, size)))
	{
		board[targetRow - 1][targetCol] = EMPTY;
		cout << "Captured piece at (" << targetRow - 1 << ", " << targetCol << ")\n";
	}

	// left
	if (targetCol > 1 && board[targetRow][targetCol - 1] == ATTACKER_PIECE &&
		(board[targetRow][targetCol - 2] == DEFENDER_PIECE ||
			board[targetRow][targetCol - 2] == KING ||
			isCorner(targetRow, targetCol - 2, size) ||
			isThrone(targetRow, targetCol - 2, size)))
	{
		board[targetRow][targetCol - 1] = EMPTY;
		cout << "Captured piece at (" << targetRow << ", " << targetCol - 1 << ")\n";
	}

	// down
	if (targetRow < size - 2 && board[targetRow + 1][targetCol] == ATTACKER_PIECE &&
		(board[targetRow + 2][targetCol] == DEFENDER_PIECE ||
			board[targetRow + 2][targetCol] == KING ||
			isCorner(targetRow + 2, targetCol, size) ||
			isThrone(targetRow + 2, targetCol, size)))
	{
		board[targetRow + 1][targetCol] = EMPTY;
		cout << "Captured piece at (" << targetRow + 1 << ", " << targetCol << ")\n";
	}

	// right
	if (targetCol < size - 2 && board[targetRow][targetCol + 1] == ATTACKER_PIECE &&
		(board[targetRow][targetCol + 2] == DEFENDER_PIECE ||
			board[targetRow][targetCol + 2] == KING ||
			isCorner(targetRow, targetCol + 2, size) ||
			isThrone(targetRow, targetCol + 2, size)))
	{
		board[targetRow][targetCol + 1] = EMPTY;
		cout << "Captured piece at (" << targetRow << ", " << targetCol + 1 << ")\n";
	}
}

void checkCapture(int targetRow, int targetCol, char pieceMoved, int size, char** board, char*** history)
{
	if (pieceMoved == ATTACKER_PIECE)
	{
		checkCaptureForAttackers(targetRow, targetCol, size, board, history);
	}
	else
	{
		checkCaptureForDefenders(targetRow, targetCol, size, board);
	}
}

bool isValidMove(int startX, int startY, int endX, int endY, int& moveCounter, int size, char** board)
{
	if (endX < 0 || endX >= size || endY < 0 || endY >= size) return false; // Out of bounds (moving out of board)
	if (startX < 0 || startX >= size || startY < 0 || startY >= size) return false; // Out of bounds (selecting outside the board)
	if (board[endX][endY] != EMPTY && (board[startX][startY] == ATTACKER_PIECE || board[startX][startY] == DEFENDER_PIECE)) return false; // Destination not empty
	if (board[startX][startY] == KING && (board[endX][endY] == ATTACKER_PIECE || board[endX][endY] == DEFENDER_PIECE)) return false; // Destination not empty, but for the king (because only he can be on corners)
	if (board[startX][startY] == EMPTY || board[startX][startY] == CORNER) return false; // Not a piece
	if (startX != endX && startY != endY) return false; // Only straight moves allowed
	if (moveCounter % 2 == 0 && board[startX][startY] != ATTACKER_PIECE) return false; // Can't move defender and king on attacker turn
	if (moveCounter % 2 == 1 && board[startX][startY] == ATTACKER_PIECE) return false; // Can't move attacker on defender turn
	if (isThrone(endX, endY, size) && (board[startX][startY] == ATTACKER_PIECE || board[startX][startY] == DEFENDER_PIECE)) return false; // Can't enter throne

	int directionX = (endX > startX) - (endX < startX);
	int directionY = (endY > startY) - (endY < startY);

	int currentX = startX + directionX;
	int currentY = startY + directionY;
	while (currentX != endX || currentY != endY)
	{
		if (board[currentX][currentY] != EMPTY) return false; // Cannot jump over other pieces
		currentX += directionX;
		currentY += directionY;
	}

	return true;
}

void makeMove(int startX, int startY, int endX, int endY, int& moveCounter, int size, char** board, char*** history)
{
	if (isValidMove(startX, startY, endX, endY, moveCounter, size, board))
	{
		char piece = board[startX][startY];
		board[startX][startY] = EMPTY;
		board[endX][endY] = piece;
		cout << "Moved piece from (" << startX + 1 << ", " << startY + 1 << ") to (" << endX + 1 << ", " << endY + 1 << ")." << endl;
		checkCapture(endX, endY, piece, size, board, history);
		moveCounter++;
		if (piece == KING && isCorner(endX, endY, size))
		{
			cout << "The king has reached a corner!" << endl << "Defenders Win!!!\n";
			quitGame(size, board, history);
		}
	}
	else
	{
		cout << "Invalid move. Try again." << endl;
	}
}

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
