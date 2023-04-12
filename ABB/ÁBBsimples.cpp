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
        Noh* inserirRecursivamente(Noh* umNoh,int umValor);
        Noh* maximarAux(Noh* raizSubArvore);
        Noh* minimarAux(Noh* raizSubArvore);
        Noh* buscarAux(int v);
        void percorrerEmOrdemAux(Noh* umNoh);
        void percorrerPreOrdemAux(Noh* umNoh);
        void percorrerPosOrdemAux(Noh* umNoh);
        Noh* removerRecAux(Noh* umNoh,int umValor);
        Noh* removerMenor(Noh* raizSub);
    public:
        ABB();
        ~ABB();
        void destruirRecursivamente(Noh* r);
        void inserir(int v);
        int minimar();
        int maximar();
        void buscar(int v);
        void imprimir(Noh* valor);
        void percorrerEmOrdem();
        void percorrerPreOrdem();
        void percorrerPosOrdem();
        void removerRecursivamente(int v);
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

int ABB::minimar(){
    if(raiz == NULL){
        cerr<<"Árvore vazia"<<endl;
        exit(EXIT_FAILURE);
    }else{
        Noh* minimo = minimarAux(raiz);
        return minimo->dado;
    }
}

Noh* ABB::minimarAux(Noh* raizSubArvore){
    while(raizSubArvore->esquerdo != NULL){
        raizSubArvore = raizSubArvore->esquerdo;
    }
    return raizSubArvore;
}

int ABB::maximar(){
    if(raiz == NULL){
        cerr<<"Árvore vazia"<<endl;
        exit(EXIT_FAILURE);
    }else{
        Noh* maximo = maximarAux(raiz);
        return maximo->dado;
    }
}

Noh* ABB::maximarAux(Noh* raizSubArvore){
    while(raizSubArvore->direito != NULL){
        raizSubArvore = raizSubArvore->direito;
    }
    return raizSubArvore;
}

void ABB::buscar(int umValor){
    Noh* valor = buscarAux(umValor);
    if(valor == NULL){
        cerr<<"Nó não encontrado"<<endl;
        exit(EXIT_FAILURE);
    }else{
        imprimir(valor);
    }
}

Noh* ABB::buscarAux(int umValor){
    Noh* atual = raiz;
    while(atual!=NULL){
        if(atual->dado == umValor)
            return atual;
        else if(atual->dado > umValor)
            atual = atual->esquerdo;
        else 
            atual = atual->direito;
    }
    return atual;
}

void ABB::imprimir(Noh* valor){
    cout<<valor->dado<<" ";
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

void ABB::percorrerPreOrdem(){
    percorrerPreOrdemAux(raiz);
}

void ABB::percorrerPreOrdemAux(Noh* umNoh){
    if(umNoh != NULL){
        imprimir(umNoh);
        percorrerPreOrdemAux(umNoh->esquerdo);
        percorrerPreOrdemAux(umNoh->direito);
    }
}

void ABB::percorrerPosOrdem(){
    percorrerPosOrdemAux(raiz);
}

void ABB::percorrerPosOrdemAux(Noh* umNoh){
    if(umNoh != NULL){
        percorrerPosOrdemAux(umNoh->esquerdo);
        percorrerPosOrdemAux(umNoh->direito);
        imprimir(umNoh);
    }
}

void ABB::removerRecursivamente(int umValor){
    raiz = removerRecAux(raiz,umValor);
}

Noh* ABB::removerRecAux(Noh* umNoh,int umValor){
    if(umNoh == NULL){
        cerr<<"Nó não encontrado"<<endl;
        exit(EXIT_FAILURE);
    }
    Noh* novaRaizSubArvore = umNoh;
    if (umValor < umNoh->dado) {
        umNoh->esquerdo = removerRecAux(umNoh->esquerdo, umValor);
    } else if (umValor > umNoh->dado) {
        umNoh->direito = removerRecAux(umNoh->direito, umValor);
    } else { 
        if (umNoh->esquerdo == NULL) 
            novaRaizSubArvore = umNoh->direito;
        else if (umNoh->direito == NULL) \
            novaRaizSubArvore = umNoh->esquerdo;
        else {
            novaRaizSubArvore = minimarAux(umNoh->direito);
            novaRaizSubArvore->direito = removerMenor(umNoh->direito);  
            novaRaizSubArvore->esquerdo = umNoh->esquerdo;
        }
        delete umNoh;
    } 
    return novaRaizSubArvore;
}

Noh* ABB::removerMenor(Noh* raizSub){
    if(raizSub->esquerdo == NULL)
        return raizSub->direito;
    else { 
        raizSub->esquerdo = removerMenor(raizSub->esquerdo);
        return raizSub;
    }
}

int main(){
    ABB arvore;
    int valor;
    char opcao;
    cin>>opcao;
    while(opcao!='f'){
        switch (opcao)
        {
        case 'i':
            cin>>valor;
            arvore.inserir(valor);
            break;
        case 'r':
            cin>>valor;
            arvore.removerRecursivamente(valor);
            break;
        case 'b':
            cin>>valor;
            arvore.buscar(valor);
            cout<<endl;
            break;
        case 'M':
            cout<<arvore.maximar()<<endl;
            break;
        case 'm':
            cout<<arvore.minimar()<<endl;
            break;
        case 'p':
            arvore.percorrerPreOrdem();
            cout<<endl;
            arvore.percorrerEmOrdem();
            cout<<endl;
            arvore.percorrerPosOrdem();
            cout<<endl;
            break;
        default:
            break;
        }
        cin>>opcao;
    }
    return 0;
}
