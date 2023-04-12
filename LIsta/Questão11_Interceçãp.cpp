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
		void imprime();
		inline bool vazia();
		void removerNoInicio();
        void remove(listadup& L2);
		void removerValor(int valor);
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

void listadup::imprime(){
	noh* aux = primeiro;
	while(aux!=NULL){
		cout<<aux->dado<<" ";
		aux = aux->proximo;
	}
	cout<<endl;
	aux = ultimo;
	while(aux!=NULL){
		cout<<aux->dado<<" ";
		aux = aux->anterior;
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

inline bool listadup::vazia(){
	return (tamanho == 0);
}

void listadup::remove(listadup& L2){
    noh* aux;
    noh* temp = L2.primeiro;
	int cont=0,v;
    while(temp!=NULL){
        aux = primeiro;
		v = temp->dado;
        while(aux!=NULL){
            if(v == aux->dado){
				cont++;
            }
            aux = aux->proximo;
        }
		while(cont>0){
			removerValor(v);
			cont--;
		}
		temp = temp->proximo;
    }
}

int main(){
    int n,valor;
    listadup L1,L2;
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>valor;
        L1.insere(valor);
    }
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>valor;
        L2.insere(valor);
    }
    L1.remove(L2);
    if(L1.vazia())
        cout<<"-1";
    else
        L1.imprime();
    return 0;
}