//------------------------------------------------------------------
// University of Central Florida
// CIS3360 - Fall 2016
// Program Author: Subhash Naidu
//------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int convert(char c);
int main(int argc, const char *argv[])
{
    char *inputfilename = malloc(sizeof(char));
    char keyword[11];
    char vector[11];
    char cleantxt[5000];
    char inputchar = NULL;
    int workarray[11];
    FILE *ifp;
    int i = 0;
    int j = 0;

    strcpy(inputfilename, argv[1]);
    strcpy(keyword, argv[2]);
    strcpy(vector, argv[3]);

    ifp = fopen(inputfilename, "r");
    if (ifp == 0)
    {
        puts("Sorry could not open file.");
        exit(1);
    }


    while (inputchar != EOF)
    {
        inputchar = getc(ifp);
        //scanning input from file.
        if (isupper(inputchar) == 1 && isalpha(inputchar) == 1)
        {
            cleantxt[i] = tolower(inputchar);
            i++;
        }
        else if(islower(inputchar) == 1 && isalpha(inputchar) == 1)
        {
            cleantxt[i] = inputchar;
            i++;
        }
    }
    fclose(ifp);

    for (i = 0; i < strlen(cleantxt); i++)
    {
        int k = 0;
        for (j = (i - strlen(vector)); (i % strlen(vector)) == 0; j++)
        {
            //workarray[] = convert(cleantxt[i]);
            printf("%d\n",workarray[k]);
            k++;
        }

    }


    return 0;
}

int convert(char c)
{
    int n = -1;
    char * const alphabet = "abcdefghijklmnopqrstuvwxyz";
    char *p = strchr(alphabet, c);

    if (p)
    {
        n = p - alphabet;
    }
    return n;
}
