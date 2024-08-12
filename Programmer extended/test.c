#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "numeral system converter.c"

int main(){
    int num = 2147483647;
    unsigned int base = 94;
    char *convertednumber;
    convertednumber = (char *)malloc(sizeof(char));
    memorycheck(convertednumber);

    frombase10(num, base, convertednumber);

    printf("%s\n", convertednumber);
    free(convertednumber);

    char number1[] = {'1', '~', '0'};
    size_t size = sizeof(number1) / sizeof(number1[0]);
    unsigned int base2 = 94;

    printf("%d\n", tobase10(number1, size, base2));

    size_t size2 = 5;
    char *number2 = malloc(sizeof(char) * size2);
    memorycheck(number2);

    int frombase = 12;
    int tobase = 94;

    number2[0]='A';number2[1]='1';number2[2]='B';number2[3]='1';number2[4]='1';

    convertbase(number2, size2, frombase, tobase);
    printf("%s", number2);

    free(number2);

    return 0;
}