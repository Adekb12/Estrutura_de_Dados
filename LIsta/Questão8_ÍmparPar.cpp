#include <iostream>
#include <cstdlib>
using namespace std;

class noh{
	friend class listadup;
	private:
		int dado;
		noh* proximo;
		noh* anterior;
	public:
		noh(int dado);
};

noh::noh(int d){
    dado = d;
    proximo = NULL;
	anterior = NULL;
}

class listadup{
	private:
		noh* primeiro;
		noh* ultimo;
		int tamanho;
		void removeTodos();
	public:
		listadup();
		~listadup();
		inline void insere(int dado);
		void insereNoFim(int dado);
        void insereNaPosicao(int pos,int dado);
		void imprime();
		inline bool vazia();
		void removerNoInicio();
        void remove(listadup& L2);
		void removerValor(int valor);
        void criaordenada(listadup& l1,listadup& l2);
};

listadup::listadup(){
	tamanho = 0;
	primeiro = NULL;
	ultimo = NULL;

}

listadup::~listadup(){
	removeTodos();
}

void listadup::removeTodos(){
	noh* aux = primeiro;
	noh* temp;
	while(aux!=NULL){
		temp = aux;
		aux = aux->proximo;
		delete temp;
	}
	tamanho = 0;
	primeiro = NULL;
	ultimo = NULL;
}

void listadup::insere(int dado){
	insereNoFim(dado);
}


void listadup::insereNoFim(int dado){
	noh* novo = new noh(dado);
	if(vazia()){
		primeiro = novo;
		ultimo = novo;
	}
	else{
		ultimo->proximo = novo;
		novo->anterior = ultimo;
		ultimo = novo;
	}
	tamanho++;
}

void listadup::insereNaPosicao(int posicao, int dado){
	noh* novo = new noh(dado);
	if((posicao<=tamanho) and (posicao>=0)){
		if(vazia()){
			primeiro = novo;
			ultimo = novo;
		}
		else if(posicao == 0){
			novo->proximo = primeiro;
			primeiro->anterior = novo;
			primeiro = novo;
		}
		else if(posicao == tamanho){
			ultimo->proximo = novo;
			novo->anterior = ultimo;
			ultimo = novo;
		}
		else{
			noh* aux = primeiro;
			int posAux = 0;
			while(posAux<(posicao - 1)){
				aux = aux->proximo;
				posAux++;
			}
			novo->proximo = aux->proximo;
			aux->proximo->anterior = novo;
			aux->proximo = novo;
			novo->anterior = aux;
		}
		tamanho++;
	}
}

void listadup::imprime(){
	noh* aux = primeiro;
	while(aux!=NULL){
        cout << aux->dado << " ";
		aux = aux->proximo;
	}
	cout<<endl;
}

void listadup::removerNoInicio(){
	if(vazia()){
		cerr<<"Lista vazia"<<endl;
	}
	else{
		noh* removido = primeiro;
		primeiro = primeiro->proximo;
		if(primeiro != NULL)
			primeiro->anterior = NULL;
		delete removido;
		tamanho--;
		if(vazia())
			ultimo = NULL;
	}
}

void listadup::removerValor(int valor){
	noh* aux = primeiro;
	while((aux!=NULL) and (aux->dado != valor)){
		aux = aux->proximo;
	}
	noh* anterior = aux->anterior;
	noh* proximo = aux->proximo;
	if(anterior != NULL)
		anterior->proximo = proximo;
	else
		primeiro = aux->proximo;
	if(proximo != NULL)
		proximo->anterior = anterior;
	else
		ultimo = aux->anterior;
	delete aux;
	tamanho--;
	if(vazia()){
		primeiro = NULL;
		ultimo = NULL;
	}
}

void listadup::criaordenada(listadup &L1,listadup &L2){
    noh* auxl = L1.primeiro;
    while(auxl!=NULL){
        if(auxl->dado%2 == 0){
            insere(auxl->dado);
        }
        auxl = auxl->proximo;
    }
    delete auxl;
    auxl = L2.primeiro;
    while(auxl!=NULL){
        if(auxl->dado%2 != 0){
            insere(auxl->dado);
        }
        auxl = auxl->proximo;
    }
    delete auxl;
    auxl = primeiro;
    noh* temp;
    int var,pos;
    while(auxl!=NULL){
        var = auxl->dado;
        temp = auxl;
        pos = 0;
        while(temp!=NULL){
            if(auxl->dado<temp->dado){
                removerValor(auxl->dado);
                insereNaPosicao(pos,auxl->dado);
            }
            pos++;
            temp = temp->proximo;
        }
        auxl = auxl->proximo;
    }
    delete auxl;
    delete temp;
    auxl = ultimo;
    temp;
    while(auxl!=NULL){
        var = auxl->dado;
        temp = auxl;
        pos = tamanho;
        while(temp!=NULL){
            if(auxl->dado>temp->dado){
                removerValor(auxl->dado);
                insereNaPosicao(pos,auxl->dado);
            }
            pos--;
            temp = temp->anterior;
        }
        auxl = auxl->anterior;
    }
}

inline bool listadup::vazia(){
	return (tamanho == 0);
}

int main(){
    listadup L1,L2,L3;
    int v;
    cin>>v;
    while(v!=-1){
        L1.insere(v);
        cin>>v;
    }
    cin>>v;
    while(v!=-1){
        L2.insere(v);
        cin>>v;
    } 
    L3.criaordenada(L1,L2);  
    L3.imprime();
}