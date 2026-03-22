#include <iostream>
#include <random>
#include <vector>
#include <string>
#include <fstream>
#include <ctime>
#include <curl/curl.h>
//ATENTION: DEPRECATED WITH BUGS
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
    else chance = 100;

    uniform_int_distribution<> d100(1, 100);
    if (d100(gen) <= chance) {
        if (jg == 1) jg2vivo = 0;
        else jg1vivo = 0;
        return 1;
    }
    return 0;
}

void avaliacao(string nome_jogador) {
    cout << "\nGostaria de avaliar o nosso jogo? (1. Sim | 2. Não): ";
    string choice;
    cin >> choice;
    if (choice == "1") {
        cout << "Digite sua mensagem: ";
        string msg;
        cin.ignore();
        getline(cin, msg);
        time_t agora = time(0);
        char* dt = ctime(&agora);
        string data_hora(dt);
        if (!data_hora.empty()) data_hora.pop_back();
        string json_payload = "{\"content\": \"**Nova Avaliação!**\\n**Usuário:** " + nome_jogador + 
                              "\\n**Mensagem:** " + msg + 
                              "\\n**Data/Hora:** " + data_hora + "\"}";
        string url_webhook = get_url_from_assets();
        if (!url_webhook.empty()) {
            CURL* curl = curl_easy_init();
            if(curl) {
                struct curl_slist* headers = NULL;
                headers = curl_slist_append(headers, "Content-Type: application/json");
                curl_easy_setopt(curl, CURLOPT_URL, url_webhook.c_str());
                curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
                curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_payload.c_str());
                CURLcode res = curl_easy_perform(curl);
                if(res == CURLE_OK) cout << "\nObrigado! Feedback enviado.\n";
                else cout << "\nErro no envio do feedback.\n";
                curl_easy_cleanup(curl);
                curl_slist_free_all(headers);
            }
        }
    } else {
        cout << "Ok! Até mais!\n";
    }
}