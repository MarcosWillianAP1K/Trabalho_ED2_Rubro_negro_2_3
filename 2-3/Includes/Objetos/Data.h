
#pragma once


typedef struct DATA {
    short int dia;
    short int mes;
    short int ano;
} DATA;

// Function prototypes

// DATA *alocar_data();

DATA criar_data(short int dia, short int mes, short int ano);

// void liberar_data(DATA **data);

short int digitar_dia();

short int digitar_mes();

short int digitar_ano();

int eh_bissexto(int ano);

int dias_no_mes(int mes, int ano);

int validar_data(DATA data);

int validar_data_nascimento(DATA data);

DATA digitar_data_nascimento();

void imprimir_data(DATA data);

short int comparar_data(DATA data1, DATA data2);


