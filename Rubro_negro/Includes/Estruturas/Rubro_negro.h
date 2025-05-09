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
    RUBRO_NEGRO *esquerda;
    RUBRO_NEGRO *direita;
    COR cor;

}RUBRO_NEGRO;

RUBRO_NEGRO *alocar_no();

COR cor(RUBRO_NEGRO *no);

short int inserir_rubro_negro(RUBRO_NEGRO **raiz, DADOS *info, short int (*comparar)(DADOS *, DADOS *));
