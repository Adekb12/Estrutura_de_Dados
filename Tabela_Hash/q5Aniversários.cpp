#include <iostream>
using namespace std;

int funcaoHash(int d,int m,int limite) {
    return (d*m - 1)%limite;
}

class Noh{
    friend class Lista;
    friend class tabelaHash;
    private:
        string nome;
        int dia,mes,ano;
        Noh* proximo;
    public:
        Noh(string n,int d,int m,int a);
};

Noh::Noh(string n,int d,int m,int a){
    nome = n;
    dia = d;
    mes = m;
    ano = a;
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
        void inserirFim(string n,int d,int m,int a);
        int contar(int d,int m);
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

int Lista::contar(int d,int m){
    Noh* aux = primeiro;
    int cont = 0;
    while(aux != NULL){
        if(aux->dia == d and aux->mes == m){
            cont ++;
        }
        aux = aux->proximo;
    }
    return cont;
}

void Lista::inserirFim(string n,int d,int m,int a){
    Noh* novo = new Noh(n,d,m,a);
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
        Lista* EoHash;
    public:
        tabelaHash(int cap);
        ~tabelaHash();
        void inserir(string n,int d,int m,int a);
        void buscar(int d,int m);
        void proporcionar();
};

tabelaHash::tabelaHash(int cap){
    EoHash = new Lista[cap];
    capacidade = cap;
}

tabelaHash::~tabelaHash(){
    for(int i;i<capacidade;i++){
        EoHash[i].removerTudo();
    }
    delete[] EoHash;
}

void tabelaHash::inserir(string n,int d,int m,int a){
    int pos = funcaoHash(d,m,capacidade);
    EoHash[pos].inserirFim(n,d,m,a);
}

void tabelaHash::buscar(int d,int m){
    int pos = funcaoHash(d,m,capacidade);
    cout<<EoHash[pos].contar(d,m)<<" ";
}

void tabelaHash::proporcionar(){
    float cont;
    for(int i=0;i<capacidade;i++){
        if(EoHash[i].primeiro!=NULL)
            cont++;
    }
    cout<<cont/float(capacidade);
}

int main(){
    int tam,qfun,dia,mes,ano;
    cin>>tam;
    tabelaHash hablas(tam);
    string nome;
    cin>>qfun;
    for(int i=0;i<qfun;i++){
        cin>>nome>>dia>>mes>>ano;
        hablas.inserir(nome,dia,mes,ano);
    }
    cin>>dia>>mes;
    hablas.buscar(dia,mes);
    hablas.proporcionar();
    return 0;
}
