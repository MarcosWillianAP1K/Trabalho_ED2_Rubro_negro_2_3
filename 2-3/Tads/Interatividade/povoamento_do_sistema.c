#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../../Includes/Estruturas/Lista_duplamente.h"
#include "../../Includes/Estruturas/Dados.h"
#include "../../Includes/Interatividade/func_interatividade.h"
#include "../../Includes/Objetos/Estado.h"
#include "../../Includes/Objetos/Cidade.h"
#include "../../Includes/Objetos/Pessoa.h"
#include "../../Includes/Objetos/CEP.h"
#include "../../Includes/Objetos/Data.h"
#include "../../Includes/Objetos/CPF.h"
#include "../../Includes/Utilitarios/funcao_sistema.h"
#include "../../Includes/Interatividade/povoamento_do_sistema.h"

#define quantidade_estados 10
#define quantidade_cidades 20
#define quantidade_ceps 40
#define quantidade_pessoas 10

LISTA_DUPLAMENTE *povoar_estados()
{
    limpar_tela();
    print_amarelo("=== INICIANDO POVOAMENTO DE ESTADOS ===\n\n");

    pausar_tela();
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

    print_amarelo("=== Criando Cidades ===\n");

    // Criar 20 cidades com populações crescentes
    CIDADE cidades[quantidade_cidades];
    for (int i = 0; i < quantidade_cidades; i++)
    {
        char nome_cidade[20];
        sprintf(nome_cidade, "cidade%d", i + 1);
        limpar_buffer();
        int populacao = (i + 1) * 10; // Começando com 10 e incrementando de 10 em 10
        cidades[i] = criar_cidade(strdup(nome_cidade), populacao, NULL);
        printf("Cidade criada: %s, Populacao: %d\n", nome_cidade, populacao);
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
        estado[i] = criar_estado(strdup(nome_estado), cidades[num_capital - 1].nome, 0, (i + 1) * 10, NULL);
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
            printf("Atribuindo CEP %s a cidade %s\n", ceps[j], cidades[i].nome);
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
        printf("Adicionando estado %s a lista\n", estado[i].nome_estado);

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

    print_amarelo("\n=== POVOAMENTO CONCLUIDO ===\n");

    pausar_tela();

    return lista_estados;
}

// Função para povoar pessoas
AVR_23 *povoar_pessoas()
{
    srand(time(NULL)); // Inicializar gerador de números aleatórios

    limpar_tela();
    print_amarelo("=== INICIANDO POVOAMENTO DE PESSOAS ===\n\n");

    // Inicializar a árvore de pessoas
    AVR_23 *raiz_pessoas = NULL;

    print_amarelo("=== Criando Pessoas ===\n");

    

    // Criar 10 pessoas
    for (int i = 0; i < quantidade_pessoas; i++)
    {
        // Criar nome da pessoa
        char nome_pessoa[20];
        sprintf(nome_pessoa, "pessoa%d", i + 1);

        // Criar CPF único
        char cpf[15];
        sprintf(cpf, "%03d.%03d.%03d-%02d", 100 + i, 200 + i, 300 + i, 10 + i);

        // Criar data de nascimento
        int dia = 1 + (i % 28); // dia entre 1 e 28
        int mes = 1 + (i % 12); // mês entre 1 e 12
        int ano = 1970 + i;     // ano a partir de 1970
        DATA data_nascimento = criar_data(dia, mes, ano);

        // Definir CEP natal e atual
        char *cep_natal, *cep_atual;
        char buffer[50];

        if (i < 5)
        {
            sprintf(buffer, "00000-%03d", rand() % quantidade_ceps + 1);
            limpar_buffer();
            cep_natal = strdup(buffer); // Exemplo de CEP natal

            while (1) // Loop para garantir que o CEP atual seja diferente do natal
            {
                sprintf(buffer, "00000-%03d", rand() % quantidade_ceps + 1);
                limpar_buffer();
                if (strcmp(buffer, cep_natal) != 0)
                {
                    cep_atual = strdup(buffer);
                    break;
                }
            }
            
            cep_atual = strdup(buffer); // Exemplo de CEP atual

            printf("Criando %s com CEPs diferentes (natal: %s, atual: %s)\n",
                   nome_pessoa, cep_natal, cep_atual);
        }
        else
        {
            sprintf(buffer, "00000-%03d", rand() % quantidade_ceps + 1);
            cep_natal = strdup(buffer); // Exemplo de CEP natal
            cep_atual = cep_natal;           // Mesmo CEP
            printf("Criando %s com CEPs iguais (natal e atual: %s)\n",
                   nome_pessoa, cep_natal);
        }

        // Criar a pessoa
        PESSOA pessoa = criar_pessoa(strdup(cpf), strdup(nome_pessoa),
                                     cep_natal, cep_atual,
                                     data_nascimento);

        // Cadastrar pessoa
        short int resultado = cadastrar_pessoa(&raiz_pessoas, pessoa);
        if (resultado)
        {
            mensagem_sucesso("Pessoa cadastrada com sucesso!\n");
        }
        else
        {
            mensagem_erro("Falha ao cadastrar pessoa!\n");
        }
    }

    mensagem_sucesso("POVOAMENTO DE PESSOAS CONCLUIDO COM SUCESSO!\n");

    print_amarelo("Total de pessoas cadastradas: 10\n");

    pausar_tela();
    return raiz_pessoas;
}
