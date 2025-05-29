/*
 * Comando para compilar:
gcc -Wall teste_func_interatividade.c ../Tads/Estruturas/Lista_duplamente.c ../Tads/Estruturas/2-3.c ../Tads/Estruturas/Dados.c ../Tads/Interatividade/func_interatividade.c ../Tads/Objetos/Estado.c ../Tads/Objetos/Cidade.c ../Tads/Objetos/Pessoa.c ../Tads/Objetos/CEP.c ../Tads/Objetos/Data.c ../Tads/Objetos/CPF.c ../Tads/Utilitarios/funcao_sistema.c -I../Includes/
 *
 * Para executar:
 * ./a.exe
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Includes/Estruturas/Lista_duplamente.h"
#include "../Includes/Estruturas/2-3.h" // Mudança para 2-3
#include "../Includes/Estruturas/Dados.h"
#include "../Includes/Interatividade/func_interatividade.h"
#include "../Includes/Objetos/Estado.h"
#include "../Includes/Objetos/Cidade.h"
#include "../Includes/Objetos/Pessoa.h"
#include "../Includes/Objetos/CEP.h"
#include "../Includes/Objetos/Data.h"
#include "../Includes/Objetos/CPF.h"
#include "../Includes/Utilitarios/funcao_sistema.h"

// Manter de forma que a sub arvore seja o dobro da arvore atual. ou seja, se a arvore atual tiver 5 elementos, a sub arvore tera 10 elementos.
#define quantidade_estados 10
#define quantidade_cidades 20
#define quantidade_ceps 40

// Função para criar estados, cidades e CEPs
LISTA_DUPLAMENTE *povoar_estados()
{
    limpar_tela();
    print_amarelo("=== INICIANDO POVOAMENTO DE ESTADOS ===\n\n");
    // Inicializar a lista de estados
    LISTA_DUPLAMENTE *lista_estados = NULL;

    print_amarelo("=== Criando CEPs ===\n");

    // Criar 40 CEPs com formato "00000-001" até "00000-040" - alterado para ponteiros
    char *ceps[quantidade_ceps];
    for (int i = 0; i < quantidade_ceps; i++)
    {
        char temp_cep[10];
        sprintf(temp_cep, "%05d-%03d", 0, i + 1);
        limpar_buffer();
        ceps[i] = strdup(temp_cep); // Alocação dinâmica com strdup
        printf("CEP criado: %s\n", ceps[i]);
    }
    mensagem_sucesso("CEPs CRIADOS COM SUCESSO.\n\n");

    print_amarelo("Agora sera criado as cidades...\n");

    pausar_tela();
    limpar_tela();
    limpar_tela();

    print_amarelo("=== Criando Cidades ===\n");

    // Criar 20 cidades com populações crescentes
    CIDADE cidades[quantidade_cidades];
    for (int i = 0; i < quantidade_cidades; i++)
    {
        char nome_cidade[20];
        sprintf(nome_cidade, "cidade%d", i + 1);
        limpar_buffer();
        int populacao = (i + 1) * 10; // Começando com 10 e incrementando de 10 em 10
        cidades[i] = criar_cidade(nome_cidade, populacao, NULL);
        printf("Cidade criada: %s, População: %d\n", nome_cidade, populacao);
    }

    mensagem_sucesso("CIDADES CRIADAS COM SUCESSO.\n\n");

    print_amarelo("Agora sera criado os estados...\n");

    pausar_tela();
    limpar_tela();

    print_amarelo("=== Criando Estados ===\n");

    // Criar 10 estados, cada um com duas cidades (sendo uma delas a capital)
    ESTADO estado[quantidade_estados];
    for (int i = 0; i < quantidade_estados; i++)
    {
        char nome_estado[20];
        sprintf(nome_estado, "estado%d", i + 1);
        limpar_buffer();

        // A capital é a cidade número (estado * 2)
        int num_capital = (i + 1) * 2;
        

        // Criar o estado
        printf("Criando estado: %s com capital: %s\n", nome_estado, cidades[num_capital - 1].nome);
        estado[i] = criar_estado(nome_estado, cidades[num_capital - 1].nome, 0, (i + 1) * 10, NULL);
    }

    mensagem_sucesso("ESTADOS CRIADOS COM SUCESSO.\n\n");

    print_amarelo("Agora iniciara o processo de cadastros dos ceps nas cidades...\n");

    pausar_tela();
    limpar_tela();

    print_amarelo("=== Iniciando o cadastros dos ceps nas cidades ===\n");

    for (int i = 0; i < quantidade_cidades; i++)
    {
        // Cada cidade recebe 2 CEPs
        for (int j = i * 2; j < (i * 2) + 2; j++)
        {
            // Atribuir o CEP à cidade
            printf("Atribuindo CEP %s à cidade %s\n", ceps[j], cidades[i].nome);
            if (cadastrar_CEP(NULL, &cidades[i], ceps[j]))
            {
                mensagem_sucesso("\n");
            }
            else
            {
                mensagem_erro("\n");
            }
        }
    }

    mensagem_sucesso("CEPs CADASTRADOS COM SUCESSO.\n\n");

    print_amarelo("Agora iniciara o processo de cadastros das cidades nos estados...\n");

    pausar_tela();
    limpar_tela();

    print_amarelo("=== Iniciando o cadastros das cidades nos estados ===\n");

    for (int i = 0; i < quantidade_estados; i++)
    {
        // Cada estado recebe 2 cidades
        for (int j = i * 2; j < (i * 2) + 2; j++)
        {
            // Atribuir a cidade ao estado
            printf("Atribuindo cidade %s ao estado %s\n", cidades[j].nome, estado[i].nome_estado);
            if (cadastrar_cidade(&estado[i], cidades[j]))
            {
                mensagem_sucesso("\n");
            }
            else
            {
                mensagem_erro("\n");
            }
        }
    }

    mensagem_sucesso("CIDADES CADASTRADAS NOS ESTADOS COM SUCESSO.\n\n");

    print_amarelo("Agora iniciara o processo de cadastros dos estados na lista...\n");

    pausar_tela();
    limpar_tela();

    print_amarelo("=== Iniciando o cadastros dos estados na lista ===\n");

    for (int i = 0; i < quantidade_estados; i++)
    {
        // Adicionar o estado à lista
        printf("Adicionando estado %s à lista\n", estado[i].nome_estado);

        if (inserir_ordernado_duplamente(&lista_estados, estado[i]))
        {
            mensagem_sucesso("\n");
        }
        else
        {
            mensagem_erro("\n");
        }
    }

    mensagem_sucesso("ESTADOS CADASTRADOS NA LISTA COM SUCESSO.\n\n");

    print_amarelo("\n=== POVOAMENTO CONCLUÍDO ===\n");

    pausar_tela();

    return lista_estados;
}

int main()
{
    LISTA_DUPLAMENTE *lista_estados = povoar_estados();

    // Aqui pode adicionar código para verificar os elementos povoados

    return 0;
}
