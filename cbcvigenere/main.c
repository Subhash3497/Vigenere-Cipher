//------------------------------------------------------------------
// University of Central Florida
// CIS3360 - Fall 2016
// Program Author: Subhash Naidu
//------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
//Auxiliary function i created to convert letters into numbers.
int converttonum(char c);

int main(int argc, const char *argv[])
{
    char *inputfilename = malloc(sizeof(char));
    char inputkeyword[11];
    int transkeyword[11];
    char inputvector[11];
    int transvector[11];
    char cleantxt[5000];
    char ciphertext[5000];
    int cipherblock[11];
    char inputchar = NULL;
    int workarray[11];
    FILE *ifp;
    int i = 0;
    int j = 0;
    int padchar = 0;

    //Copying commmand line arguments into local variables.
    strcpy(inputfilename, argv[1]);
    strcpy(inputkeyword, argv[2]);
    strcpy(inputvector, argv[3]);
    
    //opening file and error checking.
    ifp = fopen(inputfilename, "r");
    if (ifp == 0)
    {
        puts("Sorry could not open file.");
        exit(1);
    }
    
    //Initializing the integer arrays.
    for (i = 0; i < 11; i++)
    {
        workarray[i] = 0;
    }
    
    for (i = 0; i < 11; i++)
    {
        transkeyword[i] = 0;
    }
    
    for (i = 0; i < 11; i++)
    {
        transvector[i] = 0;
    }
    
    for (i = 0; i < 11; i++)
    {
        cipherblock[i] = 0;
    }
    
    
    //Initializing Char arrays.
    for (i = 0; i < 5000; i++)
    {
        ciphertext[i] = '\0';
    }
    for (i = 0; i < 5000; i++)
    {
        cleantxt[i] = '\0';
    }
    
    
    //Translating keyword letters into numeric values
    for (i = 0; i < strlen(inputkeyword); i++)
    {
        transkeyword[i] = converttonum(inputkeyword[i]);
    }
    
    //Translating vector letters into numeric values
    for (i = 0; i < strlen(inputvector); i++)
    {
        transvector[i] = converttonum(inputvector[i]);
    }
    i = 0;
    
    //Cleaning up input file by removing extraneous spaces capital letters and symbols.
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
    
    //Padding with x
    while ((strlen(cleantxt) % strlen(inputvector)) != 0)
    {
        padchar++;
        strcat(cleantxt, "x" );
    }

    //Encryption Loop -- takes string of size block length and encrypts the text and puts it into the ciphertext array.
    for (i = 0; i <= strlen(cleantxt); i++)
    {
        //Block 1 Encryption
        if (i % strlen(inputvector) == 0 && i <= strlen(inputvector))
        {
            int k = i - strlen(inputvector);
            for (j = 0; j < strlen(inputvector); j++)
            {
                workarray[j] = converttonum(cleantxt[k]);
                k++;
            }
            for (k = 0; k < strlen(inputvector); k++)
            {
                int workval = workarray[k];
                int ivval = transvector[k];
                cipherblock[k] = ((workval + ivval) % 26);
            }
            for (k = 0; k < strlen(inputvector); k++)
            {
                int cipherval = cipherblock[k];
                int keyval = transkeyword[k];
                cipherblock[k] = (((cipherval + keyval) % 26) + 97);
            }
            
            for (int p = (i - strlen(inputvector)), j = 0; j < strlen(inputvector) ; p++, j++)
            {
                ciphertext[p] = cipherblock[j];
            }
            
            for (k = 0; k < strlen(inputvector); k++)
            {
                cipherblock[k] = cipherblock[k] - 97;
            }
        }//Block 2+ encryption
        else if (i % strlen(inputvector) == 0 && i >= strlen(inputvector))
        {
            int k = i - strlen(inputvector);
            for (j = 0; j < strlen(inputvector); j++)
            {
                workarray[j] = converttonum(cleantxt[k]);
                k++;
            }
            for (k = 0; k < strlen(inputvector); k++)
            {
                int workval = workarray[k];
                int blockval = cipherblock[k];
                cipherblock[k] = ((workval + blockval) % 26);
            }
            for (k = 0; k < strlen(inputvector); k++)
            {
                int cipherval = cipherblock[k];
                int keyval = transkeyword[k];
                cipherblock[k] = (((cipherval + keyval) % 26) + 97);
            }
            
            for (int p = (i - strlen(inputvector)), j = 0; j < strlen(inputvector) ; p++, j++)
            {
                ciphertext[p] = cipherblock[j];
            }
            
            for (k = 0; k < strlen(inputvector); k++)
            {
                cipherblock[k] = cipherblock[k] - 97;
            }
        }
    }
    
    //Printing the output.
    puts("CBC Vigenere by Subhash Naidu");
    printf("Plaintext file name: %s\n",inputfilename);
    printf("Vigenere keyword: %s\n", inputkeyword);
    printf("Initialization vector: %s\n\n",inputvector);
    
    printf("Clean Plaintext:\n\n");
    for (i = 0; i <= strlen(cleantxt); i++)
    {
        printf("%c",cleantxt[i]);
    }
    
    printf("\n\nCiphertext:\n\n");
    for (i = 0; i <= strlen(cleantxt); i++)
    {
        printf("%c",ciphertext[i]);
    }
    
    printf("\n\nNumber of characters in clean plaintext file: %lu\n",strlen(cleantxt) - padchar);
    printf("Block size = %lu\n",strlen(inputvector));
    printf("Number of pad characters added: %d\n\n",padchar);
      
    return 0;
}

int converttonum(char c)
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
