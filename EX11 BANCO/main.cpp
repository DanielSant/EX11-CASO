#include "funcoes.h"

//QUESTAO: Considerando a seguinte descriçãa narrativa, a descrição do caso
//de uso Realizar Saque e, utilizando os conceitos de PROGRAMAÇAO COM ARQUIVOS,
//PONTEIROS e VETORES DINAMICOS apresentados ate o momento, implemente
//sua soluçao.

//Caso de Uso - Realizar Saque bancário

int main()
{setlocale(LC_ALL,"portuguese");

    char choice, ans;

    do
    {clrscr();
        choice = menu();
        switch(choice)
        {
            case '1'://Abrir conta
                cout << "Abrir conta";
                cout << "\n\nOutra vez? (s/n)";
                cin >> ans;
            break;

            case '2'://Saque
                cout << "Saque";
                cout << "\n\nOutra vez? (s/n)";
                cin >> ans;
            break;

            case '3'://Depósito
                cout << "Depositar";
                cout << "\n\nOutra vez? (s/n)";
                cin >> ans;
            break;

            case '4'://Encerrar
                cout << "Tchau";
            break;

            default:
                cout << "Erro de escolha";
        }
    }while(choice != '4' && toupper(ans) == 'S');
    return 0;
}
