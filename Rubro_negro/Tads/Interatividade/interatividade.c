#include <stdio.h>
#include <stdlib.h>
#include "../../Includes/Utilitarios/funcao_sistema.h"
#include "../../Includes/Interatividade/Interatividade.h"

void cadastrar_estados_interativo(LISTA_DUPLAMENTE **lista)
{
    //PARTE DO CADASTRO
    printf("Digite o nome do estado: ");
    char *nome_estado = digitar_string();
    corrigir_espacos(&nome_estado);

    printf("Digite o nome da capital: ");
    char *nome_capital = digitar_string();
    corrigir_espacos(&nome_capital);

    printf("Digite a quantidade de populacao da capital: ");
    int quant_populacao = digitar_short_int();

    printf("Digite um CEP generico da capital: ");
    char *cep_inicial = digitar_CEP();
    corrigir_espacos(&cep_inicial);

    //Criação das variaveis para cadastros
    ESTADO estado = criar_estado(nome_estado, nome_capital, quant_populacao, 0, NULL);
    CIDADE cidade = criar_cidade(nome_capital, quant_populacao, NULL);

    //Cadastrando as subs arvores
    RUBRO_NEGRO *no_CEP = cadastrar_CEP(*lista, &cidade, cep_inicial);
    RUBRO_NEGRO *no_cidade = cadastrar_cidade(&estado, cidade);


    short int sucesso = 0;

    //VERIFICAÇÃO DE ERROS.
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

    //Liberando em caso de error
    if (sucesso == 0)
    {
        liberar_no_rubro_negro(&no_CEP, NULL);
        liberar_no_rubro_negro(&no_cidade, NULL);
        liberar_CEP(&cep_inicial);
        liberar_cidade(&cidade);
        liberar_estado(&estado);
    }

}

// void cadastrar_cidade_interativo(LISTA_DUPLAMENTE *lista)
// {
//     printf("Procure o estado.\nnDigite o nome do estado: ");
//     char *nome_estado = digitar_string();
//     corrigir_espacos(&nome_estado);

//     ESTADO estado = criar_estado(nome_estado, NULL, 0, 0, NULL);
//     LISTA_DUPLAMENTE *no_estado = buscar_duplamente(lista, estado);

//     if (no_estado != NULL)
//     {
//         printf("Digite o nome da cidade: ");
//         char *nome_cidade = digitar_string();
//         corrigir_espacos(&nome_cidade);

//         printf("Digite a quantidade de populacao: ");
//         int quant_populacao = digitar_short_int();

//         printf("Digite 1 CEP inicial: ");
//         char *cep_inicial = digitar_CEP();

//         CIDADE cidade = criar_cidade(nome_cidade, quant_populacao, cep_inicial);
//         if (cadastrar_cidade(&no_estado->estado, cidade, lista, cep_inicial) != NULL)
//         {
//             mensagem_sucesso("Cidade cadastrada com sucesso!\n");
//         }
//         else
//         {
//             mensagem_erro("CIDADE JA EXISTENTE!");
//             liberar_cidade(&cidade);
//         }
//     }
//     else
//     {
//         mensagem_erro("ESTADO NAO ENCONTRADO!");
//     }

//     free(nome_estado);
// }

// void cadastrar_CEP_interativos(LISTA_DUPLAMENTE *lista)
// {
//     printf("Procure o estado.\nnDigite o nome do estado: ");
//     char *nome_estado = digitar_string();
//     corrigir_espacos(&nome_estado);

//     ESTADO estado = criar_estado(nome_estado, NULL, 0, 0, NULL);
//     LISTA_DUPLAMENTE *no_estado = buscar_duplamente(lista, estado);

//     if (no_estado != NULL)
//     {

//         printf("Procure o cidade.\nDigite o nome da cidade: ");
//         char *nome_cidade = digitar_string();
//         corrigir_espacos(&nome_cidade);

//         DADOS buscar_cidade;
//         buscar_cidade.cidade = criar_cidade(nome_cidade, 0, NULL);
//         RUBRO_NEGRO *no_cidade = buscar_rubro_negro(no_estado->estado.raiz_arvore_cidade, buscar_cidade, comparar_dados_nome_cidade);

//         if (nome_cidade != NULL)
//         {
//             printf("Digite o CEP: ");
//             char *CEP = digitar_CEP();

//             if (cadastrar_CEP(lista, &no_cidade->info.cidade, CEP) != NULL)
//             {
//                 mensagem_erro("CEP ja existente!");
//             }
//             else
//             {
//                 mensagem_sucesso("CEP CADASTRADO COM SUCESSO!");
//                 liberar_CEP(&CEP);
//             }
//         }
//         free(nome_cidade);
//     }
//     free(nome_estado);
// }

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
            // cadastrar_cidade_interativo(*Lista_estados);
            // pausar_tela();
            break;
        case 'c':
            // cadastrar_CEP_interativos(*Lista_estados);
            // pausar_tela();
            break;
        case 'd':

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
