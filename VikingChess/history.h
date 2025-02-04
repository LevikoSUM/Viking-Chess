/*
Solution to course project # 7
Introduction to programming course
Faculty of Mathematics and Informatics of Sofia University
Winter semester 2024/2025

@author Kosta Ilev
@idnumber 4MI0600514
@compiler VC
<h file with functions related to the history>
*/
#ifndef HISTORY_H
#define HISTORY_H

#include <iostream>

void changeBoardToPreviousFromHistory(char** board, char*** history, int moveCounter, int size);
void undoMove(char** board, char*** history, int& moveCounter, int size);
void addCurrentBoardToHistory(char** board, char*** history, int moveCounter, int size);

#endif
