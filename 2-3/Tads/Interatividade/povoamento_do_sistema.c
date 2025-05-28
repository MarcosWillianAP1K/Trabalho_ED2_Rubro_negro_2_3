#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../Includes/Estruturas/Lista_duplamente.h"
#include "../../Includes/Estruturas/Rubro_negro.h"
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

short int contador_de_digitos(int numero)
{
    short int contador = 0;
    do
    {
        contador++;
        numero /= 10;
    } while (numero != 0);
    return contador;
}

// Funcoes auxiliares basicas
char *gerar_nome_estado(int numero)
{
    char *nome = (char *)malloc((6 + contador_de_digitos(numero) + 1) * sizeof(char));
    if (nome == NULL)
        return NULL;
    sprintf(nome, "Estado%d", numero);
    return nome;
}

char *gerar_nome_capital(int numero)
{
    char *nome = (char *)malloc((7 + contador_de_digitos(numero) + 1) * sizeof(char));
    if (nome == NULL)
        return NULL;
    sprintf(nome, "Capital%d", numero);
    return nome;
}

char *gerar_nome_cidade(int numero_estado, int numero_cidade)
{
    char *nome = (char *)malloc((7 + contador_de_digitos(numero_estado) + contador_de_digitos(numero_cidade) + 1) * sizeof(char));
    if (nome == NULL)
        return NULL;
    sprintf(nome, "Cidade%d.%d", numero_estado, numero_cidade);
    return nome;
}

char *gerar_cep(int numero_estado, int numero_cep)
{
    char *cep = (char *)malloc((11) * sizeof(char));
    if (cep == NULL)
        return NULL;
    sprintf(cep, "%05d-%03d", numero_estado, numero_cep);

    corrigir_formatacao_CEP(&cep);
    return cep;
}

char *gerar_cpf(int numero_pessoa)
{
    char *cpf = (char *)malloc(15 * sizeof(char));
    if (cpf == NULL)
        return NULL;

    // Formata o CPF como XXX.YYY.ZZZ-WW onde numero da pessoa e distribuido
    int x = (numero_pessoa % 900) + 100;            // Garante um numero de 3 digitos para XXX
    int y = ((numero_pessoa / 900) % 900) + 100;    // Garante um numero de 3 digitos para YYY
    int z = ((numero_pessoa / 810000) % 900) + 100; // Garante um numero de 3 digitos para ZZZ
    int w = (numero_pessoa % 90) + 10;              // Garante um numero de 2 digitos para WW

    sprintf(cpf, "%d.%d.%d-%d", x, y, z, w);

    corrigir_formatacao_cpf(&cpf);
    return cpf;
}

char *gerar_nome_pessoa(int numero)
{
    char *nome = (char *)malloc(20 * sizeof(char));
    if (nome == NULL)
        return NULL;
    sprintf(nome, "Pessoa%d", numero);
    return nome;
}

// Funcoes auxiliares para coleta de CEPs (ordenadas por dependencia)
void coletar_ceps_cidade(RUBRO_NEGRO *cep_node, char **ceps, int *total, int max)
{
    if (cep_node == NULL || *total >= max)
        return;

    // Percorrer a arvore em in-ordem
    coletar_ceps_cidade(cep_node->esquerda, ceps, total, max);

    if (*total < max)
    {
        // Duplicar o CEP para uso posterior
        ceps[*total] = strdup(cep_node->info.CEP);
        (*total)++;
    }

    coletar_ceps_cidade(cep_node->direita, ceps, total, max);
}

void coletar_ceps_arvore(LISTA_DUPLAMENTE *estado, RUBRO_NEGRO *cidade_node, char **ceps, int *total, int max)
{
    if (cidade_node == NULL || *total >= max)
        return;

    // Coletar CEPs da cidade atual
    coletar_ceps_cidade(cidade_node->info.cidade.raiz_arvore_CEPs, ceps, total, max);

    // Percorrer outras cidades
    coletar_ceps_arvore(estado, cidade_node->esquerda, ceps, total, max);
    coletar_ceps_arvore(estado, cidade_node->direita, ceps, total, max);
}

void coletar_ceps(LISTA_DUPLAMENTE *lista_estados, char **ceps, int *total, int max)
{
    LISTA_DUPLAMENTE *estado_atual = lista_estados;

    while (estado_atual != NULL && *total < max)
    {
        coletar_ceps_arvore(estado_atual, estado_atual->estado.raiz_arvore_cidade, ceps, total, max);
        estado_atual = estado_atual->prox;
    }
}

// Funcoes para povoamento
short int povoar_estados(LISTA_DUPLAMENTE **lista_estados, int quantidade)
{
    if (lista_estados == NULL || quantidade <= 0)
        return 0;

    short int sucesso = 1; // Começamos considerando sucesso

    for (int i = 1; i <= quantidade; i++)
    {
        char *nome_estado = gerar_nome_estado(i);

        if (nome_estado == NULL)
        {
            sucesso = 0;
            free(nome_estado);
            continue;
        }

        ESTADO estado = criar_estado(nome_estado, NULL, 0, 0, NULL);
        LISTA_DUPLAMENTE *no_estado = cadastrar_estado(lista_estados, estado);

        if (no_estado != NULL)
        {
            printf("Estado %s cadastrado com sucesso!\n", nome_estado);
        }
        else
        {
            printf("Falha ao cadastrar estado %s!\n", nome_estado);

            free(nome_estado);

            sucesso = 0;
        }
    }

    return sucesso;
}

short int povoar_cidades(LISTA_DUPLAMENTE *lista_estados, int cidades_por_estado)
{
    if (lista_estados == NULL || cidades_por_estado <= 0)
        return 0;

    LISTA_DUPLAMENTE *atual = lista_estados;
    int contador_estado = 1;
    short int sucesso = 1; // Começamos considerando sucesso

    while (atual != NULL)
    {
        for (int i = 1; i <= cidades_por_estado; i++)
        {
            char *nome_cidade = gerar_nome_cidade(contador_estado, i);

            if (nome_cidade == NULL)
            {
                free(nome_cidade);
                sucesso = 0;
                continue;
            }

            // Populacao arbitraria
            int populacao = (i * 10) * contador_estado;

            CIDADE cidade = criar_cidade(nome_cidade, populacao, NULL);
            RUBRO_NEGRO *no_cidade = cadastrar_cidade(&atual->estado, cidade);

            if (i == 1)
            {
                // Se for a primeira cidade, podemos definir como capital
                atual->estado.nome_capital = nome_cidade;
            }

            if (no_cidade != NULL)
            {
                printf("Cidade %s cadastrada com sucesso no Estado%d!\n", nome_cidade, contador_estado);
                atual->estado.quantidade_cidade++;
                atual->estado.quantidade_populacao += populacao;
            }
            else
            {
                printf("Falha ao cadastrar cidade %s no Estado%d!\n", nome_cidade, contador_estado);
                free(nome_cidade);
                sucesso = 0;
            }
        }

        atual = atual->prox;
        contador_estado++;
    }

    return sucesso;
}

short int povoar_ceps_cidade(LISTA_DUPLAMENTE *estado, RUBRO_NEGRO *cidade_node, int numero_estado, int ceps_por_cidade, int *cont)
{
    if (cidade_node == NULL)
        return 1; // Base case - success (there's no error in having no node)

    short int sucesso = 1; // Começamos considerando sucesso

    if (!povoar_ceps_cidade(estado, cidade_node->esquerda, numero_estado, ceps_por_cidade, cont))
        sucesso = 0;

    // Adicionar CEPs à cidade atual
    for (int i = 1; i <= ceps_por_cidade; i++)
    {
        char *cep = gerar_cep(numero_estado, *cont);
        (*cont)++;

        if (cep == NULL)
        {
            sucesso = 0;
            free(cep);
            continue;
        }

        RUBRO_NEGRO *cep_node = cadastrar_CEP(estado, &cidade_node->info.cidade, cep);

        if (cep_node != NULL)
        {
            printf("CEP %s cadastrado com sucesso em %s!\n", cep, cidade_node->info.cidade.nome);
        }
        else
        {
            printf("Falha ao cadastrar CEP %s em %s!\n", cep, cidade_node->info.cidade.nome);
            free(cep);
            sucesso = 0; // Marcar falha se não conseguir cadastrar um CEP
        }
    }

    // Percorrer outras cidades (pre-ordem)
    // Se falhar em qualquer recursão, propaga falha

    if (!povoar_ceps_cidade(estado, cidade_node->direita, numero_estado, ceps_por_cidade, cont))
        sucesso = 0;

    return sucesso;
}

short int povoar_ceps(LISTA_DUPLAMENTE *lista_estados, int ceps_por_cidade)
{
    if (lista_estados == NULL)
        return 0;

    LISTA_DUPLAMENTE *estado_atual = lista_estados;
    int contador_estado = 1;
    short int sucesso = 1; // Começamos considerando sucesso

    while (estado_atual != NULL)
    {
        RUBRO_NEGRO *cidade_atual = estado_atual->estado.raiz_arvore_cidade;

        // Percorrer cidades em pre-ordem (simplificacao)
        // Se falhar em qualquer estado, marcamos falha mas continuamos para os outros
        int contador_cep = 1;
        if (!povoar_ceps_cidade(estado_atual, cidade_atual, contador_estado, ceps_por_cidade, &contador_cep))
            sucesso = 0;

        estado_atual = estado_atual->prox;
        contador_estado++;
    }

    return sucesso;
}

short int povoar_pessoas(RUBRO_NEGRO **raiz_pessoas, LISTA_DUPLAMENTE *lista_estados, int quantidade)
{
    if (raiz_pessoas == NULL || lista_estados == NULL || quantidade <= 0)
        return 0;

    // Coletar todos os CEPs disponiveis para uso
    int max_ceps = 100; // Limite arbitrario
    char **ceps_disponiveis = (char **)malloc(max_ceps * sizeof(char *));
    if (ceps_disponiveis == NULL)
        return 0;

    int total_ceps = 0;
    short int sucesso = 1; // Começamos considerando sucesso

    // Inicializar array
    for (int i = 0; i < max_ceps; i++)
    {
        ceps_disponiveis[i] = NULL;
    }

    // Coletar CEPs de todos os estados/cidades
    coletar_ceps(lista_estados, ceps_disponiveis, &total_ceps, max_ceps);

    if (total_ceps == 0)
    {
        printf("Nenhum CEP disponivel para cadastro de pessoas!\n");
        free(ceps_disponiveis);
        return 0;
    }

    // Cadastrar pessoas usando os CEPs coletados
    for (int i = 1; i <= quantidade && i <= max_ceps; i++)
    {
        char *nome = gerar_nome_pessoa(i);
        char *cpf = gerar_cpf(i);

        if (nome == NULL || cpf == NULL)
        {
            if (nome)
                free(nome);
            if (cpf)
                free(cpf);
            sucesso = 0;
            continue;
        }

        // Escolher dois CEPs aleatorios para residencia e nascimento
        int idx_res = i % total_ceps;
        int idx_nasc = (i * 3) % total_ceps; // Garantir variacao

        // Criar data de nascimento variada
        int dia = 1 + (i % 28);
        int mes = 1 + (i % 12);
        int ano = 1950 + (i % 50);
        DATA data = criar_data(dia, mes, ano);

        PESSOA pessoa = criar_pessoa(cpf, nome, strdup(ceps_disponiveis[idx_res]), strdup(ceps_disponiveis[idx_nasc]), data);
        RUBRO_NEGRO *pessoa_node = cadastrar_pessoa(raiz_pessoas, pessoa);

        if (pessoa_node != NULL)
        {
            printf("Pessoa %s com CPF %s cadastrada com sucesso!\n", nome, cpf);
        }
        else
        {
            printf("Falha ao cadastrar pessoa %s com CPF %s!\n", nome, cpf);
            free(nome);
            free(cpf);
            sucesso = 0; // Marcar falha se não conseguir cadastrar uma pessoa
        }
    }

    // Liberar memoria dos CEPs
    for (int i = 0; i < total_ceps; i++)
    {
        if (ceps_disponiveis[i])
        {
            free(ceps_disponiveis[i]);
        }
    }
    free(ceps_disponiveis);

    return sucesso;
}

short int povoar_sistema(LISTA_DUPLAMENTE **lista_estados, RUBRO_NEGRO **raiz_pessoas, int num_estados, int cidades_por_estado, int ceps_por_cidade, int num_pessoas)
{
    if (lista_estados == NULL || raiz_pessoas == NULL ||
        num_estados <= 0 || cidades_por_estado <= 0 ||
        ceps_por_cidade <= 0 || num_pessoas <= 0)
        return 0;

    short int sucesso = 1; // Começamos considerando sucesso

    printf("=== INICIANDO POVOAMENTO DO SISTEMA ===\n");

    printf("\n=== POVOANDO ESTADOS ===\n");
    if (!povoar_estados(lista_estados, num_estados))
    {
        printf("Erro ao povoar estados!\n");
        sucesso = 0;
    }

    printf("\n=== POVOANDO CIDADES ===\n");
    if (!povoar_cidades(*lista_estados, cidades_por_estado))
    {
        printf("Erro ao povoar cidades!\n");
        sucesso = 0;
    }

    printf("\n=== POVOANDO CEPs ===\n");
    if (!povoar_ceps(*lista_estados, ceps_por_cidade))
    {
        printf("Erro ao povoar CEPs!\n");
        sucesso = 0;
    }

    printf("\n=== POVOANDO PESSOAS ===\n");
    if (!povoar_pessoas(raiz_pessoas, *lista_estados, num_pessoas))
    {
        printf("Erro ao povoar pessoas!\n");
        sucesso = 0;
    }

    if (sucesso)
        printf("\n=== POVOAMENTO CONCLUIDO COM SUCESSO ===\n");
    else
        printf("\n=== POVOAMENTO CONCLUIDO COM FALHAS ===\n");

    return sucesso;
}
