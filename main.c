#include <stdio.h>

int             main(void)
{
    unsigned char a = 0b00001001;
    unsigned char b = 0b00000001;
    unsigned char c = 0b00000001;

    // a = a & 0b0111;
    c = (0b11111111 - b);
    c |= a;
    if (c == 0b00001000)
        printf("yes, %i\n", (int)c);
    else
        printf("no, %i\n", (int)c);
    printf("%i\n", 0b00001000);
} 