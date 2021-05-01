/****************************************************************
 * Name(s)  Patrick Charlton                                    *
 * Box(s):  E189                                                *
 * Assignment name Test: Supplemental Problem 3: Gemstones      *
 *      (25% off if name/number does not match assignment)      *
 * Assignment for Tuesday April 16, 2019;                       *
 ***************************************************************/

/* **************************************************************
 * Academic honesty certification:                              *
 *   Written/online sources used:                               *
 *   Silberschatz, Abraham. Operating Systems Concepts. 9th     *
 *   edition                                                    *
 *                                                              *
 *   http://www.cs.grinnell.edu/~walker/courses/451.sp19-       *
 *   willamette/labs/lab-semaphores.php                         *
 *   Help obtained                                              *
 *     Professor Henry Walker                                   *
 *   My/our signature(s) below confirms that the above list of  *
 *  sources is complete AND that I/we have not talked to        *
 *       anyone else                                            *
 *   (e.g., CSC 161 students) about the solution to this        *
 *  problem                                                     *
 *                                                              *
 *   Signature:                                                 *
 *                                                              *
 ***************************************************************/

/*
 reads input (color desired, lower and upper bounds for desired hardness, lower and upper bounds for specific gravity) from stdin
 using pipe/fork, spawns process to run utility cat program, which will send file data to control/main on a file input
 using pipe/fork, spawns process to read data from control/main through a pipe, and to filter only those records that have an appropriate hardness and specific gravity. (If desired, the control/main program may send the hardness and specific gravity ranges to the child through the pipe, before sending the gemstone data. Alternatively, if desired, these values may be saved as global variables or transmitted as command-line parameters, so they would be available to any child process.)
 using popen, spawns process to read data from control/main through stdin and filters only records for a designated color. (If desired, the control/main program may send the desired color through the pipe, before sending the gemstone data. Alternatively, if desired, these values may be saved as global variables or transmitted as command-line parameters, so they would be available to any child process.)
 */

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define MAX_COLOR 11 /* maximum size allocated for name of color to use for filter */
#define MAX_INPUT 75 /* maximum size allocated for each line in gems.txt */

int main (void)
{
    FILE *fpout; /* file variables for main process I/O */
    char color [MAX_COLOR];
    char input [MAX_INPUT];
    char ch; /* current character being processed */
    int i; /* index variable */
    
    /* variables for user input */
    int lowH;
    int highH;
    int lowG;
    int highG;
    
    int pipe_fd[2];     /* provide file descriptor pointer array for pipe */
                        /* within pipe: pipe_fd[0] will be input end pipe_fd[1]
                         will be output end */
    int pipe_main[2];
    
    pid_t pid1, pid2;        /* process id’s for each child */

    
    
    /* User input for filter by color */
    printf("Please enter desired color: ");
    scanf(" %s", color);
    
    /* User input for filter by properties */
    printf("Please enter desired range for Specific Hardness from low to high: \n");
    scanf("%d %d", &lowH, &highH);
    printf("Please enter desired range for Specific Gavity from low to high: \n");
    scanf("%d %d", &lowG, &highG);
    
    /* print header for output */
    printf ("Table of Gemstone names, Color, Hardness, Specific Gravity, and the Refractive Index\n\n");
    printf ("       Gemstone Name       Color       Specific      Specific     Refractive\n");
    printf("                                       Hardness      Gravity         Index\n\n");
    fflush(stdout); /* be sure headers printed before proceeding */
    
    if (pipe (pipe_fd) < 0) {       /* Create pipe and check for error */
        perror("pipe error");
        exit (1);
    }
    
    if ((pid1 = fork()) < 0) {      /* Create fork and check for error */
        perror ("error in fork");
        exit (1);
    }
    
    /* filter by properties */
    if (0 == pid1)
    { // processing for child
        printf ("The first child process is active.\n");
        close (pipe_fd[1]); // close output end, leaving input open
        if (pipe_fd[0] != STDIN_FILENO) // set standard input to pipe
        {
            if (dup2(pipe_fd[0], STDIN_FILENO) != STDIN_FILENO) {
                perror("dup2 error for standard input");
                exit(1);
            }
            close(pipe_fd[0]); // not needed after dup2
        }
        execlp ("./filterByProp", "filterByProp", (char *) 0);
        printf ("First child finished\n");
        
    }
    else
    {   // processing for parent
        printf ("The parent process continues.\n");
        // spawn second process
        if (pipe (pipe_main) < 0) {  // Create pipe and check for error
            perror("pipe error");
            exit (1);
        }
        if ((pid2 = fork()) < 0)   // apply fork again for second child/
        {
            perror ("error in fork");
            exit (1);
        }
        
        if (0 == pid2)
        { // processing for second child
            printf ("The second child process is active.\n");
            close (pipe_fd[0]);
            close (pipe_fd[1]);
            close (pipe_main[0]); // close input end, leaving output open
            if (pipe_main[1] != STDOUT_FILENO) {
                if (dup2(pipe_main[1], STDOUT_FILENO) != STDOUT_FILENO) {
                    perror("dup2 error for standard output");
                    exit(1);
                }
                close(pipe_main[1]); // not needed after dup2
            }
            execlp("cat", "cat", "gems.txt", (char *) 0);
            // print to the pipe, now standard output
        }
        
        /* use popen to set up pipe, fork, bind one end of pipe to stdin and other to
            stdout then open file filterByColor */
        fpout = popen("./filterByColor", "w");
        if (fpout == NULL) {
            perror("error in opening filterByColor");
            exit(1);
        }
        
        close(pipe_fd[0]);
        if (pipe_fd[1] != STDOUT_FILENO) // set standard output to pipe
        {
            if(dup2(pipe_fd[1], STDOUT_FILENO) != STDOUT_FILENO) {
                perror("dup2 error for standard output");
                exit(1);
            }
            close (pipe_fd[1]);
        }
        //print to pipes to fbc and fbp
        fprintf(fpout, "%s", color);
        printf("%d %d", lowH, highH);
        printf("%d %d", lowG, highG);
        
        while (fgets(input, MAX_INPUT, stdin) != NULL) {
            fprintf (stderr, "loop:  %s\n", input);
            printf("%s", input);   //writes to pipe going to filterByProp
            fprintf(fpout, "%s", input);    //writes to pipe going to filterByColor
        }
        
        printf ("Parent closing its pipe ends: parent does not use pipe\n");
        printf ("Parent waits for both children to finish.\n");
        waitpid (pid1, NULL, 0); /* wait for first child to finish */
        waitpid (pid2, NULL, 0); /* wait for second child to finish */
        printf ("Parent finished.\n");

    }
    
    exit (0);
    
}
    




