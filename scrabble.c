

/***********************************************************************
 * Name(s)  Patrick Charlton                                           *
 * Box(s): e189                                                        *
 * Assignment name Supplemental Problem 1: Modified Scrabble           *
 *                                                                     *
 * Assignment for February 19, 2019;                                   *
 ***********************************************************************/

/* *********************************************************************
 * Academic honesty certification:                                     *
 *   Written/online sources used:                                      *
 *     [include textbook(s), CS 451 labs or readings;                  *
 *                                                                     *
 *       None                                                          *
 *   Help obtained                                                     *
 *     [indicate names of instructor, class mentors                    *
 *      or evening tutors, consulted according to class policy;        *
 *                                                                     *
 *     Henry Walker                                                    *
 *   My/our signature(s) below confirms that the above list of sources *
 *   is complete AND that I/we have not talked to anyone else          *
 *   (e.g., CSC 161 students) about the solution to this problem       *
 *                                                                     *
 *   Signature:                                                        *
 ***********************************************************************/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100

/****************************** Function Prototypes **************************************/

void createBoard(int row, int col, int num_rows, int num_cols,
                 char board[MAX][MAX], char word[MAX]);

int check_horizontal (int check, int row, int col, int num_rows, int num_cols,
                      char board[MAX][MAX], char word[MAX]);

int check_vertical (int check, int row, int col, int num_rows, int num_cols,
                      char board[MAX][MAX], char word[MAX]);

void printBoard(int num_rows, int num_cols, char board[MAX][MAX]);

void placeHorizontal(int row, int col, int num_rows, int num_cols,
                     char board[MAX][MAX], char word[MAX]);

void placeVertical(int row, int col, int num_rows, int num_cols,
                   char board[MAX][MAX], char word[MAX]);

/****************************** main logic ***********************************************/
int main()
{

    int row;
    int col;
    int num_rows;
    int num_cols;
    char board[MAX][MAX];
    char word[MAX];
    char drxn;
    char quit[] = {"QUITQUIT"};
    int check;
    
    printf("Please enter your board size: ");
    scanf("%d %d", &num_rows, &num_cols);
    
    //intializes board in memory, DOES NOT PRINT
    createBoard(row, col, num_rows, num_cols, board, word);
    
    printf("You may enter QUITQUIT in place of a word to exit the program...\n");
    
    //While loop to keep the program asking for more input words to be added to the scrabble board
    while(1)
    {
        printf("Please enter a word: ");
        scanf("%s", word);
        
        /* Checks to see if the word entered is QUITQUIT. If so the program will exit automatically,
            if not the program will run as normal */
        if(strcmp(word, quit) == 0)
        {
            printf("Exiting program...\n");
            return 0;
        } else
        {
            printf("Please enter H (horizontal), V (vertical), or R (random) for Orientation: ");
            scanf(" %c", &drxn);
            
            /* First checks to see if orientation entered is R. If so, no more input is asked for.
                The orientation and location of the first elemnt of word is randomized.
                If not the prgoram moves on for more input. */
            if(drxn == 'R')
            {
                for(int i = 0; i <strlen(word); i++)
                {
                    row = rand() % num_rows;
                    col = rand() % num_cols;
                }
                
                int a = rand() % 2;
                
                if(a == 1)
                {
                    check_horizontal(check, row, col, num_rows, num_cols, board, word);
                } else
                {
                    check_vertical(check, row, col, num_rows, num_cols, board, word);
                }
                printf("Randomizing...");
            } else
            {
                /* Program prompts further user input for the location of the first element in
                    the array, word. If 'H' is entered then the program will check horizontally
                    and print the word on the baord if it fits. If 'V' is entered then the program
                    will check vetically and print the word on the board if it fits. */
                printf("Please enter location: ");
                scanf("%d %d", &row, &col);
                
                if(drxn == 'H')
                {
                    check_horizontal(check, row, col, num_rows, num_cols, board, word);
                } else if(drxn == 'V')
                {
                    check_vertical(check, row, col, num_rows, num_cols, board, word);
                } else
                {
                    printf("Must enter valid orientation!");
                }
            }
        }
    }
}

/***************************** Function Definitions **************************************/

/* Initializes the board purely in memory. DOES NOT PRINT OUT BOARD but gives empty spaces the
    value of '.' to be printed once printBoard is called. */
void createBoard(int row, int col, int num_rows, int num_cols, char board[MAX][MAX], char word[MAX])
{
    for (int i = 0; i < num_rows; i++)
    {
        for (int j = 0; j < num_cols; j++)
        {
            board[i][j] = '.';
        }
    }
}

// Logic for checking to see whether there are enough spaces horizontally in the grid to fit said word.
int check_horizontal (int check, int row, int col, int num_rows, int num_cols,
                      char board[MAX][MAX], char word[MAX])
{
    check = 0;
    for (int i = col; i < col + strlen(word); i++)
    {
        if (i <= num_cols || (board[num_rows][i] == word[i] || board[num_rows][i] == '.'))
        {
            check = 1;
        } else
        {
            check = 0;
        }
    }
    if (check == 1)
    {
        printf("Word fits horizontally!\n");
        placeHorizontal(row, col, num_rows, num_cols, board, word);
    } else
    {
        printf("Out of horizontal bounds!\n");
    }
}

// Logic for checking to see whether there are enough spaces vertically in the grid to fit said word.
int check_vertical (int check, int row, int col, int num_rows, int num_cols,
                    char board[MAX][MAX], char word[MAX])
{
    check = 0;
    for (int j = row; j < row + strlen(word); j++)
    {
        if (j <= num_rows || (board[num_rows][j] == word[j] || board[num_rows][j] == '.'))
        {
            check = 1;
        } else
        {
            check = 0;
        }
    }
    if (check == 1)
    {
        printf("Word fits vertically!\n");
        placeVertical(row, col, num_rows, num_cols, board, word);
    } else
    {
        printf("Out of vertical bounds!\n");
    }
}

/*Nested for loops iterate through rows and columns of 2D array, board, and print the characters given
 for each index i and j. Empty characters will be printed as '.' and characters belonging to a word
 will be printed as such. */
void printBoard(int num_rows, int num_cols, char board[MAX][MAX])
{
    for (int i = 0; i < num_rows; i++)
    {
        for (int j = 0; j < num_cols; j++)
        {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}

/* If the word fits horizontally, the word will be placed horizontally into
the 2D array using the for loop then will be printed horizontally with the printBoard function. */
void placeHorizontal(int row, int col, int num_rows, int num_cols,
                     char board[MAX][MAX], char word[MAX])
{
    //horizontal placement
    for (int i = col; i < col + strlen(word); i ++)
    {
        board[row][i] = word[i - col];
    }
        printBoard(num_rows, num_cols, board);
}

/* If the word fits vertically, the word will be placed vertically into the 2D array using the for
 loop then will be printed vertically with the printBoard function. */
void placeVertical(int row, int col, int num_rows, int num_cols,
                   char board[MAX][MAX], char word[MAX])
{
    //vertical placement
    for (int i = row; i < row + strlen(word); i ++)
    {
        board[i][col] = word[i - row];
    }
    printBoard(num_rows, num_cols, board);
}


/* Functions deemed redundant after testing. Kept to show process
 

void randomize(int a, int row, int col, int num_rows, int num_cols, char board[MAX][MAX], char word[MAX])
{
    a = rand() % 2;
    
    for(int i = 0; i <strlen(word); i++)
    {
        row = rand() % num_rows;
        col = rand() % num_cols;
    }
    
    if(a == 1)
    {
        placeHorizontal(row, col, num_rows, num_cols, board, word);
    } else
    {
        placeVertical(row, col, num_rows, num_cols, board, word);
    }
    printf("Randomizing...");
}
 
*/
