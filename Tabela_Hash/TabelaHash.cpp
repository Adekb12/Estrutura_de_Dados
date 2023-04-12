#include <iostream>
using namespace std;

int funHash(int c,int capa){
    return c%capa;
}

class Noh{
    friend class Lista;
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
        //void inserirInicio(int c,string v);
        string procurar(int cha);
        void alterar(int c,string nw);
        void removerInicio();
        void removerFim();
        void removerValor(string v);
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

string Lista::procurar(int cha){
    Noh* aux = primeiro;
    int posAux = 0;
    while((aux != NULL) and (aux->chave != cha)){
        posAux++;
        aux = aux->proximo;
    }
    if(aux == NULL){
        return "NAOENCONTRADO";
    }
    return "ENCONTRADO";
}

void Lista::alterar(int cha,string nw){

}

void Lista::inserirFim(int c,string v){
    Noh* novo = new Noh(c,v);
    if(vaziar()){
        primeiro = novo;
        ultimo = novo;
    }else{
        if(procurar(c) != "ENCONTRADO"){
            ultimo->proximo = novo;
            ultimo = novo;
        }else{
            cout<<"Chave já existente!!"<<endl;
            tamanho--;
        }
    }
    tamanho++;
}

//Caso precise inserir no inicio das Listas
/*void Lista::inserirInicio(int c,string v){
    Noh* novo = new Noh(c,v);
    if(vaziar()){
        primeiro = novo;
        ultimo = novo;
    }else{
        novo->proximo = primeiro;
        primeiro = novo;
    }
    tamanho++;
}*/

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

void Lista::removerValor(string vava){
    Noh* aux;
    Noh* anterior;
    if(not vaziar()){
        aux = primeiro;
        while((aux != NULL) and (aux->valor != vava)){
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

class tabelaHash{
    private:
        int capacidade;
        Lista* tabeHa;
    public:
        tabelaHash(int cap);
        ~tabelaHash();
        void inserir(int c,string v);
        void remover(int c,string v);
        void alterar(int c,string nv);
};

tabelaHash::tabelaHash(int cap){
    tabeHa = new Lista[cap];
    capacidade = cap;
}

tabelaHash::~tabelaHash(){
    delete[] tabeHa;
}

void tabelaHash::inserir(int chave,string valor){
    int pos = funHash(chave,capacidade);
    tabeHa[pos].inserirFim(chave, valor);
}

void tabelaHash::remover(int c,string v){
    int pos = funHash(c,capacidade);
    //estou enviando só o valor como parãmetro no remover, possivelmente pode ser a chave
    tabeHa[pos].removerValor(v);
}

/*void tabelaHash::alterar(int chave,string newvalor){
    int pos = funHash(c,capacidade);
    if(tabeHa[pos].procurar(chave) == "ENCONTRADO"){
        tabeHa[pos].alterar(chave,newvalor);
    }else{
        cout<<"A chave não foi encontrada"<<endl;
    }
}*/

int main(){
    int tam;
    cin>>tam;
    tabelaHash tata(tam);
}