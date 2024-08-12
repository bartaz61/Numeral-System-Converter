#include <stdio.h>
#include <stdlib.h>

#include "Programmer\numeral_system_converter.c"

long long int btobase10(char number[], size_t size, unsigned int base){
    //Safety checks for user input
    numeralsystemcheck(base);
    validarray(size);

    //Defining variables
    long long int sum = 0; //Used to create base10 number
    unsigned int exponent = 0;  //used to increase the exponent the further with the baseX number we go

    //for base 1 numbers
    if(base==1){
        return size;
    }

    int x;
    for(/*long1*/ /*long2*/ /*un*/signed int i = size-1; i>=0; i--){ //We begin from the end of the baseX number
        if(number[i]=='-'){
            sum = 0-sum;
            break;
        }

        x = (number[i]-48);
        //Safety checks for array and its elements
        validigitcheck(x, base);
       // integeroverflowcheck(sum, x, base);

        sum += x * custompow(base, exponent); //We convert baseX digit to base10
        exponent++; //We increase the exponent when we move to the left
    }

    return sum; //We return the base 10 number
}

void fileopeningcheck(FILE* file){
    if(file==NULL){
        printf("File didn't open");
        exit(-1);
    }
}

int main(){
    FILE* databyse;

    //Opening of the file
    databyse = fopen("1ids.txt", "r");
    //Error handling for succesfull opening of the file
    fileopeningcheck(databyse);
    
    //Creating the output file
    FILE* output;

    output = fopen("1codedids.txt", "w");

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
    output = fopen("1codedids.txt", "a");

    fileopeningcheck(output);

    do
    {
        // Taking input single character at a time
        char c = fgetc(databyse);
 
        //; is the separator for the normal numbers.
        if(c==';'){
            //Converting this number from string into long long int
            long long int num = btobase10(number, (j-1), 10);

            //This will be reallocated later so I have to allocate it first
            char *convertednumber;
            convertednumber = (char *)malloc(sizeof(char));
            memorycheck(convertednumber);

            //I convert the number to base 94
            frombase10(num, 94, convertednumber);

            //I reset those values for next numbers
            j=1;
            i=0;

            //printing the convertednumber into the file, " " or whitespace is a separator for this, you can use any other character that isn't used by the numeral number converter
            fprintf(output, "%s ", convertednumber);
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