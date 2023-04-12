#include <iostream>
using namespace std;
class Noh {
    friend class Fila;
    private:
        string mDado;
        Noh* mPtProx;
    public:
		Noh(string placas);
};

Noh::Noh(string placas){
    mDado = placas;
    mPtProx = NULL;
}

class Fila {
    public:
        Fila();
        ~Fila();
        string Remover();
        void Inserir(string placas);
        void LimparTudo();
        bool Vazia() const;
        int Tamanhar();
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

void Fila::Inserir(string placas) {
	Noh *novo = new Noh(placas);
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

int Fila::Tamanhar(){
	return mTamanho;
}
int main() {
    Fila Carro,Aux;
    char sComando;
    string placa,var;
    int cont,tam1;
    bool encontrou;
    cin >> sComando;
    
    while(sComando!='S'){
		cin >> placa;
		switch(sComando){
			case 'E':
				Carro.Inserir(placa);
				break;
			case 'D':
				cont = 0;
				encontrou = false;
				tam1 = Carro.Tamanhar();
				for(int i=0;i<tam1;i++){
					var = Carro.Remover();
					if(var == placa and encontrou == false){
						i = tam1;
						cont++;
						encontrou = true;
					}else{
						if(not encontrou)
							cont++;
						Carro.Inserir(var);
					}
				}
				if(encontrou == false){
					cout << "NAO ENCONTRADO" << endl;
				}else{
					cout << cont << endl;
					tam1 = Carro.Tamanhar();
					for(int i=0;i<tam1;i++){
						Aux.Inserir(Carro.Remover());
					}
					tam1 = Aux.Tamanhar();
					for(int i=0;i<tam1;i++){
						var =  Aux.Remover();
						cout << var << endl;
						Carro.Inserir(var);
					}
				}
				break;
			case 'S':
				break;
		}
		cin>>sComando;
	}
    return 0;
}
