#include "funcoes.h"

//QUESTAO: Considerando a seguinte descri��a narrativa, a descri��o do caso
//de uso Realizar Saque e, utilizando os conceitos de PROGRAMA�AO COM ARQUIVOS,
//PONTEIROS e VETORES DINAMICOS apresentados ate o momento, implemente
//sua solu�ao.

//Caso de Uso - Realizar Saque banc�rio

int main()
{setlocale(LC_ALL,"portuguese");

    char choice, ans;

    do
    {clrscr();
        choice = menu();
        switch(choice)
        {
            case '1':
                cadastro();
                //Abrir conta
                cout << "\n\nOutra vez? (s/n)";
                cin >> ans;
            break;

            case '2'://Saque
                cout << "Saque";
                cout << "\n\nOutra vez? (s/n)";
                cin >> ans;
            break;

            case '3'://Dep�sito
                cout << "Depositar";
                cout << "\n\nOutra vez? (s/n)";
                cin >> ans;
            break;

            case '4'://Encerrar
                cout << "Encerrando...";
            break;

            default:
                cout << "Erro de escolha";
        }
    }while(choice != '4' && toupper(ans) == 'S');
    return 0;
}
