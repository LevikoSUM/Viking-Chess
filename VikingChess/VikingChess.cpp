// VikingChess.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;

const char EMPTY = '.', KING = 'K', DEFENDER_PIECE = 'D', ATTACKER_PIECE = 'A';
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
}

void printBoard() 
{
    cout << "   ";
    for (int i = 0; i < BOARD_SIZE; i++) 
    {
        char cordinate = 'A' + i;
        cout << cordinate << " ";
    }
    cout << endl;
    for (int i = 0; i < BOARD_SIZE; i++) 
    {
        cout << i + 1 << " ";
        if (i + 1< 10)
        {
            cout << " ";
        }
        for (int j = 0; j < BOARD_SIZE; j++) 
        {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

bool isValidMove(int startX, int startY, int endX, int endY) 
{
    if (endX < 0 || endX >= BOARD_SIZE || endY < 0 || endY >= BOARD_SIZE) return false; // Out of bounds
    if (board[endX][endY] != EMPTY) return false; // Destination not empty
    if (board[startX][startY] == EMPTY) return false; // Not a piece
    if (startX != endX && startY != endY) return false; // Only straight moves allowed

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

void makeMove(int startX, int startY, int endX, int endY) 
{
    if (isValidMove(startX, startY, endX, endY)) 
    {
        char piece = board[startX][startY];
        board[startX][startY] = EMPTY;
        board[endX][endY] = piece;
        cout << "Moved piece from (" << startX + 1 << ", " << startY + 1 << ") to (" << endX + 1 << ", " << endY + 1 << ")." << endl;
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

    char command[10];
    while (true) 
    {
        cout << "> ";
        cin >> command;

        if (command[0] == 'm' && command[1] == 'o' && command[2] == 'v' && command[3] == 'e')
        {
            int startX, startY, endX, endY;
            cin >> startX >> startY >> endX >> endY;
            makeMove(startX - 1, startY - 1, endX - 1, endY - 1);
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
