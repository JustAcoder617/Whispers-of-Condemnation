#include <iostream>
#include <random>
#include <vector>
#include <string>
#include <fstream>
#include <ctime>
#include <curl/curl.h>

using namespace std;

// Protótipos
int sorteio(int jg);
void game(string player1);
void avaliacao(string nome_jogador);
string get_url_from_assets();

// Globais (Estado do Jogo)
int jg1vivo = 1;
int jg2vivo = 1;
int vez = 1;

string get_url_from_assets() {
    ifstream file("asset.txt");
    if (!file.is_open()) {
        cerr << "Erro: Arquivo asset.txt nao encontrado no diretorio atual!" << endl;
        return "";
    }
    string encrypted;
    getline(file, encrypted);
    file.close();

    string decrypted = "";
    for (char c : encrypted) {
        decrypted += c ^ 42; // Sua chave XOR
    }
    return decrypted;
}

int main() {
    cout << "--- Whispers of Condemnation (v2.0 C++) ---\n";
    string nome;
    cout << "Digite seu nome de usuario/dev: ";
    getline(cin, nome); // Mais seguro que cin >> nome

    cout << "Ola, " << nome << "! Redirecionando...\n";
    game(nome);
    return 0;
}

void game(string player1) {
    string player2;
    cout << "Jogador 2, digite seu nome: ";
    getline(cin, player2);

    cout << "\n[!] Que comecem os julgamentos...\n";

    while (jg1vivo && jg2vivo) {
        string atual = (vez == 1) ? player1 : player2;
        cout << "\n>> " << atual << ", escolha: (1) Condenar | (2) Passar: ";
        
        string choice;
        getline(cin, choice);

        if (choice == "1") {
            if (sorteio(vez) == 0) {
                cout << "[*] O martelo falhou... voce sobreviveu.\n";
            } else {
                cout << "[!] CONDENADO! O martelo caiu com forca.\n";
            }
        } else {
            cout << "[*] Voce hesitou e passou a vez...\n";
        }
        
        vez = (vez == 1) ? 2 : 1; // Alterna a vez de 1 para 2
    }

    if (!jg1vivo) cout << "\n--- " << player2 << " VENCEU O DUELO! ---\n";
    else cout << "\n--- " << player1 << " VENCEU O DUELO! ---\n";

    avaliacao(player1);
}

int sorteio(int jg) {
    // Static garante que o gerador so inicie uma vez (Performance!)
    static mt19937 gen(time(0)); 
    uniform_int_distribution<> d100(1, 100);

    // Simplificando sua logica de 25% em 25%
    int chance = (d100(gen) % 4 + 1) * 25; 

    if (d100(gen) <= chance) {
        if (jg == 1) jg2vivo = 0;
        else jg1vivo = 0;
        return 1;
    }
    return 0;
}

void avaliacao(string nome_jogador) {
    cout << "\nDeseja enviar feedback ao Discord? (1. Sim | 2. Nao): ";
    string choice;
    getline(cin, choice);

    if (choice == "1") {
        cout << "Mensagem: ";
        string msg;
        getline(cin, msg);

        time_t agora = time(0);
        string data = ctime(&agora);
        if (!data.empty()) data.pop_back();

        string json = "{\"content\": \"**[Whispers Log]**\\n**User:** " + nome_jogador + 
                      "\\n**Msg:** " + msg + 
                      "\\n**Time:** " + data + "\"}";

        string url = get_url_from_assets();
        if (url.empty()) return;

        CURL* curl = curl_easy_init();
        if(curl) {
            struct curl_slist* headers = NULL;
            headers = curl_slist_append(headers, "Content-Type: application/json");
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json.c_str());
            
            // Silenciar o output do curl no terminal
            curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);

            if(curl_easy_perform(curl) == CURLE_OK) cout << "Feedback enviado!\n";
            else cout << "Erro ao conectar com o servidor.\n";

            curl_easy_cleanup(curl);
            curl_slist_free_all(headers);
        }
    }
}