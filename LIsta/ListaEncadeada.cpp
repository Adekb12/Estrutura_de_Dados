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
        void imprimirReversoAux(Noh* umNoh);
    public:
        Lista();
        Lista(const Lista& umaLista);
        ~Lista();
        Lista& operator=(const Lista& umaLista);
        inline void inserir(Dado dado);
        void inserirFim(Dado dado);
        void inserirInicio(Dado dado);
        void inserirPos(int pos, Dado dado);
        int procurar(Dado dado);
        void removerInicio();
        void removerFim();
        void removerValor(Dado valor);
        void imprimir();
        void imprimirReverso();
        inline bool vaziar();
};

Lista::Lista(){
    primeiro = NULL;
    ultimo = NULL;
    tamanho = 0;
}

Lista::Lista(const Lista& umaLista){
    primeiro = NULL;
    ultimo = NULL;
    tamanho = 0;
    Noh* aux = umaLista.primeiro;
    while(aux != NULL){
        inserirFim(aux->dado);
        aux = aux->proximo;
    }
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

Lista& Lista::operator=(const Lista& umaLista){
    removerTudo();
    Noh* aux = umaLista.primeiro;
    while(aux != NULL){
        inserirFim(aux->dado);
        aux = aux->proximo;
    }
    return *this;
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

void Lista::inserirInicio(Dado dado){
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

void Lista::inserirPos(int pos, Dado dado){
    Noh* novo = new Noh(dado);
    if((pos <= tamanho) and (pos >= 0)){
        if(vaziar()){
            primeiro = novo;
            ultimo = novo;
        }else if(pos == 0){
            novo->proximo = primeiro;
            primeiro = novo;
        }else if(pos == tamanho){
            ultimo->proximo = novo;
            ultimo = novo;
        }else{
            Noh* aux = primeiro;
            int posAux = 0;
            while(posAux < (pos-1)){
                aux = aux->proximo;
                posAux++;
            }
            novo->proximo = aux->proximo;
            aux->proximo = novo;
        }
        tamanho++;
    }else{
        cerr << "Posição Inexistente!" << endl;
        exit(EXIT_FAILURE);
    }
}

int Lista::procurar(Dado valor){
    Noh* aux = primeiro;
    int posAux = 0;
    while((aux != NULL) and (aux->dado != valor)){
        posAux++;
        aux = aux->proximo;
    }
    if(aux == NULL){
        posAux = -1;
    }
    return posAux;
}

void Lista::imprimir(){
    Noh* aux = primeiro;
    while(aux != NULL){
        cout << aux->dado << " ";
        aux = aux->proximo;
    }
    cout << endl;
}

void Lista::imprimirReverso(){
    imprimirReversoAux(primeiro);
    cout << endl;
}

void Lista::imprimirReversoAux(Noh* umNoh){
    if(umNoh != NULL){
        imprimirReversoAux(umNoh->proximo);
        cout << umNoh->dado << " ";
    }
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

int main(){

}