#include <iostream>
using namespace std;
class Noh {
    friend class Pilha;
    private:
        int mDado;
        Noh* mPtProx;
    public:
		Noh(int valor);
};

Noh::Noh(int valor){
    mDado = valor;
    mPtProx = NULL;
}

class Pilha {
    public:
        Pilha();
        ~Pilha();
        int Desempilhar();
        void Empilhar(const int& d);
        void Ordenar(Pilha &Alcalina);
    private:
        Noh* mPtTopo;
        int mTamanho;
};

Pilha::Pilha() {
	mPtTopo = NULL;
	mTamanho = 0;
}

Pilha::~Pilha() {
	Desempilhar();
}

int Pilha::Desempilhar() {
	int valor = mPtTopo->mDado;
	Noh* temp = mPtTopo;
	mPtTopo = mPtTopo->mPtProx;
	delete temp;
	mTamanho--;
	return valor;
}

void Pilha::Empilhar(const int& d) {
    Noh* novo = new Noh(d);
    novo->mPtProx = mPtTopo;
    mPtTopo = novo;
    mTamanho++;
}

void Pilha::Ordenar(Pilha &Alcalina){
	Pilha Aux;
	int var,maior,tam;
	tam = mTamanho;
	for(int i=0;i<mTamanho;i++){
		maior = Alcalina.mPtTopo->mDado;
		for(int j = 0;j<tam;j++){
			var = Alcalina.Desempilhar();
			if(var>maior){
				Aux.Empilhar(maior);
				maior = var;
			}else{
				Aux.Empilhar(var);
			}
		}
		tam--;
		Alcalina.Empilhar(maior);
		for(int i = 0;i<tam;i++){
			Alcalina.Empilhar(Aux.Desempilhar());
		}
		
	}
}

int main() {
    Pilha Alcalina;
    int qElementos,valor;
    cin>>qElementos;
    for(int i=0;i<qElementos;i++){
		cin>>valor;
		Alcalina.Empilhar(valor);
	}
    Alcalina.Ordenar(Alcalina);
    for(int i=0;i<qElementos;i++){
		cout<<Alcalina.Desempilhar()<<" ";
	}
    return 0;
}
