/* Classe pilha dupla, duas pilhas usando um armazenamento 
 * compartilhado em um vetor com 50 posições
 *
 * by Joukim, 2019, Estruturas de Dados
 *
 */

#include <iostream>

using namespace std;

// pilha dupla em vetor de 50 elementos
// não é permitido alterar a estrutura da classe
// inserindo ou retirando métodos
// classe não precisa de destrutor, já que não 
// aloca dados dinamicamente
class pilhaDupla {
private:
    int topo1;
    int topo2;
    int tamanho1;
    int tamanho2;
    int dados[50];
public:
    pilhaDupla();
    // escolha é um inteiro para indicar qual pilha sendo usada:
    // 1 -> pilha 1 (início do arranjo)
    // 2 -> pilha 2 (final do arranjo)
    void empilha(int escolha, int valor); // empilha valor na pilha escolhida
    int desempilha(int escolha); // retorna o topo da pilha escolhida
    bool vazia(int escolha); // verifica se pilha escolhida é vazia
};


pilhaDupla::pilhaDupla() {
    tamanho1 = 0;
    topo1 = -1;
    tamanho2 = 0;
    topo2 = 50;
}

void pilhaDupla::empilha(int escolha, int valor) {
	if(escolha==1){
		dados[tamanho1] = valor;
		topo1++;
		tamanho1++;
	}
	else if(escolha==2){
		dados[topo2-1] = valor;
		topo2--;
		tamanho2++;
	}
}

int pilhaDupla::desempilha(int escolha) {
	int aux;
	if(escolha==1){
		aux = dados[topo1];
		topo1--;
		tamanho1--;
	}
	else if(escolha==2){
		aux = dados[topo2];
		topo2++;
		tamanho2--;
	}
	return aux;
}


bool pilhaDupla::vazia(int escolha) {
    if (escolha == 1) 
        return (tamanho1 == 0);
    else if (escolha == 2)
        return (tamanho2 == 0);
    return true;
}


int main() {
    pilhaDupla PP;
    char opcao;
    int escolha,cont1=0,cont2=0;
    int valor;
    
    do {
        cin >> opcao;
        switch (opcao) {
        case 'E': 
            cin >> escolha >> valor;
            if(escolha==1)cont1++;
            else if(escolha==2)cont2++;	
            if((cont1==50 and escolha==1)or(cont2==50 and escolha==2))
				cout<<"INVALIDO"<<endl;
            else
				PP.empilha(escolha,valor);  
            break;      
        case 'D':
            cin >> escolha;
            if(escolha==1)cont1--;
            else if(escolha==2)cont2--;	
            if ( PP.vazia(escolha) ) cout << "VAZIA" << endl;
            else cout << PP.desempilha(escolha) << " ";  
            break;      
        }
    } while (opcao != 'T');

    return 0;
}
