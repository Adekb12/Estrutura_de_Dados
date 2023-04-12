#include <iostream>
#include <queue>

typedef int Dado;

enum Posicao {DIR, ESQ};

class Noh {
    friend class ABB;
    public:
        Noh (Dado d);
    private:
        Dado valor;
        Noh* esq;
        Noh* dir;
};

class ABB {
    public:
        ABB() { raiz = NULL; }
        ~ABB();
        void DestruirRecursivamente(Noh* umNoh);
        void Busca(Dado d,Noh* umNoh);
        void EscreverNivelANivel(std::ostream& saida);
        void Inserir(Dado d);
        void Sucessor(Dado d);
        void ImprimirSucessor(Noh* umNoh, Dado d);
    private:
        Noh* raiz;
        Noh* InserirRecursivamente(Noh* umNoh,Dado d);
};

using namespace std;

Noh::Noh(Dado d) {
    valor = d;
    esq = NULL;
    dir = NULL;
}

// === Classe ABB ==============================================================
ABB::~ABB(){
    DestruirRecursivamente(raiz);
}

void ABB::DestruirRecursivamente(Noh* umNoh){
    if(umNoh != NULL){
        DestruirRecursivamente(umNoh->esq);
        DestruirRecursivamente(umNoh->dir);
        delete umNoh;
    }
}

void ABB::Inserir(Dado d){
    raiz = InserirRecursivamente(raiz,d);
}

Noh* ABB::InserirRecursivamente(Noh* umNoh,Dado d){
    if(umNoh == NULL){
        Noh* novo = new Noh(d);
        return novo;
    }else{
        if(d < umNoh->valor){
            umNoh->esq = InserirRecursivamente(umNoh->esq,d);
        }else{
            umNoh->dir = InserirRecursivamente(umNoh->dir,d);
        }
    }
    return umNoh;
}

void ABB::Sucessor(Dado d) {
     Busca(d,raiz);
}

void ABB::Busca(Dado d,Noh* umNoh) {
    if(umNoh != NULL){
        Busca(d,umNoh->esq);
        ImprimirSucessor(umNoh,d);
        Busca(d,umNoh->dir);
    }
}

void ABB::ImprimirSucessor(Noh* umNoh,Dado d){
    if(umNoh->valor > d)
        cout<<umNoh->valor<<" ";
}

void ABB::EscreverNivelANivel(ostream& saida) {
    queue<Noh*> filhos;
    Noh noh = Dado();
    Noh* fimDeNivel = &noh; // noh especial para fim de nivel
    filhos.push(raiz);
    filhos.push(fimDeNivel);
    while (not filhos.empty()) {
        Noh* ptNoh = filhos.front();
        filhos.pop();
        if (ptNoh == fimDeNivel) {
            saida << "\n";
            if (not filhos.empty())
                filhos.push(fimDeNivel);
        }
        else {
            saida << '[';
            if (ptNoh != NULL) {
                saida << ptNoh->valor;
                filhos.push(ptNoh->esq);
                filhos.push(ptNoh->dir);
            }
            saida << ']';
        }
    }
}

// === Programa ================================================================
int main() {
    ABB arvore;
    Dado chave;
    char operacao;
    do {
        cin >> operacao;
        switch (operacao) {
            case 'i': // Inserir
                cin >> chave;
                arvore.Inserir(chave);
                break;
            case 'e': // Escrever
                arvore.EscreverNivelANivel(cout);
                break;
            case 's': { // Sucessor
                cin >> chave;
                arvore.Sucessor(chave);
                cout << endl;
                break;
            }
        }
    } while (operacao != 'f');
    return 0;
}