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
        void corrigeSubindo(int i);
    public:
        MaxHeap(int vet[]);
        ~MaxHeap();
        void imprime();
        int espiaRaiz();
        int retiraRaiz();
        void insere(int d);
        void heapsort();
};

MaxHeap::MaxHeap(int vet[]){
    capacidade = 20;
    heap = new int[capacidade];
    for(int i=0; i<15; i++){
        heap[i] = vet[i];
    }
    tamanho = 15;
    arruma();
}

MaxHeap::~MaxHeap(){
    delete[] heap;
}

void MaxHeap::arruma(){
    for(int i=(tamanho/2-1); i>=0; i--){
        corrigeDescendo(i);
    }
    imprime();
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

int MaxHeap::espiaRaiz(){
    return heap[0];
}

int MaxHeap::retiraRaiz(){
    int aux = heap[0];
    swap(heap[0], heap[tamanho-1]);
    tamanho--;
    corrigeDescendo(0);
	return aux;
  
}

void MaxHeap::insere(int d){
    if(tamanho != capacidade){
		heap[tamanho] = d;
		corrigeSubindo(tamanho);
		tamanho++;
	}
}

void MaxHeap::heapsort(){
	int tam = tamanho;
	while(tamanho > 0){
		retiraRaiz();
	}
	//tamanho = tam;
	for(int i=(tam-1); i>=0; i--){
        cout<<heap[i]<<" ";
    }
    cout<<endl;
}

int main(){
	int vet[15],elemento;
	for(int i=0;i<15;i++)cin>>vet[i];
	MaxHeap* hype = new MaxHeap(vet);
	for(int i=0;i<5;i++){
		cin>>elemento;
		hype->insere(elemento);
	}
	hype->imprime();
	hype->heapsort();
	delete hype;
	return 0;
}
