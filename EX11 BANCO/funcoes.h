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
bool login(char password[], char *arquivo);
char menu(void);
//=======================================

//Functions--------------------------------
bool login(char password[], char *arquivo)
{
    ifstream fin;
    stclient client;
    fin.open(arquivo, ios::in);
        fin.read((char *)(&client), sizeof(stclient));
            while(fin && !fin.eof())
            {
                if(strcmp(password,client.password)==0)
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
        << "3 - Depósito\n"
        << "4 - Encerrar\n\n"
        << "  - Digite uma opção";
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
    cin.getline(cad.name, 51);
    cout << "Informe senha: ";
    cin.getline(cad.password, 10);

    arq.open("clientes.txt", ios::out | ios::app);
    arq.write((const char*) (&cad), sizeof(stclient));
    arq.close();

    arq.open("clientes.txt", ios::in);
    arq.read((char* ) (&cad), sizeof(stclient));
    while(!arq.eof())
    {
        cout << "Nome: " << cad.name << endl;
        cout << "senha: " << cad.password << endl;
        arq.read((char *) (&cad), sizeof(stclient));
    }
}

#endif // FUNCOES_H_INCLUDED
