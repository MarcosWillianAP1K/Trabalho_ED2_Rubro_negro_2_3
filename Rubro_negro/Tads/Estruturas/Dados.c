#include "../../Includes/Estruturas/Dados.h"
#include "../../Includes/Utilitarios/funcao_sistema.h"
#include <stdio.h>
#include <stdlib.h>

void imprimir_dados_cidade(DADOS *dado)
{
    imprimir_cidade(&dado->cidade);
}

void imprimir_dados_pessoa(DADOS *dado)
{
    imprimir_pessoa(&dado->pessoa);
}

void imprimir_dados_CEP(DADOS *dado)
{
    imprimir_CEP(dado->CEP);
}

// DADOS *alocar_dados()
// {
//     DADOS *dado = (DADOS *)malloc(sizeof(DADOS));

//     verificar_alocacao(dado);

//     return dado;
// }

// void liberar_dados(DADOS **dado)
// {
//     if(dado != NULL)
//     {
//         free(*dado);
//         *dado = NULL;
//     }
// }

void liberar_dados_cidade(DADOS *dado)
{
    if (dado != NULL)
    {
        liberar_cidade(&dado->cidade);
    }
}

void liberar_dados_pessoa(DADOS *dado)
{
    if (dado != NULL)
    {
        liberar_pessoa(&dado->pessoa);
    }
}

void liberar_dados_CEP(DADOS *dado)
{
    if (dado != NULL)
    {
        liberar_CEP(&dado->CEP);
    }
}

short int comparar_dados_nome_cidade(DADOS *dado1, DADOS *dado2)
{
    return comparar_nome_cidades(&dado1->cidade, &dado2->cidade);
}

short int comparar_dados_nome_pessoa(DADOS *dado1, DADOS *dado2)
{
    return comparar_nome_pessoas(&dado1->pessoa, &dado2->pessoa);
}

short int comparar_dados_CPF_pessoa(DADOS *dado1, DADOS *dado2)
{
    return comparar_CPF_pessoas(&dado1->pessoa, &dado2->pessoa);
}

short int comparar_dados_CEP(DADOS *dado1, DADOS *dado2)
{
    return comparar_CEPs(dado1->CEP, dado2->CEP);
}

short int comparar_dados_data_nascimento(DADOS *dado1, DADOS *dado2)
{
    return comparar_data(&dado1->pessoa.data_nascimento, &dado2->pessoa.data_nascimento);
}
