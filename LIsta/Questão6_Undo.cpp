#include <iostream>
using namespace std;

class noh{
    friend class deque;
    private:
        string comando;
        noh* proximo;
    public:
        noh(string cmd);
};

noh::noh(string cmd){
    comando = cmd;
}

class deque {
private:
   noh* esquerda;
   noh* direita;
   int tamanho;
   int maximo;
public:
   deque(int m);
   ~deque();
   void insereNaDireita(string cmd);
   string retiraEsquerda();
   void retiraDireita();
   inline bool vazia();
};

deque::deque(int m){
    esquerda = NULL;
    direita = NULL;
    tamanho = 0;
    maximo = m;
}

deque::~deque(){
    noh* aux = esquerda;
    noh* temp;
    while(aux != NULL){
        temp = aux;
        aux = aux->proximo;
        delete temp;
    }
    tamanho = 0;
    esquerda = NULL;
    direita = NULL;
}

void deque::insereNaDireita(string cmd){
    noh* novo = new noh(cmd);
    if(vazia()){
        esquerda = novo;
        direita = novo;
    }else{
        if(tamanho == maximo){
            cout<<"esqueci: "<<retiraEsquerda()<<endl;
        }
        direita->proximo = novo;
        direita = novo;
    }
    tamanho++;
}

string deque::retiraEsquerda(){
    noh* removido = esquerda;
    string comando;
    comando = removido->comando;
    esquerda = esquerda->proximo;
    delete removido;
    tamanho--;
    if(vazia()) direita = NULL;
    return comando;
}

void deque::retiraDireita(){
    cout<<"aqui"<<endl;
    if(vazia()){
        cout<<"ERRO"<<endl;
    }else{
        noh* aux = esquerda;
        noh* anterior;
        while(aux->proximo != NULL){
            anterior = aux;
            aux = aux->proximo;
        }
        string comando;
        comando = direita->comando;
        delete direita;
        anterior->proximo = NULL;
        direita = anterior;
        tamanho--;
        if(tamanho == 0) esquerda = NULL;
        cout<<"desfazer: "<<comando<<endl;
    }
    
}

inline bool deque::vazia(){
    return (esquerda == NULL);
}

int main(){
    int max;
    cin>>max;
    deque Undo(max);
    string comandos,undo;
    cin.clear();
    getline(cin,comandos);
    while(comandos != "sair"){
        if(comandos == "undo"){
            Undo.retiraDireita();
        }else
            Undo.insereNaDireita(comandos);
        getline(cin,comandos);
    }
    return 0;
}