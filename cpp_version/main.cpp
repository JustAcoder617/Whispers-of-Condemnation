#include <iostream>
#include <random>
#include <vector>
#include <string>
#include <fstream>
#include <ctime>
#include <curl/curl.h>

using namespace std;

int sorteio(int jg);
void game(string player1);
void avaliacao(string nome_jogador);
string get_url_from_assets();

int jg1vivo = 1;
int jg2vivo = 1;
int vez = 1;

string get_url_from_assets() {
    ifstream file("asset.txt");
    string encrypted;
    string decrypted = "";
    if (file.is_open()) {
        getline(file, encrypted);
        file.close();
        for (char c : encrypted) {
            decrypted += c ^ 42;
        }
    } else {
        cerr << "Erro: Arquivo asset.txt não encontrado!" << endl;
    }
    return decrypted;
}

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
    while (jg1vivo == 1 && jg2vivo == 1) {
        if (vez == 1) {
            cout << "\n" << player1 << ", escolha: 1.condenar 2.passar: ";
            string choice;
            cin >> choice;
            if (choice == "1") {
                if (sorteio(1) == 0) cout << "O martelo falhou...\n";
            }
            vez = 0;
        } 
        else {
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
    else cout << "\n" << player1 << " GANHOU O JOGO!\n";
    avaliacao(player1);
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