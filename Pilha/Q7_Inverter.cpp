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
    private:
        Noh* mPtTopo;
        unsigned mTamanho;
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
int main (){
	int nElementos,valor;
	cin>>nElementos;
	Pilha P1,AUX;
	for(int i = 0;i<nElementos;i++){
		cin>>valor;
		P1.Empilhar(valor);
	}
	for(int i = 0;i<nElementos;i++){
		AUX.Empilhar(P1.Desempilhar());
	}
	/*for(int i = 0;i<nElementos;i++){
		cout<<AUX.Desempilhar()<<" ";
	}*/
	P1 = AUX;
	for(int i = 0;i<nElementos;i++){
		cout<<P1.Desempilhar()<<" ";
	}
	return 0;
}
