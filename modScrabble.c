

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
 *       complete citations for Web or other written sources           *
 *      write "none" if no sources used]                               *
 *   Help obtained                                                     *
 *     [indicate names of instructor, class mentors                    *
 *      or evening tutors, consulted according to class policy;        *
 *      write "none" if none of these sources used]                    *
 *     ["none" or the instructor's name for Supplemental Problems      *
 *   My/our signature(s) below confirms that the above list of sources *
 *   is complete AND that I/we have not talked to anyone else          *
 *   (e.g., CSC 161 students) about the solution to this problem       *
 *                                                                     *
 *   Signature:                                                        *
 ***********************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Function Prototypes
int check_horizontal (char * word, int row, int col,
                      int num_rows, int num_cols, char board[num_rows][num_cols]);

int check_vertical (char * word, int row, int col,
                    int num_rows, int num_cols, char board[num_rows][num_cols]);

void createBoard(int num_rows, int num_cols);

void printNewBoard(int num_rows, int num_cols, char *board[num_rows][num_cols]);

void printNewBoard(int num_rows, int num_cols, char *board[num_rows][num_cols]);

void placeHorizontal(char * word, int row, int col,
                     int num_rows, int num_cols, char *board[num_rows][num_cols]);

void placeVertical(char * word, int row, int col,
                   int num_rows, int num_cols, char *board[num_rows][num_cols]);

int main()
{

    //variables for input
    char word[] = {};
    char drxn;
    int row;
    int col;
    int count;
    int wordlen;
    int num_rows;
    int num_cols;
    char board[num_rows][num_cols];
    
    
    /* Main logic for reading in words, orientation of said word, and location of the initial character of the word.
     
        The program first prompts the user to decide whether they will be choosing between Horizontal H or Vertical V orientation (drxn) by typing in 4. The program then reads in the orientation, and if H is entered the program checks Horizontally and, if valid, prints horizontally. If V is entered for orientation  then the program checks vertically and, if valid, prints vertically.
     
        If the user types in 2 after the first command prompt, the program will only give them the option to type in R, for random. This will randomly choose between horizontal H and vertical V orientation. It will then proceed to randomly place the word too.
     */
    while(1)
    {
        printf("Please enter the number of rows and columns for the board size: ");
        scanf("%d %d", &num_rows, &num_cols);
        
        printf("Please enter either 2 or 4 depending on the amount of words you plan on entering: \n");
        scanf("%d", &count);
        if(count == 4)
        {
            printf("Please enter a word: \n");
            scanf("%s", word);
            wordlen = strlen(word);
            
            printf("Now please enter H or V for the desired orientation of the word: \n");
            scanf(" %c", &drxn);
            
            //printf("You said: %s %c %d %d \n", &word, &drxn, &row, &col);
            if(drxn == 'H')
            {
                printf("Please enter the row and column where you want the word to begin: \n");
                scanf("%d %d", &row, &col);
                check_horizontal (word, row, col, num_rows, num_cols, board[num_rows][num_cols]);
                placeHorizontal(&word, row, col, num_rows, num_cols, &board[num_rows][num_cols]);
                printf("Adding word horizontally...");
            } else if(drxn == 'V')
            {
                printf("Please enter the row and column where you want the word to begin: \n");
                scanf("%d %d", &row, &col);
                check_vertical (word, row, col, num_rows, num_cols, board[num_rows][num_cols]);
                placeVertical(&word, row, col, num_rows, num_cols, &board[num_rows][num_cols]);
                printf("Adding word vertically...");
            }
        } else if(count == 2)
        {
            printf("\n Please enter a word: ");
            scanf(" %s", &word);
            printf("\n Now please enter R for a random orientation and placement: ");
            scanf(" %c", &drxn);
            int * a = rand() % 2;
            if(*a == 0)
            {
                check_horizontal (word, row, col, num_rows, num_cols, board[num_rows][num_cols]);
                placeHorizontal(&word, row, col, num_rows, num_cols, &board[num_rows][num_cols]);
            } else
            {
                check_vertical (word, row, col, num_rows, num_cols, board[num_rows][num_cols]);
                placeVertical(&word, row, col, num_rows, num_cols, &board[num_rows][num_cols]);
            }
            printf("Adding word at random...");
        } else
        {
            printf("Invalid! Please enter 2 or 4.");
        }
        return 0;
    }
}

//Logic for checking to see whether there are enough spaces horizontally in the grid to fit said word
int check_horizontal (char * word, int row, int col,
                      int num_rows, int num_cols, char board[num_rows][num_cols])
{
    for (int i = 0; i < col + strlen(word); i++)
    {
        if (board[i][num_cols] == word[i] || board[i][num_cols] == ' _ ')
        {
            return 1;
        }
        else //if (i > num_cols || (!board[i][num_cols] == word[i] || !board[i][num_cols] == ' _ '))
        {
            return 0;
        }
    }
}

//Logic for checking to see whether there are enough spaces vertically in the grid to fit said word
int check_vertical (char * word, int row, int col,
                    int num_rows, int num_cols, char board[num_rows][num_cols])
{
    for (int j = 0; j < col + strlen(word); j++)
    {
        if (board[num_rows][j] == word[j] || board[num_rows][j] == ' _ ')
        {
            return 1;
        }
        else //if (i > num_rows || (!board[num_rows][j] == word[j] || !board[num_rows][j] == ' _ '))
        {
            return 0;
        }
    }
}

//Initializes and prints the empty board as a 2D array
void createBoard(int num_rows, int num_cols)
{
    char *board[num_rows][num_cols];
    for (int i = 0; i < num_rows; i++)
    {
        for (int j = 0; j < num_cols; j++)
        {
            board[i][j] = ' _ ';
            printf("%c - ", board[i][j]);
        }
        printf("\n");
    }
    
}

//Prints a new board as a 2D array for the new board after the word is added
void printNewBoard(int num_rows, int num_cols, char *board[num_rows][num_cols])
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

//places the word into the 2d array board horizontally
void placeHorizontal(char * word, int row, int col,
                     int num_rows, int num_cols, char *board[num_rows][num_cols])
{
    for (int j = col; j < col + strlen(word); j ++)
    {
        board[row][j] = word[j - col];
    }
    printNewBoard(num_rows, num_cols, board[num_rows][num_cols]);
    
}

//places the word into the 2d array board vertically
void placeVertical(char * word, int row, int col,
                   int num_rows, int num_cols, char *board[num_rows][num_cols])
{
    for (int i = col; i < row + strlen(word); i ++)
    {
        board[i][col] = word[i - row];
    }
    printNewBoard(num_rows, num_cols, board[num_rows][num_cols]);
}

