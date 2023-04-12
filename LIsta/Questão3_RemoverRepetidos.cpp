#include <iostream>
#include <string>

using namespace std;

class elemento{
    friend class lista;
    private:
        int chave;
        elemento *proximo;
        elemento *anterior;
    public:
        elemento (int c){
            chave = c;
            proximo = NULL;
            anterior = NULL;
        }
};

class lista{
    private:
        elemento *inicio;
        elemento *fim;
        void removerTodos();
    public:
        lista();
        ~lista();       
        void insereInicio(int c);
        void insereFim (int c);
        int removeRepetidos();//retorna a quantidade de elementos restantes na lista
        bool vazia();
        void imprimeLista();
};
    
lista::lista(){
    inicio = NULL;
    fim = NULL;
}
        
lista::~lista(){
    removerTodos();
}  

void lista::removerTodos(){
	elemento* aux = inicio;
	elemento* temp;
	while(aux!=NULL){
		temp = aux;
		aux = aux->proximo;
		delete temp;
	}
	inicio = NULL;
	fim = NULL;
}

void lista::insereInicio (int c){
    elemento* novo = new elemento(c);
	if(vazia()){
		inicio = novo;
		fim = novo;
	}
	else{
		novo->proximo = inicio;
		inicio->anterior = novo;
		inicio = novo;
	}
}
        
void lista::insereFim (int c){
    elemento* novo = new elemento(c);
	if(vazia()){
		inicio = novo;
		fim = novo;
	}
	else{
		fim->proximo = novo;
		novo->anterior = fim;
		fim = novo;
	}
}
        
int lista::removeRepetidos(){
    int valor,cont,tam = 0;
    elemento* temp = inicio;
    elemento* aux;

    while(temp!=NULL){
        cont = 0;
        valor = temp->chave;
        aux = temp;
        while(aux!=NULL){
            if(aux->chave == valor)
                cont++;
            aux = aux->proximo;
        }
        if(cont>1){
            while(cont>1){
                aux = fim;
                while((aux!=NULL) and (aux->chave != valor)){
                    aux = aux->anterior;
                }
                if(aux == NULL){
                    cerr<<"Erro: remoção de valor não encontrado"<<endl;
                }
                else{
                    elemento* anterior = aux->anterior;
                    elemento* proximo = aux->proximo;
                    if(anterior != NULL)
                        anterior->proximo = proximo;
                    else
                        inicio = aux->proximo;
                    if(proximo != NULL)
                        proximo->anterior = anterior;
                    else
                        fim = aux->anterior;
                    delete aux;
                }
                if(vazia()){
                    inicio = NULL;
                    fim = NULL;
                }
                cont--;
            }
        } 
        temp = temp->proximo; 
    }
    temp = inicio;
    while(temp!=NULL){
        tam++;
        temp = temp->proximo;
    }
    delete temp;
    return tam;
}
        
void lista::imprimeLista(){
    if (inicio != NULL){
        elemento *auxiliar = inicio;
        while (auxiliar->proximo != NULL){
            cout<<"("<<auxiliar->chave<<") ";
            auxiliar =  auxiliar->proximo;
        }
        cout<<"("<<auxiliar->chave<<")"<<endl;
    } else {
            cout<<"VAZIA";
    }
}  

bool lista::vazia(){
    return (inicio == NULL);
}
    
int main(){
    
    lista listaD;
    
    int chave;
    string dado;
    
    cin>>chave;
    
    while (chave != -1){
        listaD.insereFim(chave);        
        cin>>chave;  
    }
    cout<<listaD.removeRepetidos()<<endl;
    listaD.imprimeLista();
    
    
    return 0;
}