#include <iostream>
#include "mods/simplemath.hpp"
#include <random>
#include <vector>
using namespace std;


int main(void){
    cout <<"Olá, Bem-vindo ao Whispers of condemnation (Versão c++)!\n";
    string nome;
    cout <<"Digite seu nome de usuário/dev:";
    cin >>nome;
    cout <<"Olá," <<nome<<"! bem vindo! redirecionando ao jogo principal...";
    game(nome);
}
void game(string player1);
int jg1vivo=1;
int jg2vivo=1;
int vez=1;
void game(string player1){
    cout <<"Jogador 2, digite seu nome:";
    string player2;
    cin >>player2;
    cout<<"\n";
    cout <<"Começando os jogos...";


int* first_round=new int;
*first_round=1;
    while (true)
    {
        if (*first_round==1)
        {
            cout<<player1<<", escolha: 1.condenar 2.passar o martelo";
            string choice;
            cin >>choice;
            if (choice=="1")
            {
                int comofoi=sorteio(1);
                if (comofoi==0){cout<<"O martelo falhou...";}
                delete first_round;
                
            }
            
        }
        
    }
    
}
int sorteio(int jg){
    if (jg==1)
    {
        using namespace std;
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> distrib(1,4);
        int sorteio=distrib(gen);
        if (sorteio==1){
            vector<string> chances={"s","n","n","n"};
            string resultado=frase_aleatoria(chances, 1);
            if (resultado=="s")
            {
                jg2vivo=0;
                return;
            }
            if (resultado=="n")
            {
                return 0;
            }
            
           
        }
    }
    
}