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
        void removerInicio();
        void imprimir();
        inline bool vaziar();
        void somarListas(Lista &listado1,Lista &listado2);
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


void Lista::inserir(Dado dado){
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

inline bool Lista::vaziar(){
    return (primeiro == NULL);
}

void Lista::removerInicio(){
    if(vaziar()){
        cerr << "Remoção em lista vazia!" << endl;
        exit(EXIT_FAILURE);
    }
    Noh* removido = primeiro;
    primeiro = primeiro->proximo;
    delete removido;
    tamanho--;
    if(vaziar()) ultimo = NULL;
}

void Lista::somarListas(Lista &listado1,Lista &listado2){
    Lista soma;
    int tam,inteiro,total;
    if(listado1.tamanho > listado2.tamanho) tam = listado1.tamanho;
    else tam = listado2.tamanho;
    for(int i=0;i<tam;i++){   
        if(listado1.vaziar() and not listado2.vaziar()){
            soma.inserir(listado2.primeiro->dado);
        }
        else if(listado2.vaziar() and not listado1.vaziar()){
            soma.inserir(listado1.primeiro->dado);
        }
        else if(not listado2.vaziar() and not listado1.vaziar()){
            soma.inserir(listado1.primeiro->dado + listado2.primeiro->dado);
        }
        if(not listado1.vaziar())
            listado1.removerInicio();
        if(not listado2.vaziar())
            listado2.removerInicio();
    }
    tam = soma.tamanho;
    Noh* aux = soma.primeiro;
    Noh* superior = aux->proximo;
    for(int i=0;i<tam;i++){
        if(i<(tam-1)){
            inteiro = (aux->dado)/10;
            total = superior->dado;
            total += inteiro;
            superior->dado = total;
            aux->dado = (aux->dado)%10;
            aux = aux->proximo;
            superior = aux->proximo;
        }
    }
    soma.imprimir();
}

int main(){
    Lista listado1,listado2;
    int valor;
    cin>>valor;
    while(valor != -1){
        listado1.inserir(valor);
        cin>>valor;
    }
    cin>>valor;
    while(valor != -1){
        listado2.inserir(valor);
        cin>>valor;
    }
    listado1.somarListas(listado1,listado2);
    return 0;
}