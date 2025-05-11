#include "../Estruturas/Lista_duplamente.h"
#include "../Estruturas/Rubro_negro.h"


#pragma once

short int cadastrar_estado(LISTA_DUPLAMENTE **raiz, ESTADO *info);

short int cadastrar_cidade(ESTADO *estado, CIDADE *info, short int (*comparar)(DADOS *, DADOS *));

short int cadastrar_CEP(CIDADE *cidade, char *cep, short int (*comparar)(DADOS *, DADOS *));

short int cadastrar_pessoa(RUBRO_NEGRO **raiz, PESSOA *info, short int (*comparar)(DADOS *, DADOS *));
