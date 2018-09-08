#ifndef FUNCOES_H_INCLUDED
#define FUNCOES_H_INCLUDED

//Libraries and namespaces
#include <iostream>
//#include <windows.h>
//#include <stdlib.h>
#include <string.h>
//#include <sstream>
#include <fstream>
#include <conio2.h>
//#include <time.h>
#include "structs.h"

using namespace std;
//========================

//Function prototypes--------------------
bool login(char senha[], char *arquivo);
char menu(void);
void cadastro(void);
void saque(void);
void listaClientes(void);
void calculaNotas(int valorDaNota, int& numNotas, int& quantiaRestante);
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
        << "4 - Encerrar\n"
        << "5 - Lista Clientes\n"
        << "  << Digite uma op��o";
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
    arq.close();
}

void saque()
{
    clrscr();
    char cpfVer[12], senhaVer[10];
    int localizar = 0, cont = 0;
    int saqueVer, saqueVerAlt;

    fstream arqVer;
    stclient verificar;

    fflush(stdin);
    cout << "Informe o CPF: ";
    cin.getline(cpfVer, 12);
    cout << "Informe a senha: ";
    cin.getline(senhaVer, 10);

    arqVer.open("clientes.txt", ios::in|ios::out);
    arqVer.read((char *) (&verificar), sizeof(stclient));

    while(arqVer && !arqVer.eof())
    {
        cont++;
        if( (strcmp(cpfVer, verificar.cpf) == 0) && (strcmp(senhaVer, verificar.senha) == 0) )
        {
            cout << endl;
            cout << "Nome: " << verificar.nome << endl;
            cout << "CPF: " << verificar.cpf << endl;
            cout << "Saldo Dispon�vel (R$): " << verificar.saldo << endl;
            localizar = 1;
            break;
        }
        arqVer.read((char *) (&verificar), sizeof(stclient));
    }

    //arqVer.open("clientes.txt", ios::out);
    if (localizar == 1)
    {
        int numComp;
        cout << "Informe a quantia do saque: ";
        cin >> saqueVer;
        saqueVerAlt = saqueVer;

        cout << endl;
        calculaNotas(100,numComp,saqueVerAlt);
        cout << "RS100 = " << numComp << endl;
        calculaNotas(50,numComp,saqueVerAlt);
        cout << "RS50 = " << numComp << endl;
        calculaNotas(20,numComp,saqueVerAlt);
        cout << "RS20 = " << numComp << endl;
        calculaNotas(10,numComp,saqueVerAlt);
        cout << "RS10 = " << numComp << endl;
        calculaNotas(5,numComp,saqueVerAlt);
        cout << "RS5 = " << numComp << endl;
        calculaNotas(2,numComp,saqueVerAlt);
        cout << "RS2 = " << numComp << endl;

        if (saqueVer <= verificar.saldo)
        {

            cout << "Quantia dispon�vel! Aguarde o saque." << endl;
            verificar.saldo = verificar.saldo - saqueVer;
            arqVer.seekg((cont-1) * sizeof(stclient));
            arqVer.write((const char*) (&verificar), sizeof(stclient));

            cout << "Seu saldo restante � de: " << verificar.saldo << " R$";

        }else{
            cout << "Voc� n�o possui tal quantia dispon�vel.";
        }
    }
    else
    {
        cout << "Conta inv�lida/N�o registrada!";
    }
    arqVer.close();
}

void listaClientes()
{
    clrscr();
    stclient cad;

    fstream arq;

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
    arq.close();
}

void calculaNotas(int valorDaNota, int& numNotas, int& quantiaRestante)
{
        numNotas = quantiaRestante/valorDaNota;
        quantiaRestante = quantiaRestante % valorDaNota;
}

void deposito()
{
    clrscr();
    char cpfVer[12], senhaVer[10];
    int localizar = 0, cont = 0;
    int depositar, saqueVerAlt;

    fstream arqVer;
    stclient verificar;

    fflush(stdin);
    cout << "Informe o CPF: ";
    cin.getline(cpfVer, 12);
    cout << "Informe a senha: ";
    cin.getline(senhaVer, 10);

    arqVer.open("clientes.txt", ios::in|ios::out);
    arqVer.read((char *) (&verificar), sizeof(stclient));

    while(arqVer && !arqVer.eof())
    {
        cont++;
        if( (strcmp(cpfVer, verificar.cpf) == 0) && (strcmp(senhaVer, verificar.senha) == 0) )
        {
            cout << endl;
            cout << "Nome: " << verificar.nome << endl;
            cout << "CPF: " << verificar.cpf << endl;
            cout << "Saldo Dispon�vel (R$): " << verificar.saldo << endl;
            localizar = 1;
            break;
        }
        arqVer.read((char *) (&verificar), sizeof(stclient));
    }

    if (localizar == 1)
    {
        int numComp;
        cout << endl << "Informe a quantia de dep�sito: ";
        cin >> depositar;

            cout << "Dep�sito recebido! Saldo total cadastrado." << endl;
            verificar.saldo = verificar.saldo + depositar;
            arqVer.seekg((cont-1) * sizeof(stclient));
            arqVer.write((const char*) (&verificar), sizeof(stclient));

            cout << "Seu saldo total � de: " << verificar.saldo << " R$";

    }
    else
    {
        cout << "Conta inv�lida/N�o registrada!";
    }
    arqVer.close();
}
#endif // FUNCOES_H_INCLUDED
