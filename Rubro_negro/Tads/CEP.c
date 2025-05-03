#include "../Includes/CEP.h"
#include "../Includes/funcao_sistema.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

CEP *alocar_cep()
{
    CEP *cep = (CEP *)malloc(sizeof(CEP));

    verificar_alocacao(cep);

    cep->cep = NULL;

    return cep;
}

CEP *criar_cep(char *cep)
{
    CEP *cep_alocado = alocar_cep();

    cep_alocado->cep = cep;

    return cep_alocado;
}

void imprimir_cep(CEP *cep)
{
    if (cep != NULL)
    {
        printf("CEP: %s\n", cep->cep);
    }
}

void liberar_cep(CEP **cep)
{
    if (*cep != NULL)
    {
        free((*cep)->cep);
        free(*cep);
        *cep = NULL;
    }
}

int validar_cep(CEP *cep)
{
    int valido = 0;
    if (cep && cep->cep && strlen(cep->cep) == 9 && cep->cep[5] == '-')
    {
        int formato_ok = 1;
        for (int i = 0; i < 9 && formato_ok; i++)
        {
            if (i != 5 && !isdigit(cep->cep[i]))
            {
                formato_ok = 0;
            }
        }
        valido = formato_ok;
    }
    return valido;
}