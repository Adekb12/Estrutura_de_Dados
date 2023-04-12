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
        int cLeft,cRight;
        Noh* inserirRecursivamente(Noh* umNoh,int umValor);
    public:
        ABB();
        ~ABB();
        void destruirRecursivamente(Noh* r);
        void inserir(int v);
        void imprimir();
};

ABB::ABB(){
    raiz = NULL;
    cLeft = 0;
    cRight = 0;
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
	if(raiz!=NULL){
		if(umValor<raiz->dado)
			cLeft++;
		else 
			cRight++;
	}
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

void ABB::imprimir(){
    cout<<cLeft-cRight;
}


int main(){
    ABB arvore;
    int valor,cont = 0;
    cin>>valor;
    while(valor!=-1){
        cont++;
        arvore.inserir(valor);
        cin>>valor;
    }
    cout<<cont<<" ";
    arvore.imprimir();
    return 0;
}
