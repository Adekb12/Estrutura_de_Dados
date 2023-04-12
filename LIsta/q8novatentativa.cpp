//desisti novamente
#include <iostream>
#include <cstdlib>
using namespace std;

typedef int Dado;

class noh{
	friend class listadup;
	private:
		const Dado dado;
		noh* proximo;
		noh* anterior;
	public:
		noh(Dado d = 0);
};

noh::noh(Dado d) : dado(d){
	proximo = NULL;
	anterior = NULL;
};

class listadup{
	private:
		noh* primeiro;
		noh* ultimo;
		int tamanho;
		void removeTodos();
	public:
		listadup();
		~listadup();
		void insereNoFim(Dado dado);
		void insereNaPosicao(int posicao, Dado dado);
		int procura(Dado valor);
		void imprime();
		inline bool vazia();
		void removerNoFim();
		void removerNoInicio();
		void removerValor(Dado valor);
        void desrrepetir(int paridade);
        void juntarcrescendo(listadup &L1,listadup &L2);
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

void listadup::insereNoFim(Dado dado){
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

void listadup::insereNaPosicao(int posicao, Dado dado){
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

int listadup::procura(Dado valor){
	noh* aux = primeiro;
	int posAux = 0;
	while((aux!=NULL) and (aux->dado != valor)){
		posAux++;
		aux = aux->proximo;
	}
	if(aux == NULL){
		posAux = -1;
	}
	return posAux;
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

void listadup::removerNoFim(){
	if(vazia()){
		cerr<<"Lista vazia"<<endl;
	}
	else{
		noh* removido = ultimo;
		ultimo = ultimo->anterior;
		if(ultimo != NULL)
			ultimo->proximo = NULL;
		delete removido;
		tamanho--;
		if(vazia())
			ultimo = NULL;
	}
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

void listadup::removerValor(Dado valor){
	noh* aux = primeiro;
	while((aux!=NULL) and (aux->dado != valor)){
		aux = aux->proximo;
	}
	if(aux == NULL){
		cerr<<"Erro: remoção de valor não encontrado"<<endl;
	}
	else{
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
	}
	tamanho--;
	if(vazia()){
		primeiro = NULL;
		ultimo = NULL;
	}
}

inline bool listadup::vazia(){
	return (tamanho == 0);
}

void listadup::desrrepetir(int paridade){
    int cont;
    noh* aux = primeiro;
    noh* temp;
    while(aux != NULL){
        if((aux->dado%2 != 0 and paridade == 0) or (aux->dado%2 == 0 and paridade == 1))
            removerValor(aux->dado);
        else {
            temp = aux;
            cont = 0;
            while(temp!=NULL){
                if(temp->dado == aux->dado){
                    cont++;
                }
                temp = temp->proximo;
            }
            while(cont>1){
                removerValor(aux->dado);
            }
        }
        aux = aux->proximo;
    }
}

void listadup::juntarcrescendo(listadup &L1,listadup &L2){
    L1.desrrepetir(0);
    L1.imprime();
    L2.desrrepetir(1);
    L2.imprime();
    L2.imprime();
}

int main(){
    listadup L1,L2,L3;
    int n;
    cin>>n;
    while(n != -1){
        L1.insereNoFim(n);
        cin>>n;
    }
    cin>>n;
    while(n != -1){
        L2.insereNoFim(n);
        cin>>n;
    }
    L3.juntarcrescendo(L1,L2);
    return 0;
}