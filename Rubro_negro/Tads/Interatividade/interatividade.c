#include <stdio.h>
#include "../../Includes/Utilitarios/funcao_sistema.h"
#include "../../Includes/Interatividade/Interatividade.h"

void cadastro_estados_interativo(LISTA_DUPLAMENTE **lista)
{
    short int sucesso = 0;

    printf("Digite o nome do estado: ");
    char *nome_estado = digitar_string();
    corrigir_espacos(nome_estado);

    printf("Digite o nome da capital: ");
    char *nome_capital = digitar_string();
    corrigir_espacos(nome_capital);

    printf("Digite a quantidade de populacao: ");
    int quant_populacao = digitar_short_int();

    printf("Digite 1 CEP inicial: ");
    char *cep_inicial = digitar_CEP();
    corrigir_espacos(cep_inicial);

    corrigir_formatacao_CEP(cep_inicial);

    ESTADO estado = criar_estado(nome_estado, nome_capital, quant_populacao, 0, NULL);
    CIDADE cidade = criar_cidade(nome_capital, quant_populacao, NULL);
    
    
    if(cadastrar_estado(lista, estado, &cidade, cep_inicial) != NULL)
    {
        mensagem_sucesso("Estado cadastrado com sucesso!\n");
    }
    else
    {
        liberar_estado(&estado);
        liberar_cidade(&cidade);
        liberar_CEP(&cep_inicial);
        mensagem_erro("Falha ao cadastrar estado!\n");
    }
}

// LISTA_DUPLAMENTE cadastro_cidade_interativo(LISTA_DUPLAMENTE *raiz)
// {
//     printf("Digite o nome do estado: ");
//     char *nome_estado = digitar_string();
//     ESTADO estado = criar_estado(nome_estado, NULL, 0, 0, NULL);
//     LISTA_DUPLAMENTE *aux = buscar_duplamente(raiz, estado);

//     if (aux != NULL)
//     {
//         printf("Digite o nome da cidade: ");
//         char *nome_cidade = digitar_string();

//         printf("Digite a quantidade de populacao: ");
//         int quant_populacao = digitar_short_int();
//         CIDADE cidade = criar_cidade(nome_cidade, quant_populacao, NULL);
//         if (cadastrar_cidade(&aux->estado, cidade, comparar_nome_cidades) != 1)
//         {
//             print_amarelo("CIDADE JA EXISTENTE!");
//         }
//         else
//         {
//             cidade.nome = nome_cidade;
//             cidade.quantidade_populacao = quant_populacao;
//             print_verde("Cidade cadastrada com sucesso!\n");
//         }
//     }
//     else
//     {
//         print_amarelo("ESTADO NAO ENCONTRADO!");
//     }
// }

// LISTA_DUPLAMENTE cadastro_cps_cidades_interativos(LISTA_DUPLAMENTE *raiz, RUBRO_NEGRO *raiz_rubro)
// {
//     int encontrado = 0;
//     printf("Digite o nome do estado: ");
//     char *nome_estado = digitar_string();
//     ESTADO estado = criar_estado(nome_estado, NULL, 0, 0, NULL);
//     LISTA_DUPLAMENTE *aux = buscar_duplamente(raiz, estado);

//     if (aux != NULL)
//     {
//         printf("Digite o nome da cidade: ");
//         char *nome_cidade = digitar_string();
//         DADOS cidade;
//         cidade.cidade = criar_cidade(nome_cidade, 0, NULL);
//         RUBRO_NEGRO *busca_cidade_rubro = buscar_rubro_negro(raiz_rubro, cidade, comparar_nome_cidades);
//         if (busca_cidade_rubro != NULL)
//         {
//             printf("Digite o CEP: ");
//             char *CEP = digitar_CEP();

//             if (cadastrar_CEP(aux, busca_cidade_rubro->info.cidade, CEP, comparar_CEPs) != 1)
//             {
//                 print_amarelo("CEP JA EXISTENTE!");
//                 encontrado = 1;
//             }
//             else
//                 cidade.CEP = CEP;
//             liberar_CEP(&CEP);
//         }
//     }
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
            cadastro_estados_interativo(Lista_estados);
            pausar_tela();
            break;
        case 'b':

            break;
        case 'c':

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
