#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "numeral system converter.c"

int main(){
    int num = 2147483647;
    unsigned int base = 2147483646;
    char *convertednumber;
    convertednumber = (char *)malloc(sizeof(char));
    memorycheck(convertednumber);

    frombase10inf(num, base, convertednumber);

    printf("%s\n", convertednumber);
    free(convertednumber);

    char number1[] = {'-', '(', 'E', ')', '(', '1', 'o', ')'}; //-4312
    size_t size = sizeof(number1) / sizeof(number1[0]);
    unsigned int base2 = 300;

    printf("%d\n", tobase10inf(number1, size, base2));


    size_t size2 = 7;
    char *number2 = malloc(sizeof(char) * size2);
    memorycheck(number2);

    int frombase = 300;
    int tobase = 400;

    number2[0]='(';number2[1]='E';number2[2]=')';number2[3]='(';number2[4]='1';number2[5]='o';number2[6]=')'; //4312

    convertbaseinf(number2, size2, frombase, tobase);
    printf("%s", number2);

    free(number2);

    return 0;
}