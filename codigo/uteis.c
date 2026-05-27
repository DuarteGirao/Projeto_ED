#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../headers/uteis.h"
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
    LimparBuffer();

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
    }
    fclose(fp);
}

void paginacao(void *array, int size, int dataPage, void (*fshow)(void *data)) {
    if (array == NULL || size <= 0 || dataPage <= 0 || fshow == NULL) {
        return;
    }

    void **arr = (void **)array; 

    int pag = 0;
    int max = (size + dataPage - 1) / dataPage;
    char line[128];

    while (1) {
        printf("\n\n\n");
        int start = pag * dataPage;
        int end = start + dataPage;
        if (end > size) end = size;

        printf("Pagina %d de %d\n", pag + 1, max);
        printf("=====================\n");

        for (int i = start; i < end; i++) {
            fshow(arr[i]);
        }

        printf("\nComandos: [n] Proxima, [p] Anterior, [f] Primeira, [l] Ultima, [q] Sair\n");
        printf("Escolha (n/p/f/l/q ou numero 1-%d): ", max);

        if (!fgets(line, sizeof(line), stdin)) {
            break;
        }

        
        size_t ln = strlen(line);
        if (ln > 0 && line[ln-1] == '\n') line[ln-1] = '\0';

        if (line[0] == '\0') {
            continue;
        }

        if ((line[0] == 'q' || line[0] == 'Q') && line[1] == '\0') {
            break;
        }
        else if ((line[0] == 'n' || line[0] == 'N') && line[1] == '\0') {
            if (pag < max - 1) pag++;
            else printf("Ja esta na ultima pagina.\n");
            continue;
        }
        else if ((line[0] == 'p' || line[0] == 'P') && line[1] == '\0') {
            if (pag > 0) pag--;
            else printf("Ja esta na primeira pagina.\n");
            continue;
        }
        else if ((line[0] == 'f' || line[0] == 'F') && line[1] == '\0') {
            pag = 0; continue;
        }
        else if ((line[0] == 'l' || line[0] == 'L') && line[1] == '\0') {
            pag = max - 1; continue;
        }

        char *endptr = NULL;
        long v = strtol(line, &endptr, 10);
        if (endptr != line && *endptr == '\0') {
            if (v >= 1 && v <= max) {
                pag = (int)(v - 1);
                continue;
            } else {
                printf("Numero invalido. Introduza 1 a %d.\n", max);
                continue;
            }
        }

        printf("Comando invalido. Tente novamente.\n");
    }
}
