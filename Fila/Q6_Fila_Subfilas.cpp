#include <iostream>
using namespace std;
class Noh {
    friend class Fila;
    private:
        int mDado;
        Noh* mPtProx;
    public:
		Noh(int iDado);
};

Noh::Noh(int iDado){
    mDado = iDado;
    mPtProx = NULL;
}

class Fila {
    public:
        Fila();
        ~Fila();
        int Remover();
        void Inserir(int iValor);
        void LimparTudo();
        void Desenfileirar();
    private:
        Noh* mPrimeiro;
        Noh* mUltimo;
        unsigned mTamanho;
        
};


Fila::Fila() {
	mPrimeiro = NULL;
	mUltimo = NULL;
	mTamanho = 0;
}

Fila::~Fila() {
	LimparTudo();
}

void Fila::Inserir(int iValor) {
	Noh *novo = new Noh(iValor);
    if(mTamanho == 0)
        mPrimeiro = novo;
    else
        mUltimo -> mPtProx = novo;
    mUltimo = novo;
    mTamanho++;
}
int Fila::Remover() {
	int pessoa = mPrimeiro -> mDado;
    Noh* temp = mPrimeiro;
    mPrimeiro = mPrimeiro -> mPtProx;
    delete temp;
    mTamanho--;
    return pessoa;
}

void Fila::LimparTudo() {
	while(mTamanho>0){
		Remover();
	}
}

int main (){
	Fila Fila1,Aux;
	int N,iN,iK,iV,iNegativo,tam,cont,par,ines;
	cin>>N;
	for(int i = 0;i<N;i++){
		cin>>iN;
		Fila1.Inserir(iN);
	}
	cin>>iK;
	par = N-iK+1;
	for(int i=0;i<par;i++){
		tam = 0;
		iV = 0;
		cont = 0;
		ines = 0;
		for(int i = 0;i<iK;i++){
			if(iV!=0){
				iNegativo = Fila1.Remover();
				Aux.Inserir(iNegativo);
				tam++;
				if(iNegativo < 0 and cont==0){
					cout << iNegativo <<" ";
					cont++;
					ines++;
				}
			}else{
				iNegativo = Fila1.Remover();
				tam++;
				if(iNegativo < 0){
					cout << iNegativo <<" ";
					cont++;
					ines++;
				}
				iV++;
			}
			if(ines==0 and i==iK-1)
				cout << "inexistente" << " " ; 
		}
		for(int i = 0;i<(N-tam);i++){
			Aux.Inserir(Fila1.Remover());
		}
		N--;
		for(int i = 0;i<N;i++){
			Fila1.Inserir(Aux.Remover());
		}
	}
	return 0;
}
