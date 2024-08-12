#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "header/helperfunctions.h"
#include "header/stack.h"

void frombase10(int number,unsigned int base,unsigned char convertednumber[]){
    numeralsystemcheck(base);

    if(number!=0&&base>1){
    //Creating stack and defining variables
    size_t size;
    stack_el* OPstack = NULL; //Operator stack 
    int i = 0; //Variable for poping the value to the array
    bool negative;

    //value 255, means that number is negative.
    //Negative number handling, required so I can push value 255 to the stack at the end of the operation
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
        push(&OPstack, (number%base)+0); 
        number/=base;
    }

    //Pushing '�' to the last place of the stack so it gets poped first 
    if(negative==true){
        push(&OPstack, 255);
    }

    //After number is converted, I pop it out of the stack into the array
    while(OPstack!=NULL){
        convertednumber[i] = pop(&OPstack);
        i++;
    }

    }
    
    //Supporting 0
    else if(number==0){
            //allocating memory for one element
            char *ptrconvertednumber;
            ptrconvertednumber = (char *)realloc(convertednumber, sizeof(char));
            memorycheck(ptrconvertednumber);
            convertednumber = ptrconvertednumber;

            convertednumber[0] = 0;
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
                convertednumber[i]=1;
            }
    }
    
}

unsigned int tobase10(unsigned char number[], size_t size, unsigned int base){
    //Safety checks for user input
    numeralsystemcheck(base);
    validarray(size);

    //Defining variables
    int sum = 0; //Used to create base10 number
    unsigned int exponent = 0;  //used to increase the exponent the further with the baseX number we go

    //for base 1 numbers
    if(base==1){
        return size;
    }

    int x;

    for(int i = size-1; i>=0; i--){ //We begin from the end of the baseX number 
        if(number[i]==255){
            sum = 0-sum;
            break;
        }

        x = number[i]-0;
        //Safety checks for array and its elements
        validigitcheck(x, base);
        integeroverflowcheck(sum, x, base);

        sum += x * custompow(base, exponent); //We convert baseX digit to base10

        exponent++; //We increase the exponent when we move to the left
    }

    return sum; //We return the base 10 number
}

void convertbase(unsigned char number[], size_t size, unsigned int frombase, unsigned int tobase){
    //First I convert the number to base 10 from its original base
    int decimalnumber = tobase10(number, size, frombase);
    
    //Then I convert the base 10 number to its output base
    frombase10(decimalnumber, tobase, number);
}

//Floats

void frombase10f(/*long1*/ /*double*/ float number, unsigned int base, char convertednumber[]) {
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
        size = digitcount(abs(integer), base) + digitcount(fractional, base) + 1; // +2 for decimal point and null terminator
        
        //Reallocating memory
        char *ptrconvertednumber = (char *)realloc(convertednumber, sizeof(char) * size);
        memorycheck(ptrconvertednumber);
        convertednumber = ptrconvertednumber;

        //Converting base10 number to baseX number
        integer = abs(integer);
        
        // Push fractional part
        do {
            push(&OPstack, (fractional % base) + 0);
            fractional /= base;
        } while (fractional > 0);

        push(&OPstack, 254);

        // Push integer part
        do {
            push(&OPstack, (integer % base) + 0);
            integer /= base;
        } while (integer > 0);

        //Pushing '-' to the last place of the stack so it gets popped first 
        if (negative==true) {
            push(&OPstack, 255);
        }

        //After number is converted, I pop it out of the stack into the array
        i = 0;
        while (OPstack != NULL) {
            convertednumber[i] = (char)pop(&OPstack);
            i++;
        }

    } else if (integer == 0) {
        // Handle zero
        convertednumber[0] = 0;
    } else if (base == 1) {
        // Handle base 1
        for (int i = 0; i < integer; i++) {
            convertednumber[i] = 1;
        }
    }
}

/*long1*/ /*double*/ float tobase10f(char number[], size_t size, unsigned int base){
    //Safety checks for user input
    numeralsystemcheck(base);
    validarray(size);

    //Defining variables
    /*long1*/ /*double*/ float sum = 0.0; //Used to create base10 number
    unsigned int exponent = 0;  //used to increase the exponent the further with the baseX number we go

    //for base 1 numbers
    if(base==1){
        return size;
    }

    int x;
    for(int i = size-1; i>=0; i--){ //We begin from the end of the baseX number
        if(number[i]==-1){
            sum = 0-sum;
            break;
        }
        if(number[i]==-2){
            sum /= custompow(10, digitcount(sum, 10));
            i--;
            exponent = 0;
        }

        x = (number[i]-0);
        //Safety checks for array and its elements
        validigitcheck(x, base);
        //integeroverflowcheck(sum, x, base);

        sum += x * custompow(base, exponent); //We convert baseX digit to base10
        exponent++; //We increase the exponent when we move to the left
    }

    return sum; //We return the base 10 number
}

void convertbasef(char number[], size_t size, unsigned int frombase, unsigned int tobase){
    //First I convert the number to base 10 from its original base
    /*long1*/ /*double*/ float decimalnumber = tobase10f(number, size, frombase);
    
    //Then I convert the base 10 number to its output base
    frombase10f(decimalnumber, tobase, number);
}