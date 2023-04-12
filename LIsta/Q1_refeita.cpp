#include <iostream>
using namespace std;

class Noh{
    friend class Lista;
    private:
        int dado;
        Noh* proximo;
    public:
        Noh(int d);
};

Noh::Noh(int d){
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
        inline void inserir(int dado);
        void inserirFim(int dado);
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


void Lista::inserir(int dado){
    inserirFim(dado);
}

void Lista::inserirFim(int dado){
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
    Noh* removido = primeiro;
    primeiro = primeiro->proximo;
    delete removido;
    tamanho--;
    if(vaziar()) ultimo = NULL;
}

void Lista::somarListas(Lista &listado1,Lista &listado2){
    int tam,v1,v2,soma = 0,sobra = 0;
    if(listado1.tamanho > listado2.tamanho)
        tam = listado1.tamanho;
    else 
        tam = listado2.tamanho;
    while(tam>0){
        v1 = 0;
        v2 = 0;
        if(not listado1.vaziar()){
            v1 = listado1.primeiro->dado;
            listado1.removerInicio();
        }
        if(not listado2.vaziar()){
            v2 = listado2.primeiro->dado;
            listado2.removerInicio();
        }
        soma = (v1+v2+sobra)%10;
        sobra = (v1+v2+sobra)/10;
        inserir(soma);
        tam--;
    }
}

int main(){
    Lista listado1,listado2,listasom;
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
    listasom.somarListas(listado1,listado2);
    listasom.imprimir();
    return 0;
}