#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;

const int INVALIDO = -1;
struct Valores{
	int base;
	int progresso;
};
class torneio{
    private:
        Valores* heap;
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
        torneio(Valores vet[],int tam);
        torneio(int numFolhas);
        ~torneio();
        void imprime();
        Valores retiraRaiz();
        void insere(Valores d);
};

torneio::torneio (Valores vet[], int tam){
    capacidade = 1;
    while(capacidade < tam){
        capacidade *= 2;
    }
    capacidade = capacidade -1 + tam;
    heap = new Valores[capacidade];
    inicioDados = capacidade - tam;
    
    memcpy(&heap[inicioDados],vet,tam*sizeof(Valores));
    
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
		if((dir < capacidade) and (heap[dir].progresso > heap[esq].progresso)){
			maior = dir;
		}else if((dir < capacidade) and (heap[dir].progresso == heap[esq].progresso)){
			if(heap[dir].base > heap[esq].base)
				maior = dir;
			else
				maior = esq;
		}else{
			maior = esq;
		}
		if(maior == dir)
			heap[i].progresso = heap[maior].progresso-heap[esq].progresso;
		else
			heap[i].progresso = heap[maior].progresso-heap[dir].progresso;
    }else{
		heap[i].base = INVALIDO;
		heap[i].progresso = INVALIDO;
	}
}

/*void torneio::copiaSubindo(int i){
    int p = pai(i);
    if(heap[i] > heap[p]){
        heap[p] = heap[i];
        copiaSubindo(p);
    }
}*/

void torneio::imprime(){
    for(int i=0; i<tamanho; i++){
        cout<<heap[i].base<<" ";
    }
    cout<<endl;
}

Valores torneio::retiraRaiz(){
    if(tamanho == 0){
        cerr<<"Erro ao retirar"<<endl;
    }
    Valores aux = heap[0];
    tamanho--;
    copiaMaior(0);
    return aux;
}

/*void torneio ::insere(Valores d){
    if(tamanho == capacidade){
        cerr<<"Erro ao inserir"<<endl;
        exit(EXIT_FAILURE);
	}
    heap[tamanho+inicioDados] = d;
    copiaSubindo(tamanho+inicioDados);
    tamanho++;
}*/

int main(){
	int quantidade;
	cin>>quantidade;
	Valores vet[quantidade];
	for(int i=0;i<quantidade;i++){
		cin>>vet[i].base;
		vet[i].progresso = vet[i].base;
	}
	torneio *spring = new torneio(vet,quantidade);
	spring->imprime();
	cout<<spring->retiraRaiz().base;
	delete spring;
	return 0;
}
