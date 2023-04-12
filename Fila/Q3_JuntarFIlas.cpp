#include <iostream>
using namespace std;
class Noh {
    friend class Fila;
    private:
        int mDado;
        Noh* mPtProx;
    public:
		Noh(int pessoa);
};

Noh::Noh(int pessoa){
    mDado = pessoa;
    mPtProx = NULL;
}

class Fila {
    public:
        Fila();
        ~Fila();
        int Remover();
        void Inserir(int pessoa);
        bool Vazia() const;
        int Tamanhar();
        void Debugar();
        void TiraIgual();
        int DadoInicio();
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
	while(mTamanho>0){
		Remover();
	}
}

void Fila::Inserir(int pessoa) {
	Noh *novo = new Noh(pessoa);
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


bool Fila::Vazia() const {
	if(mTamanho==0){
		return true;
	}else{
		return false;
	}
}

int Fila::Tamanhar(){
	return mTamanho;
}

int Fila::DadoInicio(){
	return mPrimeiro->mDado;
}
void Fila::TiraIgual(){
    Fila Aux;
    int v2,v1 = Remover();
    while(not Vazia()){
		v2 = Remover();
		if(v1!=v2){
			Aux.Inserir(v1);
			v1 = v2;
		}
	}
	Aux.Inserir(v1);
	int tam = Aux.Tamanhar();
	for(int i=0;i<tam;i++){
		Inserir(Aux.Remover());
	}
}

int main() {
    Fila F1,F2,FR;
    int iF1,iF2,var,var1,var2;
    cin>>iF1;
    for(int i=0;i<iF1;i++){
		cin>>var;
		F1.Inserir(var);	  
	}
	cin>>iF2;
	for(int i=0;i<iF2;i++){
		cin>>var;
		F2.Inserir(var);	  
	}
	while(not F1.Vazia() and not F2.Vazia()){
		var1 = F1.DadoInicio();
		var2 = F2.DadoInicio();
		if(var1>var2){
			FR.Inserir(var2);
			F2.Remover();		
		}else if(var1<var2){
			FR.Inserir(var1);
			F1.Remover();
		}else if(var1==var2){
			FR.Inserir(var1);
			F1.Remover();
			F2.Remover();
		}
	}
	if(not F1.Vazia()){
		while(not F1.Vazia()){
			FR.Inserir(F1.Remover());
		}
	}else if(not F2.Vazia()){
		while(not F2.Vazia()){
			FR.Inserir(F2.Remover());
		}
	}
	FR.TiraIgual();
	int tam = FR.Tamanhar();
	for(int i=0;i<tam;i++){
		cout << FR.Remover() << " ";
	}
    return 0;
}
