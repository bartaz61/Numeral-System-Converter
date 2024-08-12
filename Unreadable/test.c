#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "numeral system converter.c"

int main(){
    int num = 2147483647;
    unsigned int base = 254;
    unsigned char *convertednumber;
    convertednumber = (char *)malloc(sizeof(char));
    memorycheck(convertednumber);

    frombase10(num, base, convertednumber);
    free(convertednumber);

    unsigned char number1[] = {255, 5, 4, 7};
    size_t size = sizeof(number1) / sizeof(number1[0]);
    unsigned int base2 = 9;

    printf("%d\n", tobase10(number1, size, base2));

    size_t size2 = 5;
    unsigned char *number2 = malloc(sizeof(char) * size2);
    memorycheck(number2);

    int frombase = 2;
    int tobase = 6;

    number2[0]=1;number2[1]=1;number2[2]=1;number2[3]=1;number2[4]=0;

    convertbase(number2, size2, frombase, tobase);

    free(number2);

    return 0;
}