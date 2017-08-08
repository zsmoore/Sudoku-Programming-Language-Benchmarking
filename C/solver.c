/*
 *
 * C file for Solver functions
 *
 */

#include "solver.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/////////////////////////
//   File Reading
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
    printGrid(board);
    freeGrid(board);   
}
