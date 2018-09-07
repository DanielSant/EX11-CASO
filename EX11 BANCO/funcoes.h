#ifndef FUNCOES_H_INCLUDED
#define FUNCOES_H_INCLUDED

//Libraries and namespaces
#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include<sstream>
#include <fstream>
#include <conio2.h>
#include<time.h>
#include "structs.h"

using namespace std;
//========================

//Function prototypes--------------------
bool login(char senha[], char *arquivo);
char menu(void);
//=======================================

//Functions--------------------------------
bool login(char senha[], char *arquivo)
{
    ifstream fin;
    stclient client;
    fin.open(arquivo, ios::in);
        fin.read((char *)(&client), sizeof(stclient));
            while(fin && !fin.eof())
            {
                if(strcmp(senha,client.senha)==0)
                    return true;
                fin.read((char *)(&client), sizeof(stclient));
            }
        fin.close();
        return false;

}

char menu(void)
{
    char choice;
    cout<< "1 - Abrir conta\n"
        << "2 - Saque\n"
        << "3 - Dep�sito\n"
        << "4 - Encerrar\n\n"
        << "  - Digite uma op��o";
    gotoxy(1,6);
    fflush(stdin);
    cin >> choice;
    return choice;
}

void cadastro()
{
    clrscr();
    stclient cad;

    fstream arq;

    fflush(stdin);
    cout << "Informe nome: ";
    cin.getline(cad.nome, 51);
    cout << "Informe CPF: ";
    cin.getline(cad.cpf, 12);
    cout << "Informe senha: ";
    cin.getline(cad.senha, 10);
    cout << "Informe Saldo a depositar: ";
    cin >> cad.saldo;

    cad.avail = 1; // 1 - Para conta ativa | 0 - Para conta apagada

    arq.open("clientes.txt", ios::out | ios::app);
    arq.write((const char*) (&cad), sizeof(stclient));
    arq.close();

    arq.open("clientes.txt", ios::in);
    arq.read((char* ) (&cad), sizeof(stclient));
    while(!arq.eof() && cad.avail == 1)
    {
        cout << endl;
        cout << "Nome: " << cad.nome << endl;
        cout << "senha: " << cad.senha << endl;
        cout << "CPF: " << cad.cpf << endl;
        cout << "Saldo Dispon�vel (R$): " << cad.saldo << endl;
        arq.read((char *) (&cad), sizeof(stclient));
    }
}

int saque()
{

}

#endif // FUNCOES_H_INCLUDED
