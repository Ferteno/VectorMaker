#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#define GOOD_EXIT 1
#define BAD_EXIT 0
#define MAX_INPUT 60
#define BEGINNING_LINE 0
#define SKIP_FIRST 2
//prototypes
int processLine(char *input, int totVSize, int curVSize, float *vect, int startI);
char * makeVectorString(float *nums, int totsize);
void printVector(char * vect);
int getVSize(char *input);
float calcNorm(float *vect, int vSize);
void normalizeVect(float *vect, float *normVect, float norm, int vSize);

//getVSize
//handles obtaining vector size from user
//returns an integer of the vector size
//takes in string input
//may output BAD INPUT, specifying user error
int getVSize(char *input)
{
    int i = 0; //index for iterating thru input
    char num[MAX_INPUT] = " "; //string for storing digit characters
    int j = 0; //index for tracking num string
    int vSize = 0; //stores the index for size of vector
    //while the characters of input are digits loop thru
    //and store the char to num
    while ((input[i] > '0' && input[i] <= '9'))
    {
        num[j] = input[i];
        j++;
        i++;
    }
    //if the character after looping is anything but a digit or space,
    //print bad input & return 0
    if (!((input[i] > '0' && input[i] <= '9') || input[i] == 10 || input[i] == ' '))
    {
        printf("BAD INPUT\n");
        return 0;
    }
    else
    {
        vSize = atoi(num);
        if (vSize > 0 && vSize <= 9)
        {
            return vSize;
        }
        else
        {
            printf("BAD INPUT\n");
            return 0;
        }
    }
}

//proccessLine
//process the string input to convert information to vector data
//returns integer of the current size of the vector
//takes in a string input, integer of total vector size and current vector size, float array for vector, and integer of starting index for processing
//may output BAD INPUT specifying user error
int processLine(char *input, int totVSize, int curVSize, float *vect, int startI)
{

    int i = startI; //tracks index of input
    while (i < strlen(input))
    {
        //if input contains anything except [0-9+-. ] print BAD INPUT and return -1 specifying error
        if (!((input[i] >= '0' && input[i] <= '9') || input[i] == ' ' ||
                input[i] == '+' || input[i] == '-' || input[i] == 10 || input[i] == '.'))
        {
            printf("BAD INPUT\n");
            return -1;
        }

        char num[MAX_INPUT] = " "; //string to store appropriate characters for conversion to float
        int j=0; //index for iterating thru num string
        //while the input is only [0-9+-.] and end of string is not reached
        while (((input[i] >= '0' && input[i] <= '9')
                 || input[i] == '+' || input[i] == '-'|| input[i] == 10
                 || input[i] == '.') && i < strlen(input))
        {
            //add characters to num string
            num[j] = input[i];
            j++;
            i++;
        }
        //if num is non-empty and current size < total size
        //convert num and add to vector, increment current size
        if (strcmp(num, " ") != 0 && curVSize < totVSize){
            vect[curVSize] = atof(num);
            curVSize++;
            i--;
        }
        if (curVSize == totVSize)
        {
            return curVSize;
        }
        i++;
    }
    return curVSize;
}

//calcNorm
//calculate norm (length) of specified vector
//takes in array of floats and size
//returns float representing norm
float calcNorm(float *vect, int vSize)
{
    int i = 0; //index for for-loop
    float tot; //float for tracking and holding norm
    for (i = 0; i < vSize; i++)
    {
        tot+=pow(vect[i], 2);
    }
    tot = sqrt(tot);
    return tot;
}

//normalizeVect
//normalizes a vector
//takes in a float array of orginal vector and normalize vector, float norm value, and int size of vector
void normalizeVect(float *vect, float *normVect, float norm, int vSize)
{
    int i = 0;
    for (i = 0; i < vSize; i++)
    {
        normVect[i] = (vect[i] / norm);
    }

}

//printVector
//prints vector in specified format
//takes in a vector in string form
//outputs vector in proper format
void printVector(char * vect)
{
    printf("[%s]", vect);
}

//makeVectorString
//converts a float array to string form
//takes in float array and size of array
//returns a string version of vector
char* makeVectorString(float *nums, int totsize)
{
    static char temp[MAX_INPUT * 2]; //string for storing output
    temp[0] = '\0'; //reset temp to empty
    int i=0; //index for for-loop
    for (i=0;i<totsize;i++)
    {
        char temp2[10]; //string that stores indivdual floats
        sprintf(temp2, "%.3f, ", nums[i]);
        strcat(temp, temp2);
    }
    //add null character to specify end
    temp[strlen(temp)-2] = '\0';
    return temp;
}
