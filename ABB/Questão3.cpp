#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Noh{
    friend class ABB;
    private:
        string palavra;
        string conca = "";
        Noh* esquerdo;
        Noh* direito;
    public:
        Noh(int c,string p);
};

Noh::Noh(int cont,string plv){
    palavra = plv;
    conca += to_string(cont);
    conca += " ";
    esquerdo = NULL;
    direito = NULL;
}

class ABB{
    private:
        Noh* raiz;
        Noh* inserirRecursivamente(Noh* umNoh,int cont,string plv);
        Noh* buscarAux(string plv);
    public:
        ABB();
        ~ABB();
        void destruirRecursivamente(Noh* r);
        void inserir(int c,string p);
        void imprimir(string plv);
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

void ABB::inserir(int cont,string plv){
    Noh* noh = buscarAux(plv);
    if(noh == NULL)
        raiz = inserirRecursivamente(raiz,cont,plv);
    else{
        noh->conca += to_string(cont);
        noh->conca += " ";
    }
}

Noh* ABB::inserirRecursivamente(Noh* umNoh,int cont,string plv){
    if(umNoh == NULL){
        Noh* novo = new Noh(cont,plv);
        return novo;
    }else{
        if(plv < umNoh->palavra){
            umNoh->esquerdo = inserirRecursivamente(umNoh->esquerdo,cont,plv);
        }else{
            umNoh->direito = inserirRecursivamente(umNoh->direito,cont,plv);
        }
    }
    return umNoh;
}


void ABB::imprimir(string plv){
    Noh* buscar = buscarAux(plv);
    if(buscar == NULL)
        cout<<"-1";
    else    
        cout<<buscar->conca;
}

Noh* ABB::buscarAux(string plv){
    Noh* atual = raiz;
    while(atual != NULL){
        if(atual->palavra == plv)
            return atual;
        else if(atual->palavra > plv)
            atual = atual->esquerdo;
        else 
            atual = atual->direito;
    }
    return atual;
}

int main(){
    ABB arvore;
    int cont = 0;
    string palavra;
    ifstream arquivo("entrada.txt");
    if(arquivo){
        while(arquivo >> palavra){
            cont++;
            arvore.inserir(cont,palavra);
        }
    }
    cin>>palavra;
    arvore.imprimir(palavra);
    arquivo.close();
    return 0;
}