#include <iostream>
using namespace std;

int funcaoHash(int c, int n) {
    return c % n;
}

class Noh{
    friend class Lista;
    friend class tabelaHash;
    private:
        int chave;
        string valor;
        Noh* proximo;
    public:
        Noh(int c,string v);
};

Noh::Noh(int c,string v){
    chave = c;
    valor = v;
    proximo = NULL;
}

class Lista{
    friend class tabelaHash;
    private:
        Noh *primeiro;
        Noh *ultimo;
        int tamanho;
        void removerTudo();
    public:
        Lista();
        ~Lista();
        void inserirFim(int c,string v);
        void removerInicio();
        void removerFim();
        void removerValor(int c);
        void procurar(int cha);
        inline bool vaziar();
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
    primeiro = NULL;
    ultimo = NULL;
}

void Lista::procurar(int cha){
    Noh* aux = primeiro;
    bool achou = true;
    while(aux != NULL and achou){
        if(aux->chave == cha){
             cout<<aux->valor<<endl;
             achou = false;
        }
        aux = aux->proximo;
    }
}

void Lista::inserirFim(int c,string v){
    Noh* novo = new Noh(c,v);
    if(vaziar()){
        primeiro = novo;
        ultimo = novo;
    }else{
        ultimo->proximo = novo;
        ultimo = novo;
    }
    tamanho++;
}

inline bool Lista::vaziar(){
    return (primeiro == NULL);
}

void Lista::removerFim(){
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
    Noh* removido = primeiro;
    primeiro = primeiro->proximo;
    delete removido;
    tamanho--;
    if(vaziar()) ultimo = NULL;
}

void Lista::removerValor(int c){
    Noh* aux;
    Noh* anterior;
    bool removeu = false;
    if(not vaziar()){
        aux = primeiro;
        while((aux != NULL) and (aux->chave != c)){
            anterior  = aux;
            aux = aux->proximo;
        }
        if(aux != NULL){
            removeu = true;
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
    if(!removeu)
        cout<<"ERRO"<<endl;
}

class tabelaHash{
    private:
        int capacidade;
        Lista* tabeHa;
        int* vetorP;
    public:
        tabelaHash(int cap);
        ~tabelaHash();
        void inserir(int c,string v);
        void buscar(int c);
        void remover(int c);
        void imprimir();
        void redimensionar();
        void destruir();
};

tabelaHash::tabelaHash(int cap){
    tabeHa = new Lista[cap];
    capacidade = cap;
    vetorP = new int[capacidade];
    /*for(int i=0;i<capacidade;i++){
        vetorP[i] = -1;
    }*/
}

tabelaHash::~tabelaHash(){
    destruir();
}

void tabelaHash::destruir(){
    for(int i;i<capacidade;i++){
        tabeHa[i].removerTudo();
    }
    delete[] tabeHa;
}


void tabelaHash::inserir(int chave,string valor){
    int pos = funcaoHash(chave,capacidade);
    tabeHa[pos].inserirFim(chave, valor);
    //vetorP[pos]=pos;
    float cont = 0;
    for(int i=0;i<capacidade;i++){
        if(tabeHa[i].primeiro != NULL) {
            cont++;
        }

    }
    if(float(0.7*capacidade)<=cont){
        redimensionar();
    }
}

void tabelaHash::remover(int c){
    int pos = funcaoHash(c,capacidade);
    tabeHa[pos].removerValor(c);
}

void tabelaHash::buscar(int c){
    int pos = funcaoHash(c,capacidade);
    tabeHa[pos].procurar(c);
}

void tabelaHash::imprimir(){
    Noh* atual;
    for (int i = 0; i < capacidade; i++) {
        cout << "Posicao " << i << ": ";
        atual = tabeHa[i].primeiro;
        if(atual != NULL){
            cout<<atual->chave<<" "<<atual->valor<<endl;
        }
        if(atual == NULL)
            cout<<endl;
        else if(atual->proximo != NULL){
            cout<<"Lista de colisao: ";
            atual = atual->proximo;
            while(atual!=NULL){
                cout<<atual->chave<<" "<<atual->valor;
                atual = atual->proximo;
                if(atual!=NULL)
                    cout<<", ";
            }
            cout<<endl;
        }
    }
    cout << "-----------------------" << endl;
}

void tabelaHash::redimensionar(){
    tabelaHash tabeAux(capacidade*2);
    Noh* atual;
    for (int i = 0; i < capacidade; i++) {
        atual = tabeHa[i].primeiro;
        while (atual != NULL) {
            tabeAux.inserir(atual->chave,atual->valor);
            atual = atual->proximo;
        }
    }
    capacidade *= 2;
    destruir();
    tabeHa = new 
    Lista[capacidade];
    for (int i = 0; i < (capacidade); i++) {
        atual = tabeAux.tabeHa[i].primeiro;
        while (atual != NULL) {
            inserir(atual->chave,atual->valor);
            atual = atual->proximo;
        }
    }
}

int main(){
    int tam,chave,tamanho;
    cin>>tam;
    tabelaHash tata(tam);
    char op;
    string valor;
    cin>>op;
    while(op!='S'){
        switch(op){
        case 'I':
            cin>>chave>>valor;
            tata.inserir(chave,valor);
            break;
        case 'R':
            cin>>chave;
            tata.remover(chave);
            break;
        case 'B':
            cin>>chave;
            tata.buscar(chave);
            break;
        case 'P':
            tata.imprimir();
            break;
        }
        cin>>op;
    }
    return 0;
}