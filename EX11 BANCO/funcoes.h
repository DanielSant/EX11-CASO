
//Libraries and namespaces
#include <iostream>
#include <locale.h>
#include <cstring>
#include <fstream>
#include <conio2.h>
using namespace std;
//========================

//Function prototypes--------------------
bool login(char password[], char *arquivo);
char menu(void);
//=======================================

//Structs----------------------------------
typedef struct
{
    int numberCont;//N�mero id da conta
    char name[21];//Nome Completo
    double sale;//Saldo banc�rio
    char password[10];//Requisitada para logar
    bool avail;//Apagar conta l�gicamente
}stclient;
//=========================================

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
        << "3 - Dep�sito\n"
        << "4 - Encerrar\n\n"
        << "  - Digite uma op��o";
    gotoxy(1,6);
    cin >> choice;
    return choice;
}
