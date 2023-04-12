#include <iostream>
#include <utility> // para usar swap
#include <stdexcept> // para usar exceção com runtime_error

using namespace std;

struct dado {
    int prioridade;
    int valor;
};

bool operator>(dado d1, dado d2) {
    return d1.prioridade > d2.prioridade;
}

bool operator<(dado d1, dado d2) {
    return d1.prioridade < d2.prioridade;
}

ostream& operator<<(ostream& output,const dado& d) {
    output << "[" << d.valor << "/" << d.prioridade << "]"; 
    return output;
}

class MaxHeap {
private:
    dado* heap;
    int capacidade;
    int tamanho;
    inline int pai(int i);
    inline int esquerdo(int i);
    inline int direito(int i); 
    void corrigeDescendo(int i); 
    void corrigeSubindo(int i);
public:
    MaxHeap(int cap);
    ~MaxHeap();
    void imprime();
    dado retiraRaiz();
    void insere(dado d);
    void alteraPrioridade(int umValor, int novaPrioridade);
};

MaxHeap::MaxHeap(int cap) {
	capacidade = cap;
	heap = new dado[capacidade];
	tamanho = 0;
}

MaxHeap::~MaxHeap() {
	delete[]heap;
}

int MaxHeap::pai(int i) {
	return (i-1)/2;
}
    
int MaxHeap::esquerdo(int i) {
	return (2*i) +1;
}
    
int MaxHeap::direito(int i) {
	return (2*i) +2;
}
    
void MaxHeap::corrigeDescendo(int i) {
	int left = esquerdo(i);
	int right = direito(i);
	int maior = i;
	if((left<tamanho) and (heap[left] > heap[maior]))
		maior = left;
	if((right<tamanho) and (heap[right] > heap[maior]))
		maior = right;
	if(maior != i){
		swap(heap[i],heap[maior]);
		corrigeDescendo(maior);
	}
}

void MaxHeap::corrigeSubindo(int i) {
	int father = pai(i);
	if(heap[i] > heap[father]){
		swap(heap[i],heap[father]);
		corrigeSubindo(father);
	}
}
        
void MaxHeap::imprime() {
	for(int i=0;i<tamanho;i++){
		//cout<<"["<<heap[i].valor<<"/"<<heap[i].prioridade<<"] ";
		cout << heap[i] << " ";
	}
}

dado MaxHeap::retiraRaiz() {
	dado Aux = heap[0];
	swap(heap[0],heap[tamanho-1]);
	tamanho--;
	corrigeDescendo(0);
	return Aux;
	
}


void MaxHeap::insere(dado d){
	if(tamanho!=capacidade){
		heap[tamanho] = d;
		corrigeSubindo(tamanho);
		tamanho++;
	}
}

void MaxHeap::alteraPrioridade(int umValor, int novaPrioridade) {
    int priori,tam,pos[tamanho];
    tam = 0;
	for(int i=0;i<tamanho;i++){
		if(umValor == heap[i].valor){
			pos[tam] = i;
			tam++;
		}
	}
	for(int i=0;i<tam;i++){
		
		priori = heap[pos[i]].prioridade;
		heap[pos[i]].prioridade = novaPrioridade;
		if(novaPrioridade > priori)
			corrigeSubindo(pos[i]);
		else
			corrigeDescendo(pos[i]);
	}
}

int main () {
    int capacidade;
    cin >> capacidade;
    MaxHeap meuHeap(capacidade);
   
    char opcao;
    cin >> opcao;
    
    dado umDado;
    int valor, novaPrioridade;

    while (opcao != 'Q') {
        switch(opcao) {
            case 'I':
                cin >> umDado.valor;
                cin >> umDado.prioridade;
                meuHeap.insere(umDado);
                break;
            case 'R':
                cout << meuHeap.retiraRaiz().valor << endl;
                break;
            case 'A':
                cin >> valor >> novaPrioridade;
                meuHeap.alteraPrioridade(valor,novaPrioridade); 
                break;               
            case 'P':
                meuHeap.imprime();
                break;
            default:
                cout << "Opção inválida!" << endl;
        }
        cin >> opcao;
    }
    
    return 0;
}
