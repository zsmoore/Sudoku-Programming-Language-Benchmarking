/*
 *
 * C file for Solver functions
 *
 */

#include "solver.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

/////////////////////////
//  Checking
// Check if number already exists in row
bool
inRow(int **grid, int row, int num) {
    int i;
    for (i = 0; i < SIZE; i++) {
        if (grid[row][i] == num) {
            return true;
        }
    }
    return false;
}

// Check if number already exists in col
bool
inCol(int **grid, int col, int num) {
    int i;
    for (i = 0; i < SIZE; i++) {
        if (grid[i][col] == num) {
            return true;
        }
    }
    return false;
}

// Check if number already exists in Square
bool
inSquare(int **grid, int row, int col, int num) {
    int i, j;
    for (i = 0; i < (int) sqrt((double) SIZE); i++) {
        for (j = 0; j < (int) sqrt((double) SIZE); j++) {
            if (grid[i + row][j + col] == num) {
                return true;
            }
        }
    }
    return false;
}

// Boolean to check all our checkers
bool
safeToPlace(int **grid, int row, int col, int num) {
    return !inRow(grid, row, num)
        && !inCol(grid, col, num)
        && !inSquare(grid,
                     row - row % 3,
                     col - col % 3,
                     num);
}


/////////////////////////
// Solving
// Takes in 2d int grid and backtraces until solution or no solution
bool
solveSudoku(int **grid) {
    int row = 0;
    int col = 0;
    if (!findEmpty(grid, &row, &col)) {
        return true;
    }

    int num;
    for (num = 1; num < SIZE + 1; num++) {
        if (safeToPlace(grid, row, col, num)) {
            grid[row][col] = num;
            if (solveSudoku(grid)) {
                return true;
            }
            grid[row][col] = 0;
        }
    }
    return false;
}

// Takes in grid and two int pointer, if grid is solved return false.
// Else return true and assign int pointers to empty spot
bool
findEmpty(int **grid, int *row, int *col) {
    int i, j;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            if (grid[i][j] == 0) {
                *row = i;
                *col = j;
                return true;
            }
        }
    }
    return false;
}

/////////////////////////
//   File Reading
// Read in Grid from filename and return in double pointer
int **
readGrid(char *filename) {
    
    int i;
    int **ret = malloc(SIZE * sizeof(int *));
    for (i = 0; i < SIZE; i++) {
        ret[i] = malloc(SIZE * sizeof(int));
    }
    
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("No Such File Exists\n");
        freeGrid(ret);
        exit(0);
    }

    char *line = malloc(100);
    size_t count;
    int j ;
    i = -1;
    while (getline(&line, &count, fp) != -1) {
        //Pre check our colums so we don't segFault
        if (i++ > SIZE) {
            printf("Too many columns\n");
            
            freeGrid(ret);
            free(line);
            fclose(fp);
            exit(0);
        }

        j = -1;
        line = strtok(line, " ");
        while (line != NULL) {
            //Pre Check our rows so we don't segFault
            if (j++ > SIZE) {
                printf("Too many elements in a row\n");
                
                freeGrid(ret);
                free(line);
                fclose(fp);
                exit(0);
            }
            ret[i][j] = atoi(line);
            line = strtok(NULL, " "); 
        }
    }

    fclose(fp);
    return ret;
}


/////////////////////////
//  Util
// Print out 2d grid
void
printGrid(int **grid) {

    int i, j;
    for (i = 0; i < SIZE; i++) {
        printf("[");
        for (j = 0; j < SIZE; j++) {
            printf("%d ", grid[i][j]);
        }
        printf("]\n");
    }
}

// Free 2d Grid of ints
void
freeGrid(int **grid) {
    int i, j;
    for (i = 0; i < SIZE; i++) {
        free(grid[i]);
    }
    free(grid);
}


int
main(int argc, char *argv[]) {

    if (argc != 2) {
        printf("Incorrect number of args\n");
        exit(0);
    }
    
    int **board = readGrid(argv[1]);
    if (solveSudoku(board)) {        
        printGrid(board);
    } else {
        printf("Impossible to solve!\n");

    }
    freeGrid(board);   
}
