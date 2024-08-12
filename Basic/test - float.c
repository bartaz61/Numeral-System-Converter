#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "numeral system converter.c"

int main(){
    float num = 213.324213;
    unsigned int base = 7;
    char *convertednumber;
    convertednumber = (char *)malloc(sizeof(char));
    memorycheck(convertednumber);

    frombase10f(num, base, convertednumber);

    printf("%s\n", convertednumber);
    free(convertednumber);

    char number1[] = {'3', '7', ',', '1', '2'};
    unsigned int size = sizeof(number1) / sizeof(number1[0]);
    unsigned int base2 = 9;

    printf("%f\n", tobase10f(number1, size, base2));

    size_t size2 = 8;
    char *number2 = malloc(sizeof(char) * size2);
    memorycheck(number2);

    int frombase = 2;
    int tobase = 6;

    number2[0]='-';number2[1]='1';number2[2]='0';number2[3]='1';number2[4]='1';number2[5]=',';number2[6]='1';number2[7]='1';

    convertbasef(number2, size2, frombase, tobase);

    printf("%s\n", number2);

    free(number2);

    return 0;
}