#include <stdio.h>
#include <stdlib.h>

int main()
{

    int compilador = system("gcc -o main ../main.c ../../Tads/Interatividade/Interatividade.c ../../Tads/Interatividade/Func_interatividade.c ../../Tads/Interatividade/povoamento_do_sistema.c ../../Tads/Estruturas/Lista_duplamente.c ../../Tads/Estruturas/Rubro_negro.c ../../Tads/Estruturas/Dados.c ../../Tads/Objetos/Cidade.c ../../Tads/Objetos/Pessoa.c ../../Tads/Objetos/Estado.c ../../Tads/Objetos/CEP.c ../../Tads/Objetos/Data.c ../../Tads/Objetos/CPF.c ../../Tads/Utilitarios/funcao_sistema.c -I../Includes/");

    if (compilador == 0)
    {

        #ifdef _WIN32
        system("main.exe");
        #else
        system("./main");
        #endif
    }
}