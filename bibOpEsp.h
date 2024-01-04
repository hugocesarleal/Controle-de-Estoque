#ifndef BIBESPECIFICA_H_INCLUDED
#define BIBESPECIFICA_H_INCLUDED

void percorrerINOrdem(TNo *&no);

void percorrerPreOrdem(TNo *&no);

void percorrerPosOrdem(TNo *&no);

void mostrarED(TListaDP lp);

void mostrarP(TPilhaP p);

void cadItem(TArvoreBin &a,TNo *&n);

void separaVenda(string c, TNo *&n,TListaDP &l);

void vendedor(TArvoreBin &a, TNo *&n, TListaDP &l, TPilhaP &p);

bool estaVaziaPilhaP(TPilhaP p);

void transferir(TListaDP l, TPilhaP p);

int lendoArq(string nomeArq, int quantTokens);

int escrevendoArq(string nomeArq, string vetDados[], int quantTokens);

int carregar(string nomeArq, TNo *&n);

void limpar(string nomeArq);

int baixar(string nomeArq, int quantTokens,TArvoreBin &a, TNo *&n);

void itensVendidos(TPilhaP p);

#endif // BIBESPECIFICA_H_INCLUDED
