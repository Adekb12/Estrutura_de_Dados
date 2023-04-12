#include <iostream>
#include <stdexcept>

using namespace std;

struct dado {
    unsigned ano; 
    string cidadeRealizacao;
    unsigned qtdadeFilmesApresentados;   
};

ostream& operator<<(ostream& saida, const dado& e) {
    saida << "(" << e.ano << "," << e.cidadeRealizacao << "," << e.qtdadeFilmesApresentados << ")";
    return saida;
}

istream& operator>>(istream& entrada, dado& e) {
    entrada >> e.ano >> e.cidadeRealizacao >> e.qtdadeFilmesApresentados;
    return entrada;
}
typedef unsigned tipoChave;

class noh {
    friend class avl;
    private:
        dado elemento;
        noh* esq;
        noh* dir;
        unsigned altura;
    public:
        noh(const dado& umDado):
            elemento(umDado),  esq(NULL), dir(NULL), altura(1) { }
        ~noh() { }
        int fatorBalanceamento();
        void atualizarAltura(noh* umNoh);
        unsigned maximo(unsigned altEsq,unsigned altDir);
        unsigned informarAltura(noh* umNoh);
};

int noh::fatorBalanceamento() {
    int altEsq = informarAltura(this->esq);
    int altDir = informarAltura(this->dir);
    int fatorBal = altEsq - altDir;
    return fatorBal;
}

void noh::atualizarAltura(noh* umNoh){
    unsigned altEsq = informarAltura(umNoh->esq);
    unsigned altDir = informarAltura(umNoh->dir);
    umNoh->altura = 1 + maximo(altEsq,altDir);
}

unsigned noh::informarAltura(noh* umNoh){
    if(umNoh == NULL)
        return 0;
    else   
        return umNoh->altura;
}

unsigned noh::maximo(unsigned altEsq,unsigned altDir){
    if(altEsq > altDir)
        return altEsq;
    else   
        return altDir;
}

class avl {
    friend ostream& operator<<(ostream& output, avl& arvore);
    private:
        noh* raiz;
        noh* encontraMenor(noh* raizSub);
        noh* removeMenor(noh* raizSub);
        noh* insereAux(noh* umNoh, const dado& umDado);
        noh* removeAux(noh* umNoh, tipoChave chave);
        noh* rotacaoEsquerda(noh* umNoh);
        noh* rotacaoDireita(noh* umNoh);
        noh* arrumaBalanceamento(noh* umNoh);
        noh* buscaAux(tipoChave chave);
        void destruirRecursivamente(noh* umNoh);
        void imprimirDir(const std::string& prefixo, const noh* meuNoh);
        void imprimirEsq(const std::string& prefixo, const noh* meuNoh, bool temIrmao);
        void levantamentoAux(noh* umNoh, unsigned &ano, unsigned &quant);
    public:
        avl() { raiz = NULL; }
        ~avl();
        void imprimir();
        void insere(const dado& umDado);
        void remove(tipoChave chave);
        dado busca(tipoChave chave);
        unsigned levantamento();
};

avl::~avl() {
    destruirRecursivamente(raiz);
}

void avl::destruirRecursivamente(noh* umNoh) {
    if(umNoh != NULL){
        destruirRecursivamente(umNoh->esq);
        destruirRecursivamente(umNoh->dir);
        delete umNoh;
    }
}

void avl::insere(const dado& umDado) {
    noh* aux = buscaAux(umDado.ano);
    if(aux != NULL)
        throw runtime_error("Erro na inserção: chave já existente!");
    else
        raiz = insereAux(raiz, umDado);
}

noh* avl::insereAux(noh* umNoh, const dado& umDado) {
    if(umNoh == NULL){
        noh* novo = new noh(umDado);
        return novo;
    }else{
        if(umDado.ano < umNoh->elemento.ano){
            umNoh->esq = insereAux(umNoh->esq,umDado);
        }else{
            umNoh->dir = insereAux(umNoh->dir,umDado);
        }
    }
    return arrumaBalanceamento(umNoh);
}

noh* avl::arrumaBalanceamento(noh* umNoh) {
    if(umNoh == NULL)
        return umNoh;
    umNoh->atualizarAltura(umNoh);
    int fatorBal = umNoh->fatorBalanceamento();
    if((fatorBal >= -1) and (fatorBal <= 1))
        return umNoh;
    if((fatorBal > 1) and (umNoh->esq->fatorBalanceamento() >= 0))
        return rotacaoDireita(umNoh);
    if((fatorBal > 1) and (umNoh->esq->fatorBalanceamento()) < 0){
        umNoh->esq = rotacaoEsquerda(umNoh->esq);
        return rotacaoDireita(umNoh);
    }
    if((fatorBal < -1) and (umNoh->dir->fatorBalanceamento() <= 0))
        return rotacaoEsquerda(umNoh);
    if((fatorBal < -1) and (umNoh->dir->fatorBalanceamento()) > 0){
        umNoh->dir = rotacaoDireita(umNoh->dir);
        return rotacaoEsquerda(umNoh);
    }
    return umNoh;
}

noh* avl::rotacaoEsquerda(noh* umNoh) {
    noh* nohAux = umNoh->dir;
    umNoh->dir = nohAux->esq;
    nohAux->esq = umNoh;
    umNoh->atualizarAltura(umNoh);
    nohAux->atualizarAltura(nohAux);
    return nohAux;
}

noh* avl::rotacaoDireita(noh* umNoh) {
    noh* nohAux = umNoh->esq;
    umNoh->esq = nohAux->dir;
    nohAux->dir = umNoh;
    umNoh->atualizarAltura(umNoh);
    nohAux->atualizarAltura(nohAux);
    return nohAux;
}

noh* avl::buscaAux(tipoChave ano) {
    noh* atual = raiz;
    while(atual!=NULL){
        if(atual->elemento.ano == ano)
            return atual;
        else if(atual->elemento.ano > ano)
            atual = atual->esq;
        else 
            atual = atual->dir;
    }
    return atual;
}

dado avl::busca(tipoChave chave) {
    noh* resultado = buscaAux(chave);
    if (resultado != NULL)
        return resultado->elemento;
    else
        throw runtime_error("Erro na busca: elemento não encontrado!");
}

noh* avl::encontraMenor(noh* raizSub) { 
    while(raizSub->esq != NULL){
        raizSub = raizSub->esq;
    }
    return raizSub;
}

noh* avl::removeMenor(noh* raizSub) {
    if(raizSub->esq == NULL)
        return raizSub->dir;
    else { 
        raizSub->esq = removeMenor(raizSub->esq);
        return arrumaBalanceamento(raizSub);
    }
}

void avl::remove(tipoChave chave) {
    noh* aux = buscaAux(chave);
    if(aux == NULL)
        throw runtime_error("Erro na remoção: chave não encontrada!");
    else
        raiz = removeAux(raiz, chave);
}

noh* avl::removeAux(noh* umNoh, tipoChave chave) {
    noh* novaRaizSubArvore = umNoh;
    if (chave < umNoh->elemento.ano) {
        umNoh->esq = removeAux(umNoh->esq, chave);
    } else if (chave > umNoh->elemento.ano) {
        umNoh->dir = removeAux(umNoh->dir, chave);
    } else { 
        if (umNoh->esq == NULL) 
            novaRaizSubArvore = umNoh->dir;
        else if (umNoh->dir == NULL) \
            novaRaizSubArvore = umNoh->esq;
        else {
            novaRaizSubArvore = encontraMenor(umNoh->dir);
            novaRaizSubArvore->dir = removeMenor(umNoh->dir);  
            novaRaizSubArvore->esq = umNoh->esq;
        }
        delete umNoh;
    } 
    return arrumaBalanceamento(novaRaizSubArvore);
}

unsigned avl::levantamento(){
    unsigned ano = 0;
    unsigned quant = 0;
    levantamentoAux(raiz,ano,quant);
    return ano;
}

void avl::levantamentoAux(noh* umNoh,unsigned& ano,unsigned& quant){
    if(umNoh != NULL){
        if(umNoh->elemento.qtdadeFilmesApresentados > quant){
            quant = umNoh->elemento.qtdadeFilmesApresentados;
            ano = umNoh->elemento.ano;
        }else if(umNoh->elemento.qtdadeFilmesApresentados == quant){
            if(umNoh->elemento.ano < ano)
                ano = umNoh->elemento.ano;
        }
        levantamentoAux(umNoh->esq,ano,quant);
        levantamentoAux(umNoh->dir,ano,quant);   
    }
}

ostream& operator<<(ostream& output, avl& arvore) {
    arvore.imprimir();
    return output;
}

void avl::imprimirDir(const std::string& prefixo, const noh* meuNoh)
{
    if( meuNoh != nullptr )
    {
        std::cout << prefixo
                  << "└d─"
                  << "(" << meuNoh->elemento.ano << "," << meuNoh->elemento.cidadeRealizacao << ")"
                  << std::endl;

        // Repassa o prefixo para manter o historico de como deve ser a formatacao e chama no filho direito e esquerdo
        imprimirEsq( prefixo + "    " , meuNoh->esq , meuNoh->dir==nullptr );
        imprimirDir( prefixo + "    " , meuNoh->dir );
    }
}

// imprime formatado seguindo o padrao tree as subarvores direitas de uma avl
void avl::imprimirEsq(const std::string& prefixo, const noh* meuNoh, bool temIrmao)
{
    if( meuNoh != nullptr )
    {
        std::cout << prefixo ;

        // A impressao da arvore esquerda depende da indicacao se existe o irmao a direita
        if (temIrmao)
            std::cout << "└e─" ;
        else
            std::cout << "├e─";

        std::cout << "(" << meuNoh->elemento.ano << "," << meuNoh->elemento.cidadeRealizacao << ")"
                  << std::endl;

        // Repassa o prefixo para manter o historico de como deve ser a formatacao e chama no filho direito e esquerdo
        imprimirEsq( prefixo + "│   " , meuNoh->esq, meuNoh->dir==nullptr );
        imprimirDir( prefixo + "│   " , meuNoh->dir );
    }
}

// imprime formatado seguindo o padrao tree uma avl
void avl::imprimir()
{
    if( this->raiz != nullptr )
    {
        std::cout << "(" << this->raiz->elemento.ano << "," << this->raiz->elemento.cidadeRealizacao << ")" << std::endl;
        // apos imprimir a raiz, chama os respectivos metodos de impressao nas subarvore esquerda e direita
        // a chamada para a impressao da subarvore esquerda depende da existencia da subarvore direita
        imprimirEsq( " " , this->raiz->esq, this->raiz->dir==nullptr );
        imprimirDir( " " , this->raiz->dir );
    } else
        std::cout << "*arvore vazia*" << std::endl;
}

int main() {
    avl arvore;
    tipoChave chave;
    dado umDado;
    unsigned ano;

    char operacao;

    do {
        try {
            cin >> operacao;
            switch (operacao) {
                case 'i': // Inserir recursivamente
                    // objeto recebe nome, cidade e quantidade de filmes apresentados
                    cin >> umDado;
                    arvore.insere(umDado);
                    break;
                case 'r': // Remover recursivamente
                    cin >> chave;
                    arvore.remove(chave);
                    break;
                case 'b': // Buscar
                    cin >> chave; // ler a chave
                    umDado = arvore.busca(chave); // escrever os dados do festival
                    cout << "Elemento buscado: " << umDado << endl;
                    break;
                case 'l': // Levantamento pelo ano com maior número de filmes apresentados
                    ano = arvore.levantamento( );
                    cout << "Edição com maior quantidade de filmes apresentados: " << ano << endl;
                    break;
                case 'e': // Escrever tudo (em ordem)
                    cout << arvore;
                    break;
                case 'f': // Finalizar execução
                    break;
                default:
                    cout << "Comando invalido!\n";
            }
        } catch (runtime_error& e) {
            cout << e.what() << endl;
        }
    } while (operacao != 'f');

    return 0;
}
