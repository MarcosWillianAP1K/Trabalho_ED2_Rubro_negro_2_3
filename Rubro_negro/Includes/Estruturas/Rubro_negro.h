#include "Dados.h"

#pragma once


typedef enum COR
{
    PRETO,
    VERMELHO
}COR;

typedef struct RUBRO_NEGRO
{
    DADOS *info;
    struct RUBRO_NEGRO *esquerda;
    struct RUBRO_NEGRO *direita;
    COR cor;

}RUBRO_NEGRO;

RUBRO_NEGRO *alocar_no_rubro_negro();

void liberar_no_rubro_negro(RUBRO_NEGRO **no, void (*liberar)(DADOS **));

void liberar_rubro_negro(RUBRO_NEGRO **raiz, void (*liberar)(DADOS **));

RUBRO_NEGRO *buscar_rubro_negro(RUBRO_NEGRO *raiz, DADOS *aux, short int (*comparar)(DADOS *, DADOS *));

COR cor(RUBRO_NEGRO *no);

short int inserir_rubro_negro(RUBRO_NEGRO **raiz, DADOS *info, short int (*comparar)(DADOS *, DADOS *));

short int inserir_rubro_negro_void(void **raiz, DADOS *info, short int (*comparar)(DADOS *, DADOS *));

DADOS *remover_rubro_negro(RUBRO_NEGRO **raiz, DADOS *aux, short int (*comparar)(DADOS *, DADOS *)) ;

DADOS *remover_rubro_negro_void(void **raiz, DADOS *aux, short int (*comparar)(DADOS *, DADOS *));

short int imprimir_rubro_negro(RUBRO_NEGRO *raiz, void (*imprimir)(DADOS *));

short int imprimir_filtro_rubro_negro(RUBRO_NEGRO *raiz, DADOS *aux, void (*imprimir)(DADOS *), short int (*comparar)(DADOS *, DADOS *));


