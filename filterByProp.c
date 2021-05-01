//
//  filterByProp.c
//  
//
//  Created by Patrick Charlton on 4/19/19.
//

#include <stdio.h>
#define MAX_INPUT 75

int findRange(char*, int);  //return first index of char

int main() {
    
    int lowH, highH, lowG, highG;
    double h = 0;
    double g = 0;
    
    scanf("%d %d", &lowH, &highH);
    scanf("%d %d", &lowG, &highG);
    /* print header for output */
    printf ("Table of Gemstone names, Color, Hardness, Specific Gravity, and the Refractive Index\n\n");
    printf ("       Gemstone Name       Color       Specific      Specific     Refractive\n");
    printf("                                       Hardness      Gravity         Index\n\n");
    
    FILE *file = fopen("gems.txt","w"); //open file in read mode
    char input[MAX_INPUT];
    
    while (fgets(input, MAX_INPUT, stdin)) {
        scanf(input + 32, "%lf %lf", &g, &h);
        if (((h >= lowH) && (h <= highH)) && ((g >= lowG) && (g <= highG))) {
            printf("%s", input);
        }
    }
    return 0;
}
