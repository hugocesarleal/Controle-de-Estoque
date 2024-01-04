#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <stdio.h>

#include "bibTAD-LA.h"
#include "bibOpEsp.h"

using namespace std;

//mostra os itens no estoque
void percorrerINOrdem(TNo *&no)
{
    if(no != NULL)
    {
        percorrerINOrdem(no->esquerda);
        if(no->item.chave != "a399")
        {
            cout << "Nome: " << no->item.nome << endl;
            cout << "Categoria: " << no->item.cat << endl;
            cout << "Preço: " << no->item.preco << endl;
            cout << "Chave: " << no->item.chave << endl;
            cout << "-------------------------------------------\n" << endl;
        }
        percorrerINOrdem(no ->direita);
    }
}

//mostra os itens na lista de venda
void listaVendas(TListaDP lp)
{
    TCelula *celAux;
    celAux = lp.primeiro->proximo; // começa como a primeira célula válida, ie, que tem item válido

    cout << "\n=== MOSTRANDO A LISTA DE VENDAS === "<< endl;
    while (celAux != NULL)
    {
        cout << "Nome: " << celAux->item.nome << endl;
        cout << "Categoria: " << celAux->item.cat << endl;
        cout << "Preço: " << celAux->item.preco << endl;
        cout << "Chave: " << celAux->item.chave << endl;
        cout << "-------------------------------------------\n" << endl;
        celAux = celAux->proximo;
    }
}


void itensVendidos(TPilhaP p){
    TCelula *celAux;
    celAux = p.topo->proximo;

    cout << "=== MOSTRANDO O EXTRATO DE VENDAS === "<< endl;
    if (estaVaziaPilhaP(p))
    {
        cout << "Pilha vazia! Nenhum elemento para mostrar!" << endl;
    }
    else
    {
        while (celAux != NULL)
        {
            cout << "Nome: " << celAux->item.nome << endl;
            cout << "Categoria: " << celAux->item.cat << endl;
            cout << "Preço: " << celAux->item.preco << endl;
            cout << "Chave: " << celAux->item.chave << endl;
            celAux = celAux->proximo;
            cout << "-------------------------------------------\n" << endl;
        }
    }
}

//verifica se já existe na árvore um item que tenha a chave igual a informada
int pesquisarCode(string c, TNo *&n, int &cont)
{
    if (n == NULL)
    {
    }
    else
    {
        if (c < n->item.chave)
        {
            cont++;
            pesquisarCode(c, n->esquerda,cont);

        }
        else
        {
            if (c > n->item.chave)
            {
                cont++;
                pesquisarCode(c, n->direita,cont);
            }
            else
            {
                return -1;
            }
        }
    }
}

//retira o item a ser vendido da estoque(árvore) e o coloca na lista de venda
void separaVenda(string c, TNo *&n,TListaDP &l)
{
    if (n == NULL)
    {
        cout << "Item não localizado no estoque" << endl;
    }
    else
    {
        if (c < n->item.chave)
        {
            separaVenda(c, n->esquerda,l);
        }
        else
        {
            if (c > n->item.chave)
            {
                separaVenda(c, n->direita,l);
            }
            else
            {
                inserirL(l,n->item);
                retirar(n->item,n);
            }
        }
    }
}

/*gera um código aleatório com base na categoria do item, se for comida, ele inicia com a letra "a", se for limpeza, inicia com "b",
ambos sendo seguidos de um número entre 0 e 400, que será gerado "aleatóriamente" usando o horário do dispositivo como seed.
Também já verificado se existe um outro código igual na árvore com a função pesquisarCode, caso exista um igual, será gerado outro código*/
string code(TArvoreBin &a, TNo *&n, int c)
{
    string i;
    int teste;

volta:

    unsigned seed = time(0);

    srand(seed);

    if(c==1)
    {
        i+="a"+to_string(rand()%400);
    }
    else
    {
        i+="b"+to_string(rand()%400);
    }

    teste=pesquisarCode(i,n,a.contItens);

    if(teste==-1)
    {
        goto volta;
    }
    else
    {
        return i;
    }
}

//procedimento responsável por cadastrar os itens no estoque(árvore)
void cadItem(TArvoreBin &a,TNo *&n)
{
    TItem iAux;
    string resp;
    int c;

    //item nulo que serve como raiz fixa da árvore
    iAux.cat="Vazio";
    iAux.chave="a399";
    iAux.nome="Vazio";
    iAux.preco="0";
    inserir(a,n,iAux);

    while (resp != "n")
    {
        cout << "=== CADASTRO DE PRODUTOS ===" << endl;

        cout << "Nome do produto: ";
        cin >> iAux.nome;

        cout << "Preço do produto: ";
        cin >> iAux.preco;

volta:

        cout << "Categoria do Produto:\n1 - Comida\n2 - Limpeza " << endl;
        cin >> c;

        switch(c)
        {
        case 1:
            iAux.cat="Comida";
            iAux.chave=code(a,n,1);
            break;

        case 2:
            iAux.cat="Limpeza";
            iAux.chave=code(a,n,2);
            break;

        default:
            goto volta;
        }

        inserir(a,n,iAux);

        cout << "Continuar cadastro (s/n): ";
        cin >> resp;

        system("cls");
    }
}

//interface de venda que seleciona quais itens serão vendidos, mostra a lista de venda, e logo após efetua a venda, armazenando seus dados na pilha
void vendedor(TArvoreBin &a, TNo *&n, TListaDP &l, TPilhaP &p)
{
    string c;
    int resp=0;

venda:

    cout << "Qual a chave do item que deseja vender? " << endl;
    cin >> c;

    separaVenda(c,n,l);

    cout << "Deseja vender outro item?\n1 - Sim\n2 - Não\n " << endl;
    cin >> resp;

    if(resp==1)
    {
        goto venda;
    }

    system("cls");

    cout << "Itens separados para venda:" << endl;

    listaVendas(l);

    system("pause");

    TCelula *celAux;
    celAux = l.primeiro->proximo;

    while (celAux != NULL)
    {
        empilhar(p,celAux->item);

        retirarPorChave(l,celAux->item.chave);

        celAux=celAux->proximo;
    }
}

//transfere as informações dos itens armazenados no estoque(arvore) para a memoria secundária, em um arquivo de texto
int carregar(string nomeArq, TNo *&n)
{
    int i, quantTokens=4;
    string registro = "";
    string vetDados[4];

    if(n->esquerda != NULL)
    {
        carregar("dados.txt",n->esquerda);
    }

    if(n->direita != NULL)
    {
        carregar("dados.txt",n->direita);
    }

    vetDados[0]=n->item.cat;
    vetDados[1]=n->item.chave;
    vetDados[2]=n->item.nome;
    vetDados[3]=n->item.preco;

    fstream arquivo("dados.txt",ios::app);
    if(n->item.chave != "a399")
    {
        if (arquivo.is_open())
        {
            for (i=0; i<quantTokens; i++)
            {
                if (i < quantTokens-1)
                {
                    registro = registro + vetDados[i] + ";";
                }
                else
                {
                    registro = registro + vetDados[i] + "\n";
                }
            }
            arquivo << registro;
            arquivo.close();
            return 0;
        }
        else
        {
            cout << "Problemas com o arquivo!" << endl;
            return -1;
        }
    }
}

//apaga o arquivo de texto
void limpar(string nomeArq)
{
    ifstream arquivo("dados.txt",ios::trunc);

    remove("dados.txt");

    arquivo.close();
}

//transfere os dados dos itens que estão no arquivo para a árvore
int baixar(string nomeArq, int quantTokens,TArvoreBin &a, TNo *&n)
{
    TItem item,iAux;

    iAux.cat="Vazio";
    iAux.chave="a399";
    iAux.nome="Vazio";
    iAux.preco="0";
    inserir(a,n,iAux);

    fstream arq("dados.txt");

    if (arq.is_open())
    {
        string registro, token;
        string valores[quantTokens];
        int i, j, contToken, contRegistro;

        contRegistro = 1;
        while (arq.good())
        {
            getline(arq,registro);
            if (registro.length() > 0)
            {
                token = "";

                for (j=0; j < quantTokens; j++)
                {
                    valores[j] = token;
                }

                i=0;
                contToken=0;
                while (i <= int(registro.length()))
                {
                    if (registro[i] != ';')
                    {
                        token = token + registro[i];
                    }
                    else
                    {
                        valores[contToken] = token;

                        contToken++;
                        token = "";
                    }
                    i++;
                }
                valores[contToken] = token;

                item.cat=valores[0];
                item.chave=valores[1];
                item.nome=valores[2];
                item.preco=valores[3];

                inserir(a,n,item);
                contRegistro++;
            }
        }
    }
    else
    {
        cout << "Problemas com a abertura do arquivo!" << endl;
        return -1;
    }
    arq.close();

    //apaga o arquivo após carregar os dados
    limpar("dados.txt");

    cout << "Estoque carregado!" << endl;

    system("pause");

    return 0;
}
