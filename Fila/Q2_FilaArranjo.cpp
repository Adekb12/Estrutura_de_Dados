#include <iostream>
using namespace std;

class filaCircular{
    private:
        int mInicio;
        int mFim;
        int* dados;
        int mCapacidade;
        int mTamanho;
    public:
        filaCircular(int capacidade);
        ~filaCircular();
        void enfileira(int valor);
        int desenfileira();
        void informacoes();
        int Tamanhar();
};

filaCircular::filaCircular(int capacidade){
    mInicio = -1;
    mFim = -1;
    mCapacidade = capacidade;
    dados = new int[capacidade];
    mTamanho = 0;
}

filaCircular::~filaCircular(){
    delete[] dados;
}

void filaCircular::informacoes(){
    cout<<"tamanho="<<mTamanho<<" "<<"capacidade="<<mCapacidade<<" "<<"inicio="<<mInicio<<" "<<"fim="<<mFim<<endl;
    int pos = mInicio;
    for(int i=0; i<mTamanho; i++){
		cout<<dados[pos]<<" ";
		if(pos==mCapacidade)
			pos = 0;
        pos++;
    }
    cout<<endl;
}

void filaCircular::enfileira(int valor){
    if(mTamanho<=mCapacidade){
        mFim++;
        mFim = mFim % mCapacidade;
        dados[mFim] = valor;
        if(mTamanho == 0){
         mInicio++;
        }
        mTamanho++;
     }
     else
        cerr<<"Fila cheia!"<<endl;
}

int filaCircular::desenfileira(){
    int valor;
    valor = dados[mInicio];
    mTamanho--;
    if(mTamanho>0){
        mInicio++;
        mInicio = mInicio % mCapacidade;
    }
    else{
        mInicio = -1;
        mFim = -1;
    }
    return valor;
}

int filaCircular::Tamanhar(){
		return mTamanho;
}

int main(){
	int iN,iF;
	cin>>iN;
	filaCircular Fila(iN);
	char cComando;
	cin>>cComando;
	while(cComando!='t'){
		switch(cComando){
			case 'e':
				cin>>iF;
				Fila.enfileira(iF);
				break;
			case 'd':
				if(Fila.Tamanhar()>0)
					cout << Fila.desenfileira() << endl;
				break;
			case 'i':
				Fila.informacoes();
				break;
		}
		cin>>cComando;
	}
		
	
	return 0;
}
