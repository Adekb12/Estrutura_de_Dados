#include <iostream>
#include <cstdlib>
using namespace std;

typedef int dado;

class MaxHeap{
    private:
        dado* heap;
        int capacidade;
        int tamanho;
        inline int pai(int i);
        inline int esquerdo(int i);
        inline direito(int i);
        void arruma();
        void corrigeDescendo(int i);
        void corrigeSubindo(int i);
    public:
        MaxHeap(int cap);
        MaxHeap(dado vet[], int tam);
        ~MaxHeap();
        void imprime();
        dado espiaRaiz();
        dado retiraRaiz();
        void insere(dado d);
};

MaxHeap::MaxHeap(int cap){
    capacidade = cap;
    heap = new dado[cap];
    tamanho = 0;
}

MaxHeap::MaxHeap(dado vet[], int tam){
    capacidade = tam;
    heap = new dado[capacidade];
    for(int i=0; i<tam; i++){
        heap[i] = vet[i];
    }
    tamanho = tam;
    arruma();
}

MaxHeap::~MaxHeap(){
    delete[] heap;
}

void MaxHeap::arruma(){
    for(int i=(tamanho/2-1); i>=0; i--){
        corrigeDescendo(i);
    }
}

int MaxHeap::pai(int i){
    return (i-1)/2;
}

int MaxHeap::esquerdo(int i){
    return 2*i+1;
}
int MaxHeap::direito(int i){
    return 2*i+2;
}

void MaxHeap::corrigeDescendo(int i){
    int esq = esquerdo(i);
    int dir = direito(i);
    int maior = i;
    if((esq < tamanho) and (heap[esq] > heap[maior])){
        maior = esq;
    }
    if((dir < tamanho) and (heap[dir] > heap[maior])){
        maior = dir;
    }

    if(maior!=i){
        swap(heap[i], heap[maior]);
        corrigeDescendo(maior);
    }
}

void MaxHeap::corrigeSubindo(int i){
    int p = pai(i);
    if(heap[i] > heap[p]){
        swap(heap[i], heap[p]);
        corrigeSubindo(p);
    }
}

void MaxHeap::imprime(){
    for(int i=0; i<tamanho; i++){
        cout<<heap[i]<<" ";
    }
    cout<<endl;
}

dado MaxHeap::espiaRaiz(){
    return heap[0];
}

dado MaxHeap::retiraRaiz(){
    if(tamanho == 0){
        cerr<<"Erro ao retirar"<<endl;
    }
    dado aux = heap[0];
    swap(heap[0], heap[tamanho-1]);
    tamanho--;
    corrigeDescendo(0);
    return aux;
}

void MaxHeap::insere(dado d){
    if(tamanho == capacidade)
        cerr<<"Erro ao inserir"<<endl;
    heap[tamanho] = d;
    corrigeSubindo(tamanho);
    tamanho++;
}
