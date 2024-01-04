#include <iostream>

#include "bibTAD-LA.h"

using namespace std;

void criarArvoreBinVazia(TArvoreBin &a, string n)
{
    a.nomeArvore = n;
    a.contItens = 0;
    a.raiz = NULL;
}

void inserir(TArvoreBin &a, TNo *&no, TItem i)
{
    if (no == NULL)
    {
        no = new TNo;
        no->item = i;
        no->esquerda = NULL;
        no->direita = NULL;
        a.contItens++;
        if (a.raiz == NULL)
        {
            a.raiz = no;
        }
    }
    else
    {
        if (i.chave < no->item.chave)
        {
            inserir(a,no->esquerda,i);
        }
        else
        {
            if (i.chave > no->item.chave)
            {
                inserir(a,no->direita,i);
            }
            else
            {
                if (i.chave == no->item.chave)
                {
                    cout << "Não posso inserir. Item já existe!" << endl;
                }
            }
        }
    }
}

void pegarAnterior(TNo *q, TNo *&r)
{

    if (r->direita != NULL)
    {
        pegarAnterior(q, r->direita);
    }
    else
    {
        q->item = r->item;
        q = r;
        r = r->esquerda;
        delete q;
    }
}

void retirar(TItem c, TNo *&p)
{
    TNo *aux;

    if (p == NULL)
    {
        cout << "Item não encontrado" << endl;
    }
    else
    {
        if (c.chave < p->item.chave)
        {
            retirar(c, p->esquerda);
        }
        else
        {
            if (c.chave > p->item.chave)
            {
                retirar(c, p->direita);
            }
            else
            {
                if (p->direita == NULL)
                {
                    aux = p;
                    p = p->esquerda;
                    delete aux;
                }
                else
                {
                    if (p->esquerda != NULL)
                    {
                        pegarAnterior(p, p->esquerda);
                    }
                    else
                    {
                        aux = p;
                        p = p->direita;
                        delete aux;
                    }
                }
            }
        }
    }
}

void criarListaPVazia(TListaDP &lp)
{
    lp.primeiro = new TCelula;
    lp.ultimo = lp.primeiro;
    lp.primeiro->anterior = NULL; //adicionado para duplamente encadeada
    lp.primeiro->proximo = NULL;
}

void inserirL(TListaDP &lp, TItem x)
{
    lp.ultimo->proximo = new TCelula;
    lp.ultimo->proximo->anterior = lp.ultimo;
    lp.ultimo = lp.ultimo->proximo;
    lp.ultimo->item = x;
    lp.ultimo->proximo = NULL;
}

TCelula *pegaAnterior(TListaDP lp, string chave)
{
    TCelula *celAux;
    bool achou = false;

    celAux = lp.primeiro;

    while (celAux->proximo != NULL)
    {
        if (celAux->proximo->item.chave == chave)
        {
            achou = true;
            return celAux;
        }
        celAux = celAux->proximo;
    }
    if (achou == false)
    {
        return NULL;
    }
}

void retirarPorChave(TListaDP &lp, string chave)
{
    TCelula *p = pegaAnterior(lp,chave);
    TCelula *q;

    q = p->proximo;
    p->proximo = q->proximo;
    delete(q);
}

void criarPilhaPVazia(TPilhaP &p)
{
    p.topo = new TCelula;
    p.fundo = p.topo;
    p.fundo->proximo = NULL;
}

bool estaVaziaPilhaP(TPilhaP p)
{
    return p.topo->proximo == NULL;
}


void empilhar(TPilhaP &p, TItem x)
{
    TCelula *aux = new TCelula;
    p.topo->item = x;
    aux->proximo = p.topo;
    p.topo = aux;
}

void desempilhar(TPilhaP &p)
{
        cout << "Nenhum elemento para desempilhar. Pilha Vazia!" << endl;

        TCelula *aux = p.topo;
        cout << "Chave do elemento desempilhado: " << aux->proximo->item.chave << endl;
        p.topo = p.topo->proximo;
        delete(aux);
}
