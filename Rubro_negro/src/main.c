#include <stdio.h>
#include "../Includes/Interatividade/Interatividade.h"

//Comando para compilar, dentro do diretorio src
//gcc -o main main.c ../Tads/Interatividade/Interatividade.c ../Tads/Interatividade/Func_interatividade.c  ../Tads/Estruturas/Lista_duplamente.c ../Tads/Estruturas/Rubro_negro.c ../Tads/Estruturas/Dados.c ../Tads/Objetos/Cidade.c ../Tads/Objetos/Pessoa.c ../Tads/Objetos/Estado.c ../Tads/Objetos/CEP.c ../Tads/Objetos/Data.c ../Tads/Objetos/CPF.c ../Tads/Utilitarios/funcao_sistema.c -I../Includes/

int main()
{
    RUBRO_NEGRO *Raiz_pessoas = NULL;
    LISTA_DUPLAMENTE *Lista_estados = NULL;

    menu_principal(&Lista_estados, &Raiz_pessoas);

    //Não tem delete all pra liberar todo sistem, cuidado

    return 0;
}