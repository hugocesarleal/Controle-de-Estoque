#ifndef BIBASSINATURAS_H_INCLUDED
#define BIBASSINATURAS_H_INCLUDED

#include <iostream>

using namespace std;

struct TItem
{
    string chave;
    string nome;
    string preco;
    string cat;
};

struct TNo
{
    TItem item;
    TNo *esquerda;
    TNo *direita;
};

struct TArvoreBin
{
    string nomeArvore;
    int contItens;
    TNo *raiz;
};

struct TCelula
{
    TCelula *anterior;
    TItem item;
    TCelula *proximo;
};

struct TListaDP
{
    TCelula *primeiro;
    TCelula *ultimo;
};

struct TPilhaP
{
    TCelula *fundo;
    TCelula *topo;
};

void criarArvoreBinVazia(TArvoreBin &a, string n);

void inserir(TArvoreBin &a, TNo *&no, TItem i);

void criarListaPVazia(TListaDP &lp);

void inserirL(TListaDP &lp, TItem x);

void criarPilhaPVazia(TPilhaP &p);

void empilhar(TPilhaP &p, TItem x);

TCelula *pegaAnterior(TListaDP lp, string chave);

void retirarPorChave(TListaDP &lp, string chave);

void pesquisar(int c, TNo *&n, int &cont);

void pegarAnterior(TNo *q, TNo *&r);

void retirar(TItem c, TNo *&p);

void desempilhar(TPilhaP &p);

#endif // BIBASSINATURAS_H_INCLUDED
