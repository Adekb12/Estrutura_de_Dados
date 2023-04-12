#include <iostream>
using namespace std;

struct registro{
    int matricula,periodo;
    string nome;
};

class Noh{
    friend class Lista;
    private:
        registro dado;
        Noh* proximo;
    public:
        Noh(registro dado);
};

Noh::Noh(registro d){
    dado = d;
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
        inline void inserir(registro dado);
        void inserirPos(int pos, registro dado);
        registro removerFim();
        void inserirFim(registro dado);
        void inserirInicio(registro dado);
        void imprimir();
        void imprimirReverso();
        void imprimirReversoAux(Noh* umNoh,int& tam);
        inline bool vaziar();
        void invertida();
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

void Lista::inserir(registro dado){
    inserirFim(dado);
}

void Lista::inserirFim(registro dado){
    Noh* novo = new Noh(dado);
    if(vaziar()){
        primeiro = novo;
        ultimo = novo;
    }else{
        ultimo->proximo = novo;
        ultimo = novo;
    }
    tamanho++;
}

void Lista::inserirInicio(registro dado){
    Noh* novo = new Noh(dado);
    if(vaziar()){
        primeiro = novo;
        ultimo = novo;
    }else{
        novo->proximo = primeiro;
        primeiro = novo;
    }
    tamanho++;
}

void Lista::inserirPos(int pos, registro dado){
    Noh* novo = new Noh(dado);
    if((pos <= tamanho) and (pos >= 0)){
        if(vaziar()){
            primeiro = novo;
            ultimo = novo;
        }else if(pos == 0){
            novo->proximo = primeiro;
            primeiro = novo;
        }else if(pos == tamanho){
            ultimo->proximo = novo;
            ultimo = novo;
        }else{
            Noh* aux = primeiro;
            int posAux = 0;
            while(posAux < (pos-1)){
                aux = aux->proximo;
                posAux++;
            }
            novo->proximo = aux->proximo;
            aux->proximo = novo;
        }
        tamanho++;
    }else{
        cerr << "Posição Inexistente!" << endl;
        exit(EXIT_FAILURE);
    }
}

void Lista::imprimir(){
    Noh* aux = primeiro;
    cout << "[";
    while(aux != NULL){
        cout << aux->dado.matricula << " - " << aux->dado.nome;
        if(aux->proximo != NULL)
            cout<<", ";
        aux = aux->proximo;
    }
    cout << "]";
    cout << endl;
}

void Lista::imprimirReverso(){
    int tam = tamanho;
    cout <<"[";
    imprimirReversoAux(primeiro,tam);
    cout << "]" << endl;
}

void Lista::imprimirReversoAux(Noh* umNoh, int& tam){
    if(umNoh != NULL){
        imprimirReversoAux(umNoh->proximo,tam);
        cout << umNoh->dado.matricula << " - " << umNoh->dado.nome;
        if(tam>1){
            cout << ", ";
            tam--;
        }
            
    }
}

inline bool Lista::vaziar(){
    return (primeiro == NULL);
}

registro Lista::removerFim(){
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
    registro AUX;
    AUX = ultimo->dado;
    delete ultimo;
    anterior->proximo = NULL;
    ultimo = anterior;
    tamanho--;
    if(tamanho == 0) primeiro = NULL;
    return AUX;
}

int main(){
    Lista lista;
    registro aluno;
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>aluno.matricula>>aluno.nome>>aluno.periodo;
        lista.inserir(aluno);
    }
    lista.imprimir();
    lista.imprimirReverso();
    return 0;
}
