// bibliotecas da linguagem
#include <iostream>
#include <clocale>
#include <string>
#include <cstdlib>
#include <ctime>


// minhas bibliotecas
#include "bibTAD-LA.h"
#include "bibOpEsp.h"

using namespace std;

int main()
{
    setlocale(LC_ALL,"Portuguese");

    //instancias
    TArvoreBin estoque;
    TListaDP lista;
    TPilhaP pilha;

    //criação da arvore, lista e pilha
    criarArvoreBinVazia(estoque,"Estoque");
    criarListaPVazia(lista);
    criarPilhaPVazia(pilha);

    int opcao;

    menu:
    {
        system("cls");

        cout << "-=-=-=-=-=-=Menu de Estoque=-=-=-=-=-=-\n\n";
        cout << "1. Carregar estoque\n";
        cout << "2. Adicionar item ao estoque\n";
        cout << "3. Mostrar quais itens estão no estoque\n";
        cout << "4. Efetuar uma venda\n";
        cout << "5. Extrato de vendas do dia\n";
        cout << "6. Sair\n";
        cout << "\nEscolha uma opção: ";
        cin >> opcao;

        system("cls");

        switch (opcao)
        {
        case 1:
            baixar("dados.txt",4,estoque,estoque.raiz);
            goto menu;
            break;
        case 2:
            cadItem(estoque,estoque.raiz);
            goto menu;
            break;
        case 3:
            percorrerINOrdem(estoque.raiz);
            system("pause");
            goto menu;
            break;
        case 4:
            vendedor(estoque,estoque.raiz,lista,pilha);
            goto menu;
            break;
        case 5:
            itensVendidos(pilha);
            system("pause");
            goto menu;
            break;
        case 6:
            carregar("dados.txt",estoque.raiz);
            cout << "Saindo...\n";
            break;
        default:
            cout << "Opção inválida, escolha uma opção válida.\n";
            goto menu;
        }
    }

    return 0;
}
