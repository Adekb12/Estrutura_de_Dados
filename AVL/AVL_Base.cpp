#include <iostream>
using namespace std;

class Noh{
    friend class AVL;
    private:
        int dado;
        int altura;
        Noh* esquerdo;
        Noh* direito;
    public:
        Noh(int d);
};

Noh::Noh(int d){
    dado = d;
    esquerdo = NULL;
    direito = NULL;
    altura = 0;
}

class AVL{
    private:
        Noh* raiz;
        Noh* inserirRecursivamente(Noh* umNoh,int umValor);
        Noh* maximarAux(Noh* raizSubArvore);
        Noh* minimarAux(Noh* raizSubArvore);
        Noh* buscarAux(int v);
        void percorrerEmOrdemAux(Noh* umNoh);
        void percorrerPreOrdemAux(Noh* umNoh);
        void percorrerPosOrdemAux(Noh* umNoh);
        Noh* removerRecAux(Noh* umNoh,int umValor);
        Noh* removerMenor(Noh* raizSub);
    public:
        AVL();
        ~AVL();
        void destruirRecursivamente(Noh* r);
        void inserir(int v);
        int minimar();
        int maximar();
        void buscar(int v);
        void imprimir(Noh* valor);
        void percorrerEmOrdem();
        void percorrerPreOrdem();
        void percorrerPosOrdem();
        void removerRecursivamente(int v);
        int informarAltura(Noh* umNoh);
        void atualizarAltura(Noh* umNoh);
        int maximor(int altEsq,int altDir);
        int fatorBalancemanto(Noh* umNoh);
        Noh* rotacionarEsquerda(Noh* umNoh);
        Noh* rotacionarDireita(Noh* umNoh);
        Noh* rotacionarEsquerdaDireita(Noh* umNoh);
        Noh* rotacionarDireitaEsquerda(Noh* umNoh);
        Noh* arrumarBalanceamento(Noh* umNoh);
};

AVL::AVL(){
    raiz = NULL;
}

AVL::~AVL(){
    destruirRecursivamente(raiz);
}

void AVL::destruirRecursivamente(Noh* umNoh){
    if(umNoh != NULL){
        destruirRecursivamente(umNoh->esquerdo);
        destruirRecursivamente(umNoh->direito);
        delete umNoh;
    }
}

void AVL::inserir(int umValor){
    raiz = inserirRecursivamente(raiz,umValor);
}

Noh* AVL::inserirRecursivamente(Noh* umNoh,int umValor){
    if(umNoh == NULL){
        Noh* novo = new Noh(umValor);
        return novo;
    }else{
        if(umValor < umNoh->dado){
            umNoh->esquerdo = inserirRecursivamente(umNoh->esquerdo,umValor);
        }else{
            umNoh->direito = inserirRecursivamente(umNoh->direito,umValor);
        }
    }
    return arrumarBalanceamento(umNoh);
}

int AVL::minimar(){
    if(raiz == NULL){
        cerr<<"Árvore vazia"<<endl;
        exit(EXIT_FAILURE);
    }else{
        Noh* minimo = minimarAux(raiz);
        return minimo->dado;
    }
}

Noh* AVL::minimarAux(Noh* raizSubArvore){
    while(raizSubArvore->esquerdo != NULL){
        raizSubArvore = raizSubArvore->esquerdo;
    }
    return raizSubArvore;
}

int AVL::maximar(){
    if(raiz == NULL){
        cerr<<"Árvore vazia"<<endl;
        exit(EXIT_FAILURE);
    }else{
        Noh* maximo = maximarAux(raiz);
        return maximo->dado;
    }
}

Noh* AVL::maximarAux(Noh* raizSubArvore){
    while(raizSubArvore->direito != NULL){
        raizSubArvore = raizSubArvore->direito;
    }
    return raizSubArvore;
}

void AVL::buscar(int umValor){
    Noh* valor = buscarAux(umValor);
    if(valor == NULL){
        cerr<<"Nó não encontrado"<<endl;
        exit(EXIT_FAILURE);
    }else{
        imprimir(valor);
    }
}

Noh* AVL::buscarAux(int umValor){
    Noh* atual = raiz;
    while(atual!=NULL){
        if(atual->dado == umValor)
            return atual;
        else if(atual->dado > umValor)
            atual = atual->esquerdo;
        else 
            atual = atual->direito;
    }
    return atual;
}

void AVL::imprimir(Noh* valor){
    cout<<valor->dado<<" ";
}

void AVL::percorrerEmOrdem(){
    percorrerEmOrdemAux(raiz);
}

void AVL::percorrerEmOrdemAux(Noh* umNoh){
    if(umNoh != NULL){
        percorrerEmOrdemAux(umNoh->esquerdo);
        imprimir(umNoh);
        percorrerEmOrdemAux(umNoh->direito);
    }
}

void AVL::percorrerPreOrdem(){
    percorrerPreOrdemAux(raiz);
}

void AVL::percorrerPreOrdemAux(Noh* umNoh){
    if(umNoh != NULL){
        imprimir(umNoh);
        percorrerPreOrdemAux(umNoh->esquerdo);
        percorrerPreOrdemAux(umNoh->direito);
    }
}

void AVL::percorrerPosOrdem(){
    percorrerPosOrdemAux(raiz);
}

void AVL::percorrerPosOrdemAux(Noh* umNoh){
    if(umNoh != NULL){
        percorrerPosOrdemAux(umNoh->esquerdo);
        percorrerPosOrdemAux(umNoh->direito);
        imprimir(umNoh);
    }
}

void AVL::removerRecursivamente(int umValor){
    raiz = removerRecAux(raiz,umValor);
}

Noh* AVL::removerRecAux(Noh* umNoh,int umValor){
    if(umNoh == NULL){
        cerr<<"Nó não encontrado"<<endl;
        exit(EXIT_FAILURE);
    }
    Noh* novaRaizSubArvore = umNoh;
    if (umValor < umNoh->dado) {
        umNoh->esquerdo = removerRecAux(umNoh->esquerdo, umValor);
    } else if (umValor > umNoh->dado) {
        umNoh->direito = removerRecAux(umNoh->direito, umValor);
    } else { 
        if (umNoh->esquerdo == NULL) 
            novaRaizSubArvore = umNoh->direito;
        else if (umNoh->direito == NULL) \
            novaRaizSubArvore = umNoh->esquerdo;
        else {
            novaRaizSubArvore = minimarAux(umNoh->direito);
            novaRaizSubArvore->direito = removerMenor(umNoh->direito);  
            novaRaizSubArvore->esquerdo = umNoh->esquerdo;
        }
        delete umNoh;
    } 
    return arrumarBalanceamento(novaRaizSubArvore);
}

Noh* AVL::removerMenor(Noh* raizSub){
    if(raizSub->esquerdo == NULL)
        return raizSub->direito;
    else { 
        raizSub->esquerdo = removerMenor(raizSub->esquerdo);
        return arrumarBalanceamento(raizSub);
    }
}

int AVL::informarAltura(Noh* umNoh){
    if(umNoh == NULL)
        return 0;
    else   
        return umNoh->altura;
}

void AVL::atualizarAltura(Noh* umNoh){
    int altEsq = informarAltura(umNoh->esquerdo);
    int altDir = informarAltura(umNoh->direito);
    umNoh->altura = 1 + maximor(altEsq,altDir);
}

int AVL::maximor(int altEsq,int altDir){
    if(altEsq > altDir)
        return altEsq;
    else   
        return altDir;
}

int AVL::fatorBalancemanto(Noh* umNoh){
    int altEsq = informarAltura(umNoh->esquerdo);
    int altDir = informarAltura(umNoh->direito);
    int fatorBal = altEsq - altDir;
    return fatorBal;
}

Noh* AVL::rotacionarEsquerda(Noh* umNoh){
    Noh* nohAux = umNoh->direito;
    umNoh->direito = nohAux->esquerdo;
    nohAux->esquerdo = umNoh;
    atualizarAltura(umNoh);
    atualizarAltura(nohAux);
    return nohAux;
}

Noh* AVL::rotacionarDireita(Noh* umNoh){
    Noh* nohAux = umNoh->esquerdo;
    umNoh->esquerdo = nohAux->direito;
    nohAux->direito = umNoh;
    atualizarAltura(umNoh);
    atualizarAltura(nohAux);
    return nohAux;
}

Noh* AVL::rotacionarEsquerdaDireita(Noh* umNoh){
    umNoh->esquerdo = rotacionarEsquerda(umNoh->esquerdo);
    return rotacionarDireita(umNoh);
}

Noh* AVL::rotacionarDireitaEsquerda(Noh* umNoh){
    umNoh->direito = rotacionarDireita(umNoh->direito);
    return rotacionarEsquerda(umNoh);
}

Noh* AVL::arrumarBalanceamento(Noh* umNoh){
    if(umNoh == NULL)
        return umNoh;
    atualizarAltura(umNoh);
    int fatorBal = fatorBalancemanto(umNoh);
    if((fatorBal >= -1) and (fatorBal <= 1))
        return umNoh;
    if((fatorBal > 1) and (fatorBalancemanto(umNoh->esquerdo) >= 0))
        return rotacionarDireita(umNoh);
    if((fatorBal > 1) and (fatorBalancemanto(umNoh->esquerdo)) < 0){
        umNoh->esquerdo = rotacionarEsquerda(umNoh->esquerdo);
        return rotacionarDireita(umNoh);
    }
    if((fatorBal < -1) and (fatorBalancemanto(umNoh->direito) <= 0))
        return rotacionarEsquerda(umNoh);
    if((fatorBal < -1) and (fatorBalancemanto(umNoh->direito)) > 0){
        umNoh->direito = rotacionarDireita(umNoh->direito);
        return rotacionarEsquerda(umNoh);
    }
}

int main(){
    AVL arvore;
    int valor;
    char opcao;
    cin>>opcao;
    while(opcao!='f'){
        switch (opcao)
        {
        case 'i':
            cin>>valor;
            arvore.inserir(valor);
            break;
        case 'r':
            cin>>valor;
            arvore.removerRecursivamente(valor);
            break;
        case 'b':
            cin>>valor;
            arvore.buscar(valor);
            cout<<endl;
            break;
        case 'M':
            cout<<arvore.maximar()<<endl;
            break;
        case 'm':
            cout<<arvore.minimar()<<endl;
            break;
        case 'p':
            arvore.percorrerPreOrdem();
            cout<<endl;
            arvore.percorrerEmOrdem();
            cout<<endl;
            arvore.percorrerPosOrdem();
            cout<<endl;
            break;
        default:
            break;
        }
        cin>>opcao;
    }
    return 0;
}
