#include <iostream>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <stdexcept>
using namespace std;

class Aluno{
	friend class Heap;
	private:
		int matricula;
		string nome;
		int numeroatividades;
		int somanota;
		int tentativas;
	public:
		Aluno();
		Aluno(int mat,string n,int sn, int st);
};

Aluno::Aluno(){
	matricula = 0;
	nome = "";
	numeroatividades = 0;
	somanota = 0;
}

Aluno::Aluno(int mat,string n,int sn,int st){
	matricula = mat;
	nome = n;
	somanota = sn;
	tentativas = st;
}

class Heap {
    // classe Heap (max-heap, o maior fica na raiz/inicio)
    public:
        // Criar heap sem dados e com capacidade informada
        Heap(int cap);
        // Destruttor
        ~Heap();
        // Inserir um dado na heap
        void Inserir(Aluno& d);
        // Retira e retorna a raiz
        Aluno Retirar();
        // Verifica se a heap está vazia
        bool Vazia();
        // Mostra o aluno destaque
        void alunoDestaque();
    protected:
        void ArrumarDescendo(int i);
        void ArrumarSubindo(int i);
        inline int Direito(int i);
        inline int Esquerdo(int i);
        inline int Pai(int i);
        int mCapacidade;
        int mTamanho;
        Aluno* dados;
};

Heap::Heap(int cap){
	mCapacidade = cap;
	dados = new Aluno[mCapacidade];
	mTamanho = 0;
}

Heap::~Heap() {
	delete[]dados; 
}

void Heap::ArrumarDescendo(int i) {
	int esq = Esquerdo(i);
    int dir = Direito(i);
    int maior = i;
    if((esq < mTamanho) and (dados[esq].somanota > dados[maior].somanota)){
        maior = esq;
        
    }
    else if((esq < mTamanho) and (dados[esq].somanota == dados[maior].somanota)){
		if(dados[esq].tentativas < dados[maior].tentativas){
			maior = esq;
		}else if(dados[esq].tentativas == dados[maior].tentativas){
			if(dados[esq].nome < dados[maior].nome)
				maior = esq;
		}
	}
    if((dir < mTamanho) and (dados[dir].somanota > dados[maior].somanota)){
        maior = dir;
    }
    else if((dir < mTamanho) and (dados[dir].somanota == dados[maior].somanota)){
		if(dados[dir].tentativas < dados[maior].tentativas){
			maior = dir;
		}else if(dados[dir].tentativas == dados[maior].tentativas){
			if(dados[dir].nome < dados[maior].nome)
				maior = dir;
		}
	}
    if(maior!=i){
        swap(dados[i], dados[maior]);
        ArrumarDescendo(maior);
    }
}

void Heap::ArrumarSubindo(int i) {
    int p = Pai(i);
    if(dados[i].somanota > dados[p].somanota){
        swap(dados[i], dados[p]);
        ArrumarSubindo(p);
    }
    else if(dados[i].somanota == dados[p].somanota){
		if(dados[i].tentativas < dados[p].tentativas){
			swap(dados[i], dados[p]);
			ArrumarSubindo(p);
		}
		else if(dados[i].tentativas == dados[p].tentativas){
			if(dados[i].nome < dados[p].nome){
				swap(dados[i], dados[p]);
				ArrumarSubindo(p);
			}
		}
	}
}

int Heap::Pai(int i) {
	return (i-1)/2;
}

int Heap::Esquerdo(int i) {
	return 2*i+1;
}

int Heap::Direito(int i) {
	return 2*i+2;
}

Aluno Heap::Retirar() {
    if (mTamanho == 0) 
        throw runtime_error("Heap vazia nao tem raiz");
    else{
		Aluno aux = dados[0];
		swap(dados[0], dados[mTamanho-1]);
		mTamanho--;
		ArrumarDescendo(0);
		return aux;
	}
}

bool Heap::Vazia() {
	if(mTamanho == 0)
		return true;
	else 
		return false;
}

void Heap::Inserir(Aluno& d){
	if (mTamanho == mCapacidade) 
        throw runtime_error("Impossivel inserir em heap cheio.");
	dados[mTamanho] = d;
    ArrumarSubindo(mTamanho);
    mTamanho++;
}

void Heap::alunoDestaque(){
	Aluno AUX = Retirar();
	cout << "[" << AUX.matricula << "] " << AUX.nome;
}	

int main(){
	int qtdeAlunos;
    cin >> qtdeAlunos;
    int qtdeAtividades;
    cin >> qtdeAtividades;
    Heap *heap = new Heap(qtdeAlunos);
    string nome;
    unsigned matricula;
    int note,tenta,somnota,somtent;
    for (int i = 0; i < qtdeAlunos; i++) {
        cin >> matricula >> nome;
        somnota = 0;
        somtent = 0;
        for(int j=0;j<qtdeAtividades;j++){
			cin >> note >> tenta;
			somnota += note;
			somtent += tenta;
		}
		Aluno aluno(matricula,nome,somnota,somtent);
		heap->Inserir(aluno);
	}
	heap->alunoDestaque();
	return 0;
}
