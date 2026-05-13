#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "uteis.h"

/**
 * @brief Devolve um número aleatório dentro de um intervalo dado
 * 
 * @param min - número mínimo
 * @param max - número máximo
 * @return int - número aleatório
 */
int Aleatorio(int min, int max)
{
    return min + rand() % (max - min + 1);
}

/**
 * @brief Escreve uma mensagem de erro em vermelho no terminal e acaba a execução do programa
 * 
 * @param texto - mensagem a mostrar
 */
void throwError(const char *texto)
{
    printf("\x1b[31m" "\n%s\n" "\x1b[0m" , texto);
    
    if (THROW)
    {
        exit(1);
    }
}

/**
 * @brief Pede ao utilizador para introduzir um número, e a função devolve o inteiro
 * 
 * @param txt - mensagem que aparece antes do utilizador introduzir o número
 * @return int - inteiro dado pelo utilizador
 */
int LerInteiro(char *txt)
{
    printf("%s", txt);
    char X[100];
    int naoDigito = 0;
    scanf("%99s", X);

    //Validar que é um número do inicio ao fim
    int i = 0;
    while (X[i] != '\0' && !naoDigito)
    {
        if (X[i] < '0' || X[i] > '9')
        {
            //printf("[%c] não é um digito!\n", X[i]);
            naoDigito = 1;
        }
        
        i++;
    }
    

    //Converter para número
    int num = 0;

    if (!naoDigito)
    {
        for (i = 0; X[i] != '\0'; i++)
        {
            num = num * 10 + (X[i] - '0');
        }

        return num;
    }

    else
    {
        printf("Erro no número introduzido!\n");

        int margem=0;
        for (i = 0; X[i] != '\0'; i++)
        {
            if (X[i] < '0' || X[i] > '9')
            {
                continue;
            }
            
            num = num * 10 + (X[i] - '0');
        }

        printf("Queria introduzir este número '%d'?\n",num);
        printf("(s)Sim/(N)Não? ");  //Normalmente uma letra maiuscula significa que é o default se nada for introduzido
        char c;
        scanf(" %c", &c);

        DebugPrint(__FUNCTION__, "asd");
        if(ToMaiscula(c) == 'S')
        {
            DebugPrint(__FUNCTION__, "1");
            return num;
        }
        else
        {
            char buf[32];
            snprintf(buf, sizeof(buf), "[c][%c]", c);
            DebugPrint(__FUNCTION__, buf);
            printf("\n");
            return LerInteiro(txt);
        }
    }
}

char ToMaiscula(char x)
{
    if ((x >= 'a') && (x <= 'z'))
        return 'A' + x - 'a';
    return x;
}

void wait ( int mlseconds )
{
    clock_t endwait;
    endwait = clock () + mlseconds;
    while (clock() < endwait);
}

void wait_segundos ( int seconds )
{
    wait(seconds * CLOCKS_PER_SEC);
}

//Penso que seja esta função que pausa a simulação
int TeclaPressionada()
{
    // fazer...
    return 0;
}

void DebugPrint(const char *txt1, const char *txt2)
{
    if (DEBUG)
    {
        printf("[DEBUG]---------------------------[%s][%s]\n",txt1,txt2);
    }
    
}

void LimparBuffer()
{
    while ((getchar()) != '\n');
}

/**
 * @brief Confirma se o valor f é um inteiro ou se tem uma fração
 * 
 * @param f - valor a confirmar
 * @return int - 1 se for inteiro, 0 se não for inteiro
 */
int checkFloatInteiro(float f)
{
    int n = f;

    return (!((f-n)>0));
}

void loggar(const char *txt1, const char *txt2)
{
    const char *nf = FICH_LOG;
    FILE *fp = fopen(nf, "a");
    if (fp) 
    {
        time_t now = time(NULL);
        struct tm *timeinfo = localtime(&now);
        char timestamp[20];
        strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", timeinfo);
        fprintf(fp, "[%s]-[%s]-[%s]\n", timestamp, txt1, txt2);
        fclose(fp);
    }
}