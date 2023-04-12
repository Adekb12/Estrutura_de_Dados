#include <iostream>
using namespace std;

int funHash(string p){
    return (p.length())%23;
}

class Noh{
    friend class Lista;
    private:
        string palavra;
        string significado;
        Noh* proximo;
    public:
        Noh(string p,string s);
};

Noh::Noh(string p,string v){
    palavra = p;
    significado = v;
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
        void inserirFim(string p,string s);
        //void inserirInicio(int c,string v);
        string procurar(string p);
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

string Lista::procurar(string p){
    Noh* aux = primeiro;
    while(aux != NULL){
        if(aux->palavra == p){
            return aux->significado;
        }
        aux = aux->proximo;
    }
    return "NULL";
}

void Lista::inserirFim(string c,string v){
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

class tabelaHash{
    private:
        int capacidade;
        Lista* dicionario;
    public:
        tabelaHash(int cap = 23);
        ~tabelaHash();
        void inserir(string p,string s);
        void buscar(string p);
};

tabelaHash::tabelaHash(int cap){
    dicionario = new Lista[cap];
    capacidade = cap;
}

tabelaHash::~tabelaHash(){
    for(int i;i<23;i++){
        dicionario[i].removerTudo();
    }
    delete[] dicionario;
}

void tabelaHash::inserir(string p,string s){
    int pos = funHash(p);
    dicionario[pos].inserirFim(p, s);
}

void tabelaHash::buscar(string p){
    int pos = funHash(p);
    cout<<"["<<p<<"] => "<<dicionario[pos].procurar(p)<<endl;
}

int main(){
    tabelaHash labeta(23);
    int quantP;
    cin>>quantP;
    string palavra,significado;
    for(int i=0;i<quantP;i++){
        cin>>palavra;
        getline(cin,significado);
        labeta.inserir(palavra,significado);
    }
    cin>>palavra;
    while(palavra != "-1"){
        labeta.buscar(palavra);
        cin>>palavra;
    }
}