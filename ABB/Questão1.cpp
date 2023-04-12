#include <iostream>
using namespace std;

class Noh{
    friend class ABB;
    private:
        int dado;
        Noh* esquerdo;
        Noh* direito;
    public:
        Noh(int d);
};

Noh::Noh(int d){
    dado = d;
    esquerdo = NULL;
    direito = NULL;
}

class ABB{
    private:
        Noh* raiz;
        int cont;
        Noh* inserirRecursivamente(Noh* umNoh,int umValor);
    public:
        ABB();
        ~ABB();
        void destruirRecursivamente(Noh* r);
        void inserir(int v);
        void imprimir();
        void percorrerPosOrdem();
        void percorrerPosOrdemAux(Noh* umNoh);
};

ABB::ABB(){
    raiz = NULL;
    cont = 0;
}

ABB::~ABB(){
    destruirRecursivamente(raiz);
}

void ABB::destruirRecursivamente(Noh* umNoh){
    if(umNoh != NULL){
        destruirRecursivamente(umNoh->esquerdo);
        destruirRecursivamente(umNoh->direito);
        delete umNoh;
    }
}

void ABB::inserir(int umValor){
    raiz = inserirRecursivamente(raiz,umValor);
}

Noh* ABB::inserirRecursivamente(Noh* umNoh,int umValor){
    if(umNoh == NULL){
        Noh* novo = new Noh(umValor);
        return novo;
    }else{
        if(umValor < umNoh->dado){
            umNoh->esquerdo = inserirRecursivamente(umNoh->esquerdo,umValor);
        }else{
            umNoh->direito = inserirRecursivamente(umNoh->direito,umValor);
        }
    }
    return umNoh;
}

void ABB::percorrerPosOrdem(){
    percorrerPosOrdemAux(raiz);
}

void ABB::percorrerPosOrdemAux(Noh* umNoh){
    if(umNoh != NULL){
        if(umNoh->esquerdo==NULL and umNoh->direito==NULL)
            cont++;
    }
    if(umNoh != NULL){
        percorrerPosOrdemAux(umNoh->esquerdo);
        percorrerPosOrdemAux(umNoh->direito);
    }
}

void ABB::imprimir(){
    cout<<cont;
}


int main(){
    ABB arvore;
    int quant,valor;
    cin>>quant;
    for(int i=0;i<quant;i++){
        cin>>valor;
        arvore.inserir(valor);
    }
    arvore.percorrerPosOrdem();
    arvore.imprimir();
    return 0;
}