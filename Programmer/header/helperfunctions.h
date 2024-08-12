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

#define MAXNUMERALSYSTEM 94

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
    if (sum > (LLONG_MAX - index) / base) {
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

unsigned long long int custompow(long long int base, unsigned long long int exponent){
    unsigned long long int result = 1;

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
unsigned int digitcount(long long int number, unsigned int base) {
    numeralsystemcheck(base);

    if (base == 1)
        return number;

    unsigned int count = 0;

    if(number<0){
        number = abs(number);
        count++;
    }

    do {
        count++;
        number /= base;
    } while (number > 0);

    return count;
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


