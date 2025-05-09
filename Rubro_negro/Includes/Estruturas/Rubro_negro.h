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

RUBRO_NEGRO *alocar_no();

void liberar_no_rubro_negro(RUBRO_NEGRO **no, void (*liberar)(DADOS **));

void liberar_rubro_negro(RUBRO_NEGRO **raiz, void (*liberar)(DADOS **));

COR cor(RUBRO_NEGRO *no);

short int inserir_rubro_negro(RUBRO_NEGRO **raiz, DADOS *info, short int (*comparar)(DADOS *, DADOS *));
