#include "../Estruturas/Lista_duplamente.h"
#include "../Estruturas/Rubro_negro.h"


#pragma once

short int verificar_se_ja_existe_CEP(LISTA_DUPLAMENTE *raiz_estado, char *cep);

short int cadastrar_estado(LISTA_DUPLAMENTE **raiz, ESTADO info);

short int cadastrar_cidade(ESTADO *estado, CIDADE info, short int (*comparar)(DADOS , DADOS ));

short int cadastrar_CEP(LISTA_DUPLAMENTE *lista_estado, CIDADE *cidade, char *cep, short int (*comparar)(DADOS , DADOS ));

short int cadastrar_pessoa(RUBRO_NEGRO **raiz, PESSOA info, short int (*comparar)(DADOS , DADOS ));

RUBRO_NEGRO *remover_CEP(CIDADE *cidade, char *cep, short int (*comparar)(DADOS , DADOS ));

RUBRO_NEGRO *remover_pessoa(RUBRO_NEGRO **raiz, PESSOA info, short int (*comparar)(DADOS , DADOS ));
