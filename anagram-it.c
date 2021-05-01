/****************************************************************
 * Name(s)  Patrick Charlton                                    *
 * Box(s):  E189                                                *
 * Assignment name Test: Supplemental Problem 5: Anagrams       *
 *      (25% off if name/number does not match assignment)      *
 * Assignment for Tuesday April 16, 2019;                       *
 ***************************************************************/

/* **************************************************************
 * Academic honesty certification:                              *
 *   Written/online sources used:                               *
 *   Silberschatz, Abraham. Operating Systems Concepts. 9th     *
 *   edition                                                    *
 *                                                              *
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

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define STR_MAX 40

int delete(int index, char str[STR_MAX]);

int main () {
    
    /* set up variables for both strings and their indeces */
    char str1[STR_MAX];
    char str2[STR_MAX];
    int i = 0;
    int j = 0;
    
    /* prompt and read user input */
    printf("Please enter two strings (40 characters max) in the following lines... \n");
    printf("Line 1: \n");
    fgets(str1, STR_MAX, stdin);
    printf("Line 2: \n");
    fgets(str2, STR_MAX, stdin);
    
    
    if(strlen(str1)!=strlen(str2))  /* if the lengths of two strings are not equal
                                        obviously not an anagram */
    {
        printf("Strings are not anagrams\n");
        exit(0);
    }
    
    /* first while loop iterates through string 1 */
    while (str1[i] != '\0') {
        /* second while loop iterates through string 2 */
        while (str2[j] != '\0') {
            /* if the selected elements in both strings match,
                delete both */
            if (str1[i] == str2[j]) {
                delete(i, str1);
                delete(j, str2);
                j = 0;
                
            } else {
                j++;
                
            }
        }
        /* if the selected element in string 1 doesn't match
            any in string 2, obviously not an anagram */
        if (str1[i] != str2[j]) {
            i++;
            break;
        }
    }
    
    /* Print out what elements are left in both strings after deletion */
    printf("String 1: %s\n", str1);
    printf("String 2: %s\n", str2);
    
    if (((strlen(str1)) != 0) && ((strlen(str2) != 0))) {
        printf("Strings are not anagrams\n");
    }
    else {
        printf("Strings are anagrams\n");
    }
    
    
    return 0;
    
}

/* delete characters in both strings if they match */
int delete(int index, char str[STR_MAX]) {
    /* set k to the index for str1 or str2 in main
        (i or j respectively) */
    int k = index;
    /* move the selected element to the right past
      the null character to delete */
    while (str[k] != '\0') {
        str[k] = str[k + 1];
        k++;
    }
    str[k] = '\0';
    return index;
}

