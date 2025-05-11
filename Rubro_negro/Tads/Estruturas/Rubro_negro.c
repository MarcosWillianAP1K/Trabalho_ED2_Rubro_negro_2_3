#include "../../Includes/Estruturas/Rubro_negro.h"
#include "../../Includes/Utilitarios/funcao_sistema.h"
#include <stdio.h>
#include <stdlib.h>


//========================ALOCAÇÃO e LIBERAÇÃO========================

RUBRO_NEGRO *alocar_no_rubro_negro()
{
    RUBRO_NEGRO *no = (RUBRO_NEGRO *)malloc(sizeof(RUBRO_NEGRO));

    verificar_alocacao(no);

    no->cor = VERMELHO;
    no->esquerda = NULL;
    no->direita = NULL;
    no->info = NULL;

    return no;
}

void liberar_no_rubro_negro(RUBRO_NEGRO **no, void (*liberar)(DADOS **))
{
    if (no != NULL && *no != NULL && liberar != NULL)
    {
        liberar(&(*no)->info);
        free(*no);
        *no = NULL;
    }
}

void liberar_rubro_negro(RUBRO_NEGRO **raiz, void (*liberar)(DADOS **))
{
    if (raiz != NULL && *raiz != NULL && liberar != NULL)
    {
        liberar_rubro_negro(&(*raiz)->esquerda, liberar);
        liberar_rubro_negro(&(*raiz)->direita, liberar);

        liberar_no_rubro_negro(raiz, liberar);
    }
}


//========================BUSCA========================

RUBRO_NEGRO *buscar_rubro_negro(RUBRO_NEGRO *raiz, DADOS *aux, short int (*comparar)(DADOS *, DADOS *))
{
    RUBRO_NEGRO *retorno = NULL;

    if (raiz != NULL && aux != NULL && comparar != NULL)
    {
        if (comparar(raiz->info, aux) == 0)
        {
            retorno = raiz;
        }
        else
        {
            retorno = buscar_rubro_negro(raiz->esquerda, aux, comparar);

            if (retorno == NULL)
                retorno = buscar_rubro_negro(raiz->direita, aux, comparar);
        }
    }

    return retorno;
}


//========================ROTACIONAR========================

void de_ladinho_para_direita(RUBRO_NEGRO **raiz)
{
    if (raiz != NULL && *raiz != NULL)
    {
        RUBRO_NEGRO *aux = (*raiz)->esquerda;
        aux->cor = (*raiz)->cor;
        (*raiz)->cor = VERMELHO;
        (*raiz)->esquerda = aux->direita;
        aux->direita = *raiz;
        *raiz = aux;
    }
}

void de_ladinho_para_esquerda(RUBRO_NEGRO **raiz)
{
    if (raiz != NULL && *raiz != NULL)
    {
        RUBRO_NEGRO *aux = (*raiz)->direita;
        aux->cor = (*raiz)->cor;
        (*raiz)->cor = VERMELHO;
        (*raiz)->direita = aux->esquerda;
        aux->esquerda = *raiz;
        *raiz = aux;
    }
}


//========================COR========================

COR cor(RUBRO_NEGRO *no)
{
    COR retorno = PRETO;

    if (no != NULL)
    {
        retorno = no->cor;
    }

    return retorno;
}

void trocar_cor(RUBRO_NEGRO *no)
{
    if (no != NULL)
    {
        if (no->cor == VERMELHO)
        {
            no->cor = PRETO;
        }
        else
        {
            no->cor = VERMELHO;
        }

        if (no->esquerda != NULL)
        {
            if (cor(no->esquerda) == VERMELHO)
            {
                no->esquerda->cor = PRETO;
            }
            else
            {
                no->esquerda->cor = VERMELHO;
            }
        }

        if (no->direita != NULL)
        {
            if (cor(no->direita) == VERMELHO)
            {
                no->direita->cor = PRETO;
            }
            else
            {
                no->direita->cor = VERMELHO;
            }
        }
    }
}


//========================BALANCEAMENTO========================

void balancear(RUBRO_NEGRO **raiz)
{

    if (cor((*raiz)->esquerda) == PRETO && cor((*raiz)->direita) == VERMELHO)
    {
        de_ladinho_para_esquerda(raiz);
    }

    if (cor((*raiz)->esquerda) == VERMELHO && cor((*raiz)->esquerda->esquerda))
    {
        de_ladinho_para_direita(raiz);
    }

    if (cor((*raiz)->esquerda) == VERMELHO && cor((*raiz)->direita) == VERMELHO)
    {
        trocar_cor(*raiz);
    }
}


//========================INSERÇÃO========================

short int inserir_rubro_negro_recursivo(RUBRO_NEGRO **raiz, DADOS *info, short int (*comparar)(DADOS *, DADOS *))
{
    short int retorno = 0;

    if (*raiz == NULL)
    {
        *raiz = alocar_no_rubro_negro();
        (*raiz)->info = info;
        retorno = 1;
    }
    else
    {
        if (comparar((*raiz)->info, info) > 0)
        {
            retorno = inserir_rubro_negro_recursivo(&(*raiz)->esquerda, info, comparar);
        }
        else if (comparar((*raiz)->info, info) < 0)
        {
            retorno = inserir_rubro_negro_recursivo(&(*raiz)->direita, info, comparar);
        }

        if (retorno == 1)
        {
            balancear(raiz);
        }
    }

    return retorno;
}

short int inserir_rubro_negro(RUBRO_NEGRO **raiz, DADOS *info, short int (*comparar)(DADOS *, DADOS *))
{
    short int retorno = 0;

    if (raiz != NULL && info != NULL && comparar != NULL)
    {
        retorno = inserir_rubro_negro_recursivo(raiz, info, comparar);
        (*raiz)->cor = PRETO;
    }

    return retorno;
}


//========================REMOÇÃO========================

void move2EsquerdaVERMELHO(RUBRO_NEGRO **no)
{
    trocar_cor(*no);
    if (cor((*no)->direita->esquerda) == VERMELHO)
    {
        de_ladinho_para_direita(&(*no)->direita);
        de_ladinho_para_esquerda(&(*no));
        trocar_cor(*no);
    }
}

// Função para mover um nó vermelho para a direita
void move2DireitaVERMELHO(RUBRO_NEGRO **no)
{
    trocar_cor(*no);
    if (cor((*no)->esquerda->esquerda) == VERMELHO)
    {
        de_ladinho_para_direita(&(*no));
        trocar_cor(*no);
    }
}

// Função para procurar o menor elemento
RUBRO_NEGRO *procura_Menor(RUBRO_NEGRO *atual)
{
    while (atual->esquerda != NULL)
    {
        atual = atual->esquerda;
    }

    return atual;
}

// Função para remover o menor elemento
void remover_no_Menor(RUBRO_NEGRO **raiz)
{
    if ((*raiz)->esquerda == NULL)
    {
        free(*raiz);
        *raiz = NULL;
        return;
    }
    if (cor((*raiz)->esquerda) == PRETO && cor((*raiz)->esquerda->esquerda) == PRETO)
        move2EsquerdaVERMELHO(raiz);

    remover_no_Menor(&(*raiz)->esquerda);
    balancear(raiz);
}

DADOS *remover_rubro_negro_recursivo(RUBRO_NEGRO **raiz, DADOS *aux, short int (*comparar)(DADOS *, DADOS *))
{
    DADOS *retorno = NULL;

    if (comparar(aux, (*raiz)->info) < 0)
    {
        if (cor((*raiz)->esquerda) == PRETO && cor((*raiz)->esquerda->esquerda) == PRETO)
            move2EsquerdaVERMELHO(raiz);

        retorno = remover_rubro_negro_recursivo(&(*raiz)->esquerda, aux, comparar);
    }
    else
    {
        if (cor((*raiz)->esquerda) == VERMELHO)
            de_ladinho_para_direita(raiz);

        if (comparar(aux, (*raiz)->info) == 0 && (*raiz)->direita == NULL)
        {
            retorno = (*raiz)->info;
            free(*raiz);
            *raiz = NULL;

            return retorno;
        }

        if (cor((*raiz)->direita) == PRETO && cor((*raiz)->direita->esquerda) == PRETO)
            move2DireitaVERMELHO(raiz);

        if (comparar(aux, (*raiz)->info) == 0)
        {
            RUBRO_NEGRO *aux = procura_Menor((*raiz)->direita);
            retorno = (*raiz)->info;
            (*raiz)->info = aux->info;
            remover_no_Menor(&(*raiz)->direita);
        }
        else
        {
            retorno = remover_rubro_negro_recursivo(&(*raiz)->direita, aux, comparar);
        }
    }

    balancear(raiz);

    return retorno;
}

// Retorna o dado do no removido, precisando liberar fora da função
DADOS *remover_rubro_negro(RUBRO_NEGRO **raiz, DADOS *aux, short int (*comparar)(DADOS *, DADOS *))
{
    DADOS *retorno = NULL;

    if (buscar_rubro_negro(*raiz, aux, comparar) != NULL)
    {
        retorno = remover_rubro_negro_recursivo(raiz, aux, comparar);

        if (*raiz != NULL)
            (*raiz)->cor = PRETO;
    }

    return retorno;
}


//========================IMPRIMIR========================

void imprimir_rubro_negro(RUBRO_NEGRO *raiz, void (*imprimir)(DADOS *))
{
    if (raiz != NULL)
    {
        imprimir_rubro_negro(raiz->esquerda, imprimir);

        imprimir(raiz->info);

        imprimir_rubro_negro(raiz->direita, imprimir);
    }
}

void imprimir_filtro_rubro_negro(RUBRO_NEGRO *raiz, DADOS *aux, void (*imprimir)(DADOS *), short int (*comparar)(DADOS *, DADOS *))
{
    if (raiz != NULL)
    {
        imprimir_filtro_rubro_negro(raiz->esquerda, aux, imprimir, comparar);

        if (comparar(raiz->info, aux) == 0)
        {
            imprimir(raiz->info);
        }

        imprimir_filtro_rubro_negro(raiz->direita, aux, imprimir, comparar);
    }
}
