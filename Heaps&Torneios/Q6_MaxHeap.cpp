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
        inline int direito(int i);
        void arruma();
        void corrigeDescendo(int i);
    public:
        MaxHeap(dado vet[], int tam);
        ~MaxHeap();
        void imprime();
};

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
        cout<<i<<": ";
        imprime();
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

void MaxHeap::imprime(){
    for(int i=0; i<tamanho; i++){
        cout<<heap[i]<<" ";
    }
    cout<<endl;
}

int main(){
	int tam;
	cin>>tam;
	dado vetor[tam];
	for(int i=0;i<tam;i++){
		cin>>vetor[i];
	}
	MaxHeap* hype = new MaxHeap(vetor,tam);
	delete hype;
}
