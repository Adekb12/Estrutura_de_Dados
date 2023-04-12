#include <iostream>
using namespace std;
class Noh {
    friend class Fila;
    private:
        string mDado;
        Noh* mPtProx;
    public:
		Noh(string pessoa);
};

Noh::Noh(string pessoa){
    mDado = pessoa;
    mPtProx = NULL;
}

class Fila {
    public:
        Fila();
        ~Fila();
        string Remover();
        void Inserir(string pessoa);
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

void Fila::Inserir(string pessoa) {
	Noh *novo = new Noh(pessoa);
    if(mTamanho == 0)
        mPrimeiro = novo;
    else
        mUltimo -> mPtProx = novo;
    mUltimo = novo;
    mTamanho++;
}

string Fila::Remover() {
	string pessoa = mPrimeiro -> mDado;
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

int main() {
    Fila Fn,Fp;
    string sComando,sNome;
    int cont = 0;
    cin >> sComando;
    while(sComando != "fim") {
        if(sComando == "normal") {
			cin >> sNome;
			Fn.Inserir(sNome);
		}else if(sComando == "prioridade"){
			cin >> sNome;
			Fp.Inserir(sNome);
		}else if(sComando == "atender"){
			if(Fn.Vazia() and Fp.Vazia()){
					cout << "AGUARDE" << endl;
			}
			else if((cont<3 and not Fp.Vazia()) or Fn.Vazia()){
				cout << Fp.Remover() << endl;
				cont++;
			}else{
				cont = 0;
				cout << Fn.Remover() << endl;
			}
		}
		cin >> sComando;		  
	}
    return 0;
}
