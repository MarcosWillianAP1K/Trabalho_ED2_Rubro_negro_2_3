#include <stdio.h>
#include <stdlib.h>

// Definição das cores
#define RED 1
#define BLACK 0

// Estrutura do nó da árvore rubro-negra
struct NO
{
    int info;       // Valor do nó
    struct NO *esq; // Filho esquerdo
    struct NO *dir; // Filho direito
    int cor;        // Cor do nó (RED ou BLACK)
};

typedef struct NO *ArvLLRB;

// Função auxiliar para verificar a cor de um nó (retorna BLACK para NULL)
int cor(struct NO *H)
{
    if (H == NULL)
        return BLACK;
    return H->cor;
}

// Função auxiliar para trocar as cores de um nó e seus filhos
void trocaCor(struct NO *H)
{
    H->cor = !H->cor;
    if (H->esq != NULL)
        H->esq->cor = !H->esq->cor;
    if (H->dir != NULL)
        H->dir->cor = !H->dir->cor;
}

// Função para rotacionar à direita
struct NO *rotacionaDireita(struct NO *H)
{
    struct NO *x = H->esq;
    H->esq = x->dir;
    x->dir = H;
    x->cor = H->cor;
    H->cor = RED;
    return x;
}

// Função para rotacionar à esquerda
struct NO *rotacionaEsquerda(struct NO *H)
{
    struct NO *x = H->dir;
    H->dir = x->esq;
    x->esq = H;
    x->cor = H->cor;
    H->cor = RED;
    return x;
}

// Função para mover um nó vermelho para a esquerda
struct NO *move2EsqRED(struct NO *H)
{
    trocaCor(H);
    if (cor(H->dir->esq) == RED)
    {
        H->dir = rotacionaDireita(H->dir);
        H = rotacionaEsquerda(H);
        trocaCor(H);
    }
    return H;
}

// Função para mover um nó vermelho para a direita
struct NO *move2DirRED(struct NO *H)
{
    trocaCor(H);
    if (cor(H->esq->esq) == RED)
    {
        H = rotacionaDireita(H);
        trocaCor(H);
    }
    return H;
}

// Função para procurar o menor elemento
struct NO *procuraMenor(struct NO *atual)
{
    struct NO *no1 = atual;
    struct NO *no2 = atual->esq;
    while (no2 != NULL)
    {
        no1 = no2;
        no2 = no2->esq;
    }
    return no1;
}

// Função para remover o menor elemento
struct NO *removerMenor(struct NO *H)
{
    if (H->esq == NULL)
    {
        free(H);
        return NULL;
    }
    if (cor(H->esq) == BLACK && cor(H->esq->esq) == BLACK)
        H = move2EsqRED(H);
    H->esq = removerMenor(H->esq);
    return balancer(H);
}

// Função para balancear a árvore após remoção
struct NO *balancer(struct NO *H)
{
    // Garante que a árvore seja left-leaning e corrige violações
    if (cor(H->dir) == RED && cor(H->esq) == BLACK)
        H = rotacionaEsquerda(H);
    if (cor(H->esq) == RED && cor(H->esq->esq) == RED)
        H = rotacionaDireita(H);
    if (cor(H->esq) == RED && cor(H->dir) == RED)
        trocaCor(H);
    return H;
}

// Função para remover um nó com o valor especificado
struct NO *remove_NO(struct NO *H, int valor)
{
    if (valor < H->info)
    {
        if (cor(H->esq) == BLACK && cor(H->esq->esq) == BLACK)
            H = move2EsqRED(H);
        H->esq = remove_NO(H->esq, valor);
    }
    else
    {
        if (cor(H->esq) == RED)
            H = rotacionaDireita(H);
        if (valor == H->info && H->dir == NULL)
        {
            free(H);
            return NULL;
        }
        if (cor(H->dir) == BLACK && cor(H->dir->esq) == BLACK)
            H = move2DirRED(H);
        if (valor == H->info)
        {
            struct NO *x = procuraMenor(H->dir);
            H->info = x->info;
            H->dir = removerMenor(H->dir);
        }
        else
        {
            H->dir = remove_NO(H->dir, valor);
        }
    }
    return balancer(H);
}

// Função principal de remoção
int remove_ArvLLRB(ArvLLRB *raiz, int valor)
{
    // Assumindo que consulta_ArvLLRB verifica se o valor existe
    if (consulta_ArvLLRB(raiz, valor))
    {
        struct NO *h = *raiz;
        *raiz = remove_NO(h, valor);
        if (*raiz != NULL)
            (*raiz)->cor = BLACK;
        return 1;
    }
    else
    {
        return 0;
    }
}

// Função auxiliar para consulta (não fornecida no PDF, implementação genérica)
int consulta_ArvLLRB(ArvLLRB *raiz, int valor)
{
    struct NO *atual = *raiz;
    while (atual != NULL)
    {
        if (valor == atual->info)
            return 1;
        else if (valor < atual->info)
            atual = atual->esq;
        else
            atual = atual->dir;
    }
    return 0;
}