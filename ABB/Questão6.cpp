#include <iostream>
using namespace std;

class Noh{
    friend class ABB;
    private:
        int dado,cont,nivel;
        Noh* esquerdo;
        Noh* direito;
    public:
        Noh(int d);
};

Noh::Noh(int d){
    dado = d;
    cont = 0;
    nivel = 0;
    esquerdo = NULL;
    direito = NULL;
}

class ABB{
    private:
        Noh* raiz;
        int nivelar;
        Noh* inserirRecursivamente(Noh* umNoh,int umValor);
        Noh* minimarAux(Noh* raizSubArvore);
        Noh* buscarAux(int v);
        void percorrerPreOrdemAux(Noh* esq,Noh* dir);
        Noh* removerRecAux(Noh* umNoh,int umValor);
        Noh* removerMenor(Noh* raizSub);
        void percorrerEmOrdemAux(Noh* umNoh);
    public:
        ABB();
        ~ABB();
        void destruirRecursivamente(Noh* r);
        void inserir(int v);
        int minimar();
        void imprimir(Noh* valor);
        void percorrerPreOrdem();
        void removerRecursivamente(int v);
        void percorrerEmOrdem();
};

ABB::ABB(){
    raiz = NULL;
    nivelar = 0;
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
    Noh* aux = buscarAux(umValor);
    if(aux != NULL)
        aux->cont++;
    else{
        raiz = inserirRecursivamente(raiz,umValor);
    }
}

Noh* ABB::inserirRecursivamente(Noh* umNoh,int umValor){
    if(umNoh == NULL){
        Noh* novo = new Noh(umValor);
        novo->cont++;
        novo->nivel = nivelar;
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
    Noh* minimo = minimarAux(raiz);
    return minimo->dado;
}

Noh* ABB::minimarAux(Noh* raizSubArvore){
    while(raizSubArvore->esquerdo != NULL){
        raizSubArvore = raizSubArvore->esquerdo;
    }
    return raizSubArvore;
}

Noh* ABB::buscarAux(int umValor){
    nivelar = 0;
    Noh* atual = raiz;
    while(atual!=NULL){
        if(atual->dado == umValor){
            atual->nivel = nivelar;
            return atual;
        }
        else if(atual->dado > umValor){
            atual = atual->esquerdo;
            nivelar++;
        }
        else {
            atual = atual->direito;
            nivelar++;
        }
    }
    return atual;
}

void ABB::imprimir(Noh* valor){
    Noh* nivelado = buscarAux(valor->dado);
    cout<<nivelado->dado<<"("<<nivelado->cont<<")/"<<nivelado->nivel<<" ";
}

void ABB::removerRecursivamente(int umValor){
    Noh* aux = buscarAux(umValor);
    if(aux!=NULL){
        if(aux->cont==1)
            raiz = removerRecAux(raiz,umValor);
        else   
            aux->cont--;
    }
}

Noh* ABB::removerRecAux(Noh* umNoh,int umValor){
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
    int n;
    for(int i=0;i<10;i++){
        cin>>n;
        arvore.inserir(n);
    }
    arvore.percorrerEmOrdem();
    cout<<endl;
    for(int i=0;i<5;i++){
        cin>>n;
        arvore.removerRecursivamente(n);
    }
    arvore.percorrerEmOrdem();
    cout<<endl;
    for(int i=0;i<10;i++){
        cin>>n;
        arvore.inserir(n);
    }
    arvore.percorrerEmOrdem();
    cout<<endl;
    for(int i=0;i<5;i++){
        cin>>n;
        arvore.removerRecursivamente(n);
    }
    arvore.percorrerEmOrdem();
    return 0;
}