#include "../Includes/Estruturas/Rubro_negro.h"
#include "../Includes/Utilitarios/funcao_sistema.h"
#include <stdio.h>
#include <stdlib.h>


RUBRO_NEGRO *alocar_no()
{
    RUBRO_NEGRO *no = (RUBRO_NEGRO *)malloc(sizeof(RUBRO_NEGRO));

    verificar_alocacao(no);

    no->cor = VERMELHO;
    no->esquerda = NULL;
    no->direita = NULL;
    no->info = NULL;

    return no;
}
