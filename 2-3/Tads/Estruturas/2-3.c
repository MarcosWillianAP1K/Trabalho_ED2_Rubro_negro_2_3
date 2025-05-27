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
    UNDERFLOW
} StatusRemocao;

// Prototipos das Funcoes

StatusRemocao tratar_underflow(Arv23 **ponteiro_filho_no_pai, Arv23 *pai);
StatusRemocao redistribuir_com_irmao_esquerdo(Arv23 **ponteiro_filho_no_pai, Arv23 *pai, Arv23 *irmao_esq, int pos_filho);
StatusRemocao redistribuir_com_irmao_direito(Arv23 **ponteiro_filho_no_pai, Arv23 *pai, Arv23 *irmao_dir, int pos_filho);
StatusRemocao fundir_com_irmao_esquerdo(Arv23 **ponteiro_filho_no_pai, Arv23 *pai, Arv23 *irmao_esq, int pos_filho);
StatusRemocao fundir_com_irmao_direito(Arv23 **ponteiro_filho_no_pai, Arv23 *pai, Arv23 *irmao_dir, int pos_filho);

//================ CRIA NO ==================
Arv23 *cria_no(DADOS info, Arv23 *F_esq, Arv23 *F_cen)
{
    Arv23 *no = (Arv23 *)malloc(sizeof(Arv23));

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

//================ FUNCOES AUXILIARES  ==================

// //Verifica se o no e uma folha (sem filhos)
short int eh_folha(Arv23 *no)
{
    short int resultado = 0;
    if (no != NULL)
    {
        resultado = (no->esq == NULL && no->cen == NULL && no->dir == NULL);
    }
    return resultado;
}

//================ FUNCOES AUXILIARES DA REMOCAO==================

// // Busca o menor elemento na subarvore a partir do no dado
// Arv23 *buscar_menor_elemento(Arv23 *no)
// {
//     Arv23 *resultado = NULL;
//     if (no != NULL)
//     {
//         Arv23 *atual = no;
//         while (atual != NULL && atual->esq != NULL)
//         {
//             atual = atual->esq;
//         }
//         resultado = atual;
//     }
//     return resultado;
// }

// // Funcao principal para tratar underflow
// StatusRemocao tratar_underflow(Arv23 **ponteiro_filho_no_pai, Arv23 *pai)
// {
//     StatusRemocao status_final = OK;
//     Arv23 *filho_com_underflow = *ponteiro_filho_no_pai;

//     if (filho_com_underflow == NULL || filho_com_underflow->nInfo > 0)
//     {
//         status_final = OK;
//     }
//     else if (pai == NULL)
//     {
//         status_final = UNDERFLOW; // Underflow na raiz sera tratado em remover_23
//     }
//     else
//     {
//         printf("Tratando underflow no filho (nInfo=0, %p) do pai [%d%s%d] (%p)...\n",
//                (void *)filho_com_underflow,
//                pai->info1, pai->nInfo == 2 ? ", " : " ", pai->nInfo == 2 ? pai->info2 : -1,
//                (void *)pai);

//         Arv23 *irmao_esq = NULL;
//         Arv23 *irmao_dir = NULL;
//         int pos_filho = -1;

//         // Identifica a posicao do filho e seus irmaos
//         if (pai->esq == filho_com_underflow)
//         {
//             pos_filho = 0;
//             irmao_dir = pai->cen;
//             printf("Filho em underflow e o ESQUERDO. Irmao direito: %p\n", (void *)irmao_dir);
//         }
//         else if (pai->cen == filho_com_underflow)
//         {
//             pos_filho = 1;
//             irmao_esq = pai->esq;
//             if (pai->nInfo == 2)
//             {
//                 irmao_dir = pai->dir;
//             }
//             printf("Filho em underflow e o CENTRAL. Irmao esquerdo: %p, Irmao direito: %p\n", (void *)irmao_esq, (void *)irmao_dir);
//         }
//         else if (pai->nInfo == 2 && pai->dir == filho_com_underflow)
//         {
//             pos_filho = 2;
//             irmao_esq = pai->cen;
//             printf("Filho em underflow e o DIREITO. Irmao esquerdo: %p\n", (void *)irmao_esq);
//         }

//         // Prioridade: Redistribuicao
//         if (irmao_dir != NULL && irmao_dir->nInfo == 2)
//         {
//             printf("Tentando redistribuicao com irmao direito [%d, %d]\n", irmao_dir->info1, irmao_dir->info2);
//             status_final = redistribuir_com_irmao_direito(ponteiro_filho_no_pai, pai, irmao_dir, pos_filho);
//         }
//         else if (irmao_esq != NULL && irmao_esq->nInfo == 2)
//         {
//             printf("Tentando redistribuicao com irmao esquerdo [%d, %d]\n", irmao_esq->info1, irmao_esq->info2);
//             status_final = redistribuir_com_irmao_esquerdo(ponteiro_filho_no_pai, pai, irmao_esq, pos_filho);
//         }
//         // Se nao foi possivel redistribuir, tenta fusao
//         else if (irmao_dir != NULL && irmao_dir->nInfo == 1)
//         {
//             printf("Tentando fusao com irmao direito [%d]\n", irmao_dir->info1);
//             status_final = fundir_com_irmao_direito(ponteiro_filho_no_pai, pai, irmao_dir, pos_filho);
//         }
//         else if (irmao_esq != NULL && irmao_esq->nInfo == 1)
//         {
//             printf("Tentando fusao com irmao esquerdo [%d]\n", irmao_esq->info1);
//             status_final = fundir_com_irmao_esquerdo(ponteiro_filho_no_pai, pai, irmao_esq, pos_filho);
//         }
//         // Caso critico: Nao ha irmaos ou os irmaos nao podem ajudar (nao deveria ocorrer em arvore valida, exceto raiz)
//         else
//         {
//             // Este caso pode ocorrer se o pai for um 2-no e o outro filho ja foi fundido/removido
//             // Se o pai tem nInfo=0, o underflow sera propagado.
//             // Se o pai tem nInfo=1, e este filho e o unico, o pai entrara em underflow.
//             // A logica de fusao ja deve ter tratado isso e retornado UNDERFLOW.
//             // Se chegamos aqui, algo esta errado.
//             fprintf(stderr, "Erro critico: Nao foi possivel tratar underflow por redistribuicao ou fusao. Pai: [%d%s%d], Filho pos: %d, irmao_esq: %p, irmao_dir: %p\n",
//                     pai->info1, pai->nInfo == 2 ? ", " : " ", pai->nInfo == 2 ? pai->info2 : -1, pos_filho, (void *)irmao_esq, (void *)irmao_dir);
//             // Retorna OK para evitar loop, mas a arvore pode estar invalida.
//             status_final = OK;
//         }
//     }

//     return status_final;
// }

// // Redistribui do irmao esquerdo (3-no) para o filho (underflow)
// StatusRemocao redistribuir_com_irmao_esquerdo(Arv23 **ponteiro_filho_no_pai, Arv23 *pai, Arv23 *irmao_esq, int pos_filho)
// {
//     printf("Redistribuindo com irmao esquerdo...\n");
//     Arv23 *filho = *ponteiro_filho_no_pai;
//     int chave_pai_desce;
//     Arv23 *filho_transferido = irmao_esq->dir;
//     Arv23 *filho_original_unico = (filho->esq != NULL) ? filho->esq : filho->cen;

//     if (pos_filho == 1)
//     {
//         chave_pai_desce = pai->info1;
//         pai->info1 = irmao_esq->info2;
//     }
//     else
//     { // pos_filho == 2
//         chave_pai_desce = pai->info2;
//         pai->info2 = irmao_esq->info2;
//     }

//     filho->info1 = chave_pai_desce;
//     filho->nInfo = 1;
//     filho->esq = filho_transferido;
//     filho->cen = filho_original_unico;
//     filho->dir = NULL;

//     irmao_esq->nInfo = 1;
//     irmao_esq->info2 = 0;
//     irmao_esq->dir = NULL; // Filho dir foi transferido

//     return OK;
// }

// // Redistribui do irmao direito (3-no) para o filho (underflow)
// StatusRemocao redistribuir_com_irmao_direito(Arv23 **ponteiro_filho_no_pai, Arv23 *pai, Arv23 *irmao_dir, int pos_filho)
// {
//     printf("Redistribuindo com irmao direito...\n");
//     Arv23 *filho = *ponteiro_filho_no_pai;
//     int chave_pai_desce;
//     Arv23 *filho_transferido = irmao_dir->esq;
//     Arv23 *filho_original_unico = (filho->esq != NULL) ? filho->esq : filho->cen;

//     if (pos_filho == 0)
//     {
//         chave_pai_desce = pai->info1;
//         pai->info1 = irmao_dir->info1;
//     }
//     else
//     { // pos_filho == 1
//         chave_pai_desce = pai->info2;
//         pai->info2 = irmao_dir->info1;
//     }

//     filho->info1 = chave_pai_desce;
//     filho->nInfo = 1;
//     filho->esq = filho_original_unico;
//     filho->cen = filho_transferido;
//     filho->dir = NULL;

//     irmao_dir->info1 = irmao_dir->info2;
//     irmao_dir->nInfo = 1;
//     irmao_dir->info2 = 0;
//     irmao_dir->esq = irmao_dir->cen;
//     irmao_dir->cen = irmao_dir->dir;
//     irmao_dir->dir = NULL;

//     return OK;
// }

// // Funde o filho (underflow) com o irmao esquerdo (2-no)
// StatusRemocao fundir_com_irmao_esquerdo(Arv23 **ponteiro_filho_no_pai, Arv23 *pai, Arv23 *irmao_esq, int pos_filho)
// {
//     printf("Fundindo filho (%p) com irmao esquerdo [%d] (%p)...\n", (void *)*ponteiro_filho_no_pai, irmao_esq->info1, (void *)irmao_esq);
//     Arv23 *filho_underflow = *ponteiro_filho_no_pai;
//     int chave_pai_desce;
//     StatusRemocao status_pai = OK;

//     Arv23 *filho_u_remanescente = (filho_underflow->esq != NULL) ? filho_underflow->esq : filho_underflow->cen;
//     Arv23 *irmao_e_esq = irmao_esq->esq;
//     Arv23 *irmao_e_cen = irmao_esq->cen;

//     // Determina a chave que desce do pai e ajusta o pai
//     if (pai->nInfo == 1)
//     {
//         chave_pai_desce = pai->info1;
//         pai->nInfo = 0; // Pai entra em underflow
//         pai->info1 = 0;
//         status_pai = UNDERFLOW;
//         printf("Pai [2-no] entra em underflow. Chave descendo: %d\n", chave_pai_desce);
//     }
//     else
//     { // Pai era 3-no, ficara 2-no
//         if (pos_filho == 1)
//         { // Filho era o central (pai->cen)
//             chave_pai_desce = pai->info1;
//             pai->info1 = pai->info2;
//             printf("Pai [3-no], filho=cen. Chave descendo: %d. Pai vira [%d]\n", chave_pai_desce, pai->info1);
//         }
//         else
//         { // pos_filho == 2 (Filho era o direito, pai->dir)
//             chave_pai_desce = pai->info2;
//             printf("Pai [3-no], filho=dir. Chave descendo: %d. Pai vira [%d]\n", chave_pai_desce, pai->info1);
//         }
//         pai->info2 = 0;
//         pai->nInfo = 1;
//         status_pai = OK;
//     }

//     // Realiza a fusao no irmao esquerdo (que se torna um 3-no)
//     irmao_esq->info2 = chave_pai_desce;
//     irmao_esq->nInfo = 2;
//     irmao_esq->esq = irmao_e_esq;
//     irmao_esq->cen = irmao_e_cen;
//     irmao_esq->dir = filho_u_remanescente;
//     printf("Irmao esquerdo [%d] fundido -> [%d, %d]. Filhos: %p, %p, %p\n",
//            irmao_esq->info1, irmao_esq->info1, irmao_esq->info2,
//            (void *)irmao_esq->esq, (void *)irmao_esq->cen, (void *)irmao_esq->dir);

//     // Ajusta os ponteiros do PAI para refletir a fusao
//     // O irmao esquerdo (que absorveu o filho) permanece onde estava (pai->esq ou pai->cen)
//     if (pos_filho == 1)
//     { // Filho era pai->cen. Irmao esq era pai->esq.
//         // Remove o filho do centro, movendo o da direita (se existir) para o centro.
//         pai->cen = pai->dir;
//         pai->dir = NULL;
//         printf("Ajuste pai (filho=cen): pai->cen=%p, pai->dir=NULL\n", (void *)pai->cen);
//     }
//     else
//     { // pos_filho == 2. Filho era pai->dir. Irmao esq era pai->cen.
//         // Remove o filho da direita.
//         pai->dir = NULL;
//         printf("Ajuste pai (filho=dir): pai->dir=NULL\n");
//     }
//     // Se pai entrou em underflow (era 2-no), ele tera apenas pai->esq apontando para irmao_esq
//     if (status_pai == UNDERFLOW)
//     {
//         // O unico filho remanescente e o irmao_esq, que esta em pai->esq
//         pai->cen = NULL;
//         pai->dir = NULL;
//         printf("Ajuste pai (underflow): pai->cen=NULL, pai->dir=NULL\n");
//     }

//     printf("Liberando no em underflow (%p) (anteriormente filho na pos %d do pai)\n", (void *)filho_underflow, pos_filho);
//     free(filho_underflow);
//     // *ponteiro_filho_no_pai = NULL; // Nao necessario, ponteiro no pai foi ajustado

//     printf("Fusao com irmao esquerdo concluida. No resultante [%d, %d]. Status pai: %s\n",
//            irmao_esq->info1, irmao_esq->info2, status_pai == OK ? "OK" : "UNDERFLOW");

//     return status_pai;
// }

// // Funde o filho (underflow) com o irmao direito (2-no)
// StatusRemocao fundir_com_irmao_direito(Arv23 **ponteiro_filho_no_pai, Arv23 *pai, Arv23 *irmao_dir, int pos_filho)
// {
//     printf("Fundindo filho (%p) com irmao direito [%d] (%p)...\n", (void *)*ponteiro_filho_no_pai, irmao_dir->info1, (void *)irmao_dir);
//     Arv23 *filho_underflow = *ponteiro_filho_no_pai;
//     int chave_pai_desce;
//     StatusRemocao status_pai = OK;

//     Arv23 *filho_u_remanescente = (filho_underflow->esq != NULL) ? filho_underflow->esq : filho_underflow->cen;
//     Arv23 *irmao_d_esq = irmao_dir->esq;
//     Arv23 *irmao_d_cen = irmao_dir->cen;

//     // Determina a chave que desce do pai e ajusta o pai
//     if (pai->nInfo == 1)
//     {
//         chave_pai_desce = pai->info1;
//         pai->nInfo = 0;
//         pai->info1 = 0;
//         status_pai = UNDERFLOW;
//         printf("Pai [2-no] entra em underflow. Chave descendo: %d\n", chave_pai_desce);
//     }
//     else
//     { // Pai era 3-no, ficara 2-no
//         if (pos_filho == 0)
//         { // Filho era o esquerdo (pai->esq)
//             chave_pai_desce = pai->info1;
//             pai->info1 = pai->info2;
//             printf("Pai [3-no], filho=esq. Chave descendo: %d. Pai vira [%d]\n", chave_pai_desce, pai->info1);
//         }
//         else
//         { // pos_filho == 1 (Filho era o central, pai->cen)
//             chave_pai_desce = pai->info2;
//             printf("Pai [3-no], filho=cen. Chave descendo: %d. Pai vira [%d]\n", chave_pai_desce, pai->info1);
//         }
//         pai->info2 = 0;
//         pai->nInfo = 1;
//         status_pai = OK;
//     }

//     // Realiza a fusao no irmao direito (que se torna um 3-no)
//     irmao_dir->info2 = irmao_dir->info1;
//     irmao_dir->info1 = chave_pai_desce;
//     irmao_dir->nInfo = 2;
//     irmao_dir->esq = filho_u_remanescente;
//     irmao_dir->cen = irmao_d_esq;
//     irmao_dir->dir = irmao_d_cen;
//     printf("Irmao direito [%d] fundido -> [%d, %d]. Filhos: %p, %p, %p\n",
//            irmao_dir->info2, // info original
//            irmao_dir->info1, irmao_dir->info2,
//            (void *)irmao_dir->esq, (void *)irmao_dir->cen, (void *)irmao_dir->dir);

//     // Ajusta os ponteiros do PAI para refletir a fusao
//     // O irmao direito (que absorveu o filho) substitui a si mesmo e ao filho.
//     if (pos_filho == 0)
//     { // Filho era pai->esq. Irmao dir era pai->cen.
//         // Remove o filho da esquerda, movendo o irmao (centro) para a esquerda
//         // e o da direita (se existir) para o centro.
//         pai->esq = pai->cen; // irmao_dir estava em pai->cen
//         pai->cen = pai->dir;
//         pai->dir = NULL;
//         printf("Ajuste pai (filho=esq): pai->esq=%p, pai->cen=%p, pai->dir=NULL\n", (void *)pai->esq, (void *)pai->cen);
//     }
//     else
//     { // pos_filho == 1. Filho era pai->cen. Irmao dir era pai->dir.
//         // Remove o filho do centro, movendo o irmao (direita) para o centro.
//         pai->cen = pai->dir; // irmao_dir estava em pai->dir
//         pai->dir = NULL;
//         printf("Ajuste pai (filho=cen): pai->cen=%p, pai->dir=NULL\n", (void *)pai->cen);
//     }
//     // Se pai entrou em underflow (era 2-no), ele tera apenas pai->esq apontando para irmao_dir
//     if (status_pai == UNDERFLOW)
//     {
//         // O unico filho remanescente e o irmao_dir, que agora esta em pai->esq
//         pai->cen = NULL;
//         pai->dir = NULL;
//         printf("Ajuste pai (underflow): pai->esq=%p, pai->cen=NULL, pai->dir=NULL\n", (void *)pai->esq);
//     }

//     printf("Liberando no em underflow (%p) (anteriormente filho na pos %d do pai)\n", (void *)filho_underflow, pos_filho);
//     free(filho_underflow);
//     // *ponteiro_filho_no_pai = NULL; // Nao necessario, ponteiro no pai foi ajustado

//     printf("Fusao com irmao direito concluida. No resultante [%d, %d]. Status pai: %s\n",
//            irmao_dir->info1, irmao_dir->info2, status_pai == OK ? "OK" : "UNDERFLOW");

//     return status_pai;
// }

// //================ REMOCAO (Recursiva) ==================
// StatusRemocao remover_23_recursivo(Arv23 **ponteiro_no_atual, int valor, short int (*comparar)(DADOS, DADOS))
// {
//     StatusRemocao status_final = OK;
//     Arv23 *no_atual = *ponteiro_no_atual;

//     if (no_atual == NULL)
//     {
//         printf("Valor %d nao encontrado na subarvore.\n", valor);
//         status_final = OK;
//     }
//     else
//     {
//         // printf("Visitando no [%d%s%d] (%p) para remover %d (Pai: %p)\n", no_atual->info1,
//         //        no_atual->nInfo==2 ? ", " : " ", no_atual->nInfo==2 ? no_atual->info2 : -1,
//         //        (void*)no_atual, valor, (void*)pai_do_no_atual);

//         Arv23 **proximo_ponteiro_recursao = NULL;
//         int valor_encontrado_neste_no = 0;
//         int indice_valor_removido = -1;

//         if (valor == no_atual->info1)
//         {
//             valor_encontrado_neste_no = 1;
//             indice_valor_removido = 0;
//         }
//         else if (no_atual->nInfo == 2 && valor == no_atual->info2)
//         {
//             valor_encontrado_neste_no = 1;
//             indice_valor_removido = 1;
//         }
//         else if (valor < no_atual->info1)
//         {
//             proximo_ponteiro_recursao = &(no_atual->esq);
//         }
//         else if (no_atual->nInfo == 1 || valor < no_atual->info2)
//         {
//             proximo_ponteiro_recursao = &(no_atual->cen);
//         }
//         else
//         {
//             proximo_ponteiro_recursao = &(no_atual->dir);
//         }

//         if (valor_encontrado_neste_no)
//         {
//             printf("Valor %d encontrado no no [%d%s%d]\n", valor, no_atual->info1,
//                    no_atual->nInfo == 2 ? ", " : " ", no_atual->nInfo == 2 ? no_atual->info2 : -1);

//             if (eh_folha(no_atual))
//             {
//                 printf("Removendo %d de um no FOLHA.\n", valor);
//                 if (no_atual->nInfo == 2)
//                 {
//                     printf("Folha e 3-no. Remocao simples.\n");
//                     if (indice_valor_removido == 0)
//                     {
//                         no_atual->info1 = no_atual->info2;
//                     }
//                     no_atual->info2 = 0;
//                     no_atual->nInfo = 1;
//                     status_final = OK;
//                 }
//                 else
//                 {
//                     printf("Folha e 2-no. Remocao causa UNDERFLOW.\n");
//                     no_atual->nInfo = 0;
//                     no_atual->info1 = 0;
//                     status_final = UNDERFLOW;
//                 }
//             }
//             else
//             {
//                 printf("Removendo %d de um no INTERNO. Substituindo por sucessor.\n", valor);
//                 Arv23 *sucessor_node = NULL;
//                 int valor_sucessor;
//                 Arv23 **ponteiro_subarvore_sucessor;

//                 if (indice_valor_removido == 0)
//                 {
//                     sucessor_node = buscar_menor_elemento(no_atual->cen);
//                     ponteiro_subarvore_sucessor = &(no_atual->cen);
//                 }
//                 else
//                 {
//                     sucessor_node = buscar_menor_elemento(no_atual->dir);
//                     ponteiro_subarvore_sucessor = &(no_atual->dir);
//                 }

//                 if (sucessor_node == NULL)
//                 {
//                     fprintf(stderr, "Erro critico: Sucessor nao encontrado para valor %d no no interno!\n", valor);
//                     status_final = OK;
//                 }
//                 else
//                 {
//                     valor_sucessor = sucessor_node->info1;
//                     printf("Sucessor encontrado: %d. Substituindo %d por %d no no atual.\n", valor_sucessor, valor, valor_sucessor);

//                     if (indice_valor_removido == 0)
//                     {
//                         no_atual->info1 = valor_sucessor;
//                     }
//                     else
//                     {
//                         no_atual->info2 = valor_sucessor;
//                     }

//                     printf("Removendo recursivamente o sucessor %d da subarvore apropriada...\n", valor_sucessor);
//                     StatusRemocao status_remocao_sucessor = remover_23_recursivo(ponteiro_subarvore_sucessor, valor_sucessor);

//                     if (status_remocao_sucessor == UNDERFLOW)
//                     {
//                         printf("Underflow apos remover sucessor %d. Tratando na subarvore (pai=%p)...\n", valor_sucessor, (void *)no_atual);
//                         status_final = tratar_underflow(ponteiro_subarvore_sucessor, no_atual);
//                     }
//                     else
//                     {
//                         status_final = status_remocao_sucessor;
//                     }
//                 }
//             }
//         }
//         else
//         {
//             // printf("Valor %d nao encontrado neste no. Descendo para a subarvore...\n", valor);
//             StatusRemocao status_recursao = remover_23_recursivo(proximo_ponteiro_recursao, valor);

//             if (status_recursao == UNDERFLOW)
//             {
//                 printf("Underflow retornado da subarvore. Tratando no nivel atual (pai=%p)...\n", (void *)no_atual);
//                 status_final = tratar_underflow(proximo_ponteiro_recursao, no_atual);
//             }
//             else
//             {
//                 status_final = status_recursao;
//             }
//         }
//     }

//     return status_final;
// }

// //================ REMOCAO (Principal) ==================

// short int remover_23(Arv23 **raiz, DADOS valor, short int (*comparar)(DADOS, DADOS))
// {
//     short int sucesso = 0; // 0 para falha, 1 para sucesso

//     if (raiz == NULL || *raiz == NULL)
//     {
//         printf("Arvore vazia. Nao e possivel remover %d.\n", valor);
//         sucesso = 0;
//     }
//     else
//     {
//         printf("\n--- Iniciando remocao de %d ---\n", valor);
//         // Chama a funcao recursiva, passando a raiz e NULL como pai inicial
//         StatusRemocao status_geral = remover_23_recursivo(raiz, valor);

//         // CORRECAO: Verifica se a raiz ficou vazia (nInfo=0) APOS a remocao recursiva,
//         // independentemente do status retornado. Isso trata o caso onde a ultima fusao
//         // ocorreu no nivel superior e deixou a raiz vazia, mas retornou OK, ou
//         // se a remocao na propria raiz (sendo 2-no folha) causou underflow.
//         if (*raiz != NULL && (*raiz)->nInfo == 0)
//         {
//             printf("Raiz (%p) entrou em underflow (nInfo=0). Ajustando a raiz da arvore...\n", (void *)*raiz);
//             Arv23 *raiz_antiga = *raiz;
//             Arv23 *nova_raiz = NULL;

//             // A nova raiz e o unico filho nao-NULL da raiz antiga.
//             // Apos uma fusao que causa underflow na raiz, ou remocao da unica chave da raiz,
//             // ela tera apenas um filho, que deve estar em ->esq.
//             if (raiz_antiga->esq != NULL)
//             {
//                 nova_raiz = raiz_antiga->esq;
//                 printf("Nova raiz sera o filho esquerdo [%d%s%d] (%p) da antiga raiz.\n",
//                        nova_raiz->info1, nova_raiz->nInfo == 2 ? ", " : " ", nova_raiz->nInfo == 2 ? nova_raiz->info2 : -1,
//                        (void *)nova_raiz);
//             }
//             else if (raiz_antiga->cen != NULL)
//             {
//                 // Este caso nao deveria ocorrer se a logica de fusao estiver correta.
//                 nova_raiz = raiz_antiga->cen;
//                 printf("Nova raiz sera o filho central [%d%s%d] (%p) da antiga raiz (Inesperado!).\n",
//                        nova_raiz->info1, nova_raiz->nInfo == 2 ? ", " : " ", nova_raiz->nInfo == 2 ? nova_raiz->info2 : -1,
//                        (void *)nova_raiz);
//             }
//             else
//             {
//                 // Se nao tem nem esq nem cen, a arvore ficou vazia
//                 nova_raiz = NULL;
//                 printf("Arvore ficou vazia apos remocao da raiz.\n");
//             }

//             *raiz = nova_raiz; // Atualiza o ponteiro da raiz

//             printf("Liberando no da raiz antiga em underflow (%p).\n", (void *)raiz_antiga);
//             free(raiz_antiga);
//             status_geral = OK; // Considera o underflow da raiz resolvido
//         }

//         // Define o sucesso baseado no status final E se a raiz e valida
//         if (status_geral == OK)
//         {
//             printf("--- Remocao de %d concluida com sucesso ---\n", valor);
//             sucesso = 1;
//         }
//         else
//         {
//             fprintf(stderr, "--- Erro: Remocao de %d falhou ou deixou a arvore invalida (raiz->nInfo=%d) ---\n",
//                     valor, (*raiz != NULL ? (*raiz)->nInfo : -1));
//             sucesso = 0;
//         }
//     }

//     return sucesso;
// }



//================ FUNCOES AUXILIARES INSERCAO  ==================

void adiciona_infos(Arv23 **no, DADOS info, Arv23 *Sub_Arv_Info, short int (*comparar)(DADOS, DADOS))
{
    Arv23 *no_atual = *no;
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

Arv23 *quebra_no(Arv23 **no, DADOS info, DADOS *sobe, Arv23 *F_dir, short int (*comparar)(DADOS, DADOS))
{
    Arv23 *no_atual = *no;
    Arv23 *maior = NULL;
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

short int inserir_23_recursivo(Arv23 **raiz, DADOS valor, DADOS *sobe, Arv23 **maiorNo, short int (*comparar)(DADOS, DADOS))
{
    short int sucesso = 0;
    Arv23 *no_atual = *raiz;

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
            Arv23 **proximo_filho;
            if (comparar(valor, no_atual->info1) < 0)
            {
                proximo_filho = &(no_atual->esq);
            }
            else if (no_atual->nInfo == 1 || comparar(valor, no_atual->info2) < 0)
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
                Arv23 *novo_filho_dir = *maiorNo;
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
            // else
            // {
            //     sucesso = sucesso_rec;
            // }
        }
    }

    return sucesso;
}

//================ INSERCAO PRINCIPAL  ==================

short int inserir_23(Arv23 **raiz, DADOS valor, short int (*comparar)(DADOS, DADOS))
{
    DADOS sobe;
    Arv23 *maiorNo = NULL;
    short int sucesso = 0;

    if (raiz != NULL)
    {
        sucesso = inserir_23_recursivo(raiz, valor, &sobe, &maiorNo, comparar);

        if (maiorNo != NULL)
        {
            Arv23 *nova_raiz = cria_no(sobe, *raiz, maiorNo);

            if (nova_raiz != NULL)
            {
                *raiz = nova_raiz;
            }
        }
    }
    return sucesso;
}

//=============== IMPRIMIR ==================
void imprimir_23_em_ordem(Arv23 *raiz, void (*imprimir)(DADOS))
{
    if (raiz != NULL)
    {
        // Adiciona verificacao defensiva contra nInfo invalido
        if (raiz->nInfo > 0)
        {
            imprimir_23_em_ordem(raiz->esq, imprimir);
            imprimir(raiz->info1);
            imprimir_23_em_ordem(raiz->cen, imprimir);
            if (raiz->nInfo == 2)
            {
                imprimir(raiz->info2);
                imprimir_23_em_ordem(raiz->dir, imprimir);
            }
        }
    }
}

void imprimir_arvore_visual(Arv23 *raiz, char *prefixo, short int eh_ultimo, short int eh_raiz, void (*imprimir)(DADOS))
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
            printf("||||||||");
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

void liberar_no_23(Arv23 **no, void (*liberar)(DADOS *))
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

void liberar_23(Arv23 **raiz, void (*liberar)(DADOS *))
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
void menu(Arv23 **raiz)
{
    DADOS dado1;
    dado1.CEP = "12345-678";

    DADOS dado2;
    dado2.CEP = "23456-789";

    DADOS dado3;
    dado3.CEP = "34567-890";

    DADOS dado4;
    dado4.CEP = "45678-901";

    DADOS dado5;
    dado5.CEP = "56789-012";

    DADOS dado6;
    dado6.CEP = "67890-123";

    DADOS dado7;
    dado7.CEP = "78901-234";

    DADOS dado8;
    dado8.CEP = "89012-345";

    DADOS dado9;
    dado9.CEP = "90123-456";



    if (inserir_23(raiz, dado1, comparar_dados_CEP) == 1)
    {
        printf("Inserido: %s\n", dado1.CEP);
    }
    else
    {
        printf("Falha ao inserir: %s\n", dado1.CEP);
    }

    if (inserir_23(raiz, dado2, comparar_dados_CEP) == 1)
    {
        printf("Inserido: %s\n", dado2.CEP);
    }
    else
    {
        printf("Falha ao inserir: %s\n", dado2.CEP);
    }

    if (inserir_23(raiz, dado3, comparar_dados_CEP) == 1)
    {
        printf("Inserido: %s\n", dado3.CEP);
    }
    else
    {
        printf("Falha ao inserir: %s\n", dado3.CEP);
    }

    if (inserir_23(raiz, dado4, comparar_dados_CEP) == 1)
    {
        printf("Inserido: %s\n", dado4.CEP);
    }
    else
    {
        printf("Falha ao inserir: %s\n", dado4.CEP);
    }

    if (inserir_23(raiz, dado5, comparar_dados_CEP) == 1)
    {
        printf("Inserido: %s\n", dado5.CEP);
    }
    else
    {
        printf("Falha ao inserir: %s\n", dado5.CEP);
    }

    if (inserir_23(raiz, dado6, comparar_dados_CEP) == 1)
    {
        printf("Inserido: %s\n", dado6.CEP);
    }
    else
    {
        printf("Falha ao inserir: %s\n", dado6.CEP);
    }

    if (inserir_23(raiz, dado7, comparar_dados_CEP) == 1)
    {
        printf("Inserido: %s\n", dado7.CEP);
    }
    else
    {
        printf("Falha ao inserir: %s\n", dado7.CEP);
    }

    if (inserir_23(raiz, dado8, comparar_dados_CEP) == 1)
    {
        printf("Inserido: %s\n", dado8.CEP);
    }
    else
    {
        printf("Falha ao inserir: %s\n", dado8.CEP);
    }

    if (inserir_23(raiz, dado9, comparar_dados_CEP) == 1)
    {
        printf("Inserido: %s\n", dado9.CEP);
    }
    else
    {
        printf("Falha ao inserir: %s\n", dado9.CEP);
    }

    imprimir_23_em_ordem(*raiz, imprimir_dados_CEP); // Imprime a arvore em ordem (deve estar vazia)

}

//================ MAIN   ==================

int main()
{
    Arv23 *raiz = NULL;
    // Chama o menu interativo
    menu(&raiz);

    liberar_23(&raiz, liberar_dados_CEP); // Libera a memoria da arvore

    printf("\nPrograma encerrado. Memoria liberada.\n");

    

    return 0;
}
