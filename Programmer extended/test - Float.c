#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "numeral system converter.c"

int main(){
    float num = 3843.3843;
    unsigned int base = 94;
    char *convertednumber;
    convertednumber = (char *)malloc(sizeof(char));
    memorycheck(convertednumber);

    frombase10f(num, base, convertednumber);

    printf("%s\n", convertednumber);
    free(convertednumber);

    char number1[] = {'z', '~', ' ', 'y', '#'};
    unsigned int size = sizeof(number1) / sizeof(number1[0]);
    unsigned int base2 = 94;

    printf("%f\n", tobase10f(number1, size, base2));

    size_t size2 = 8;
    char *number2 = malloc(sizeof(char) * size2);
    memorycheck(number2);

    int frombase = 12;
    int tobase = 66;

    number2[0]=128;number2[1]='A';number2[2]='9';number2[3]='4';number2[4]='1';number2[5]=' ';number2[6]='1';number2[7]='3';

    convertbasef(number2, size2, frombase, tobase);

    printf("%s\n", number2);

    free(number2);

    return 0;
}