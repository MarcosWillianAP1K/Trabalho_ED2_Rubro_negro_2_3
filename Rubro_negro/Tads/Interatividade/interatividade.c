#include <stdio.h>
#include <stdlib.h>
#include "../../Includes/Utilitarios/funcao_sistema.h"
#include "../../Includes/Interatividade/Interatividade.h"

void cadastrar_estados_interativo(LISTA_DUPLAMENTE **lista)
{
    // PARTE DO CADASTRO
    printf("Digite o nome do estado: ");
    char *nome_estado = digitar_string();
    corrigir_espacos(&nome_estado);

    printf("Digite o nome da capital: ");
    char *nome_capital = digitar_string();
    corrigir_espacos(&nome_capital);

    printf("Digite a quantidade de populacao da capital: ");
    int quant_populacao = digitar_short_int();

    printf("Digite um CEP generico da capital (xxxxx-xxx): ");
    char *cep_inicial = digitar_CEP();
    corrigir_espacos(&cep_inicial);

    // Criação das variaveis para cadastros
    ESTADO estado = criar_estado(nome_estado, nome_capital, quant_populacao, 0, NULL);
    CIDADE cidade = criar_cidade(nome_capital, quant_populacao, NULL);

    // Cadastrando as subs arvores
    RUBRO_NEGRO *no_CEP = cadastrar_CEP(*lista, &cidade, cep_inicial);
    RUBRO_NEGRO *no_cidade = cadastrar_cidade(&estado, cidade);

    short int sucesso = 0;

    // VERIFICAÇÃO DE ERROS.
    if (no_CEP == NULL)
        mensagem_erro("CEP JA EXISTE!");

    if (no_cidade == NULL)
        mensagem_erro("CIDADE JA EXISTE!");

    if (no_CEP != NULL && no_cidade != NULL)
    {
        LISTA_DUPLAMENTE *no_estado = cadastrar_estado(lista, estado);

        if (no_estado != NULL)
        {
            mensagem_sucesso("ESTADO CADASTRADO COM SUCESSO!");
            no_estado->estado.nome_capital = nome_capital;
            no_estado->estado.quantidade_populacao = quant_populacao;
            no_estado->estado.quantidade_cidade = 1;
            sucesso = 1;
        }
    }
    else
    {
        if (buscar_duplamente(*lista, estado) != NULL)
        {
            mensagem_erro("ESTADO JA EXISTE!");
        }
    }

    // Liberando em caso de error
    if (sucesso == 0)
    {
        liberar_no_rubro_negro(&no_CEP, NULL);
        liberar_no_rubro_negro(&no_cidade, NULL);
        liberar_CEP(&cep_inicial);
        liberar_cidade(&cidade);
        liberar_estado(&estado);
    }
}

void cadastrar_cidade_interativo(LISTA_DUPLAMENTE *lista)
{
    if (lista != NULL)
    {

        printf("Procure o estado.\nDigite o nome do estado: ");
        char *nome_estado = digitar_string();
        corrigir_espacos(&nome_estado);

        ESTADO estado = criar_estado(nome_estado, NULL, 0, 0, NULL);
        LISTA_DUPLAMENTE *no_estado = buscar_duplamente(lista, estado);

        if (no_estado != NULL)
        {
            printf("Digite o nome da cidade: ");
            char *nome_cidade = digitar_string();
            corrigir_espacos(&nome_cidade);

            printf("Digite a quantidade de populacao: ");
            int quant_populacao = digitar_short_int();

            printf("Digite um CEP generico (xxxxx-xxx): ");
            char *cep_inicial = digitar_CEP();

            CIDADE cidade = criar_cidade(nome_cidade, quant_populacao, cep_inicial);

            RUBRO_NEGRO *no_cep = cadastrar_CEP(lista, &cidade, cep_inicial);

            if (no_cep != NULL)
            {
                if (cadastrar_cidade(&no_estado->estado, cidade) != NULL)
                {
                    mensagem_sucesso("Cidade cadastrada com sucesso!\n");
                }
                else
                {
                    mensagem_erro("CIDADE JA EXISTENTE!");
                }
            }
            else
            {
                mensagem_erro("CEP JA EXISTENTE!");

                // Faz a busca para verificar se a cidade daria error ou não. Mesmo se o CEP ja existir.
                DADOS busca_cidade;
                busca_cidade.cidade = criar_cidade(NULL, 0, NULL);

                if (buscar_rubro_negro(no_estado->estado.raiz_arvore_cidade, busca_cidade, comparar_dados_nome_cidade) != NULL)
                {
                    mensagem_erro("CIDADE JA EXISTENTE!");
                }
            }
        }
        else
        {
            mensagem_erro("ESTADO NAO ENCONTRADO!");
        }

        free(nome_estado);
    }
    else
    {
        mensagem_erro("CADASTRE UM ESTADO PRIMEIRO!");
    }
}

void cadastrar_CEP_interativo(LISTA_DUPLAMENTE *lista)
{
    if (lista == NULL)
    {

        printf("Procure o estado.\nnDigite o nome do estado: ");
        char *nome_estado = digitar_string();
        corrigir_espacos(&nome_estado);

        ESTADO estado = criar_estado(nome_estado, NULL, 0, 0, NULL);
        LISTA_DUPLAMENTE *no_estado = buscar_duplamente(lista, estado);

        if (no_estado != NULL)
        {

            printf("Procure o cidade.\nDigite o nome da cidade: ");
            char *nome_cidade = digitar_string();
            corrigir_espacos(&nome_cidade);

            DADOS buscar_cidade;
            buscar_cidade.cidade = criar_cidade(nome_cidade, 0, NULL);
            RUBRO_NEGRO *no_cidade = buscar_rubro_negro(no_estado->estado.raiz_arvore_cidade, buscar_cidade, comparar_dados_nome_cidade);

            if (nome_cidade != NULL)
            {
                printf("Digite o CEP (xxxxx-xxx): ");
                char *CEP = digitar_CEP();

                if (cadastrar_CEP(lista, &no_cidade->info.cidade, CEP) != NULL)
                {
                    mensagem_sucesso("CEP CADASTRADO COM SUCESSO!");
                }
                else
                {
                    mensagem_erro("CEP JA EXISTE!");
                    liberar_CEP(&CEP);
                }
            }
            else
            {

                mensagem_erro("CIDADE NAO ENCONTRADA!");
            }
            free(nome_cidade);
        }
        else
        {
            mensagem_erro("ESTADO NAO ENCONTRADA!");
        }
        free(nome_estado);
    }
    else
    {
        mensagem_erro("CADASTRE UM ESTADO PRIMEIRO!");
    }
}

void cadastrar_pessoa_interativo(LISTA_DUPLAMENTE *lista, RUBRO_NEGRO **Raiz_pessoas)
{
    if (lista == NULL)
    {

        printf("Digite o nome da pessoa: ");
        char *nome = digitar_string();
        corrigir_espacos(&nome);

        printf("Digite o CPF da pessoa (xxx.xxx.xxx-xx): ");
        char *cpf = digitar_CPF();

        printf("Digite o CEP natal (xxxxx-xxx): ");
        char *cep_natal = digitar_CEP();

        printf("Digite o CEP atual (xxxxx-xxx): ");
        char *cep_atual = digitar_CEP();

        printf("Digite a data de nascimento da pessoa: ");
        DATA data_nascimento = digitar_data_nascimento();

        PESSOA pessoa = criar_pessoa(cpf, nome, cep_natal, cep_atual, data_nascimento);

        short int validar_cep_natal = verificar_se_existe_CEP(lista, cep_natal);
        short int validar_cep_atual = verificar_se_existe_CEP(lista, cep_atual);

        if (validar_cep_natal == 1 && validar_cep_atual == 1)
        {
            if (cadastrar_pessoa(Raiz_pessoas, pessoa) != NULL)
            {
                mensagem_sucesso("Pessoa cadastrada com sucesso!\n");
            }
            else
            {
                mensagem_erro("CPF DA PESSOA JA EXISTENTE!");
                liberar_pessoa(&pessoa);
            }
        }
        else
        {
            if (validar_cep_natal == 0)
                mensagem_erro("CEP NATAL NAO ENCONTRADO!");

            if (validar_cep_atual == 0)
                mensagem_erro("CEP ATUAL NAO ENCONTRADO!");

            DADOS busca_pessoa;
            busca_pessoa.pessoa = pessoa;

            if (buscar_rubro_negro(*Raiz_pessoas, busca_pessoa, comparar_dados_CPF_pessoa) != NULL)
                mensagem_erro("CPF DA PESSOA JA EXISTENTE!");

            liberar_pessoa(&pessoa);
        }
    }
    else
    {
        mensagem_erro("CADASTRE UM ESTADO PRIMEIRO!");
    }
}

void menu_principal(LISTA_DUPLAMENTE **Lista_estados, RUBRO_NEGRO **Raiz_pessoas)
{
    char opcao;

    do
    {
        limpar_tela();
        printf("===== MENU =====\n");
        printf("(a) Cadastrar um Estado e seus respectivos dados.\n");
        printf("(b) Cadastrar uma Cidade e seus respectivos dados.\n");
        printf("(c) Cadastrar os CEPs de uma Cidade.\n");
        printf("(d) Cadastrar Pessoas e seus respectivos dados.\n");
        printf("(e) Remover um CEP (desde que não tenha nenhuma pessoa associada).\n");
        printf("(f) Remover uma Pessoa.\n");
        printf("\n===== Consultas =====\n");
        printf("(1) Qual o estado mais populoso?\n");
        printf("(2) Qual a população da Capital de um determinado estado?\n");
        printf("(3) Qual a cidade mais populosa de um estado sem ser a Capital?\n");
        printf("(4) Quantas pessoas não moram na cidade natal?\n");
        printf("(5) Qual cidade natal de uma pessoa dado o CEP da cidade?\n");
        printf("(6) Quantas pessoas nascidas em uma determinada cidade não moram na cidade natal?\n");
        printf("(7) Quantas pessoas que moram em uma determinada cidade não nasceram na cidade?\n");
        printf("(8) Mostrar tudo\n");
        printf("\nEscolha uma opcao: ");

        scanf(" %c", &opcao);

        limpar_tela();

        switch (opcao)
        {
        case 'a':
            cadastrar_estados_interativo(Lista_estados);
            pausar_tela();
            break;
        case 'b':
            cadastrar_cidade_interativo(*Lista_estados);
            pausar_tela();
            break;
        case 'c':
            cadastrar_CEP_interativo(*Lista_estados);
            pausar_tela();
            break;
        case 'd':
            cadastrar_pessoa_interativo(*Lista_estados, Raiz_pessoas);
            pausar_tela();
            break;
        case 'e':

            break;
        case 'f':

            break;
        case '1':
            break;
        case '2':

            break;
        case '3':
            break;
        case '4':
            break;
        case '5':
            break;
        case '6':
            break;
        case '7':
            break;
        case '8':
            mostrar_tudo(*Lista_estados, *Raiz_pessoas);
            pausar_tela();
            break;
        }
    } while (opcao != '0');
}
