#pragma once

#include <stdio.h>
#include <stdlib.h>

typedef struct ESTADOS
{
    char *nome;
    char *estado;
    int qnt_estados;
    float *tam_populacao;
    struct ESTADOS *ant;
    struct ESTADOS *prox;
    void *end_vp;
} ESTADOS;
