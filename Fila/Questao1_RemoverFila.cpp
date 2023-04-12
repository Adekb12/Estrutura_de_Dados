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
        bool Vazia() const;
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

bool Fila::Vazia() const {
	if(mTamanho==0){
		return true;
	}else{
		return false;
	}
}

int main (){
	Fila F1,F2,Aux;
	int iT1,iT2,iVv,Var,VarAux,iCont;
	cin>>iT1;
	for(int i=0;i<iT1;i++){
		cin>>iVv;
		F1.Inserir(iVv);
	}
	cin>>iT2;
	for(int i=0;i<iT2;i++){
		cin>>iVv;
		F2.Inserir(iVv);
	}
	for(int i=0;i<iT2;i++){
		Var = F2.Remover();
		iCont = 0;
		for(int i=0;i<iT1;i++){
			VarAux = F1.Remover();
			if(Var!=VarAux){
				Aux.Inserir(VarAux);
			}else{
				iCont++;
			}
		}
		iT1-=iCont;
		for(int i=0;i<iT1;i++){
			F1.Inserir(Aux.Remover());
		}
	}
	for(int i=0;i<iT1;i++){
		cout << F1.Remover() << " ";
		}
	return 0;
}
