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
#include <time.h>
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
void deposito(void);
void abasteceNotas(void);
void verificarNotas(int& numComp,int& temp, int& saque, int& quantianota, int valor);
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
        << "3 - Depósito\n"
        << "4 - Abastecer Notas TESTE\n"
        << "5 - Lista Clientes\n"
        << "6 - Encerrar\n"
        << "  << Digite uma opção";
    gotoxy(1,7);
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
        cout << "Saldo Disponível (R$): " << cad.saldo << endl;
        arq.read((char *) (&cad), sizeof(stclient));
    }
    arq.close();
}

void saque()
{
    clrscr();
    char cpfVer[12], senhaVer[10];
    int localizar = 0, cont = 0;
    int saque, temp;
    int valorEntrada, valorSaidoCaixa;
    int numComp;
    string CedulasFaltam = " ";

    fstream arqVer;
    fstream saqueNotas;
    stclient verificar;
    cedulas notas;

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
            cout << "Saldo Disponível (R$): " << verificar.saldo << endl;
            localizar = 1;
            break;
        }
        arqVer.read((char *) (&verificar), sizeof(stclient));
    }

    //arqVer.open("clientes.txt", ios::out);
    if (localizar == 1)
    {
        cout << "Informe a quantia do saque: ";
        cin >> saque;
        //saqueVerAlt = saqueVer;

        saqueNotas.open("cedulas.txt", ios::in|ios::out);
        saqueNotas.read((char*) (&notas), sizeof(cedulas));

        if (notas.valorTotal > saque)
        {
            temp=saque;
            valorEntrada=saque;
                if (saque <= verificar.saldo)
                {
                    valorSaidoCaixa=0;

                    if(notas.notas100 > 0)
                        calculaNotas(100,numComp,saque);
                    else
                        numComp=0;

                    verificarNotas(numComp,temp,saque,notas.notas100,100);
                        if(notas.notas100 == 0)
                            CedulasFaltam += " R$ 100 ";

                        notas.notas100=notas.notas100-numComp;
                        if(numComp!=0)
                            printf("100: %d NOTAS\n",numComp);
                        valorSaidoCaixa+=numComp*100;

                    if(notas.notas50 > 0 )
                        calculaNotas(50,numComp,saque);
                    else
                        numComp=0;

                    verificarNotas(numComp,temp,saque,notas.notas50, 50);
                        if(notas.notas50 == 0)
                            CedulasFaltam += " R$ 50 ";

                        notas.notas50=notas.notas50-numComp;
                        if(numComp!=0)
                            printf("50:  %d NOTAS\n",numComp);
                        valorSaidoCaixa+=numComp*50;

                    if(notas.notas20 > 0)
                        calculaNotas(20,numComp,saque);
                    else
                        numComp=0;

                    verificarNotas(numComp,temp,saque,notas.notas20, 20);
                        if(notas.notas20 == 0)
                            CedulasFaltam += " R$ 20 ";

                        notas.notas20=notas.notas20-numComp;
                        if(numComp!=0)
                            printf("20:  %d NOTAS\n",numComp);
                        valorSaidoCaixa+=numComp*20;

                    if(notas.notas10 > 0)
                        calculaNotas(10,numComp,saque);
                    else
                        numComp=0;

                    verificarNotas(numComp,temp,saque,notas.notas10, 10);
                        if(notas.notas10 == 0)
                            CedulasFaltam += " R$ 10 ";

                        notas.notas10=notas.notas10-numComp;
                        if(numComp!=0)
                            printf("10:  %d NOTAS\n",numComp);
                        valorSaidoCaixa+=numComp*10;

                    if(notas.notas5 > 0)
                        calculaNotas(5,numComp,saque);
                    else
                        numComp=0;

                    verificarNotas(numComp,temp,saque,notas.notas5, 5);
                        if(notas.notas5 == 0)
                            CedulasFaltam += " R$ 5 ";

                        notas.notas5=notas.notas5-numComp;
                        if(numComp!=0)
                            printf("5:   %d NOTAS\n",numComp);
                        valorSaidoCaixa+=numComp*5;

                    if(notas.notas2 > 0)
                        calculaNotas(2,numComp,saque);
                    else
                        numComp=0;

                    verificarNotas(numComp,temp,saque,notas.notas2, 2);
                        if(notas.notas2 == 0)
                            CedulasFaltam += " R$ 2 ";

                        notas.notas2=notas.notas2-numComp;
                        if(numComp!=0)
                            printf("2:   %d NOTAS\n",numComp);
                        valorSaidoCaixa+=numComp*2;

                    if(valorEntrada==valorSaidoCaixa)
                    {
                        printf("\nSaque Realizado Com Sucesso!\n");
                        verificar.saldo = verificar.saldo - valorSaidoCaixa;
                        cout << "Seu saldo restante é de: " << verificar.saldo << " R$";

                        arqVer.seekg((cont-1) * sizeof(stclient));
                            arqVer.write((const char*) (&verificar), sizeof(stclient));
                        arqVer.close();

                        saqueNotas.seekg(0);
                            saqueNotas.write((const char*) (&notas), sizeof(cedulas));
                        saqueNotas.close();
                    }
                    else
                    {
                        cout << "Não foi possível compor o valor." << endl;
                        cout << "Falta notas de: " << CedulasFaltam;
                    }

                }
                else
                {
                    cout << "Você não possui tal quantia disponível.";
                }
        }
        else
        {
            cout<< "Não há notas suficientes no caixa eletrônico. Solicitar reabastecimento." << endl;
        }

    }
    else
    {
        cout << "Conta inválida/Não registrada!";
    }
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
        cout << "Saldo Disponível (R$): " << cad.saldo << endl;
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
    int depositar;

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
            cout << "Saldo Disponível (R$): " << verificar.saldo << endl;
            localizar = 1;
            break;
        }
        arqVer.read((char *) (&verificar), sizeof(stclient));
    }

    if (localizar == 1)
    {
        cout << endl << "Informe a quantia de depósito: ";
        cin >> depositar;

            cout << "Depósito recebido! Saldo total cadastrado." << endl;
            verificar.saldo = verificar.saldo + depositar;
            arqVer.seekg((cont-1) * sizeof(stclient));
            arqVer.write((const char*) (&verificar), sizeof(stclient));

            cout << "Seu saldo total é de: " << verificar.saldo << " R$";

    }
    else
    {
        cout << "Conta inválida/Não registrada!";
    }
    arqVer.close();
}

void abasteceNotas()
{
    clrscr();
    cedulas notas;
    fstream carga;

    int temp100;
    int temp50;
    int temp20;
    int temp10;
    int temp5;
    int temp2;

    notas.notas100 = 0;
    notas.notas50 = 0;
    notas.notas20 = 0;
    notas.notas10 = 0;
    notas.notas5 = 0;
    notas.notas2 = 0;
    notas.valorTotal = 0;

    fflush(stdin);
    cout << "Informe quantas notas de R$100 foram colocadas: ";
    cin >> temp100;
    cout << "Informe quantas notas R$50 foram colocadas: ";
    cin >> temp50;
    cout << "Informe quantas notas R$20 foram colocadas: ";
    cin >> temp20;
    cout << "Informe quantas notas R$10 foram colocadas: ";
    cin >> temp10;
    cout << "Informe quantas notas R$5 foram colocadas: ";
    cin >> temp5;
    cout << "Informe quantas notas R$2 foram colocadas: ";
    cin >> temp2;

    carga.open("cedulas.txt", ios::in|ios::out);
    carga.read((char *) (&notas), sizeof(cedulas));
            notas.notas100 = notas.notas100 + temp100;
            notas.notas50 = notas.notas50 + temp50;
            notas.notas20 = notas.notas20 + temp20;
            notas.notas10 = notas.notas10 + temp10;
            notas.notas5 = notas.notas5 + temp5;
            notas.notas2 = notas.notas2 + temp2;
            notas.valorTotal = (notas.notas100*100)+(notas.notas50*50)+
            (notas.notas20*20)+(notas.notas10*10)+(notas.notas5*5)+(notas.notas2*2);

        carga.seekg(0);
        carga.write((const char*) (&notas), sizeof(cedulas));
        carga.close();

//===========================================

    carga.open("cedulas.txt", ios::in);
    carga.read((char*) (&notas), sizeof(cedulas));
    while( carga && !carga.eof())
    {
        cout << endl;
        cout << "Notas de 100: " << notas.notas100;
        cout << "\nNotas de 50: " << notas.notas50;
        cout << "\nNotas de 20: " << notas.notas20;
        cout << "\nNotas de 10: " << notas.notas10;
        cout << "\nNotas de 5: " << notas.notas5;
        cout << "\nNotas de 2: " << notas.notas2;
        cout << "\nTotal Caixa: " << notas.valorTotal << "(R$)";

        carga.read((char*) (&notas), sizeof(cedulas));
    }
    carga.close();
}

void verificarNotas(int& numComp,int& temp, int& saque, int& quantianota, int valor)
{
    if(numComp>quantianota)
    {
        numComp=quantianota;
        saque=temp-(quantianota*valor);
        temp=saque;
    }
}

#endif // FUNCOES_H_INCLUDED
