#ifndef STRUCTS_H_INCLUDED
#define STRUCTS_H_INCLUDED

typedef struct
{
    int numberCont;//Número id da conta
    char name[51];//Nome Completo
    double sale;//Saldo bancário
    char password[10];//Requisitada para logar
    bool avail;//Apagar conta lógicamente
}stclient;

#endif // STRUCTS_H_INCLUDED
