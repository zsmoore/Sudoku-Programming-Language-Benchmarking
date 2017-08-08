#ifndef _SOLVER_H_
#define _SOLVER_H_

/*
 *
 *  Header File for Sudoku Solver related methods
 *
 */

#define SIZE 9

/////////////////////
//  Checking


/////////////////////
//  File Reading
int **readGrid(char *filename);

/////////////////////
// Util 
void printGrid(int **);
void freeGrid(int **);

#endif
