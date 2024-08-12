#include <stdio.h>
#include <stdlib.h>

#include "Programmer\numeral_system_converter.c"

void fileopeningcheck(FILE* file){
    if(file==NULL){
        printf("File didn't open");
        exit(-1);
    }
}

int main(){
    FILE* databyse;

    //Opening of the file
    databyse = fopen("1codedids.txt", "r");
    //Error handling for succesfull opening of the file
    fileopeningcheck(databyse);
    
    //Creating the output file
    FILE* output;

    output = fopen("2ids.txt", "w");

    fileopeningcheck(output);

    //Closing as I don't want to replace my values later
    fclose(output);

    //Making a Dynamic string for reading number from input file, i is for assigning values while j is for memory 
    char *number;
    number = (char *)malloc(sizeof(char));
    memorycheck(number);
    int i;
    int j = 1;

    //Opening the file for editing
    output = fopen("2ids.txt", "a");

    fileopeningcheck(output);

    do
    {
        // Taking input single character at a time
        char c = fgetc(databyse);
 
        //; is the separator for the normal numbers.
        if(c==' '){
            //Converting this number from string into long long int
            long long int num = tobase10(number, (j-1), 94);

            //I reset those values for next numbers
            j=1;
            i=0;

            //printing the convertednumber into the file, " " or whitespace is a separator for this, you can use any other character that isn't used by the numeral number converter
            fprintf(output, "%lld;", num);
            fflush(output);

        }

        else{
            //Reallocating memory because so the number fits
            char *ptrnumber;
            ptrnumber = (char *)realloc(number, sizeof(char)*j);
            memorycheck(ptrnumber);
            number = ptrnumber;
            //Increasing for the next digit
            j++;

            //Assigning value
            number[i]=c;
            //Increasing for the next digit
            i++;
        }
        // Checking for end of file
        if (feof(databyse)){

            fclose(output);
            fclose(databyse);

            break;
        }
    }  while(1);

    free(number);

    return 0;
}