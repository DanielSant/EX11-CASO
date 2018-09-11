#include "funcoes.h"

//QUESTAO: Considerando a seguinte descriçãa narrativa, a descrição do caso
//de uso Realizar Saque e, utilizando os conceitos de PROGRAMAÇAO COM ARQUIVOS,
//PONTEIROS e VETORES DINAMICOS apresentados ate o momento, implemente
//sua soluçao.

//Caso de Uso - Realizar Saque bancário

int main()
{setlocale(LC_ALL,"portuguese");

    char choice, ans;
    char CPF[12];
    char key[10];

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
                saque();
                cout << "\n\nOutra vez? (s/n)";
                cin >> ans;
            break;

            case '3'://Depósito
                deposito();
                cout << "\n\nOutra vez? (s/n)";
                cin >> ans;
            break;

            case '4'://Extrato
                clrscr();
                cout << "Informe o CPF: ";
                cin >> CPF;
                cout << "Digite sua Senha: ";
                cin >> key;
                transacao(CPF,key);
                cout << "\n\nOutra vez? (s/n)";
                cin >> ans;
            break;

            case '5'://Encerrar
                abasteceNotas();
                cout << "\n\nOutra vez? (s/n)";
                cin >> ans;
            break;

            case '6':
                listarClientes();//Listar Clientes
                cout << "\n\nOutra vez? (s/n)";
                cin >> ans;
            break;
            case '7':
                cout << "\nVlw :) :c :+\n";
            break;

            default:
                cout << "Erro de escolha";
        }
    }while(choice != '7' && toupper(ans) == 'S');
    return 0;
}
