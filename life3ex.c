/* 
 * LIFE3EX: A program containing the game of life. This version prints out the
 * board after every interval of total transformations based on command line input. 
 * Transformation depends on:
 *      - if 'O' adjoins < 2 or > 3 'O' cells, become 'X'
 *      - if 'O' adjoins 2 or 3 'O' cells, remains
 *      - if 'X' adjoins exactly 3 'O', becomes 'O'
 *      - else 'X' remains
 *
 * Matt Bishop, ECS 36A, Fall 2019
 * Answer to homework 3, question 4
 * 
 * Karl Goeltner, ECS 36A
 * November 25, 2019 - Added command line cell transformation functionality
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>

/*
 * Macros
 */
#define MAXCOLS 1000
#define MAXROWS 1000

/* Board dimensions */
int cols = MAXCOLS;
int rows = MAXROWS;

/* The board -- big enough to hold any reasonable size */
char board[MAXROWS][MAXCOLS];

/*
 * pboard -- Draw the outline and contents of the board
 */
void prboard(void) {

        int i, j;       /* Counters in for loops */

        /* Top border */
        for(i = 0; i < cols+2; i++)
                putchar('-');
        putchar('\n');

        /* Now the rows */
        for(i = 0; i < rows; i++){
                putchar('|');
                for(j = 0; j < cols; j++)
                        putchar(board[i][j]);
                putchar('|');
                putchar('\n');
        }

        /* Bottom border */
        for(i = 0; i < cols+2; i++)
                putchar('-');
        putchar('\n');
}

/*
 * transform -- Count the surrounding 'O' values and change board values accordingly
 * 
 * in parameters:
 * int n        Total number of generations, default 50
 * int p        Interval of printing generations, default 5
 */
void transform(int n, int p) {

        int gen = 0;    /* Generation counter */
        int i, j;       /* Counters in for loops */
        int ocnt = 0;   /* Counter for all O values */
        char tempBoard[MAXROWS][MAXCOLS];       /* Temporary board for storing values */

        /* Go through n generations of transformation */
        for(gen = 0; gen <= n; gen++) {

                /* Print out the board every pth generation, not going beyond n generations, always printing the last generation */
                if ((gen%p == 0 && gen <= n) || gen == n) {
                        printf("Generation %d:\n", gen);
                        prboard();
                }

                /* Traverse through board cells and increment 'O' count based on surrounding cells */
                for(i = 0; i < rows; i++) {
                        for(j = 0; j < cols; j++) {

                                /* Reset 'O' counter to 0 for each cell value */
                                ocnt = 0;

                                /* First row, first column */
                                if (i == 0 && j == 0) {
                                        if (board[i][j+1] == 'O')
                                                ocnt++;
                                        if (board[i+1][j] == 'O')
                                                ocnt++;
                                        if (board[i+1][j+1] == 'O')
                                                ocnt++;
                                }
                                /* First row, last column */
                                else if (i == 0 && j == cols-1) {
                                        if (board[i][j-1] == 'O')
                                                ocnt++;
                                        if (board[i+1][j-1] == 'O')
                                                ocnt++;
                                        if (board[i+1][j] == 'O')
                                                ocnt++;
                                }
                                /* Last row, first column */
                                else if (i == rows-1 && j == 0) {
                                        if (board[i-1][j] == 'O')
                                                ocnt++;
                                        if (board[i-1][j+1] == 'O')
                                                ocnt++;
                                        if (board[i][j+1] == 'O')
                                                ocnt++;
                                }
                                /* Last row, last column */
                                else if (i == rows-1 && j == cols-1) {
                                        if (board[i-1][j] == 'O')
                                                ocnt++;
                                        if (board[i-1][j+1] == 'O')
                                                ocnt++;
                                        if (board[i][j+1] == 'O')
                                                ocnt++;
                                }
                                /* First column */
                                else if (j == 0) {
                                        if (board[i-1][j] == 'O')
                                                ocnt++;
                                        if (board[i-1][j+1] == 'O')
                                                ocnt++;
                                        if (board[i][j+1] == 'O')
                                                ocnt++;
                                        if (board[i+1][j] == 'O')
                                                ocnt++;
                                        if (board[i+1][j+1] == 'O')
                                                ocnt++;
                                }
                                /* Last column */
                                else if (j == cols-1) {
                                        if (board[i-1][j] == 'O')
                                                ocnt++;
                                        if (board[i-1][j-1] == 'O')
                                                ocnt++;
                                        if (board[i][j-1] == 'O')
                                                ocnt++;
                                        if (board[i+1][j] == 'O')
                                                ocnt++;
                                        if (board[i+1][j-1] == 'O')
                                                ocnt++;
                                }
                                /* First row */
                                else if (i == 0) {
                                        if (board[i][j-1] == 'O')
                                                ocnt++;
                                        if (board[i][j+1] == 'O')
                                                ocnt++;
                                        if (board[i+1][j-1] == 'O')
                                                ocnt++;   
                                        if (board[i+1][j] == 'O')
                                                ocnt++;   
                                        if (board[i+1][j+1] == 'O')
                                                ocnt++;
                                }
                                /* Last row */
                                else if (i == rows-1) {
                                        if (board[i][j-1] == 'O')
                                                ocnt++;
                                        if (board[i][j+1] == 'O')
                                                ocnt++;
                                        if (board[i-1][j-1] == 'O')
                                                ocnt++;   
                                        if (board[i-1][j] == 'O')
                                                ocnt++;   
                                        if (board[i-1][j+1] == 'O')
                                                ocnt++;
                                }
                                /* Any other case */
                                else {
                                        if (board[i-1][j-1] == 'O')
                                                ocnt++;
                                        if (board[i-1][j] == 'O')
                                                ocnt++;
                                        if (board[i-1][j+1] == 'O')
                                                ocnt++;
                                        if (board[i][j-1] == 'O')
                                                ocnt++;
                                        if (board[i][j+1] == 'O')
                                                ocnt++;                                        
                                        if (board[i+1][j-1] == 'O')
                                                ocnt++;
                                        if (board[i+1][j] == 'O')
                                                ocnt++;
                                        if (board[i+1][j+1] == 'O')
                                                ocnt++;
                                }

                                /* Save the revised values based on:
                                 *      - if 'O' adjoins < 2 or > 3 'O' cells, become 'X'
                                 *      - if 'O' adjoins 2 or 3 'O' cells, remains
                                 *      - if 'X' adjoins exactly 3 'O', becomes 'O'
                                 *      - else 'X' remains
                                 * into a temporary board array
                                */
                                if (board[i][j] == 'O' && (ocnt < 2 || ocnt > 4))
                                        tempBoard[i][j] = 'X';
                                else if (board[i][j] == 'O' && (ocnt == 2 || ocnt == 3))
                                        tempBoard[i][j] = 'O';
                                else if (board[i][j] == 'X' && ocnt == 3)
                                        tempBoard[i][j] = 'O';
                                else
                                        tempBoard[i][j] = 'X';

                        }
                }

                /* Save the temporary board values into the final board */
                for(i = 0; i < rows; i++) {
                        for(j = 0; j < cols; j++) {
                                board[i][j] = tempBoard[i][j];
                        }
                }
        }
}

/*
 * main -- Read a file name from the standard input, open it, scan & store characters,
 *         transform the board values accordingly and print the board every 5 generations
 * 
 * in parameters:
 * int argc             count of arguments
 * char *argv[]         array to store inputted arguments from command line
 * 
 * out parameters:
 * int                  0 for success, 1 for failure of program 
 */
int main(int argc, char *argv[]) {

        int n = 0;          /* Number of numbers read */
        int total = 50;     /* Total number of generations, default 50 */
        int interval = 5;   /* Interval of printing generations, default 5 */
        int option = 0;     /* Options p or n for the command line*/
        FILE *inpf;         /* Input file containing board pattern */

        /* 1) Check to see if you can read in the file pattern */
        if ((inpf = fopen(argv[argc-1], "r")) == NULL) {
                perror(argv[1]);
                return(1);
        }

        /* 2) Go through the command line input and check for n and p values 
        *   - n -- total number of generations
        *   - p -- number of intervals
        */
        while((option = getopt(argc, argv, "n:p:")) != -1) {
          switch(option){
             case 'p':
                interval = atoi(optarg);
                break;
             case 'n':
                total = atoi(optarg);
                break;
             case ':':
                fprintf(stderr, "%s: %c must be followed by a positive number\n", argv[0], option);
                break;
             default: /* '?' */
                fprintf(stderr, "%s: %c: invalid option\n", argv[0], option);
                return(1);
          }
        }

        /* 3) Store board pattern from input file into array, increment through each character */
        for(rows = 0; fgets(board[rows], MAXCOLS, inpf) != NULL; rows++) {

                n = strlen(board[rows]);        /* Save in the number of columns */
                
                /* If the final character is \n, replace it with \0 null character */
                if (board[rows][n-1] == '\n') {
                        board[rows][n-1] = '\0';
                        n -= 1;
                }

                /* If on row 0, set the set number of columns for following rows */
                if (rows == 0) {
                        /* Set the number of columns */
                        cols = n;
                }
                else {
                        /* Check that the row length is right */
                        if (n != cols){
                                fprintf(stderr, "%s: line %d is wrong length\n", argv[1], rows+1);
                                return(1);
                        }
                }

                /* Now check each character if 'X' or 'O' */
                for(n = 0; n < cols; n++) {
                        /* End program if cell value is ot 'X' or 'O' */
                        if (board[rows][n] != 'X' && board[rows][n] != 'O') {
                                fprintf(stderr, "%s: bad character '%c' in line %d\n", argv[1], board[rows][n], rows+1);
                                return(1);
                        }
                }
        }

        /* Transform the board for 'total' generations printing at every 'interval'*/
        transform(total, interval);

        /* Done! */
        return(0);
}
