#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//ERROR HANDLERS
#define ERROR_UNSUPPORTEDNUMERALSYSTEM -1
#define ERROR_INVALIDDIGIT -2
#define ERROR_INTEGEROVERFLOW -3
#define ERROR_INVALIDARRAY -4
#define ERROR_MEMORYALLOCATION -5
#define ERROR_NEGATIVENUMBERS -6

#define MAXNUMERALSYSTEM 254

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

void validigitcheck(int index, unsigned int base){
    if(index>=base){
        printf("Number isn't base %d", base);
        exit(ERROR_INVALIDDIGIT);
    }
}

void integeroverflowcheck(unsigned int sum, unsigned int index, unsigned int base){
    if (sum > (UINT_MAX - index) / base) {
        fprintf(stderr, "Integer overflow\n");
        exit(ERROR_INTEGEROVERFLOW);
    }
}

void validarray(size_t size){
    if(size==0){
        printf("There are no numbers in this array");
        exit(ERROR_INVALIDARRAY);
    }
}

void negativenumber(int number){
    if(number<0){
        printf("Negative numbers are not supported in this version");
        exit(ERROR_NEGATIVENUMBERS);
    }
}

//Actual functions

unsigned int custompow(unsigned int base, unsigned int exponent){
    unsigned int result = 1;

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

//Used for memory allocation, you can also count with it how much memory you need to allocate when making an array storing base X number
unsigned int digitcount(int number,unsigned int base){
    unsigned exponent; //Exponent that I use to calculate how many spaces will my number take up, necessary for memory allocation and dynamic array
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
    for(exponent = 0;number>=custompow(base, exponent); exponent++){}

    if(negative==true){
        exponent++;
    }

    return exponent;
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

