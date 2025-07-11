#include "Dados.h"


#pragma once

// Estrutura do No da Arvore 2-3
typedef struct AVR_23
{
    DADOS info1, info2; // Informacoes armazenadas no no
    short int nInfo;        // Numero de informacoes no no (1 ou 2)
    struct AVR_23 *esq, *cen, *dir;
} AVR_23;


AVR_23 *cria_no(DADOS info, AVR_23 *esq, AVR_23 *cen);

DADOS *buscar_23(AVR_23 *raiz, DADOS info, short int (*comparar)(DADOS, DADOS));

short int inserir_23(AVR_23 **raiz, DADOS valor, short int (*comparar)(DADOS, DADOS));

short int inserir_23_void(void **raiz, DADOS valor, short int (*comparar)(DADOS, DADOS));

void imprimir_23_em_ordem(AVR_23 *raiz, void (*imprimir)(DADOS));

void imprimir_arvore_visual(AVR_23 *raiz, char *prefixo, short int eh_ultimo, short int eh_raiz, void (*imprimir)(DADOS));

short int remover_23(AVR_23 **raiz, DADOS valor, DADOS *dado_removido, short int (*comparar)(DADOS, DADOS));

short int remover_23_void(void **raiz, DADOS valor, DADOS *dado_removido, short int (*comparar)(DADOS, DADOS));


void liberar_no_23(AVR_23 **no, void (*liberar)(DADOS *));

void liberar_23(AVR_23 **raiz, void (*liberar)(DADOS *));

void liberar_23_void(void **raiz, void (*liberar)(DADOS *));
