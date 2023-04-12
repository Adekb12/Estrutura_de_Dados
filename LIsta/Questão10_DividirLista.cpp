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
        void removerFim();
        void imprimir();
        inline bool vaziar();
        void dividirLista(int N,Lista &lst);
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

void Lista::removerFim(){
    if(vaziar()){
        cerr << "Remoção em lista vazia!" << endl;
        exit(EXIT_FAILURE);
    }
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

void Lista::dividirLista(int N,Lista &lst){
    int pos = tamanho-1;
    if(N!=(tamanho-1)){
        Noh* aux = primeiro;
        int posAux = 0;
        while(aux != NULL){
            if(posAux>N){
                lst.inserir(aux->dado);
            }
            posAux++;
            aux = aux->proximo;
        }
        while(pos>N){
            removerFim();
            pos--;
        }
    }
}

int main(){
    Lista lll,lst;
    int n,valor,N;
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>valor;
        lll.inserir(valor);
    }
    cin>>N;
    if(N>(n-1)){
        lll.imprimir();
        cout << "-1";
    }else{
        lll.dividirLista(N,lst);
        lll.imprimir();
        lst.imprimir();
    }
    return 0;
}
