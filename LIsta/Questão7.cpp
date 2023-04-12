#include <iostream>
using namespace std;

class Noh{
    friend class Lista;
    private:
        char letra;
        Noh* proximo;
    public:
        Noh(char l);
};

Noh::Noh(char l){
    letra = l;
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
        void inserirFim(char l);
        string palindromar();
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

void Lista::inserirFim(char l){
    Noh* novo = new Noh(l);
    if(vaziar()){
        primeiro = novo;
        ultimo = novo;
    }else{
        ultimo->proximo = novo;
        ultimo = novo;
    }
    tamanho++;
}

inline bool Lista::vaziar(){
    return (primeiro == NULL);
}

string Lista::palindromar(){
    Noh* aux = primeiro;
    string palavra = "";
    int cont = tamanho;
    while(aux != NULL){
        palavra += aux->letra;
        aux = aux->proximo;
    }
    delete aux;
    string compara = "";
    while(cont>0){
        aux = primeiro;
        for(int i=cont-1;i>0;i--){
            aux = aux->proximo;
        }
        compara += aux->letra;
        cont--;
    }
    if(palavra == compara)
        return "sim";
    return "nao";
}

int main(){
    Lista palindromo;
    char letra;
    cin>>letra;
    while(letra != '#'){
        palindromo.inserirFim(letra);
        cin>>letra;
    }
    cout<<palindromo.palindromar();
    return 0;
}