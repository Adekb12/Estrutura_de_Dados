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
        int InformarTam();
        bool Vazia();
        int Topo();
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

int Pilha::InformarTam(){
	return mTamanho;
}

int Pilha::Topo(){
	return mPtTopo->mDado;
}

bool Pilha::Vazia(){
	if(mTamanho == 0)
		return true;
	else
		return false;
}

int main() {
    Pilha P1,AUX;
    int valor, menor,tam,var;
    char comando;
    do {
        cin >> comando;
        switch (comando) {
            case 'e':
                cin >> valor;
                P1.Empilhar(valor);
                break;
            case 'd':
				if(P1.Vazia())
					cout<<"VAZIA"<<endl;
				else
					cout << P1.Desempilhar() << endl;
                break;
            case 'm':
				if(P1.Vazia())
					cout<<"VAZIA"<<endl;
				else{
					tam = P1.InformarTam();
					for(int i = 0;i<tam;i++){
						if(i==0)
							menor = P1.Topo();
						var = P1.Desempilhar();
						if(var<menor)
							menor = var;
						AUX.Empilhar(var);
					}
					cout<<menor<<endl;
					for(int i = 0;i<tam;i++){
						P1.Empilhar(AUX.Desempilhar());
					}
				}
				break;
            case 's': 
                for(int i = 0;i<tam;i++){
					cout<<P1.Desempilhar()<<" ";
				}
                break;
        }
    } while (comando != 's');
    cout << endl;
    return 0;
}
