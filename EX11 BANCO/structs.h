#ifndef STRUCTS_H_INCLUDED
#define STRUCTS_H_INCLUDED

typedef struct
{
    int numberCont;//N�mero id da conta
    char name[21];//Nome Completo
    double sale;//Saldo banc�rio
    char password[10];//Requisitada para logar
    bool avail;//Apagar conta l�gicamente
}stclient;

#endif // STRUCTS_H_INCLUDED
