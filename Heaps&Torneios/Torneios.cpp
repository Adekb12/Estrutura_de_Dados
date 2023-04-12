#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;

typedef int dado;
const int INVALIDO = -1;

class torneio{
    private:
        dado* heap;
        int capacidade;
        int tamanho;
        int inicioDados;
        inline int pai(int i);
        inline int esquerdo(int i);
        inline direito(int i);
        void arruma();
        void copiaMaior(int i);
        void copiaSubindo(int i);
    public:
        torneio(dado vet[],int tam);
        torneio(int numFolhas);
        ~torneio();
        void imprime();
        dado retiraRaiz();
        void insere(dado d);
};
torneio::torneio(int numFolhas){
    capacidade = 1;
    while(capacidade < numFolhas){
        capacidade *= 2;
    }
    capacidade = capacidade -1 + numFolhas;
    heap = new dado[capacidade];
    inicioDados = capacidade - numFolhas;
    
    for(int i=0;i<capacidade;i++)heap[i] = INVALIDO;
}
torneio::torneio (dado vet[], int tam){
    capacidade = 1;
    while(capacidade < tam){
        capacidade *= 2;
    }
    capacidade = capacidade -1 + tam;
    heap = new dado[capacidade];
    inicioDados = capacidade - tam;
    
    memcpy(&heap[inicioDados],vet,tam*sizeof(dado));
    
    tamanho = tam;
    arruma();
}

torneio::~torneio(){
    delete[] heap;
}

void torneio::arruma(){
    for(int i=(inicioDados-1); i>=0; i--){
        copiaMaior(i);
    }
}

int torneio::pai(int i){
    return (i-1)/2;
}

int torneio::esquerdo(int i){
    return 2*i+1;
}
int torneio::direito(int i){
    return 2*i+2;
}

void torneio::copiaMaior(int i){
    int esq = esquerdo(i);
    int dir = direito(i);
    int maior = INVALIDO;
    if(esq < capacidade){
		if((dir < capacidade) and (heap[dir] > heap[esq])){
			maior = dir;
		}else{
			maior = esq;
		}
		heap[i] = heap[maior];
    }else{
		heap[i] = INVALIDO;
	}
}

void torneio::copiaSubindo(int i){
    int p = pai(i);
    if(heap[i] > heap[p]){
        heap[p] = heap[i];
        copiaSubindo(p);
    }
}

void torneio::imprime(){
    for(int i=0; i<tamanho; i++){
        cout<<heap[i]<<" ";
    }
    cout<<endl;
}

dado torneio::retiraRaiz(){
    if(tamanho == 0){
        cerr<<"Erro ao retirar"<<endl;
    }
    dado aux = heap[0];
    tamanho--;
    copiaMaior(0);
    return aux;
}

void torneio ::insere(dado d){
    if(tamanho == capacidade){
        cerr<<"Erro ao inserir"<<endl;
        exit(EXIT_FAILURE);
	}
    heap[tamanho+inicioDados] = d;
    copiaSubindo(tamanho+inicioDados);
    tamanho++;
}

int main(){

	return 0;
}
