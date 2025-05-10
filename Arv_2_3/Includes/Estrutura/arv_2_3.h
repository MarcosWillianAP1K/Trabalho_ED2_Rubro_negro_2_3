#pragma once

#include <stdio.h>
#include <stdlib.h>

typedef struct ARV_2_3
{
    int info1, info2; /// mudar pro dados
    struct ARV_2_3 *esquerda;
    struct ARV_2_3 *centro;
    struct ARV_2_3 *direita;
}ARV_2_3;
