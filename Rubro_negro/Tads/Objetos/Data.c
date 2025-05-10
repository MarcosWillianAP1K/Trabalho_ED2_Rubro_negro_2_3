#include "../../Includes/Objetos/Data.h"
#include "../../Includes/Utilitarios/funcao_sistema.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>



short int digitar_dia()
{
    short int n;
    printf("Digite o dia: ");

    while (scanf("%hd", &n) != 1 || n < -1 || n > 31 || n == 0)
    {
        printf("Digite um valor valido: ");
        limpar_buffer();
    }

    limpar_buffer();

    return n;
}

short int digitar_mes()
{
    short int n;
    printf("Digite o mes: ");

    while (scanf("%hd", &n) != 1 || n < -1 || n > 12 || n == 0)
    {
        printf("Digite um valor valido: ");
        limpar_buffer();
    }

    limpar_buffer();

    return n;
}

short int digitar_ano()
{
    short int n;
    printf("Digite o ano: ");
    //+500 pra não deixar o usuario colocar um ano muito distante
    while (scanf("%hd", &n) != 1 || n < -1 || n == 0)
    {
        printf("Digite um valor valido: ");
        limpar_buffer();
    }

    limpar_buffer();

    return n;
}

int eh_bissexto(int ano)
{
    int resultado = (ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0);
    return resultado;
}

int dias_no_mes(int mes, int ano)
{
    int dias;

    if (mes == 2)
    {
        dias = eh_bissexto(ano) ? 29 : 28;
    }
    else if (mes == 4 || mes == 6 || mes == 9 || mes == 11)
    {
        dias = 30;
    }
    else
    {
        dias = 31;
    }
    return dias;
}

int validar_data(DATA *data)
{
    int valida = 0;

    if (data->mes >= 1 && data->mes <= 12)
    {
        valida = 1;
    }
    else if (data->dia >= 1 && data->dia <= dias_no_mes(data->mes, data->ano))
    {
        valida = 1;
    }

    return valida;
}

int validar_data_nascimento(DATA *data)
{
    int valida = 0;

    time_t t = time(NULL);
    // Pega a data atual
    struct tm tempo_atual = *localtime(&t);

    if (validar_data(data))
    {
        if (data->ano < tempo_atual.tm_year + 1900)
        {
            valida = 1;
        }
        else if (data->ano == tempo_atual.tm_year + 1900)
        {
            if (data->mes < tempo_atual.tm_mon + 1)
            {
                valida = 1;
            }
            else if (data->mes == tempo_atual.tm_mon + 1 && data->dia <= tempo_atual.tm_mday)
            {
                valida = 1;
            }
        }
    }

    return valida;
}

int digitar_data_nascimento(DATA *data)
{
    int sucesso = 0;

    data->dia = 0;
    data->mes = -1;
    data->ano = -1;

    // digite -1 para voltar
    while (data->dia != -1 && data->mes == -1)
    {
        data->dia = digitar_dia();

        data->mes = 0;

        while (data->dia != -1 && data->mes != -1 && data->ano == -1)
        {
            data->mes = digitar_mes();

            if (data->mes != -1)
                data->ano = digitar_ano();
        }
    }


    if (data->dia != -1)
    {
        if (validar_data_nascimento(data))
        {
            sucesso = 1;
        }
        else
        {
            sucesso = 0;
        }
    }

    return sucesso;
}


void imprimir_data(DATA *data)
{
    if (data != NULL)
    {
        printf("Data: %02hd/%02hd/%04hd\n", data->dia, data->mes, data->ano);
    }
}
