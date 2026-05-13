#ifndef UTEIS_H
#define UTEIS_H

#define DEBUG 1
#define THROW 1
#define FICH_LOG "dados/logs.txt"

int Aleatorio(int min, int max);

void throwError(const char *texto);

int LerInteiro(char *txt);

char ToMaiscula(char x);

void wait ( int mlseconds );
void wait_segundos ( int seconds );

int TeclaPressionada();

void DebugPrint(const char *txt1, const char *txt2);

void LimparBuffer();

int checkFloatInteiro(float f);

void loggar(const char *txt1, const char *txt2);

#endif