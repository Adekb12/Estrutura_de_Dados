#include <iostream>
using namespace std;

class Noh{
    friend class ABB;
    private:
        int chave;
        string pavra;
        Noh* esquerdo;
        Noh* direito;
    public:
        Noh(int c,string p);
};

Noh::Noh(int c,string p){
    chave = c;
    pavra = p;
    esquerdo = NULL;
    direito = NULL;
}

class ABB{
    private:
        Noh* raiz;
        Noh* inserirRecursivamente(Noh* umNoh,int umValor,string p);
        Noh* buscarAux(int v);
        void percorrerEmOrdemAux(Noh* umNoh);
    public:
        ABB();
        ~ABB();
        void buscar(int v);
        void destruirRecursivamente(Noh* r);
        void inserir(int c,string p);
        void imprimir(Noh* umNOh);
        void percorrerEmOrdem();
};

ABB::ABB(){
    raiz = NULL;
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

void ABB::inserir(int c,string p){
    raiz = inserirRecursivamente(raiz,c,p);
}

Noh* ABB::inserirRecursivamente(Noh* umNoh,int c,string p){
    if(umNoh == NULL){
        Noh* novo = new Noh(c,p);
        return novo;
    }else{
        if(c < umNoh->chave){
            umNoh->esquerdo = inserirRecursivamente(umNoh->esquerdo,c,p);
        }else{
            umNoh->direito = inserirRecursivamente(umNoh->direito,c,p);
        }
    }
    return umNoh;
}


void ABB::imprimir(Noh* umNoh){
    cout<<umNoh->pavra<<" ";
}

void ABB::buscar(int umValor){
    Noh* valor = buscarAux(umValor);
    if(valor == NULL){
        cout<<"INEXISTENTE"<<endl;
    }else{
        imprimir(valor);
    }
}

Noh* ABB::buscarAux(int umValor){
    Noh* atual = raiz;
    while(atual!=NULL){
        if(atual->chave == umValor)
            return atual;
        else if(atual->chave > umValor)
            atual = atual->esquerdo;
        else 
            atual = atual->direito;
    }
    return atual;
}

void ABB::percorrerEmOrdem(){
    percorrerEmOrdemAux(raiz);
}

void ABB::percorrerEmOrdemAux(Noh* umNoh){
    if(umNoh != NULL){
        percorrerEmOrdemAux(umNoh->esquerdo);
        imprimir(umNoh);
        percorrerEmOrdemAux(umNoh->direito);
    }
}

int main(){
    ABB arvore;
    string palavra;
    int chave;
    char opcao;
    cin>>opcao;
    while(opcao!='f'){
        switch (opcao)
        {
            case 'i':
                cin>>chave>>palavra;
                arvore.inserir(chave,palavra);
                break;
            case 'b':
                cin>>chave;
                arvore.buscar(chave);
                break;
            case 'e':
                arvore.percorrerEmOrdem();
                break;
        }
        cin>>opcao;
    }
}
