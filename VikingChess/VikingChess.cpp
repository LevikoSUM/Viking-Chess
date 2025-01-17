// VikingChess.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;

const char EMPTY = ' ', KING = 'K', DEFENDER_PIECE = 'D', ATTACKER_PIECE = 'A', CORNER = 'X';
int BOARD_SIZE = 11;
char board[11][11];

void initializeBoard()
{
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			board[i][j] = EMPTY;
		}
	}

	board[BOARD_SIZE / 2][BOARD_SIZE / 2] = KING;

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

	for (int i = 3; i <= 7; i++)
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
	board[0][0] = CORNER;
	board[0][10] = CORNER;
	board[10][0] = CORNER;
	board[10][10] = CORNER;

}

void printBoard()
{
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		cout << "    ";
		for (int j = 0; j < BOARD_SIZE; j++)
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

			for (int j = 0; j < BOARD_SIZE; j++)
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
	for (int j = 0; j < BOARD_SIZE; j++)
	{
		cout << "+-------";
	}
	cout << "+" << endl;


	cout << "    ";
	for (int j = 0; j < BOARD_SIZE; j++)
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

bool isCorner(int row, int col)
{
	return board[row][col] == CORNER;
}

bool isEdge(int row, int col)
{
	return row == 0 || col == 0 || row == BOARD_SIZE - 1 || col == BOARD_SIZE - 1;
}

bool isThrone(int row, int col)
{
	return row == BOARD_SIZE / 2 && col == BOARD_SIZE / 2;
}

bool isKingCaptured(int targetRow, int targetCol)
{
	int sidesSurrounded = 0;
	int sidesToCapture;
	if (isEdge(targetRow, targetCol))
	{
		sidesToCapture = 3;
	}
	else
	{
		sidesToCapture = 4;
	}
	if (board[targetRow - 1][targetCol] == ATTACKER_PIECE ||
		isCorner(targetRow - 1, targetCol) ||
		isThrone(targetRow - 1, targetCol))
	{
		sidesSurrounded++;
	}
	if (board[targetRow][targetCol - 1] == ATTACKER_PIECE ||
		isCorner(targetRow, targetCol - 1) ||
		isThrone(targetRow, targetCol - 1))
	{
		sidesSurrounded++;
	}
	if (board[targetRow + 1][targetCol] == ATTACKER_PIECE ||
		isCorner(targetRow + 1, targetCol) ||
		isThrone(targetRow + 1, targetCol))
	{
		sidesSurrounded++;
		if (sidesSurrounded == sidesToCapture)
		{
			return true;
		}
	}
	if (board[targetRow][targetCol + 1] == ATTACKER_PIECE ||
		isCorner(targetRow, targetCol + 1) ||
		isThrone(targetRow, targetCol + 1))
	{
		sidesSurrounded++;
	}
	if (sidesSurrounded == sidesToCapture)
	{
		return true;
	}
	return false;
}

void checkCaptureForAttackers(int targetRow, int targetCol)
{
	// top
	if (targetRow > 1 && board[targetRow - 1][targetCol] == DEFENDER_PIECE &&
		(board[targetRow - 2][targetCol] == ATTACKER_PIECE ||
			isCorner(targetRow - 2, targetCol) ||
			isThrone(targetRow - 2, targetCol)))
	{
		board[targetRow - 1][targetCol] = EMPTY;
		cout << "Captured piece at (" << targetRow - 1 << ", " << targetCol << ")\n";
	}

	// left
	if (targetCol > 1 && board[targetRow][targetCol - 1] == DEFENDER_PIECE &&
		(board[targetRow][targetCol - 2] == ATTACKER_PIECE ||
			isCorner(targetRow, targetCol - 2) ||
			isThrone(targetRow, targetCol - 2)))
	{
		board[targetRow][targetCol - 1] = EMPTY;
		cout << "Captured piece at (" << targetRow << ", " << targetCol - 1 << ")\n";
	}

	// down
	if (targetRow < BOARD_SIZE - 2 && board[targetRow + 1][targetCol] == DEFENDER_PIECE &&
		(board[targetRow + 2][targetCol] == ATTACKER_PIECE ||
			isCorner(targetRow + 2, targetCol) ||
			isThrone(targetRow + 2, targetCol)))
	{
		board[targetRow + 1][targetCol] = EMPTY;
		cout << "Captured piece at (" << targetRow + 1 << ", " << targetCol << ")\n";
	}

	// right
	if (targetCol < BOARD_SIZE - 2 && board[targetRow][targetCol + 1] == DEFENDER_PIECE &&
		(board[targetRow][targetCol + 2] == ATTACKER_PIECE ||
			isCorner(targetRow, targetCol + 2) ||
			isThrone(targetRow, targetCol + 2)))
	{
		board[targetRow][targetCol + 1] = EMPTY;
		cout << "Captured piece at (" << targetRow << ", " << targetCol + 1 << ")\n";
	}

	if (board[targetRow - 1][targetCol] == KING && isKingCaptured(targetRow - 1, targetCol))
	{
		cout << "Captured King\n";
	}
	else if (board[targetRow][targetCol - 1] == KING && isKingCaptured(targetRow, targetCol - 1))
	{
		cout << "Captured King\n";
	}
	else if (board[targetRow + 1][targetCol] == KING && isKingCaptured(targetRow + 1, targetCol))
	{
		cout << "Captured King\n";
	}
	else if (board[targetRow][targetCol + 1] == KING && isKingCaptured(targetRow, targetCol + 1))
	{
		cout << "Captured King\n";
	}
}

void checkCaptureForDefenders(int targetRow, int targetCol)
{
	// top
	if (targetRow > 1 && board[targetRow - 1][targetCol] == ATTACKER_PIECE &&
		(board[targetRow - 2][targetCol] == DEFENDER_PIECE ||
			board[targetRow - 2][targetCol] == KING ||
			isCorner(targetRow - 2, targetCol) ||
			isThrone(targetRow - 2, targetCol)))
	{
		board[targetRow - 1][targetCol] = EMPTY;
		cout << "Captured piece at (" << targetRow - 1 << ", " << targetCol << ")\n";
	}

	// left
	if (targetCol > 1 && board[targetRow][targetCol - 1] == ATTACKER_PIECE &&
		(board[targetRow][targetCol - 2] == DEFENDER_PIECE ||
			board[targetRow][targetCol - 2] == KING ||
			isCorner(targetRow, targetCol - 2) ||
			isThrone(targetRow, targetCol - 2)))
	{
		board[targetRow][targetCol - 1] = EMPTY;
		cout << "Captured piece at (" << targetRow << ", " << targetCol - 1 << ")\n";
	}

	// down
	if (targetRow < BOARD_SIZE - 2 && board[targetRow + 1][targetCol] == ATTACKER_PIECE &&
		(board[targetRow + 2][targetCol] == DEFENDER_PIECE ||
			board[targetRow + 2][targetCol] == KING ||
			isCorner(targetRow + 2, targetCol) ||
			isThrone(targetRow + 2, targetCol)))
	{
		board[targetRow + 1][targetCol] = EMPTY;
		cout << "Captured piece at (" << targetRow + 1 << ", " << targetCol << ")\n";
	}

	// right
	if (targetCol < BOARD_SIZE - 2 && board[targetRow][targetCol + 1] == ATTACKER_PIECE &&
		(board[targetRow][targetCol + 2] == DEFENDER_PIECE ||
			board[targetRow][targetCol + 2] == KING ||
			isCorner(targetRow, targetCol + 2) ||
			isThrone(targetRow, targetCol + 2)))
	{
		board[targetRow][targetCol + 1] = EMPTY;
		cout << "Captured piece at (" << targetRow << ", " << targetCol + 1 << ")\n";
	}
}

void checkCapture(int targetRow, int targetCol, char pieceMoved)
{
	if (pieceMoved == ATTACKER_PIECE)
	{
		checkCaptureForAttackers(targetRow, targetCol);
	}
	else
	{
		checkCaptureForDefenders(targetRow, targetCol);
	}
}

bool isValidMove(int startX, int startY, int endX, int endY, int& moveCounter)
{
	if (endX < 0 || endX >= BOARD_SIZE || endY < 0 || endY >= BOARD_SIZE) return false; // Out of bounds
	if (board[endX][endY] != EMPTY) return false; // Destination not empty
	if (board[startX][startY] == EMPTY || board[startX][startY] == CORNER) return false; // Not a piece
	if (startX != endX && startY != endY) return false; // Only straight moves allowed
	if (moveCounter % 2 == 0 && board[startX][startY] != ATTACKER_PIECE) return false; // Can't move defender and king on attacker turn
	if (moveCounter % 2 == 1 && board[startX][startY] == ATTACKER_PIECE) return false; // Can't move attacker on defender turn

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

void makeMove(int startX, int startY, int endX, int endY, int& moveCounter)
{
	if (isValidMove(startX, startY, endX, endY, moveCounter))
	{
		char piece = board[startX][startY];
		board[startX][startY] = EMPTY;
		board[endX][endY] = piece;
		cout << "Moved piece from (" << startX + 1 << ", " << startY + 1 << ") to (" << endX + 1 << ", " << endY + 1 << ")." << endl;
		checkCapture(endX, endY, piece);
		moveCounter++;
	}
	else
	{
		cout << "Invalid move. Try again." << endl;
	}
}

int main()
{
	initializeBoard();
	printBoard();

	int moveCounter = 0;

	char command[10];
	while (true)
	{
		cout << "> ";
		cin >> command;

		if (command[0] == 'm' && command[1] == 'o' && command[2] == 'v' && command[3] == 'e')
		{
			int startX, startY, endX, endY;
			cin >> startX >> startY >> endX >> endY;
			makeMove(startX - 1, startY - 1, endX - 1, endY - 1, moveCounter);
			printBoard();
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
