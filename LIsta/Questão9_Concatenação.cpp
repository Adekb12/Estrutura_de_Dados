#include <iostream>
using namespace std;
typedef int Dado;

class Noh{
    friend class Lista;
    private:
        Dado dado;
        Noh* proximo;
    public:
        Noh(Dado dado);
};

Noh::Noh(Dado d){
    dado = d;
    proximo = NULL;
}

class Lista{
    private:
        Noh *primeiro;
        Noh *ultimo;
        int tamanho;
        void removerTudo();
    public:
        Lista();
        ~Lista();
        inline void inserir(Dado dado);
        void inserirFim(Dado dado);
        void removerFim();
        void removerInicio();
        void imprimir();
        inline bool vaziar();
        void concatenar(Lista &lista1,Lista &lista2);
        void removerValor(Dado valor);
};

Lista::Lista(){
    primeiro = NULL;
    ultimo = NULL;
    tamanho = 0;
}

Lista::~Lista(){
    removerTudo();
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


inline void Lista::inserir(Dado dado){
    inserirFim(dado);
}

void Lista::inserirFim(Dado dado){
    Noh* novo = new Noh(dado);
    if(vaziar()){
        primeiro = novo;
        ultimo = novo;
    }else{
        ultimo->proximo = novo;
        ultimo = novo;
    }
    tamanho++;
}

void Lista::imprimir(){
    Noh* aux = primeiro;
    while(aux != NULL){
        cout << aux->dado << " ";
        aux = aux->proximo;
    }
    cout << endl;
}

void Lista::removerFim(){
    if(not vaziar()){
        Noh* aux = primeiro;
        Noh* anterior;
        while(aux->proximo != NULL){
            anterior = aux;
            aux = aux->proximo;
        }
        delete ultimo;
        anterior->proximo = NULL;
        ultimo = anterior;
        tamanho--;
        if(tamanho == 0) primeiro = NULL;
    }
}

void Lista::removerInicio(){
    if(not vaziar()){
        Noh* removido = primeiro;
        primeiro = primeiro->proximo;
        delete removido;
        tamanho--;
        if(vaziar()) ultimo = NULL;
    }
}

void Lista::removerValor(Dado valor){
    Noh* aux;
    Noh* anterior;
    if(not vaziar()){
        aux = primeiro;
        while((aux != NULL) and (aux->dado != valor)){
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

inline bool Lista::vaziar(){
    return (primeiro == NULL);
}

void Lista::concatenar(Lista &lista1,Lista &lista2){
    int tam = lista1.tamanho;
    Noh* aux = lista1.primeiro;
    for(int i=0;i<tam;i++){
        inserir(aux->dado);
        aux = aux->proximo;
    }
    tam = lista2.tamanho;
    aux = lista2.primeiro;
    for(int i=0;i<tam;i++){
        inserir(aux->dado);
        aux = aux->proximo;
    }
}

int main(){
    Lista lista1,lista2,lista3;
    int valor;
    for(int i=0;i<5;i++){
        cin>>valor;
        lista1.inserir(valor);
    }
    for(int i=0;i<5;i++){
        cin>>valor;
        lista2.inserir(valor);
    }
    lista3.concatenar(lista1,lista2);
    lista3.imprimir();
    lista1.imprimir();
    lista2.imprimir();
    for(int i=0;i<3;i++){
        cin>>valor;
        lista3.removerValor(valor);
    }
    lista3.imprimir();
    return 0;
}