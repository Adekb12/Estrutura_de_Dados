#include <iostream>
using namespace std;

int main(){
    string vazia = "";
    string nome;
    for(int i=0;i<3;i++){
        cin>>nome;
        vazia += nome;
    }
    cout<<endl<<vazia;
    return 0;
}