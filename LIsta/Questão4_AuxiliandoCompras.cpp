#include <iostream>
using namespace std;

struct mercado{
    string produto;
    int quantidade;
};

class Noh{
    friend class Lista;
    private:
        mercado dado;
        Noh* proximo;
    public:
        Noh(mercado dado);
};

Noh::Noh(mercado d){
    dado = d;
    proximo = NULL;
}

class Lista{
    private:
        Noh *primeiro;
        Noh *ultimo;
        int tamanho;
        void removerTudo();
        void imprimirReversoAux(Noh* umNoh);
    public:
        Lista();
        ~Lista();
        inline void inserir(mercado m);
        void inserirInicio(mercado dado);
        void inserirFim(mercado m);
        int procurar(string i);
        void removerInicio();
        mercado removerFim();
        void removerValor(string i);
        void imprimir();
        inline bool vaziar();
        bool repetizar(string p);
};

Lista::Lista(){
    primeiro = NULL;
    ultimo = NULL;
    tamanho = 0;
}

Lista::~Lista(){
    removerTudo();
}

void Lista::inserir(mercado m){
    inserirFim(m);
}

void Lista::inserirInicio(mercado dado){
    Noh* novo = new Noh(dado);
    if(vaziar()){
        primeiro = novo;
        ultimo = novo;
    }else{
        novo->proximo = primeiro;
        primeiro = novo;
    }
    tamanho++;
}

void Lista::inserirFim(mercado m){
    Noh* novo = new Noh(m);
    if(vaziar()){
        primeiro = novo;
        ultimo = novo;
    }else{
        ultimo->proximo = novo;
        ultimo = novo;
    }
    tamanho++;
}

void Lista::removerTudo(){
    Noh* aux = primeiro;
    Noh* temp;
    while(aux != NULL){
        temp = aux;
        aux = aux->proximo;
        delete temp;
    }
    tamanho = 0;
    primeiro = NULL;
    ultimo = NULL;
}

void Lista::removerInicio(){
    Noh* removido = primeiro;
    primeiro = primeiro->proximo;
    delete removido;
    tamanho--;
    if(vaziar()) ultimo = NULL;
}

mercado Lista::removerFim(){
    Noh* aux = primeiro;
    Noh* anterior;
    while(aux->proximo != NULL){
        anterior = aux;
        aux = aux->proximo;
    }
    mercado AUX;
    AUX = ultimo->dado;
    delete ultimo;
    anterior->proximo = NULL;
    ultimo = anterior;
    tamanho--;
    if(tamanho == 0) primeiro = NULL;
    return AUX;
}

void Lista::removerValor(string item){
    Noh* aux;
    Noh* anterior;
    if(not vaziar()){
        aux = primeiro;
        while((aux != NULL) and (aux->dado.produto != item)){
            anterior  = aux;
            aux = aux->proximo;
        }
        if(aux != NULL){
            if(aux == primeiro)
                removerInicio();
            else if(aux == ultimo)
                removerFim();
            else{
                anterior->proximo = aux->proximo;
                tamanho--;
                delete aux;
            }
        }
    }
}

int Lista::procurar(string i){
    Noh* aux = primeiro;
    while((aux != NULL) and (aux->dado.produto != i)){
        aux = aux->proximo;
    }
    if(aux == NULL){
        return true;
    }
    cout << "(" << aux->dado.produto << ", " << aux->dado.quantidade << ")" << endl;
    return false;
}

void Lista::imprimir(){
    Noh* aux = primeiro;
    cout << "[";
    while(aux != NULL){
        cout << "(" << aux->dado.produto << ", " << aux->dado.quantidade << ")";
        if(aux->proximo != NULL)
            cout << ", ";
        aux = aux->proximo;
    }
    cout << "]" << endl;
}

inline bool Lista::vaziar(){
    return (primeiro == NULL);
}

bool Lista::repetizar(string p){
    if(tamanho == 0)
        return false;
    else {
        Noh* aux = primeiro;
        while(aux!=NULL){  
            if(aux->dado.produto == p)
                return true;
            aux = aux->proximo;
        }
        return false;
    }
}

int main(){
    char op;
    Lista compras;
    mercado rex;
    string item;
    cin>>op;
    while(op!='q'){
        switch (op)
        {
            case 'i':
                cin>>rex.produto>>rex.quantidade;
                if(not compras.repetizar(rex.produto)){
                    compras.inserir(rex);
                }
                break;
            case 'r':
                cin>>item;
                if(compras.repetizar(item)){
                    compras.removerValor(item);
                }else{
                    cout << "item nao existente" << endl;
                }
                break;
            case 'c':
                cin>>item;
                if(compras.procurar(item))
                    cout << "item nao existente" << endl;
                break;
            case 'p':
                compras.imprimir();
                break;
        }
        cin>>op;
    }
    compras.imprimir();
}