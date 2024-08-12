#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "numeral_system_converter.c"

int main(){
    long long int num = 2147483647;
    unsigned int base = 94;
    char *convertednumber;
    convertednumber = (char *)malloc(sizeof(char));
    memorycheck(convertednumber);

    frombase10(num, base, convertednumber);

    printf("%s\n", convertednumber);
    free(convertednumber);

    char number1[] = {'4', 'M', '|', 'C', 's'};
    size_t size = sizeof(number1) / sizeof(number1[0]);
    unsigned int base2 = 94;

    printf("%lld\n", tobase10(number1, size, base2));

    size_t size2 = 5;
    char *number2 = malloc(sizeof(char) * size2);
    memorycheck(number2);

    int frombase = 2;
    int tobase = 6;

    number2[0]=128;number2[1]='"';number2[2]='!';number2[3]='"';number2[4]='"';

    convertbase(number2, size2, frombase, tobase);
    printf("%s", number2);

    free(number2);

    return 0;
}