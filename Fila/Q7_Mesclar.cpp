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

void Fila::Debugar(){
	int tam = mTamanho;
	for(int i=0;i<tam;i++){
		cout << Remover() <<" ";
	}
	
}
int Fila::Tamanhar(){
	return mTamanho;
}

int main() {
    Fila Fa,Fb,Ft,Faux,Faux1;
    char cComando,cL;
    int iN,PorI = 0,tam,var;
    cin >> cComando;
    while(cComando != 't') {
		switch (cComando){
			case 'i':
				cin>>cL;
				if(cL == 'a'){
					cin>>iN;
					Fa.Inserir(iN);
				}
				else if(cL == 'b'){
					cin>>iN;
					Fb.Inserir(iN);
				}
				break;
			case 'e':
				cin>>cL;
				if(cL == 'a'){
					tam = Fa.Tamanhar();
					for(int i=0;i<tam;i++){
						var = Fa.Remover();
						Faux.Inserir(var);
						Fa.Inserir(var);
					}
					Faux.Debugar();
				}
				else if(cL == 'b'){
					tam = Fb.Tamanhar();
					for(int i=0;i<tam;i++){
						var = Fb.Remover();
						Faux1.Inserir(var);
						Fb.Inserir(var);
					}
					Faux1.Debugar();
				}
				cout<<endl;
				break;
			case 'm':
				while(not Fa.Vazia() or not Fb.Vazia()){
					if(PorI%2==0 and not Fa.Vazia()){
						Ft.Inserir(Fa.Remover());
						PorI++;
					}else if(Fa.Vazia()){
						PorI++;
					}
					if(PorI%2!=0 and not Fb.Vazia()){
						Ft.Inserir(Fb.Remover());
						PorI++;
					}else if(Fb.Vazia()){
						PorI++;
					}
				}
				tam = Ft.Tamanhar();
				for(int i=0;i<tam;i++){
					var = Ft.Remover();
					cout << var <<" ";
					Ft.Inserir(var);
				}
				break;
		}
		cin >> cComando;		  
	}
    return 0;
}
