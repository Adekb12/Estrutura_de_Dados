#include <iostream>
using namespace std;
class Noh {
    friend class Fila;
    private:
        string mDado;
        Noh* mPtProx;
    public:
		Noh(string bin);
};

Noh::Noh(string bin){
    mDado = bin;
    mPtProx = NULL;
}

class Fila {
    public:
        Fila();
        ~Fila();
        string Remover();
        void Inserir(string bin);
        void LimparTudo();
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

void Fila::Inserir(string bin) {
	Noh *novo = new Noh(bin);
    if(mTamanho == 0)
        mPrimeiro = novo;
    else
        mUltimo -> mPtProx = novo;
    mUltimo = novo;
    mTamanho++;
}

string Fila::Remover() {
	string bin = mPrimeiro -> mDado;
    Noh* temp = mPrimeiro;
    mPrimeiro = mPrimeiro -> mPtProx;
    delete temp;
    mTamanho--;
    return bin;
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

int main() {
    Fila Fbin;
    string inicio;
    int iN;
    cin >> iN;
    inicio = "1";
    Fbin.Inserir(inicio);
    for(int i=0;i<iN;i++){
		inicio = Fbin.Remover(); 
		Fbin.Inserir(inicio + "0"); // fila = (1, 10)
		Fbin.Inserir(inicio + "1"); // fila(1, 10, 11)
		cout<<inicio<<" ";
		
		//elemento = Fbin.desenfileira(); 
	}
    return 0;
}
