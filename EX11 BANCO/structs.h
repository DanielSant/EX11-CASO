#ifndef STRUCTS_H_INCLUDED
#define STRUCTS_H_INCLUDED

typedef struct
{
    int numberCont;//N�mero id da conta
    char nome[51];//Nome Completo
    char cpf[12]; // CPF do cliente
    double saldo;//Saldo banc�rio
    char senha[10];//Requisitada para logar
    bool avail;//Apagar conta l�gicamente
}stclient;

typedef struct
{
    int notas100=0;
    int notas50=0;
    int notas20=0;
    int notas10=0;
    int notas5=0;
    int notas2=0;
    int valorTotal=0;
}cedulas;

#endif // STRUCTS_H_INCLUDED
