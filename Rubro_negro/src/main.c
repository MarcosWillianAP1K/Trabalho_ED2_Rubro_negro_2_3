#include <stdio.h>
#include "../Includes/Interatividade/Interatividade.h"
#include "../Includes/Utilitarios/funcao_sistema.h"
#include "../Includes/Interatividade/povoamento_do_sistema.h"

//Comando para compilar, dentro do diretorio src
//gcc -o main main.c ../Tads/Interatividade/Interatividade.c ../Tads/Interatividade/Func_interatividade.c  ../Tads/Estruturas/Lista_duplamente.c ../Tads/Estruturas/Rubro_negro.c ../Tads/Estruturas/Dados.c ../Tads/Objetos/Cidade.c ../Tads/Objetos/Pessoa.c ../Tads/Objetos/Estado.c ../Tads/Objetos/CEP.c ../Tads/Objetos/Data.c ../Tads/Objetos/CPF.c ../Tads/Utilitarios/funcao_sistema.c -I../Includes/

int main()
{
    RUBRO_NEGRO *Raiz_pessoas = NULL;
    LISTA_DUPLAMENTE *Lista_estados = NULL;

    //Povoar_sistema esta com problemas na hora de liberar a memoria, mas o problema esta no cadastro dele.
    //Porem como foi feito para apenas testes das consultas sera apenas ignorado, o problema deve ser em alguma alocação dos char *.
    // povoar_sistema(&Lista_estados, &Raiz_pessoas, 5, 5, 5, 5);

    // pausar_tela();

    menu_principal(&Lista_estados, &Raiz_pessoas);

    delete_all(&Lista_estados, &Raiz_pessoas);
    print_verde("\nTodos os dados foram liberados com sucesso!\n\n");

    return 0;
}