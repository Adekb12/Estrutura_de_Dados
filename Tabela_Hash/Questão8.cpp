#include <iostream>
#include <string>

using namespace std;

int funcaoHash(int c, int n) {
    return c % n;
}

struct Dados{
    int chave;
    string valor;
};

class noh {
    friend class tabelaHash;
    private:
        Dados *vetor;
    public:
        noh();
};

noh::noh(){
    vetor = new Dados[4];
}

class tabelaHash {
    private:
        noh** elementos;
        int capacidade;
    public:
        tabelaHash(int n);
        ~tabelaHash();
        void insere(int c, string v);
        void recupera(int c);
};

tabelaHash::tabelaHash(int cap) {
    elementos = new noh*[cap];
    capacidade = cap;
    cout<<"aqui";
    for (int i = 0; i < cap; i++){
        cout<<"dentro";
        for(int j=0;j<4;j++){
            cout<<"entra";
            elementos[i]->vetor[j].chave = -1;
            elementos[i]->vetor[j].valor = "";
        }
    }
}

tabelaHash::~tabelaHash() {
    for (int i = 0; i < capacidade; i++) {
        delete[] elementos[i]->vetor;
    }
    delete[] elementos;
}

void tabelaHash::insere(int c, string v) {
    int posicao = funcaoHash(c,capacidade);
    bool verifica = true;
    int cont = 0;
    while(cont<4 and verifica==true){
        if(elementos[posicao]->vetor[cont].chave == c){
            cout<<"ITEM JÁ ESTÁ NA TABELA!"<<endl;
            cont = 4;
        }
        else if(elementos[posicao]->vetor[cont].chave == -1){
            elementos[posicao]->vetor[cont].chave = c;
            elementos[posicao]->vetor[cont].valor = v;
            verifica = false;
        }
        cont++;
    }
    if(verifica){
        cout<<"NÚMERO MÁXIMO DE COLISÕES PARA CHAVE!"<<endl;
    }
}

void tabelaHash::recupera(int c) {
    int posicao = funcaoHash(c,capacidade);
    bool encontrou = true;
    int cont = 0;
    while(cont<4 and encontrou==true){
        if(elementos[posicao]->vetor[cont].chave == c){
            cout<<elementos[posicao]->vetor[cont].valor<<endl;
            encontrou = false;
        }
        cont++;
    }
    if(encontrou)
        cout<<"NÃO ENCONTRADO!"<<endl;
}

int main() {
    int tamHash,quantHash,chave;
    string valor;
    cin>>tamHash>>quantHash;
    tabelaHash taha(tamHash);
    //cout<<"aqui";
    for(int i=0;i<quantHash;i++){
        cin>>chave>>valor;
        taha.insere(chave,valor);
    }
    for(int i=0;i<4;i++){
        cin>>chave;
        taha.recupera(chave);
    }
    return 0;
}