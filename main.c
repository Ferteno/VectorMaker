#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "myfunctions.h"
#define GOOD_EXIT 1
#define BAD_EXIT 0
//I certify that this assignment is entrely my own work

//Main exection function
//Function is executed when file is run
//Takes input from user
//Returns value indicating whether errors during runtime or not (1, bad, 0 good)
int main()
{
    int exitCode = GOOD_EXIT; //tracks exitcode, returned at termination
    int totVSize = 0; //tracks size of vector
    int curVSize = 0; //tracks the number of current elements in vector
    char input[MAX_INPUT + 1]; //string receives input from stdin
    float *vect; //vector array

    //while llop does not terminate until user input
    //read user input and execute accordingly
    while (1 == 1)
    {
        fgets(input, MAX_INPUT, stdin);
        //terminate on '0' or 'EOF' input
        if (input[0] == '0')
        {
            return exitCode;
        }
        else if (input[0] == 'E' && input[1] == 'O' && input[2] == 'F')
        {
            return exitCode;
        }
        else if (strlen(input) <= 1)
        {
        }
        else
        {
            //if both size variables are 0, treat input as new vector, else continue adding to prev vector
            if (curVSize == 0 && totVSize == 0)
            {
                totVSize = getVSize(input);
                //if getVSize returns 0, then something went wrong, change exitCode
                if (totVSize == 0) { exitCode = BAD_EXIT;}
                else
                {
                    //allocate storage for vect of totVSize and process input
                    vect = malloc(sizeof(float) * totVSize);
                    curVSize = processLine(input, totVSize, curVSize, vect, SKIP_FIRST);
                }
            }
            else
            {
                curVSize = processLine(input, totVSize, curVSize, vect, BEGINNING_LINE);
            }
            //if curVSize equals -1, something went wrong, change exitCode
            if (curVSize == -1)
            {
                totVSize = 0;
                curVSize = 0;
                exitCode = BAD_EXIT;
            }
        }
        //if the size of current elements equals total size (not zero), normalize vector
        //and print output
        if (curVSize == totVSize && totVSize != 0)
        {
            float normVect[totVSize]; //stores the normalized vector
            normalizeVect(vect, normVect, calcNorm(vect, totVSize), totVSize);
            printf("VECTOR: ");
            printVector(makeVectorString(vect, totVSize));
            printf(" NORMALIZED: ");
            printVector(makeVectorString(normVect, totVSize));
            printf("\n");
            curVSize = 0;
            totVSize = 0;
        }
    }
}
