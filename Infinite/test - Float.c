#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "numeral system converter.c"

int main(){
    float num = 3843.3843;
    unsigned int base = 300;
    char *convertednumber;
    convertednumber = (char *)malloc(sizeof(char));
    memorycheck(convertednumber);

    frombase10inff(num, base, &convertednumber);

    printf("%s\n", convertednumber);
    free(convertednumber);

    char number1[] = {'(', 'z', ')', '(', 'z', ')', '.', '(', 'y', ')', '(', '2', ')'};
    unsigned int size = sizeof(number1) / sizeof(number1[0]);
    unsigned int base2 = 300;

    printf("%f\n", tobase10inff(number1, size, base2));

    size_t size2 = 13;
    char *number2 = malloc(sizeof(char) * size2);
    memorycheck(number2);

    int frombase = 300;
    int tobase = 400;

    number2[0]='(';number2[1]='1';number2[2]=')';number2[3]='(';number2[4]='1';number2[5]=')';number2[6]='.';number2[7]='(';number2[8]='1';number2[9]=')';number2[10]='(';number2[11]='1';number2[12]=')';

    convertbaseinff(&number2, size2, frombase, tobase);

    printf("%s\n", number2);

    free(number2);

    return 0;
}