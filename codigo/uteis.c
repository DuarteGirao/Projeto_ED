#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../headers/uteis.h"

int numAleatorio(int min, int max)
{
    return (rand() % (max - min + 1)) + min;
}

void throwError(const char *texto)
{
    printf("\x1b[31m" "%s\n" "\x1b[0m" , texto);
    exit(1);
}