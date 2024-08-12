#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "header/helperfunctions.h"
#include "header/stack.h"

void frombase10(int number,unsigned int base,char convertednumber[]){
    numeralsystemcheck(base);

    if(number!=0&&base>1){
    //Creating stack and defining variables
    size_t size;
    stack_el* OPstack = NULL; //Operator stack 
    int i = 0; //Variable for poping the value to the array
    bool negative;

    //Negative number handling, required so I can push '-' to the stack at the end of the operation
    if(number<0){
        negative = true;
    }

    size = digitcount(number, base);
    
    //Reallocating memory
    char *ptrconvertednumber;
    ptrconvertednumber = (char *)realloc(convertednumber, sizeof(char)*size);
    memorycheck(ptrconvertednumber);
    convertednumber = ptrconvertednumber;

    //Converting base10 number to baseX number
    number = abs(number);
    while(number!=0){
        int x = number%base;

        //ranges 0-9, A-Z, a-z
        if(x>-1&&x<10){
            push(&OPstack, x+48); 
        }
        else if(x>9&&x<36){
            push(&OPstack, x+55); 
        }
        else if(x>35&&x<62){
            push(&OPstack, x+61); 
        }
        number/=base;
    }

    //Pushing '-' to the last place of the stack so it gets poped first 
    if(negative==true){
        push(&OPstack, 45);
    }

    //After number is converted, I pop it out of the stack into the array
    while(OPstack!=NULL){
        convertednumber[i] = pop(&OPstack);
        i++;
    }
    convertednumber[i] = 0;

    }
    
    //Supporting 0
    else if(number==0){
            //allocating memory for one element
            char *ptrconvertednumber;
            ptrconvertednumber = (char *)realloc(convertednumber, sizeof(char));
            memorycheck(ptrconvertednumber);
            convertednumber = ptrconvertednumber;

            convertednumber[0] = 48;
            convertednumber[1] = 0;
    }

    //Supporting base 1 numeral system
    else if(base==1){
            //allocating memory for the number in base 1 system, number of the digits in unary system is equal to the number
            char *ptrconvertednumber;
            ptrconvertednumber = (char *)realloc(convertednumber, sizeof(char)*number);
            memorycheck(ptrconvertednumber);
            convertednumber = ptrconvertednumber;

            int i;

            //printing those numbers to the array
            for(i=0; i<number; i++){
                convertednumber[i]=49;
            }
            convertednumber[i] = 0;
    }
    
}

void frombase10inf(int number,unsigned int base,char convertednumber[]){
    numeralsystemcheck(base);

    if(number!=0&&base>1){
    //Creating stack and defining variables
    size_t size = 0;
    stack_el* OPstack = NULL; //Operator stack 
    int i = 0; //Variable for poping the value to the array
    bool negative;

    //Negative number handling, required so I can push '-' to the stack at the end of the operation
    if(number<0){
        negative = true;
    }

    //Converting base10 number to baseX number
    number = abs(number);
    while(number!=0){
        int x = number%base;

        //ranges 0-9, A-Z, a-z
        if(x>-1&&x<10){
            push(&OPstack, 41);
            push(&OPstack, x+48); 
            push(&OPstack, 40);
            size+=3;
        }
        else if(x>9&&x<36){
            push(&OPstack, 41);
            push(&OPstack, x+55);
            push(&OPstack, 40); 
            size+=3;
        }
        else if(x>35&&x<62){
            push(&OPstack, 41);
            push(&OPstack, x+61); 
            push(&OPstack, 40);
            size+=3;
        }
        else if(x>61){
            push(&OPstack, 41);

            char *convertednumber2;
            int size2 = digitcount(x, 62);
            convertednumber2 = (char *)malloc(sizeof(char)*size2);
            frombase10(x, 62, convertednumber2);

            size += size2 + 2;
            while(size2!=0){
                push(&OPstack, convertednumber2[size2-1]);
                size2--;
            }
            push(&OPstack, 40);
            free(convertednumber2);
        }
        number/=base;
    }

    //Reallocating memory
    char *ptrconvertednumber;
    ptrconvertednumber = (char *)realloc(convertednumber, sizeof(char)*size);
    memorycheck(ptrconvertednumber);
    convertednumber = ptrconvertednumber;

    //Pushing '-' to the last place of the stack so it gets poped first 
    if(negative==true){
        push(&OPstack, 45);
    }

    //After number is converted, I pop it out of the stack into the array
    while(OPstack!=NULL){
        convertednumber[i] = pop(&OPstack);
        i++;
    }
    convertednumber[i] = 0;

    }
    
    //Supporting 0
    else if(number==0){
            //allocating memory for one element
            char *ptrconvertednumber;
            ptrconvertednumber = (char *)realloc(convertednumber, sizeof(char));
            memorycheck(ptrconvertednumber);
            convertednumber = ptrconvertednumber;

            convertednumber[0] = 48;
            convertednumber[1] = 0;
    }

    //Supporting base 1 numeral system
    else if(base==1){
            //allocating memory for the number in base 1 system, number of the digits in unary system is equal to the number
            char *ptrconvertednumber;
            ptrconvertednumber = (char *)realloc(convertednumber, sizeof(char)*number);
            memorycheck(ptrconvertednumber);
            convertednumber = ptrconvertednumber;

            int i;

            //printing those numbers to the array
            for(i=0; i<number; i++){
                convertednumber[i]=49;
            }
            convertednumber[i] = 0;
    }
    
}

int tobase10inf(char number[], size_t size, unsigned int base){
    //Safety checks for user input
    numeralsystemcheck(base);
    validarray(size);

    //Defining variables
    int sum = 0; //Used to create base10 number
    unsigned int exponent = 0;  //used to increase the exponent the further with the baseX number we go
    bool braclet;

    //for base 1 numbers
    if(base==1){
        return size;
    }

    int x;

    for(int i = size-1; i>=0; i--){ //We begin from the end of the baseX number
        int tempsum = 0;
        int tempexponent = 0; 

        if(number[i]=='-'){
            sum = 0-sum;
        }

        if(number[i]==')'){
            braclet=true;
            i--;
        }

        while(braclet==true){
            //ranges 0-9, A-Z, a-z
            if(number[i]>47&&number[i]<58){
                x = number[i]-48;
            }
            else if(number[i]>64&&number[i]<91){
                x = number[i]-55; 
            }
            else if(number[i]>96&&number[i]<123){
                x = number[i]-61;
            }
        
            //Safety checks for array and its elements
            validigitcheck(x, 62);
            integeroverflowcheck(tempsum, x, 62);

            tempsum += x * custompow(62, tempexponent); //We convert baseX digit to base10

            tempexponent++; //We increase the exponent when we move to the left

            i--;
            
            if(number[i]=='('){
                braclet=false;

                sum += tempsum * custompow(base, exponent);
                exponent++;
            }
        }
        
    }

    return sum; //We return the base 10 number
}

void convertbaseinf(char number[], size_t size, unsigned int frombase, unsigned int tobase){
    //First I convert the number to base 10 from its original base
    int decimalnumber = tobase10inf(number, size, frombase);
    
    //Then I convert the base 10 number to its output base
    frombase10inf(decimalnumber, tobase, number);
}

//Floats

void frombase10inff(/*long1*/ /*double*/ float number, unsigned int base, char **convertednumber) {
    numeralsystemcheck(base);

    int integer = extractIntegerPart(number);
    int fractional = extractFractionalPart(number);

    if (integer != 0 && base > 1) {
        //Creating stack and defining variables
        size_t size;
        stack_el* OPstack = NULL; //Operator stack 
        int i = 0; //Variable for popping the value to the array
        bool negative = (integer < 0);

        //The size of the array is integer and fractional digit count added together.

        //Converting base10 number to baseX number
        integer = abs(integer);
        
        // Push fractional part
        while(fractional!=0){
            int x = fractional%base;

            //ranges 0-9, A-Z, a-z
            if(x>-1&&x<10){
                push(&OPstack, 41);
                push(&OPstack, x+48); 
                push(&OPstack, 40);
                size+=3;
            }
            else if(x>9&&x<36){
                push(&OPstack, 41);
                push(&OPstack, x+55);
                push(&OPstack, 40); 
                size+=3;
            }
            else if(x>35&&x<62){
                push(&OPstack, 41);
                push(&OPstack, x+61); 
                push(&OPstack, 40);
                size+=3;
            }
            else if(x>61){
                push(&OPstack, 41);

                char *convertednumber2;
                int size2 = digitcount(x, 62);
                convertednumber2 = (char *)malloc(sizeof(char)*size2);
                frombase10(x, 62, convertednumber2);

                size += size2 + 2;
            while(size2!=0){
                push(&OPstack, convertednumber2[size2-1]);
                size2--;
            }
            push(&OPstack, 40);
            free(convertednumber2);
        }
        fractional/=base;
        }

        push(&OPstack, '.');

        integer = abs(integer);
        // Push integer part
        while(integer!=0){
            int x = integer%base;

            //ranges 0-9, A-Z, a-z
            if(x>-1&&x<10){
                push(&OPstack, 41);
                push(&OPstack, x+48); 
                push(&OPstack, 40);
                size+=3;
            }
            else if(x>9&&x<36){
                push(&OPstack, 41);
                push(&OPstack, x+55);
                push(&OPstack, 40); 
                size+=3;
            }
            else if(x>35&&x<62){
                push(&OPstack, 41);
                push(&OPstack, x+61); 
                push(&OPstack, 40);
                size+=3;
            }
            else if(x>61){
                push(&OPstack, 41);

                char *convertednumber2;
                int size2 = digitcount(x, 62);
                convertednumber2 = (char *)malloc(sizeof(char)*size2);
                frombase10(x, 62, convertednumber2);

                size += size2 + 2;
            while(size2!=0){
                push(&OPstack, convertednumber2[size2-1]);
                size2--;
            }
            push(&OPstack, 40);
            free(convertednumber2);
        }
        integer/=base;
        }

        //Pushing '-' to the last place of the stack so it gets popped first 
        if (negative==true) {
            push(&OPstack, 45);
            size++;
        }

        size++;

        //Reallocating memory
        char *ptrconvertednumber = (char *)realloc(*convertednumber, sizeof(char) * size);
        memorycheck(ptrconvertednumber);
        *convertednumber = ptrconvertednumber;

        //After number is converted, I pop it out of the stack into the array
        i = 0;
        while (OPstack != NULL) {
            (*convertednumber)[i] = pop(&OPstack);
            i++;
        }
        (*convertednumber)[i] = '\0';  // Null-terminate the string

    } else if (integer == 0) {
        // Handle zero
        char *ptrconvertednumber = (char *)realloc(convertednumber, sizeof(char) * 2);
        memorycheck(ptrconvertednumber);
        (*convertednumber) = ptrconvertednumber;

        (*convertednumber)[0] = '0';
        (*convertednumber)[1] = '\0';
    } else if (base == 1) {
        // Handle base 1
        for (int i = 0; i < integer; i++) {
            (*convertednumber)[i] = '1';
        }
        (*convertednumber)[integer] = '\0';
        
    }
}

/*long1*/ /*double*/ float tobase10inff(char number[], size_t size, unsigned int base){
    //Safety checks for user input
    numeralsystemcheck(base);
    validarray(size);

    //Defining variables
    /*long1*/ /*double*/ float sum = 0.0; //Used to create base10 number
    unsigned int exponent = 0;  //used to increase the exponent the further with the baseX number we go
    bool braclet;

    //for base 1 numbers
    if(base==1){
        return size;
    }

    int x;
    for(int i = size-1; i>=0; i--){ //We begin from the end of the baseX number
        if(number[i]=='.'){
            sum /= custompow(10, digitcount(sum, 10));
            i--;
            exponent = 0;
        }

        int tempsum = 0;
        int tempexponent = 0; 

        if(number[i]=='-'){
            sum = 0-sum;
        }

        if(number[i]==')'){
            braclet=true;
            i--;
        }

        while(braclet==true){
            //ranges 0-9, A-Z, a-z
            if(number[i]>47&&number[i]<58){
                x = number[i]-48;
            }
            else if(number[i]>64&&number[i]<91){
                x = number[i]-55; 
            }
            else if(number[i]>96&&number[i]<123){
                x = number[i]-61;
            }
        
            //Safety checks for array and its elements
            validigitcheck(x, 62);
            integeroverflowcheck(tempsum, x, 62);

            tempsum += x * custompow(62, tempexponent); //We convert baseX digit to base10

            tempexponent++; //We increase the exponent when we move to the left

            i--;
            
            if(number[i]=='('){
                braclet=false;

                sum += tempsum * custompow(base, exponent);
                exponent++;
            }
        }
    }

    return sum; //We return the base 10 number
}

void convertbaseinff(char **number, size_t size, unsigned int frombase, unsigned int tobase){
    //First I convert the number to base 10 from its original base
    /*long1*/ /*double*/ float decimalnumber = tobase10inff((*number), size, frombase);
    
    //Then I convert the base 10 number to its output base
    frombase10inff(decimalnumber, tobase, number);
}