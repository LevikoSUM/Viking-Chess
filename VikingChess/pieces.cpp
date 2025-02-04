/*
Solution to course project # 7
Introduction to programming course
Faculty of Mathematics and Informatics of Sofia University
Winter semester 2024/2025

@author Kosta Ilev
@idnumber 4MI0600514
@compiler VC
<cpp file with functions related to the pieces and how they interact>
*/
#include "pieces.h"
#include "constants.h"
#include "utility.h"
#include "board.h"
#include <iostream>
using namespace std;

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
	if (targetRow > 0)
	{

		if (board[targetRow - 1][targetCol] == ATTACKER_PIECE ||
			isCorner(targetRow - 1, targetCol, size) ||
			isThrone(targetRow - 1, targetCol, size))
		{
			sidesSurrounded++;
		}
	}
	if (targetCol > 0)
	{
		if (board[targetRow][targetCol - 1] == ATTACKER_PIECE ||
			isCorner(targetRow, targetCol - 1, size) ||
			isThrone(targetRow, targetCol - 1, size))
		{
			sidesSurrounded++;
		}
	}
	if (targetRow < size - 1)
	{
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
	}
	if (targetCol < size - 1)
	{
		if (board[targetRow][targetCol + 1] == ATTACKER_PIECE ||
			isCorner(targetRow, targetCol + 1, size) ||
			isThrone(targetRow, targetCol + 1, size))
		{
			sidesSurrounded++;
		}
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

	if (targetRow > 0 && board[targetRow - 1][targetCol] == KING && isKingCaptured(targetRow - 1, targetCol, size, board))
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