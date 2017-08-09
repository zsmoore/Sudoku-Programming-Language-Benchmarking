#ifndef _SOLVER_H_
#define _SOLVER_H_

/*
 *
 *  Header File for Sudoku Solver related methods
 *
 */

#include <stdbool.h>

#define SIZE 9

/////////////////////
//  Checking
bool inRow(int **, int, int);
bool inCol(int **, int, int);
bool inSquare(int **, int, int, int);
bool safeToPlace(int **, int, int, int);

/////////////////////
// Solving
bool solveSudoku(int **);
bool findEmpty(int **, int *, int *);

/////////////////////
//  File Reading
int **readGrid(char *filename);

/////////////////////
// Util 
void printGrid(int **);
void freeGrid(int **);

#endif
