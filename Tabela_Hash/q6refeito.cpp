#include <iostream>
using namespace std;

const int UMPRIMO = 83;
int funcaoHash(string s, int M) {
    long h = 0;
    for (unsigned i = 0; i < s.length(); i++) {
        h = (UMPRIMO * h + s[i]) % M;
    }
    return h;
}

class Noh{
    friend class Lista;
    friend class tabelaHash;
    private:
        string chave;
        string valor;
        Noh* proximo;
    public:
        Noh(string c,string v);
};

Noh::Noh(string c,string v){
    chave = c;
    valor = v;
    proximo = NULL;
}

class Lista{
    friend class tabelaHash;
    private:
        Noh *primeiro;
        Noh *ultimo;
        int tamanho;
        void removerTudo();
    public:
        Lista();
        ~Lista();
        void inserirFim(string c,string v);
        string procurar(string cha);
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
    primeiro = NULL;
    ultimo = NULL;
}

string Lista::procurar(string cha){
    Noh* aux = primeiro;
    string conca = "";
    while(aux != NULL){
        if(aux->chave == cha){
            conca += aux->valor;
        }
        aux = aux->proximo;
    }
    return conca;
}

void Lista::inserirFim(string c,string v){
    Noh* novo = new Noh(c,v);
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

class tabelaHash{
    private:
        int capacidade;
        Lista* tabeHa;
    public:
        tabelaHash(int cap);
        ~tabelaHash();
        void inserir(string c,string v);
        void recuperar(string c);
        void percorrer();
};

tabelaHash::tabelaHash(int cap){
    tabeHa = new Lista[cap];
    capacidade = cap;
}

tabelaHash::~tabelaHash(){
    for(int i;i<capacidade;i++){
        tabeHa[i].removerTudo();
    }
    delete[] tabeHa;
}

void tabelaHash::inserir(string chave,string valor){
    int pos = funcaoHash(chave,capacidade);
    tabeHa[pos].inserirFim(chave, valor);
}

void tabelaHash::recuperar(string c){
    int pos = funcaoHash(c,capacidade);
    cout<<tabeHa[pos].procurar(c)<<endl;
}

void tabelaHash::percorrer(){
    Noh* atual;
    for (int i = 0; i < capacidade; i++) {
        cout << i << ":";
        atual = tabeHa[i].primeiro;
        while (atual != NULL) {
            cout << "[" << atual->chave << "/"
                 << atual->valor << "]->";
            atual = atual->proximo;

        }
        cout << "NULL  ";
    }
    cout << endl;
}

int main(){
    int tam;
    cin>>tam;
    tabelaHash tata(tam);
    char op;
    string chave,valor;
    cin>>op;
    while(op!='Q'){
        switch(op){
        case 'I':
            cin>>chave>>valor;
            tata.inserir(chave,valor);
            break;
        case 'R':
            cin>>chave;
            tata.recuperar(chave);
            break;
        
        case 'P':
            tata.percorrer();
            break;
        }
        cin>>op;
    }
    return 0;
}