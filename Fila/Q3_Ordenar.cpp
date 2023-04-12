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

void Fila::TiraIgual(){
    Fila aux;
    int var1,var2=0,T=mTamanho;
    for(int i=0;i<T;i++){
        var1 = Remover();
        if(var2 != var1 and i > 0){
            aux.Inserir(var2);
            aux.Inserir
            (var1);
        }
        var2 = var1;
    }
    int T1 = aux.Tamanhar();
    for(int i=0;i<T1;i++){
        Inserir(aux.Remover());
    }
}

int main() {
    Fila fila1,fila2,filaR;
    int iF1,iF2,var,aux;
    cin>>iF1;
    for(int i=0;i<iF1;i++){
		cin>>var;
		fila1.Inserir(var);	  
	}
	cin>>iF2;
	for(int i=0;i<iF2;i++){
		cin>>var;
		fila2.Inserir(var);	  
	}
	//fila1.TiraIgual();
	//fila2.TiraIgual();
	for(int i=0;i<iF1;i++){
		var = fila1.Remover();
		for(int j=0;j<iF2;j++){
			aux = fila2.Remover();
			if(var<aux){
				filaR.Inserir(var);
				j = iF2;
				filaR.Inserir(aux);
				fila2.Inserir(aux);
			}else if(var == aux){
				filaR.Inserir(var);
				j = iF2;
				iF2--;	
			}else{
				filaR.Inserir(aux); 
				fila2.Inserir(aux);
			}	
		}
	}
	filaR.TiraIgual();
	for(int i=0;i<(iF1+iF2);i++){
		cout << filaR.Remover() << " ";
	}
    return 0;
}
