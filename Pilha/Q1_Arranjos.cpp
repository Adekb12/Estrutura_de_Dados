#include <iostream>
using namespace std;
// pilha implementada em arranjo
struct Dado{
	int vl;
};
class pilhav{
    private:
        int capacidade;
        Dado *dados;
        int tamanho;
        int posTopo;
    public:
        pilhav(int cap = 20);
        ~pilhav();
        void empilha(Dado valor);
        Dado desempilha();
        Dado espia(); // acessa elemento do topo, mas não retira
        void depura(); // imprime os dados do vetor da pilha sem removê-los (desempilhar)
        void info();  // imprime informações da pilha (tamanho e  posição do topo)
        
};
pilhav::pilhav(int cap){
	capacidade = cap;
	dados = new Dado[capacidade];
	tamanho = 0;
	posTopo = -1;
}
pilhav::~pilhav(){
	delete[]dados;
}
void pilhav::empilha(Dado valor){
	dados[tamanho] = valor;
	tamanho++;
	posTopo++;
}
Dado pilhav::desempilha(){
	Dado aux = dados[posTopo];
	tamanho--;
	posTopo--;
	return aux;
}
Dado pilhav::espia(){
	Dado aux = dados[posTopo];
	return aux;
}
void pilhav::depura(){
    Dado *copia = dados;
    for(int i=0; i<tamanho; i++){
     cout<<copia[i].vl<<" ";
    }
}
void pilhav::info(){
	cout<<tamanho<<" "<<posTopo<<endl;
}
int main (){
	pilhav pilha;
	Dado teste;
	for(int i=0;i<5;i++){
		cin>>teste.vl;
		pilha.empilha(teste);
	}
	for(int i=0;i<3;i++){
		teste = pilha.desempilha();
		cout<<teste.vl<<" ";
	}
	cout<<endl;
	for(int i=0;i<4;i++){
		cin>>teste.vl;
		pilha.empilha(teste);
	}
	for(int i=0;i<3;i++){
		teste = pilha.desempilha();
		cout<<teste.vl<<" ";
	}
	cout<<endl;
	teste = pilha.espia();
	cout<<teste.vl<<endl;
	pilha.depura();
	cout<<endl;
	pilha.info();
}
