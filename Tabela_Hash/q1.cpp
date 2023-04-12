#include <iostream>
#include <exception>

using namespace std;

struct dado {
    int chave,valor;
};

bool operator==(const dado& d1, const dado& d2) {
    return (d1.chave == d2.chave and d1.valor == d2.valor);
}

bool operator!=(const dado& d1, const dado& d2) {
    return (d1.chave != d2.chave or d1.valor != d2.valor);
}

class taHashbela {
    private:
        unsigned posicao(const int& chave);
        int buscarChave(const int& chave);
        dado* vetDados;
        unsigned capacidade;
        unsigned tamanho;
    public:
        taHashbela(unsigned cap = 101);
        ~taHashbela();
        void imprimir();
        void inserir(const int& chave);
        void remover(const int& chave);
        int consultar(const int& chave);
};


taHashbela::taHashbela(unsigned cap) {
    capacidade = cap;
    vetDados = new dado[capacidade];
    tamanho = 0;
    for(unsigned i=0;i<capacidade;i++){
        vetDados[i].valor = -1;
    }
}

taHashbela::~taHashbela() {
    delete[] vetDados;
}

unsigned taHashbela::posicao(const int& chave) {
    return chave % 101;
}

int taHashbela::buscarChave(const int& chave) {
    int pos = posicao(chave);
    int posiFinal = pos;
    dado viciado;
    do{
        viciado = vetDados[pos];
        if(viciado.valor == -1 or viciado.valor == -2)
            return -1;
        if(viciado.chave == chave)
            return pos;
        pos = (pos + 1) % capacidade;
    }while(pos != posiFinal);
    return -1;
}

void taHashbela::inserir(const int& chave) {
    if(buscarChave(chave) == -1){
        int pos = posicao(chave);
        while((vetDados[pos].valor != -1) and (vetDados[pos].valor != -2)){
            pos = (pos + 1) % capacidade;
        } 
        vetDados[pos].chave = chave;
        vetDados[pos].valor = 1;
        tamanho++;
    }
}

void taHashbela::imprimir() {
    for(int i=0;i<101;i++){
        if(vetDados[i].valor == 1)
            cout<<vetDados[i].chave<<" ";
    }
    cout<<endl;
}

void taHashbela::remover(const int& chave) {
    int pos = buscarChave(chave);
    if(pos != -1){
        vetDados[pos].valor = -2;
        tamanho--;
    }
}

int taHashbela::consultar(const int& chave) {
    int pos = posicao(chave);
    if(vetDados[pos].valor == -1 or vetDados[pos].valor == -2)
        return -1;
    return 1;
}

int main() {
    taHashbela verdade;
    int chave;
    for(int i=0;i<10;i++){
        cin >> chave;
        verdade.inserir(chave);
    }
    for(int i=0;i<3;i++){
        cin >> chave;
        verdade.remover(chave);
    }
    for(int i=0;i<2;i++){
        cin >> chave;
        cout<<verdade.consultar(chave)<<endl;
    }
    verdade.imprimir();
    for(int i=0;i<3;i++){
        cin >> chave;
        verdade.inserir(chave);
    }
    verdade.imprimir();
    return 0;
}
