#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../Includes/Estruturas/2-3.h"
#include "../../Includes/Utilitarios/funcao_sistema.h"

// gcc -o teste 2-3.c ../Utilitarios/funcao_sistema.c Dados.c ../Objetos/CEP.C ../Objetos/Cidade.c ../Objetos/CPF.c ../Objetos/Data.c ../Objetos/Estado.c ../Objetos/Pessoa.c -I../Includes

// Enum para status da remocao
typedef enum
{
    OK,
    UNDERFLOW,
    NAO_ENCONTADO
} StatusRemocao;

// Prototipos das Funcoes

StatusRemocao tratar_underflow(AVR_23 **ponteiro_filho_no_pai, AVR_23 *pai);
StatusRemocao redistribuir_com_irmao_esquerdo(AVR_23 **ponteiro_filho_no_pai, AVR_23 *pai, AVR_23 *irmao_esq, short int pos_filho);
StatusRemocao redistribuir_com_irmao_direito(AVR_23 **ponteiro_filho_no_pai, AVR_23 *pai, AVR_23 *irmao_dir, short int pos_filho);
StatusRemocao fundir_com_irmao_esquerdo(AVR_23 **ponteiro_filho_no_pai, AVR_23 *pai, AVR_23 *irmao_esq, short int pos_filho);
StatusRemocao fundir_com_irmao_direito(AVR_23 **ponteiro_filho_no_pai, AVR_23 *pai, AVR_23 *irmao_dir, short int pos_filho);

//================ CRIA NO ==================
AVR_23 *cria_no(DADOS info, AVR_23 *F_esq, AVR_23 *F_cen)
{
    AVR_23 *no = (AVR_23 *)malloc(sizeof(AVR_23));

    verificar_alocacao(no);

    if (no != NULL)
    {
        no->info1 = info;
        no->nInfo = 1;
        no->esq = F_esq;
        no->cen = F_cen;
        no->dir = NULL;
    }

    return no;
}

//================ BUSCAR INFO ==================

DADOS *buscar_23(AVR_23 *raiz, DADOS info, short int (*comparar)(DADOS, DADOS))
{
    DADOS *retorno = NULL;

    if (raiz != NULL)
    {
        if (comparar(info, raiz->info1) == 0)
        {
            retorno = &(raiz->info1);
        }
        else if (raiz->nInfo == 2 && comparar(info, raiz->info2) == 0)
        {
            retorno = &(raiz->info2);
        }
        else if (comparar(info, raiz->info1) < 0)
        {
            retorno = buscar_23(raiz->esq, info, comparar);
        }
        else if (raiz->nInfo == 1 || comparar(info, raiz->info2) < 0)
        {
            retorno = buscar_23(raiz->cen, info, comparar);
        }
        else
        {
            retorno = buscar_23(raiz->dir, info, comparar);
        }
    }

    return retorno;
}

//================ FUNCOES AUXILIARES  ==================

// //Verifica se o no e uma folha (sem filhos)
short int eh_folha(AVR_23 *no)
{
    short int resultado = 0;
    if (no != NULL)
    {
        resultado = (no->esq == NULL && no->cen == NULL && no->dir == NULL);
    }
    return resultado;
}

//================ FUNCOES AUXILIARES DA REMOCAO==================

// Busca o menor elemento na subarvore a partir do no dado
AVR_23 *buscar_menor_elemento(AVR_23 *no)
{
    AVR_23 *resultado = NULL;
    if (no != NULL)
    {
        AVR_23 *atual = no;
        while (atual != NULL && atual->esq != NULL)
        {
            atual = atual->esq;
        }
        resultado = atual;
    }
    return resultado;
}

// Funcao principal para tratar underflow
StatusRemocao tratar_underflow(AVR_23 **ponteiro_filho_no_pai, AVR_23 *pai)
{
    StatusRemocao status_final = OK;
    AVR_23 *filho_com_underflow = *ponteiro_filho_no_pai;

    if (filho_com_underflow != NULL && filho_com_underflow->nInfo <= 0)
    {

        if (pai == NULL)
        {
            status_final = UNDERFLOW; // Underflow na raiz sera tratado em remover_23
        }
        else
        {
            // Caso de underflow: filho_com_underflow e um 2-no ou 3-no com apenas 1 info

            AVR_23 *irmao_esq = NULL;
            AVR_23 *irmao_dir = NULL;
            short int pos_filho = -1;

            // Identifica a posicao do filho e seus irmaos
            if (pai->esq == filho_com_underflow)
            {
                pos_filho = 0;
                irmao_dir = pai->cen;
            }
            else if (pai->cen == filho_com_underflow)
            {
                pos_filho = 1;
                irmao_esq = pai->esq;
                if (pai->nInfo == 2)
                {
                    irmao_dir = pai->dir;
                }
            }
            else if (pai->nInfo == 2 && pai->dir == filho_com_underflow)
            {
                pos_filho = 2;
                irmao_esq = pai->cen;
            }

            // Prioridade: Redistribuicao
            if (irmao_dir != NULL && irmao_dir->nInfo == 2)
            {
                status_final = redistribuir_com_irmao_direito(ponteiro_filho_no_pai, pai, irmao_dir, pos_filho);
            }
            else if (irmao_esq != NULL && irmao_esq->nInfo == 2)
            {
                status_final = redistribuir_com_irmao_esquerdo(ponteiro_filho_no_pai, pai, irmao_esq, pos_filho);
            }
            // Se nao foi possivel redistribuir, tenta fusao
            else if (irmao_dir != NULL && irmao_dir->nInfo == 1)
            {
                status_final = fundir_com_irmao_direito(ponteiro_filho_no_pai, pai, irmao_dir, pos_filho);
            }
            else if (irmao_esq != NULL && irmao_esq->nInfo == 1)
            {
                status_final = fundir_com_irmao_esquerdo(ponteiro_filho_no_pai, pai, irmao_esq, pos_filho);
            }
            // Caso critico: Nao ha irmaos ou os irmaos nao podem ajudar (nao deveria ocorrer em arvore valida, exceto raiz)
            else
            {
                // Este caso pode ocorrer se o pai for um 2-no e o outro filho ja foi fundido/removido
                // Se o pai tem nInfo=0, o underflow sera propagado.
                // Se o pai tem nInfo=1, e este filho e o unico, o pai entrara em underflow.
                // A logica de fusao ja deve ter tratado isso e retornado UNDERFLOW.
                // Se chegamos aqui, algo esta errado.
                // Retorna OK para evitar loop, mas a arvore pode estar invalida.
                status_final = OK;
            }
        }
    }

    return status_final;
}

// Redistribui do irmao esquerdo (3-no) para o filho (underflow)
StatusRemocao redistribuir_com_irmao_esquerdo(AVR_23 **ponteiro_filho_no_pai, AVR_23 *pai, AVR_23 *irmao_esq, short int pos_filho)
{
    AVR_23 *filho = *ponteiro_filho_no_pai;
    DADOS chave_pai_desce;
    AVR_23 *filho_transferido = irmao_esq->dir;
    AVR_23 *filho_original_unico = (filho->esq != NULL) ? filho->esq : filho->cen;

    if (pos_filho == 1)
    {
        chave_pai_desce = pai->info1;
        pai->info1 = irmao_esq->info2;
    }
    else
    { // pos_filho == 2
        chave_pai_desce = pai->info2;
        pai->info2 = irmao_esq->info2;
    }

    filho->info1 = chave_pai_desce;
    filho->nInfo = 1;
    filho->esq = filho_transferido;
    filho->cen = filho_original_unico;
    filho->dir = NULL;

    irmao_esq->nInfo = 1;
    irmao_esq->dir = NULL; // Filho dir foi transferido

    return OK;
}

// Redistribui do irmao direito (3-no) para o filho (underflow)
StatusRemocao redistribuir_com_irmao_direito(AVR_23 **ponteiro_filho_no_pai, AVR_23 *pai, AVR_23 *irmao_dir, short int pos_filho)
{
    AVR_23 *filho = *ponteiro_filho_no_pai;
    DADOS chave_pai_desce;
    AVR_23 *filho_transferido = irmao_dir->esq;
    AVR_23 *filho_original_unico = (filho->esq != NULL) ? filho->esq : filho->cen;

    if (pos_filho == 0)
    {
        chave_pai_desce = pai->info1;
        pai->info1 = irmao_dir->info1;
    }
    else
    { // pos_filho == 1
        chave_pai_desce = pai->info2;
        pai->info2 = irmao_dir->info1;
    }

    filho->info1 = chave_pai_desce;
    filho->nInfo = 1;
    filho->esq = filho_original_unico;
    filho->cen = filho_transferido;
    filho->dir = NULL;

    irmao_dir->info1 = irmao_dir->info2;
    irmao_dir->nInfo = 1;
    irmao_dir->esq = irmao_dir->cen;
    irmao_dir->cen = irmao_dir->dir;
    irmao_dir->dir = NULL;

    return OK;
}

// Funde o filho (underflow) com o irmao esquerdo (2-no)
StatusRemocao fundir_com_irmao_esquerdo(AVR_23 **ponteiro_filho_no_pai, AVR_23 *pai, AVR_23 *irmao_esq, short int pos_filho)
{
    AVR_23 *filho_underflow = *ponteiro_filho_no_pai;
    DADOS chave_pai_desce;
    StatusRemocao status_pai = OK;

    AVR_23 *filho_u_remanescente = (filho_underflow->esq != NULL) ? filho_underflow->esq : filho_underflow->cen;
    AVR_23 *irmao_e_esq = irmao_esq->esq;
    AVR_23 *irmao_e_cen = irmao_esq->cen;

    // Determina a chave que desce do pai e ajusta o pai
    if (pai->nInfo == 1)
    {
        chave_pai_desce = pai->info1;
        pai->nInfo = 0; // Pai entra em underflow
        status_pai = UNDERFLOW;
    }
    else
    { // Pai era 3-no, ficara 2-no
        if (pos_filho == 1)
        { // Filho era o central (pai->cen)
            chave_pai_desce = pai->info1;
            pai->info1 = pai->info2;
        }
        else
        { // pos_filho == 2 (Filho era o direito, pai->dir)
            chave_pai_desce = pai->info2;
        }
        pai->nInfo = 1;
        status_pai = OK;
    }

    // Realiza a fusao no irmao esquerdo (que se torna um 3-no)
    irmao_esq->info2 = chave_pai_desce;
    irmao_esq->nInfo = 2;
    irmao_esq->esq = irmao_e_esq;
    irmao_esq->cen = irmao_e_cen;
    irmao_esq->dir = filho_u_remanescente;

    // Ajusta os ponteiros do PAI para refletir a fusao
    // O irmao esquerdo (que absorveu o filho) permanece onde estava (pai->esq ou pai->cen)
    if (pos_filho == 1)
    { // Filho era pai->cen. Irmao esq era pai->esq.
        // Remove o filho do centro, movendo o da direita (se existir) para o centro.
        pai->cen = pai->dir;
        pai->dir = NULL;
    }
    else
    { // pos_filho == 2. Filho era pai->dir. Irmao esq era pai->cen.
        // Remove o filho da direita.
        pai->dir = NULL;
    }

    // Se pai entrou em underflow (era 2-no), ele tera apenas pai->esq apontando para irmao_esq
    if (status_pai == UNDERFLOW)
    {
        // O unico filho remanescente e o irmao_esq, que esta em pai->esq
        pai->cen = NULL;
        pai->dir = NULL;
    }

    // Libera apenas o no em underflow, pois o irmao esquerdo absorveu ele
    free(filho_underflow);
    // *ponteiro_filho_no_pai = NULL; // Nao necessario, ponteiro no pai foi ajustado

    return status_pai;
}

// Funde o filho (underflow) com o irmao direito (2-no)
StatusRemocao fundir_com_irmao_direito(AVR_23 **ponteiro_filho_no_pai, AVR_23 *pai, AVR_23 *irmao_dir, short int pos_filho)
{
    AVR_23 *filho_underflow = *ponteiro_filho_no_pai;
    DADOS chave_pai_desce;
    StatusRemocao status_pai = OK;

    AVR_23 *filho_u_remanescente = (filho_underflow->esq != NULL) ? filho_underflow->esq : filho_underflow->cen;
    AVR_23 *irmao_d_esq = irmao_dir->esq;
    AVR_23 *irmao_d_cen = irmao_dir->cen;

    // Determina a chave que desce do pai e ajusta o pai
    if (pai->nInfo == 1)
    {
        chave_pai_desce = pai->info1;
        pai->nInfo = 0;
        status_pai = UNDERFLOW;
        // Pai entra em underflow
    }
    else
    { // Pai era 3-no, ficara 2-no
        if (pos_filho == 0)
        { // Filho era o esquerdo (pai->esq)
            chave_pai_desce = pai->info1;
            pai->info1 = pai->info2;
            // Pai vira 2-no
        }
        else
        { // pos_filho == 1 (Filho era o central, pai->cen)
            chave_pai_desce = pai->info2;
        }
        pai->nInfo = 1;
        status_pai = OK;
    }

    // Realiza a fusao no irmao direito (que se torna um 3-no)
    irmao_dir->info2 = irmao_dir->info1;
    irmao_dir->info1 = chave_pai_desce;
    irmao_dir->nInfo = 2;
    irmao_dir->esq = filho_u_remanescente;
    irmao_dir->cen = irmao_d_esq;
    irmao_dir->dir = irmao_d_cen;

    // Ajusta os ponteiros do PAI para refletir a fusao
    // O irmao direito (que absorveu o filho) substitui a si mesmo e ao filho.
    if (pos_filho == 0)
    { // Filho era pai->esq. Irmao dir era pai->cen.
        // Remove o filho da esquerda, movendo o irmao (centro) para a esquerda
        // e o da direita (se existir) para o centro.
        pai->esq = pai->cen; // irmao_dir estava em pai->cen
        pai->cen = pai->dir;
        pai->dir = NULL;
    }
    else
    { // pos_filho == 1. Filho era pai->cen. Irmao dir era pai->dir.
        // Remove o filho do centro, movendo o irmao (direita) para o centro.
        pai->cen = pai->dir; // irmao_dir estava em pai->dir
        pai->dir = NULL;
    }
    // Se pai entrou em underflow (era 2-no), ele tera apenas pai->esq apontando para irmao_dir
    if (status_pai == UNDERFLOW)
    {
        // O unico filho remanescente e o irmao_dir, que agora esta em pai->esq
        pai->cen = NULL;
        pai->dir = NULL;
    }

    // Libera apenas o no em underflow, pois o irmao direito absorveu ele
    free(filho_underflow);

    return status_pai;
}

//================ REMOCAO (Recursiva) ==================
DADOS remover_23_recursivo(AVR_23 **ponteiro_no_atual, DADOS valor, StatusRemocao *status_final, short int (*comparar)(DADOS, DADOS))
{
    DADOS dado_removido;
    // Valor nao encontrado na subarvore
    *status_final = NAO_ENCONTADO;
    AVR_23 *no_atual = *ponteiro_no_atual;

    if (no_atual != NULL)
    {
        AVR_23 **proximo_ponteiro_recursao = NULL;
        short int valor_encontrado_neste_no = 0;
        short int indice_valor_removido = -1;

        if (comparar(valor, no_atual->info1) == 0)
        {

            dado_removido = no_atual->info1; // Armazena o valor removido
            printf("Valor removido: %s\n", dado_removido.CEP);

            valor_encontrado_neste_no = 1;
            indice_valor_removido = 0;
        }
        else if (no_atual->nInfo == 2 && comparar(valor, no_atual->info2) == 0)
        {
            dado_removido = no_atual->info2; // Armazena o valor removido
            printf("Valor removido: %s\n", dado_removido.CEP);

            valor_encontrado_neste_no = 1;
            indice_valor_removido = 1;
        }
        else if (comparar(valor, no_atual->info1) < 0)
        {
            proximo_ponteiro_recursao = &(no_atual->esq);
        }
        else if (no_atual->nInfo == 1 || comparar(valor, no_atual->info2) < 0)
        {
            proximo_ponteiro_recursao = &(no_atual->cen);
        }
        else
        {
            proximo_ponteiro_recursao = &(no_atual->dir);
        }

        if (valor_encontrado_neste_no)
        {
            if (eh_folha(no_atual))
            {
                if (no_atual->nInfo == 2)
                {
                    if (indice_valor_removido == 0)
                    {
                        no_atual->info1 = no_atual->info2;
                    }

                    no_atual->nInfo = 1;
                    *status_final = OK;
                }
                else
                {
                    no_atual->nInfo = 0;
                    *status_final = UNDERFLOW;
                }
            }
            else
            {
                AVR_23 *sucessor_node = NULL;
                DADOS valor_sucessor;
                AVR_23 **ponteiro_subarvore_sucessor;

                if (indice_valor_removido == 0)
                {
                    sucessor_node = buscar_menor_elemento(no_atual->cen);
                    ponteiro_subarvore_sucessor = &(no_atual->cen);
                }
                else
                {
                    sucessor_node = buscar_menor_elemento(no_atual->dir);
                    ponteiro_subarvore_sucessor = &(no_atual->dir);
                }

                if (sucessor_node == NULL)
                {
                    // Erro critico: Sucessor nao encontrado para valor no no interno!
                   *status_final = OK;
                }
                else
                {
                    valor_sucessor = sucessor_node->info1;
                    // Sucessor encontrado:  Substituindo

                    if (indice_valor_removido == 0)
                    {
                        no_atual->info1 = valor_sucessor;
                    }
                    else
                    {
                        no_atual->info2 = valor_sucessor;
                    }

                    // Removendo recursivamente o sucessor  da subarvore apropriada...
                    dado_removido = remover_23_recursivo(ponteiro_subarvore_sucessor, valor_sucessor, status_final, comparar);

                    if (*status_final == UNDERFLOW)
                    {
                        // Underflow apos remover sucessor . Tratando na subarvore (pai=%p)...
                        *status_final = tratar_underflow(ponteiro_subarvore_sucessor, no_atual);
                    }
                }
            }
        }
        else
        {
            // Valor nao encontrado neste no. Descendo para a subarvore...
            dado_removido = remover_23_recursivo(proximo_ponteiro_recursao, valor, status_final, comparar);

            // Se a subarvore retornou underflow, trata no nivel atual
            if (*status_final == UNDERFLOW)
            {
                // Underflow retornado da subarvore. Tratando no nivel atual ...
                *status_final = tratar_underflow(proximo_ponteiro_recursao, no_atual);
            }
        }
    }

    return dado_removido;
}

//================ REMOCAO (Principal) ==================

short int remover_23(AVR_23 **raiz, DADOS valor, DADOS *dado_removido ,  short int (*comparar)(DADOS, DADOS))
{
    short int sucesso = 0; // 0 para falha, 1 para sucesso

    if (raiz != NULL && *raiz != NULL)
    {
        // Chama a funcao recursiva, passando a raiz e NULL como pai inicial
        //Foi necessario a função retorna o dado por motivos de que estava dando erros de copia dos dados
        StatusRemocao status_geral;
       
        if (dado_removido != NULL)
        {
            *dado_removido = remover_23_recursivo(raiz, valor, &status_geral, comparar);
        }
        else
        {
            remover_23_recursivo(raiz, valor, &status_geral, comparar);
        }

        if (*raiz != NULL && (*raiz)->nInfo == 0)
        {
            AVR_23 *raiz_antiga = *raiz;
            AVR_23 *nova_raiz = NULL;

            // A nova raiz e o unico filho nao-NULL da raiz antiga.
            // Apos uma fusao que causa underflow na raiz, ou remocao da unica chave da raiz,
            // ela tera apenas um filho, que deve estar em ->esq.
            if (raiz_antiga->esq != NULL)
            {
                nova_raiz = raiz_antiga->esq;
            }
            else if (raiz_antiga->cen != NULL)
            {
                // Este caso nao deveria ocorrer se a logica de fusao estiver correta.
                nova_raiz = raiz_antiga->cen;
            }
            else
            {
                // Se nao tem nem esq nem cen, a arvore ficou vazia
                nova_raiz = NULL;
            }

            *raiz = nova_raiz; // Atualiza o ponteiro da raiz

            // printf("Liberando no da raiz antiga em underflow (%p).\n", (void *)raiz_antiga);
            free(raiz_antiga);
            status_geral = OK; // Considera o underflow da raiz resolvido
        }

        // Define o sucesso baseado no status final E se a raiz e valida
        if (status_geral == OK)
        {
            sucesso = 1;
        }
    }

    return sucesso;
}

short int remover_23_void(void **raiz, DADOS valor, DADOS *dado_removido ,  short int (*comparar)(DADOS, DADOS))
{
    short int retorno = 0;

    AVR_23 *raiz_23 = *raiz;
    retorno = remover_23(&raiz_23, valor, dado_removido, comparar);
    *raiz = raiz_23;
    return retorno;
}

//================ FUNCOES AUXILIARES INSERCAO  ==================

void adiciona_infos(AVR_23 **no, DADOS info, AVR_23 *Sub_Arv_Info, short int (*comparar)(DADOS, DADOS))
{
    AVR_23 *no_atual = *no;
    if (comparar(info, no_atual->info1) > 0)
    {
        no_atual->info2 = info;
        no_atual->dir = Sub_Arv_Info;
    }
    else
    {
        no_atual->info2 = no_atual->info1;
        no_atual->info1 = info;
        no_atual->dir = no_atual->cen;
        no_atual->cen = Sub_Arv_Info;
    }

    no_atual->nInfo = 2;
}

AVR_23 *quebra_no(AVR_23 **no, DADOS info, DADOS *sobe, AVR_23 *F_dir, short int (*comparar)(DADOS, DADOS))
{
    AVR_23 *no_atual = *no;
    AVR_23 *maior = NULL;
    if (comparar(info, no_atual->info2) > 0)
    {
        *sobe = no_atual->info2;
        maior = cria_no(info, no_atual->dir, F_dir);
        no_atual->nInfo = 1;
        no_atual->dir = NULL;
    }
    else if (comparar(info, no_atual->info1) > 0)
    {
        *sobe = info;
        maior = cria_no(no_atual->info2, F_dir, no_atual->dir);
        no_atual->nInfo = 1;
        no_atual->dir = NULL;
    }
    else
    {
        *sobe = no_atual->info1;
        maior = cria_no(no_atual->info2, no_atual->cen, no_atual->dir);
        no_atual->info1 = info;
        no_atual->cen = F_dir;
        no_atual->nInfo = 1;
        no_atual->dir = NULL;
    }

    return maior;
}

//================ INSERCAO RECURSIVA  ==================

short int inserir_23_recursivo(AVR_23 **raiz, DADOS valor, DADOS *sobe, AVR_23 **maiorNo, short int (*comparar)(DADOS, DADOS))
{
    short int sucesso = 0;
    AVR_23 *no_atual = *raiz;

    if (no_atual == NULL)
    {
        *raiz = cria_no(valor, NULL, NULL);
        *maiorNo = NULL;
        sucesso = (*raiz != NULL);
    }
    else if (comparar(valor, no_atual->info1) == 0 || (no_atual->nInfo == 2 && comparar(valor, no_atual->info2) == 0))
    {
        // Valor ja existe na arvore, nao insere
        *maiorNo = NULL;
        sucesso = 0;
    }
    else
    {
        if (eh_folha(no_atual))
        {
            if (no_atual->nInfo == 1)
            {
                adiciona_infos(raiz, valor, NULL, comparar); // Passa o endereco do ponteiro
                *maiorNo = NULL;
                sucesso = 1;
            }
            else
            {
                *maiorNo = quebra_no(raiz, valor, sobe, NULL, comparar); // Passa o endereco do ponteiro
                sucesso = (*maiorNo != NULL);
            }
        }
        else
        {
            AVR_23 **proximo_filho;
            if (comparar(valor, no_atual->info1) < 0)
            {
                proximo_filho = &(no_atual->esq);
            }
            else if ((no_atual->nInfo == 1) || (comparar(valor, no_atual->info2) < 0))
            {
                proximo_filho = &(no_atual->cen);
            }
            else
            {
                proximo_filho = &(no_atual->dir);
            }

            // short int sucesso_rec;
            sucesso = inserir_23_recursivo(proximo_filho, valor, sobe, maiorNo, comparar);

            if (*maiorNo != NULL)
            {
                DADOS chave_que_subiu = *sobe;
                AVR_23 *novo_filho_dir = *maiorNo;
                *maiorNo = NULL;

                if (no_atual->nInfo == 1)
                {
                    adiciona_infos(raiz, chave_que_subiu, novo_filho_dir, comparar); // Passa o endereco do ponteiro
                    sucesso = 1;
                }
                else
                {
                    *maiorNo = quebra_no(raiz, chave_que_subiu, sobe, novo_filho_dir, comparar); // Passa o endereco do ponteiro
                    sucesso = (*maiorNo != NULL);
                }
            }
        }
    }

    return sucesso;
}

//================ INSERCAO PRINCIPAL  ==================

short int inserir_23(AVR_23 **raiz, DADOS valor, short int (*comparar)(DADOS, DADOS))
{
    DADOS sobe;
    AVR_23 *maiorNo = NULL;
    short int sucesso = 0;

    if (raiz != NULL)
    {
        sucesso = inserir_23_recursivo(raiz, valor, &sobe, &maiorNo, comparar);

        if (maiorNo != NULL)
        {
            AVR_23 *nova_raiz = cria_no(sobe, *raiz, maiorNo);

            if (nova_raiz != NULL)
            {
                *raiz = nova_raiz;
            }
            else
            {
                sucesso = 0; // Falha na insercao
                if (maiorNo)
                    free(maiorNo); // Tenta liberar
            }
        }
    }
    return sucesso;
}

short int inserir_23_void(void **raiz, DADOS valor, short int (*comparar)(DADOS, DADOS))
{
    short int retorno = 0;

    AVR_23 *raiz_23 = *raiz;
    retorno = inserir_23(&raiz_23, valor, comparar);
    *raiz = raiz_23;
    return retorno;
}

//=============== IMPRIMIR ==================
void imprimir_23_em_ordem(AVR_23 *raiz, void (*imprimir)(DADOS))
{
    if (raiz != NULL)
    {
        // Adiciona verificacao defensiva contra nInfo invalido
        if (raiz->nInfo > 0)
        {
            imprimir_23_em_ordem(raiz->esq, imprimir);
            imprimir(raiz->info1);
            printf("  ");
            imprimir_23_em_ordem(raiz->cen, imprimir);
            if (raiz->nInfo == 2)
            {
                imprimir(raiz->info2);
                imprimir_23_em_ordem(raiz->dir, imprimir);
            }
        }
    }
}

void imprimir_arvore_visual(AVR_23 *raiz, char *prefixo, short int eh_ultimo, short int eh_raiz, void (*imprimir)(DADOS))
{
    if (raiz != NULL)
    {
        printf("%s", prefixo);
        if (!eh_raiz)
        {
            printf("%s", eh_ultimo ? "`------ " : "+------ ");
        }
        else
        {
            printf(" Raiz--> ");
        }

        if (raiz->nInfo == 1)
        {
            imprimir(raiz->info1);
            printf("\n");
            // printf("[%d] (nfo=%d, %p)\n", raiz->info1, raiz->nInfo, (void*)raiz);
        }
        else if (raiz->nInfo == 2)
        {
            imprimir(raiz->info1);
            printf(" | ");
            imprimir(raiz->info2);
            printf("\n");
            // printf("[%d, %d] (nfo=%d, %p)\n", raiz->info1, raiz->info2, raiz->nInfo, (void*)raiz);
        }
        else
        {
            // Este caso (nInfo=0) so deve ocorrer temporariamente durante a remocao
            // Se aparecer na impressao final, indica um erro.
            // printf("[UNDERFLOW!] (nfo=%d, %p)\n", raiz->nInfo, (void*)raiz);
        }

        char novo_prefixo[1024];
        sprintf(novo_prefixo, "%s%s", prefixo, eh_raiz ? "         " : (eh_ultimo ? "         " : "|        "));

        int num_filhos = 0;
        if (raiz->esq)
            num_filhos++;
        if (raiz->cen)
            num_filhos++;
        if (raiz->dir)
            num_filhos++;

        int filhos_impressos = 0;
        if (raiz->esq != NULL)
        {
            filhos_impressos++;
            imprimir_arvore_visual(raiz->esq, novo_prefixo, filhos_impressos == num_filhos, 0, imprimir);
        }
        if (raiz->cen != NULL)
        {
            filhos_impressos++;
            imprimir_arvore_visual(raiz->cen, novo_prefixo, filhos_impressos == num_filhos, 0, imprimir);
        }
        if (raiz->dir != NULL)
        {
            filhos_impressos++;
            imprimir_arvore_visual(raiz->dir, novo_prefixo, filhos_impressos == num_filhos, 0, imprimir);
        }
    }
}

//================ LIBERAR MEMORIA ==================

void liberar_no_23(AVR_23 **no, void (*liberar)(DADOS *))
{
    if (no != NULL && *no != NULL)
    {
        liberar(&(*no)->info1);
        if ((*no)->nInfo == 2)
        {
            liberar(&(*no)->info2);
        }
        free(*no);
        *no = NULL; // Define o ponteiro para NULL apos liberar
    }
}

void liberar_23(AVR_23 **raiz, void (*liberar)(DADOS *))
{
    if (raiz != NULL && *raiz != NULL)
    {

        liberar_23(&(*raiz)->esq, liberar);
        liberar_23(&(*raiz)->cen, liberar);
        if ((*raiz)->nInfo == 2)
        {
            liberar_23(&(*raiz)->dir, liberar);
        }

        liberar_no_23(raiz, liberar);
    }
}

//================ MENU para testes ==================
void menu(AVR_23 **raiz)
{
    DADOS dado1;
    dado1.cidade = criar_cidade("Cidade1", 0, NULL);

    DADOS dado2;
    dado2.cidade = criar_cidade("Cidade2", 0, NULL);

    DADOS dado3;
    dado3.cidade = criar_cidade("Cidade3", 0, NULL);

    DADOS dado4;
    dado4.cidade = criar_cidade("Cidade4", 0, NULL);

    DADOS dado5;
    dado5.cidade = criar_cidade("Cidade5", 0, NULL);

    DADOS dado6;
    dado6.cidade = criar_cidade("Cidade6", 0, NULL);

    DADOS dado7;
    dado7.cidade = criar_cidade("Cidade7", 0, NULL);

    DADOS dado8;
    dado8.cidade = criar_cidade("Cidade8", 0, NULL);

    DADOS dado9;
    dado9.cidade = criar_cidade("Cidade9", 0, NULL);

    printf("Inserindo dados na arvore 2-3...\n");

    if (inserir_23(raiz, dado1, comparar_dados_nome_cidade) == 1)
    {
        printf("Inserido: %s\n", dado1.cidade.nome);
    }
    else
    {
        printf("Falha ao inserir: %s\n", dado1.cidade.nome);
    }

    if (inserir_23(raiz, dado2, comparar_dados_nome_cidade) == 1)
    {
        printf("Inserido: %s\n", dado2.cidade.nome);
    }
    else
    {
        printf("Falha ao inserir: %s\n", dado2.cidade.nome);
    }

    if (inserir_23(raiz, dado3, comparar_dados_nome_cidade) == 1)
    {
        printf("Inserido: %s\n", dado3.cidade.nome);
    }
    else
    {
        printf("Falha ao inserir: %s\n", dado3.cidade.nome);
    }

    if (inserir_23(raiz, dado4, comparar_dados_nome_cidade) == 1)
    {
        printf("Inserido: %s\n", dado4.cidade.nome);
    }
    else
    {
        printf("Falha ao inserir: %s\n", dado4.cidade.nome);
    }

    if (inserir_23(raiz, dado5, comparar_dados_nome_cidade) == 1)
    {
        printf("Inserido: %s\n", dado5.cidade.nome);
    }
    else
    {
        printf("Falha ao inserir: %s\n", dado5.cidade.nome);
    }

    if (inserir_23(raiz, dado6, comparar_dados_nome_cidade) == 1)
    {
        printf("Inserido: %s\n", dado6.cidade.nome);
    }
    else
    {
        printf("Falha ao inserir: %s\n", dado6.cidade.nome);
    }

    if (inserir_23(raiz, dado7, comparar_dados_nome_cidade) == 1)
    {
        printf("Inserido: %s\n", dado7.cidade.nome);
    }
    else
    {
        printf("Falha ao inserir: %s\n", dado7.cidade.nome);
    }

    if (inserir_23(raiz, dado8, comparar_dados_nome_cidade) == 1)
    {
        printf("Inserido: %s\n", dado8.cidade.nome);
    }
    else
    {
        printf("Falha ao inserir: %s\n", dado8.cidade.nome);
    }

    if (inserir_23(raiz, dado9, comparar_dados_nome_cidade) == 1)
    {
        printf("Inserido: %s\n", dado9.cidade.nome);
    }
    else
    {
        printf("Falha ao inserir: %s\n", dado9.cidade.nome);
    }

    imprimir_23_em_ordem(*raiz, imprimir_dados_cidade); // Modificado para cidade
    printf("\n\n");
    imprimir_arvore_visual(*raiz, "", 1, 1, imprimir_dados_cidade); // Modificado para cidade

    printf("\nRemovendo dados da arvore 2-3...\n");

    DADOS dado_removido;

    if (remover_23(raiz, dado1, &dado_removido, comparar_dados_nome_cidade) == 1)
    {
        printf("Removido: %s\n", dado_removido.cidade.nome);
        liberar_dados_cidade(&dado_removido); // Libera a memoria do dado removido
    }
    else
    {
        printf("Falha ao remover: %s\n", dado1.cidade.nome);
    }

    if (remover_23(raiz, dado1, &dado_removido, comparar_dados_nome_cidade) == 1)
    {
        printf("Removido inexistente: \n");
        
    }
    else
    {
        printf("Falha ao remover inexistente\n");
    }

    if (remover_23(raiz, dado2, &dado_removido, comparar_dados_nome_cidade) == 1)
    {
        printf("Removido: %s\n", dado_removido.cidade.nome);
        liberar_dados_cidade(&dado_removido); // Libera a memoria do dado removido
    }
    else
    {
        printf("Falha ao remover: %s\n", dado2.cidade.nome);
    }

    if (remover_23(raiz, dado3, &dado_removido, comparar_dados_nome_cidade) == 1)
    {
        printf("Removido: %s\n", dado_removido.cidade.nome);
        liberar_dados_cidade(&dado_removido); // Libera a memoria do dado removido
    }
    else
    {
        printf("Falha ao remover: %s\n", dado3.cidade.nome);
    }

    if (remover_23(raiz, dado4, &dado_removido, comparar_dados_nome_cidade) == 1)
    {
        printf("Removido: %s\n", dado_removido.cidade.nome);
        liberar_dados_cidade(&dado_removido); // Libera a memoria do dado removido
    }
    else
    {
        printf("Falha ao remover: %s\n", dado4.cidade.nome);
    }

    if (remover_23(raiz, dado5, &dado_removido, comparar_dados_nome_cidade) == 1)
    {
        printf("Removido: %s\n", dado_removido.cidade.nome);
        liberar_dados_cidade(&dado_removido); // Libera a memoria do dado removido
    }
    else
    {
        printf("Falha ao remover: %s\n", dado5.cidade.nome);
    }

    if (remover_23(raiz, dado6, &dado_removido, comparar_dados_nome_cidade) == 1)
    {
        printf("Removido: %s\n", dado_removido.cidade.nome);
        liberar_dados_cidade(&dado_removido); // Libera a memoria do dado removido
    }
    else
    {
        printf("Falha ao remover: %s\n", dado6.cidade.nome);
    }

    if (remover_23(raiz, dado7, &dado_removido, comparar_dados_nome_cidade) == 1)
    {
        printf("Removido: %s\n", dado_removido.cidade.nome);
        liberar_dados_cidade(&dado_removido); // Libera a memoria do dado removido
    }
    else
    {
        printf("Falha ao remover: %s\n", dado7.cidade.nome);
    }

    if (remover_23(raiz, dado8, &dado_removido, comparar_dados_nome_cidade) == 1)
    {
        printf("Removido: %s\n", dado_removido.cidade.nome);
        liberar_dados_cidade(&dado_removido); // Libera a memoria do dado removido
    }
    else
    {
        printf("Falha ao remover: %s\n", dado8.cidade.nome);
    }

    if (remover_23(raiz, dado9, &dado_removido, comparar_dados_nome_cidade) == 1)
    {
        printf("Removido: %s\n", dado_removido.cidade.nome);
        liberar_dados_cidade(&dado_removido); // Libera a memoria do dado removido
    }
    else
    {
        printf("Falha ao remover: %s\n", dado9.cidade.nome);
    }

    imprimir_23_em_ordem(*raiz, imprimir_dados_cidade); // Modificado para cidade
    printf("\n\n");
    imprimir_arvore_visual(*raiz, "", 1, 1, imprimir_dados_cidade); // Modificado para cidade
}

//================ MAIN PARA TESTES  ==================

// int main()
// {
//     AVR_23 *raiz = NULL;
//     // Chama o menu interativo
//     menu(&raiz);

//     liberar_23(&raiz, liberar_dados_CEP); // Libera a memoria da arvore

//     printf("\nPrograma encerrado. Memoria liberada.\n");

//     return 0;
// }
