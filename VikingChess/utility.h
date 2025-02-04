/*
Solution to course project # 7
Introduction to programming course
Faculty of Mathematics and Informatics of Sofia University
Winter semester 2024/2025

@author Kosta Ilev
@idnumber 4MI0600514
@compiler VC
<h file with helper functions>
*/
#ifndef UTILITY_H
#define UTILITY_H

#include <iostream>

void clearInputBuffer();
void deleteBoard(char** board, int size);
void deleteHistory(char*** history, int size);
void quitGame(int size, char** board, char*** history);

#endif