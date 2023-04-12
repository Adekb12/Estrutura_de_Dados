#include <iostream>   
#include <cstdlib>

typedef unsigned TCodProcesso;
struct Processos{
	TCodProcesso cod;
	int priori;
};

class Heap {
    // classe Heap (max-heap, o maior fica na raiz/inicio)
    public:
        // Criar heap sem dados e com capacidade informada
        Heap(int cap);
        // Destruttor
        ~Heap();
        // Inserir um dado na heap
        bool Inserir(TCodProcesso codigo, int prioridade);
        // Retira e retorna a raiz
        bool Retirar(TCodProcesso* ptCodigo, int* ptPrioridade);
        // Verifica se a heap está vazia
        bool Vazia();
    private:
        void ArrumarDescendo(int i);
        void ArrumarSubindo(int i);
        inline int Direito(int i);
        inline int Esquerdo(int i);
        inline int Pai(int i);
        Processos* heap;
        int capacidade;
        int tamanho;
};

using namespace std;

Heap::Heap(int cap) {
	capacidade = cap;
    heap = new Processos[cap];
    tamanho = 0;
}

Heap::~Heap() {
	delete[]heap;
}

void Heap::ArrumarDescendo(int i) {
    int esq = Esquerdo(i);
    int dir = Direito(i);
    int maior = i;
    if((esq < tamanho) and (heap[esq].priori > heap[maior].priori)){
        maior = esq;
    }
    if((dir < tamanho) and (heap[dir].priori > heap[maior].priori)){
        maior = dir;
    }

    if(maior!=i){
        swap(heap[i], heap[maior]);
        ArrumarDescendo(maior);
    }
}

void Heap::ArrumarSubindo(int i) {
    int p = Pai(i);
    if(heap[i].priori > heap[p].priori){
        swap(heap[i], heap[p]);
        ArrumarSubindo(p);
    }
}

int Heap::Pai(int i) {
	return (i-1)/2;
}

int Heap::Esquerdo(int i) {
	return 2*i + 1;
}

int Heap::Direito(int i) {
	return 2*i + 2;
}

bool Heap::Retirar(TCodProcesso* ptCodigo, int* ptPrioridade) {
	if(Vazia())
		return false;
	else{
		Processos Aux = heap[0];
		swap(heap[0], heap[tamanho-1]);
		tamanho--;
		ArrumarDescendo(0);
		*ptCodigo = Aux.cod;
		*ptPrioridade = Aux.priori;
		return true;
	}
	// Retira um codigo/prioridade, retornando os dois valores.
    // Retorna falso se o heap estiver vazio.
}

bool Heap::Vazia() {
    if(tamanho == 0)
		return true;
	else
		return false;
}

bool Heap::Inserir(TCodProcesso codigo, int prioridade) {
	if(tamanho == capacidade)
		return false;
	else{	
		Processos urgente;
		urgente.cod = codigo;
		urgente.priori = prioridade;
		heap[tamanho] = urgente;
		ArrumarSubindo(tamanho);
		tamanho++;
		return true;
	}
	// Insere um codigo/prioridade no heap.
    // Retorna falso se o heap estiver cheio.
}

int main() {
    unsigned capacidade;
    cin >> capacidade;
    Heap heap(capacidade);
    char comando;
    TCodProcesso codigo;
    int prioridade;
    do {
        cin >> comando;
        switch (comando) {
            case 'i': // inserir um processo no heap
                cin >> codigo >> prioridade;
                heap.Inserir(codigo, prioridade);
                break;
            case 'o': // obter um processo do heap
                if (heap.Retirar(&codigo, &prioridade))
                    cout << codigo << ' ' << prioridade << endl;
                else
                    cout << "Nao encontrado" << endl;
                break;
            case 's': //sair
                break;
        }
    } while (comando != 's');
    return 0;
}
