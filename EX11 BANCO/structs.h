#ifndef STRUCTS_H_INCLUDED
#define STRUCTS_H_INCLUDED

typedef struct
{
    char nome[51];//Nome Completo
    char cpf[12]; // CPF do cliente
    double saldo;//Saldo bancário
    char senha[10];//Requisitada para logar
    bool avail;//Apagar conta lógicamente
}stclient;

typedef struct
{
    int notas100;
    int notas50;
    int notas20;
    int notas10;
    int notas5;
    int notas2;
    int valorTotal;
}cedulas;

typedef struct
{
    char CPF[12];
    char Data[11];
    int retiradas;
    double saldoAtual;
    double depositos;
}relatorio;

#endif // STRUCTS_H_INCLUDED
