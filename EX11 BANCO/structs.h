#ifndef STRUCTS_H_INCLUDED
#define STRUCTS_H_INCLUDED

typedef struct
{
    int numberCont;//Número id da conta
    char nome[51];//Nome Completo
    char cpf[12]; // CPF do cliente
    double saldo;//Saldo bancário
    char senha[10];//Requisitada para logar
    bool avail;//Apagar conta lógicamente
}stclient;

#endif // STRUCTS_H_INCLUDED
