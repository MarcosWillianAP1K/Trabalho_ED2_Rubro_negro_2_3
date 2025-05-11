#include <stdio.h>
#include "../../Includes/Utilitarios/funcao_sistema.h"
#include "../../Includes/Interatividade/func_interatividade.h"




ESTADO *cadastro_estados_interativo(void)
{
    
    printf("Digite o nome do estado: ");
    char *nome_estado = digitar_string();
    
    printf("Digite o nome da capital: ");
    char *nome_capital = digitar_string();
    

    ESTADO *estado = criar_estado(nome_estado, nome_capital, 0, 0, NULL);

    return estado;
}

void menu_principal(void)
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
        printf("\nEscolha uma opcao: ");


        scanf(" %c", &opcao);

        switch (opcao)
        {
        case 'a':
            cadastro_estados_interativo();
           
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
        
        }
    } while (opcao != '0');
}

int main()
{
    menu_principal();

    return 0;
}
