#include <iostream>
using namespace std;

struct Equipe{
    string nome,nick;
};

class Noh{
    friend class Lista;
    private:
        string Nome,Lider,Linguagem;
        int qtdMbrs;
        Equipe* membros;
        Noh* proximo;
    public:
        Noh(string nE,string lD,string lG,int qtM,Equipe time[]);
};

Noh::Noh(string nE,string lD,string lG,int qtM,Equipe time[]){
    Nome = nE;
    Lider = lD;
    Linguagem = lG;
    qtdMbrs = qtM;
    membros = time;
    proximo = NULL;
}

class Lista{
    private:
        Noh *primeiro;
        Noh *ultimo;
        int tamanho;
        void removerTudo();
    public:
        Lista();
        ~Lista();
        void inserirFim(string nE,string lD,string lG,int qtM,Equipe time[]);
        void procurar(string nE);
        void removerInicio();
        void removerFim();
        void removerValor(string nE);
        void imprimir();
        inline bool vaziar();
};

Lista::Lista(){
    primeiro = NULL;
    ultimo = NULL;
    tamanho = 0;
}

Lista::~Lista(){
    removerTudo();
}

void Lista::removerTudo(){
    Noh* aux = primeiro;
    Noh* temp;
    while(aux != NULL){
        temp = aux;
        aux = aux->proximo;
        delete temp;
    }
    tamanho = 0;
    primeiro = NULL;
    ultimo = NULL;
}

void Lista::inserirFim(string nE,string lD,string lG,int qtM,Equipe time[]){
    Noh* novo = new Noh(nE,lD,lG,qtM,time);
    if(vaziar()){
        primeiro = novo;
        ultimo = novo;
    }else{
        ultimo->proximo = novo;
        ultimo = novo;
    }
    tamanho++;
}

void Lista::procurar(string nE){
    Noh* aux = primeiro;
    while((aux != NULL) and (aux->Nome != nE)){
        aux = aux->proximo;
    }
    if(aux == NULL){
        cout<<"Nao encontrado"<<endl;
    }else{
        cout<<"("<<aux->Nome<<", "<<aux->Lider<<", "<<aux->Linguagem<<", [";
        for(int i=0;i<aux->qtdMbrs;i++){
            cout<<aux->membros[i].nome<<"/"<<aux->membros[i].nick;
            if(i != aux->qtdMbrs - 1)
                cout<<", ";
        }
        cout<<"])"<<endl;
    }
}

void Lista::imprimir(){
    Noh* aux = primeiro;
    while(aux != NULL){
        cout<<"("<<aux->Nome<<", "<<aux->Lider<<", "<<aux->Linguagem<<", [";
        for(int i=0;i<aux->qtdMbrs;i++){
            cout<<aux->membros[i].nome<<"/"<<aux->membros[i].nick;
            if(i != aux->qtdMbrs - 1)
                cout<<", ";
        }
        cout<<"])"<<endl;
        aux = aux->proximo;
    }      
}

inline bool Lista::vaziar(){
    return (primeiro == NULL);
}

void Lista::removerFim(){
    if(vaziar()){
        cerr << "Remoção em lista vazia!" << endl;
        exit(EXIT_FAILURE);
    }
    Noh* aux = primeiro;
    Noh* anterior;
    while(aux->proximo != NULL){
        anterior = aux;
        aux = aux->proximo;
    }
    delete ultimo;
    anterior->proximo = NULL;
    ultimo = anterior;
    tamanho--;
    if(tamanho == 0) primeiro = NULL;
    
}

void Lista::removerInicio(){
    if(vaziar()){
        cerr << "Remoção em lista vazia!" << endl;
        exit(EXIT_FAILURE);
    }
    Noh* removido = primeiro;
    primeiro = primeiro->proximo;
    delete removido;
    tamanho--;
    if(vaziar()) ultimo = NULL;
}

void Lista::removerValor(string nE){
    Noh* aux;
    Noh* anterior;
    if(not vaziar()){
        aux = primeiro;
        while((aux != NULL) and (aux->Nome != nE)){
            anterior  = aux;
            aux = aux->proximo;
        }
        if(aux != NULL){
            if(aux == primeiro)
                removerInicio();
            else if(aux == ultimo)
                removerFim();
            else{
                anterior->proximo = aux->proximo;
                tamanho--;
                delete aux;
            }
        }else
            cout<<"Nao encontrado"<<endl;
    }else
        cout<<"Nao encontrado"<<endl;
}

int main(){
    Lista maratona;
    Equipe* time;
    string Nequipe,lider,lingua;
    int qtMb;
    char op;
    cin>>op;
    while(op != 's'){
        switch(op){
            case 'i':
                cin>>Nequipe>>lider>>lingua>>qtMb;
                time = new Equipe[qtMb];
                for(int i=0;i<qtMb;i++){
                    cin>>time[i].nome>>time[i].nick;
                }
                maratona.inserirFim(Nequipe,lider,lingua,qtMb,time);
                break;
            case 'a':
                cin>>Nequipe;
                maratona.removerValor(Nequipe);
                break;
            case 'p':
                maratona.imprimir();
                break;
            case 'b':
                cin>>Nequipe;
                maratona.procurar(Nequipe);
                break;
        }
        cin>>op;
    }
    return 0;
}