#include <iostream>
using namespace std;

int funcaoHash(int k, int n) {
    return k % n;
}

struct ChaLor{
    int chave;
    string valor;
};

class Noh{
    friend class tabelaHash;
    private:
        ChaLor vetor[4];
        int tam;
        Noh* proximo;
    public:
        Noh();
};

Noh::Noh(){
    for(int i=0;i<4;i++){
        vetor[i].chave = -1;
        vetor[i].valor = "";
    }
    tam = 0;
    proximo = NULL;
}

class tabelaHash{
    private:
        int capacidade;
        Noh* tabeHa;
    public:
        tabelaHash(int cap);
        ~tabelaHash();
        void inserir(int c,string v);
        void recuperar(int c);
        void imprimir();
};

tabelaHash::tabelaHash(int cap){
    tabeHa = new Noh[cap];
    capacidade = cap;
}

tabelaHash::~tabelaHash(){
    delete[] tabeHa;
}

void tabelaHash::inserir(int c,string v){
    int pos = funcaoHash(c,capacidade);
    int cont = 0;
    int t = tabeHa[pos].tam;
    while(cont<4){
        if(tabeHa[pos].vetor[cont].chave == c){
            cout<<"ITEM JÁ ESTÁ NA TABELA!"<<endl;
            cont = 4;
        }
        else if(t < 4){
            tabeHa[pos].vetor[t].chave = c;
            tabeHa[pos].vetor[t].valor = v;
            tabeHa[pos].tam += 1;
            cont = 4;
        }
        cont++;
    }
    if(t==4 and cont!=5)
        cout<<"NÚMERO MÁXIMO DE COLISÕES PARA CHAVE!"<<endl;
}

void tabelaHash::recuperar(int c){
    int pos = funcaoHash(c,capacidade);
    bool encontrou = false;
    int cont = 0;
    while(cont<4 and not encontrou){
        if(tabeHa[pos].vetor[cont].chave == c){
            cout<<tabeHa[pos].vetor[cont].valor<<endl;
            encontrou = true;
        }
        cont++;
    }
    if(!encontrou)
        cout<<"NÃO ENCONTRADO!"<<endl;
}

void tabelaHash::imprimir(){
    for(int i=0;i<capacidade;i++){
        cout<<i<<":";
        for(int j=0;j<4;j++){
            cout<<"["<<tabeHa[i].vetor[j].chave<<"/"<<tabeHa[i].vetor[j].valor<<"]";
        }
        cout<<endl;
    }
}

int main(){
    int n,quantidade,chave;
    cin>>n;
    tabelaHash tata(n);
    cin>>quantidade;
    string valor;
    for(int i=0;i<quantidade;i++){
        cin>>chave>>valor;
        tata.inserir(chave,valor);
    }
    for(int i=0;i<4;i++){
        cin>>chave;
        tata.recuperar(chave);
    }
    tata.imprimir();
    return 0;
}
