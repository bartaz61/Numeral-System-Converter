#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "header/helperfunctions.h"
#include "header/stack.h"

//Used for memory allocation, you can also count with it how much memory you need to allocate when making an array storing base X number
unsigned int digitcount(int number,unsigned int base){
    unsigned int exponent; //Exponent that I use to calculate how many spaces will my number take up, necessary for memory allocation and dynamic array
    bool negative;

    //negative number handling
    if(number<0){
        number = abs(number);
        negative = true;
    }

    numeralsystemcheck(base);

    if(base==1){
        return number;
    }

    //Calculating how much memory I will need for the number, you need atleast (exponent of the closest exponetiation of base that is greater or equal to the number that user inputed) bytes
    for(exponent = 0;number>custompow(base, exponent);exponent++){}
    
    //You need one extra byte for '-'
    if(negative==true){
        exponent++;
    }

    return exponent;
}

void frombase10(/*long1*/ /*long2*/ /*un*/signed int number,unsigned int base,char convertednumber[]){
    numeralsystemcheck(base);

    if(number!=0&&base>1){
    //Creating stack and defining variables
    size_t size;
    stack_el* OPstack = NULL; //Operator stack 
    /*long1*/ /*long2*/ /*un*/signed int i = 0; //Variable for poping the value to the array
    bool negative;

    //Negative number handling, required so I can push '-' to the stack at the end of the operation
    if(number<0){
        negative = true;
    }

    size = digitcount(number, base);
    
    //Reallocating memory
    char *ptrconvertednumber;
    ptrconvertednumber = (char *)realloc(convertednumber, (sizeof(char)*size)+1);
    memorycheck(ptrconvertednumber);
    convertednumber = ptrconvertednumber;

    //Converting base10 number to baseX number
    number = abs(number);
    push(&OPstack, 0);
    while(number!=0){
        push(&OPstack, (number%base)+48); 
        number/=base;
    }

    //Pushing '-' to the last place of the stack so it gets poped first 
    if(negative==true){
        push(&OPstack, '-');
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

            convertednumber[0]=48;
    }

    //Supporting base 1 numeral system
    else if(base==1){
            //allocating memory for the number in base 1 system, number of the digits in unary system is equal to the number
            char *ptrconvertednumber;
            ptrconvertednumber = (char *)realloc(convertednumber, sizeof(char)*number);
            memorycheck(ptrconvertednumber);
            convertednumber = ptrconvertednumber;

            //printing those numbers to the array
            for(int i=0; i<number; i++){
                convertednumber[i]=49;
            }
    }
    
}

long long int tobase10(char number[], size_t size, unsigned int base){
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

void convertbase(char number[], size_t size, unsigned int frombase, unsigned int tobase){
    //First I convert the number to base 10 from its original base
    /*long1*/ /*long2*/ /*un*/signed int decimalnumber = tobase10(number, size, frombase);
    
    //Then I convert the base 10 number to its output base
    frombase10(decimalnumber, tobase, number);
}

unsigned int digitcountf(int number, unsigned int base){
    int integer = extractIntegerPart(number);
    int fractional = extractFractionalPart(number);

    int exponent;

    if(integer<0){
        exponent++;
    }

    exponent = (digitcount(abs(integer), base) + digitcount(fractional, base))+1;

    return exponent;
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
        size = digitcount(abs(integer), base) + digitcount(fractional, base) + 2; // +2 for decimal point and null terminator
        
        //Reallocating memory
        char *ptrconvertednumber = (char *)realloc(convertednumber, sizeof(char) * size);
        memorycheck(ptrconvertednumber);
        convertednumber = ptrconvertednumber;

        //Converting base10 number to baseX number
        integer = abs(integer);
        
        // Push fractional part
        do {
            push(&OPstack, (fractional % base) + 48);
            fractional /= base;
        } while (fractional > 0);

        push(&OPstack, '.');

        // Push integer part
        do {
            push(&OPstack, (integer % base) + 48);
            integer /= base;
        } while (integer > 0);

        //Pushing '-' to the last place of the stack so it gets popped first 
        if (negative==true) {
            push(&OPstack, '-');
        }

        //After number is converted, I pop it out of the stack into the array
        i = 0;
        while (OPstack != NULL) {
            convertednumber[i] = (char)pop(&OPstack);
            i++;
        }
        convertednumber[i] = '\0';  // Null-terminate the string

    } else if (integer == 0) {
        // Handle zero
        convertednumber[0] = '0';
        convertednumber[1] = '\0';
    } else if (base == 1) {
        // Handle base 1
        for (int i = 0; i < integer; i++) {
            convertednumber[i] = '1';
        }
        convertednumber[integer] = '\0';
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
        if(number[i]=='-'){
            sum = 0-sum;
            break;
        }
        if(number[i]==','){
            sum /= custompow(10, digitcount(sum, 10));
            i--;
            exponent = 0;
        }

        x = (number[i]-48);
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