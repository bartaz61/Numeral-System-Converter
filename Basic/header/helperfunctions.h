#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//ERROR HANDLERS
#define ERROR_UNSUPPORTEDNUMERALSYSTEM -1
#define ERROR_INVALIDDIGIT -2
#define ERROR_INTEGEROVERFLOW -3
#define ERROR_INVALIDARRAY -4
#define ERROR_MEMORYALLOCATION -5

#define MAXNUMERALSYSTEM 10

//ERROR handling

void memorycheck(char *ptr){
    //Checking if memory was allocated properly
    if(ptr==NULL){
        printf("Memory allocation failed");
        exit(ERROR_MEMORYALLOCATION);
    }
}

void numeralsystemcheck(unsigned int base){
    //Checking if numeralsystem is supported
    if(base<1||base>MAXNUMERALSYSTEM){
        printf("Those base numeral systems are unsupported in this version");
        exit(ERROR_UNSUPPORTEDNUMERALSYSTEM);
    }
}

void validigitcheck(unsigned int index, unsigned int base){
    if(index>=base){
        printf("Digit isn't base %d", base);
        exit(ERROR_INVALIDDIGIT);
    }
}
/*
void integeroverflowcheck(unsigned int sum, unsigned int index, unsigned int base){
    if (sum > (INT_MAX - index) / base) {
        fprintf(stderr, "Integer overflow\n");
        exit(ERROR_INTEGEROVERFLOW);
    }
}
*/
void validarray(size_t size){
    if(size==0){
        printf("There are no numbers in this array");
        exit(ERROR_INVALIDARRAY);
    }
}

//Actual functions

long long int custompow(/*long1*/ /*long2*/ unsigned int base, unsigned int exponent){
    long long int result = 1;

    //X^0=1 OR 1^X=1
    if(exponent==0||base==1)
        return result;

    //doing the exponentiation
    while(exponent!=0){
        result*=base;
        exponent--;
    }

    return result;
}

int extractIntegerPart(/*long1*/ /*double*/ float number) {
    int integer = (int)number;

    return integer;
}

int extractFractionalPart(/*long1*/ /*double*/ float number) {
    // Extract the fractional part
    double fractional = number - (int)number;
    
    // Multiply by 1,000,000 to get 6 decimal places and round
    int fractionalPart = (int)roundf(fractional * 1000000);
    
    // Ensure it's positive (in case of negative numbers)
    fractionalPart = abs(fractionalPart);
    
    return fractionalPart;
}

//For printng arrays
void printarray(int array[], size_t size){
    for(int i=0; i<size; i++){
        printf("%d", array[i]);
    }
}

