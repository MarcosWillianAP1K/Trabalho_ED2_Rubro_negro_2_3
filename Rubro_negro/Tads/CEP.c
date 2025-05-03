#include "../Includes/CEP.h"
#include "../Includes/funcao_sistema.h"
#include <stdio.h>
#include <stdlib.h>

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