#include <iostream>
#include <random>
#include <vector>
#include <string>

using namespace std;

int sorteio(int jg);
void game(string player1);

int jg1vivo = 1;
int jg2vivo = 1;
int vez = 1;

int main(void) {
    cout << "Olá, Bem-vindo ao Whispers of condemnation (Versão c++)!\n";
    string nome;
    cout << "Digite seu nome de usuário/dev: ";
    cin >> nome;
    cout << "Olá, " << nome << "! bem vindo! redirecionando ao jogo principal...\n";
    game(nome);
    return 0;
}

void game(string player1) {
    cout << "Jogador 2, digite seu nome: ";
    string player2;
    cin >> player2;
    cout << "\nComeçando os jogos...\n";

    bool first_round = true;

    while (jg1vivo == 1 && jg2vivo == 1) {
        if (first_round) {
            cout << "\n" << player1 << ", escolha: 1.condenar 2.passar o martelo: ";
            string choice;
            cin >> choice;
            if (choice == "1") {
                if (sorteio(1) == 0) cout << "O martelo falhou...\n";
            }
            vez = 0;
            first_round = false;
        } 
        else if (vez == 1) {
            cout << "\n" << player1 << ", escolha: 1.condenar 2.passar: ";
            string choice;
            cin >> choice;
            if (choice == "1") {
                if (sorteio(1) == 0) cout << "O martelo falhou...\n";
            }
            vez = 0;
        } 
        else if (vez == 0) {
            cout << "\n" << player2 << ", escolha: 1.condenar 2.passar: ";
            string choice;
            cin >> choice;
            if (choice == "1") {
                if (sorteio(2) == 0) cout << "O martelo falhou...\n";
            }
            vez = 1;
        }
    }

    if (jg1vivo == 0) cout << "\n" << player2 << " GANHOU O JOGO!\n";
    else if (jg2vivo == 0) cout << "\n" << player1 << " GANHOU O JOGO!\n";
}

int sorteio(int jg) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(1, 4);
    int s = distrib(gen);
    
    int chance;
    if (s == 1) chance = 25;
    else if (s == 2) chance = 50;
    else if (s == 3) chance = 75;
    else chance = 100;

    uniform_int_distribution<> d100(1, 100);
    if (d100(gen) <= chance) {
        if (jg == 1) jg2vivo = 0;
        else jg1vivo = 0;
        return 1;
    }
    return 0;
}