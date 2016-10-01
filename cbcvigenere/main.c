//------------------------------------------------------------------
// University of Central Florida
// CIS3360 - Fall 2016
// Program Author: Subhash Naidu
//------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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
    
    strcpy(inputfilename, argv[1]);
    strcpy(inputkeyword, argv[2]);
    strcpy(inputvector, argv[3]);
    
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
    
   while ((strlen(cleantxt) % strlen(inputvector)) != 0)
   {
       strcat(cleantxt, "x");
       int padchar = 0;
       padchar++;
   }
    
    
    
    
    
    i = 0;
    

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
        }
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
        }
        
       
    }
    
    
    
    
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
