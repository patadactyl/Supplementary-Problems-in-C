//
//  filterByColor.c
//  
//
//  Created by Patrick Charlton on 4/18/19.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_COLOR 11
#define MAX_INPUT 75

int main() {
    char color [MAX_COLOR];
    char filtered_color [MAX_COLOR];
    char input [MAX_INPUT];

    scanf("%s", color);
    /* print header for output */
    printf ("Table of Gemstone names, Color, Hardness, Specific Gravity, and the Refractive Index\n\n");
    printf ("       Gemstone Name       Color       Specific      Specific     Refractive\n");
    printf("                                       Hardness      Gravity         Index\n\n");

    
    FILE* fpin = popen("sort -b", "w"); // should check the result
    
    while (fgets(input, MAX_INPUT, stdin)) {
        sscanf(input + 22, "%s", filtered_color);
        if(!strcmp(filtered_color, color)) {
            fputs(input, fpin);
        }
        //in = fgetc(file);
    }
    pclose(fpin);
    
    return 0;
}


