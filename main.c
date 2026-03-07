#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <curl/curl.h>

// Protótipos
void inicio(void);
void jogo(char jg1[], char jg2[]);
void avaliacao(void);
void disparar_webhook(char *texto);
void descriptografar(char *dados, int tamanho, int chave);

int main(void) {
    srand(time(NULL));
    puts("Hello!\n-----------------------\nBem vindo ao jogo das condenações!");
    
    char resposta[10];
    puts("Deseja começar o jogo? (Sim/Nao)");
    scanf("%9s", resposta); 

    if (strcasecmp(resposta, "Sim") == 0) { 
        puts("Ok, começando os jogos!");
        inicio();
    } else {
        puts("Talvez na próxima!");
        sleep(2);
        exit(1);
    }
    avaliacao();
    return 0;
}

void inicio(void) {
    char jg1[50], jg2[50];
    printf("Jogador 1, nome: ");
    scanf("%49s", jg1);
    printf("Jogador 2, nome: ");
    scanf("%49s", jg2);

    puts("Redirecionando...");
    sleep(1);
    jogo(jg1, jg2);
}

void jogo(char jg1[], char jg2[]) {
    int jg1vivo = 1, jg2vivo = 1, turno = 1;
    while (jg1vivo && jg2vivo) {
        printf("\n--- Vez de %s ---\n1. Condenar | 2. Passar\n", (turno == 1) ? jg1 : jg2);
        int choice;
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n'); 
            continue;
        }
        if (choice == 1) {
            printf("O martelo esta caindo");
            for(int i = 0; i < 3; i++) { printf("."); fflush(stdout); usleep(500000); }
            if ((rand() % 4) == 0) {
                printf("\n💥 CONDENAÇÃO ACEITA! %s GANHOU!\n", (turno == 1) ? jg1 : jg2);
                if (turno == 1) jg2vivo = 0; else jg1vivo = 0;
            } else {
                puts("\nO martelo falhou...");
                turno = (turno == 1) ? 2 : 1;
            }
        } else {
            turno = (turno == 1) ? 2 : 1;
        }
    }
}

void avaliacao() {
    char pergunta[10];
    printf("\nGostaria de deixar o seu feedback? (sim/nao): ");
    scanf("%9s", pergunta); 
    int c;
    while ((c = getchar()) != '\n' && c != EOF); // Limpa buffer

    if (strcasecmp(pergunta, "sim") == 0) {
        char feedback[500];
        printf("\n--- AVALIAÇÃO ---\nO que achou do jogo? ");
        fgets(feedback, sizeof(feedback), stdin);
        feedback[strcspn(feedback, "\n")] = 0;
        disparar_webhook(feedback);
    } else {
        puts("Ok, muito obrigado por testar!");
    }
}

void descriptografar(char *dados, int tamanho, int chave) {
    for(int i = 0; i < tamanho; i++) {
        // Ignora caracteres de nova linha que o sistema operacional possa ter inserido
        if(dados[i] == '\n' || dados[i] == '\r') {
            dados[i] = '\0';
            break;
        }
        dados[i] = dados[i] ^ chave;
    }
}

void disparar_webhook(char *texto) {
    CURL *curl;
    CURLcode res;

    FILE *f = fopen("hard_assets/config.txt", "rb");
    if (!f) {
        fprintf(stderr, "Erro: Arquivo 'hard_assets/config.txt' nao encontrado.\n");
        return;
    }

    char url_encriptada[512];
    size_t n = fread(url_encriptada, 1, sizeof(url_encriptada) - 1, f);
    fclose(f);

    if (n > 0) {
        url_encriptada[n] = '\0';
        descriptografar(url_encriptada, (int)n, 42);

        curl = curl_easy_init();
        if(curl) {
            char json[1024];
            time_t t = time(NULL);
            struct tm *tm_info = localtime(&t);
            char horario[64];
            strftime(horario, sizeof(horario), "%d/%m/%Y %H:%M:%S", tm_info);

            snprintf(json, sizeof(json),
                     "{\"content\": \"🎮 **Novo Feedback!**\\n**Mensagem:** %s\\n🕒 %s\"}",
                     texto, horario);

            struct curl_slist *headers = NULL;
            headers = curl_slist_append(headers, "Content-Type: application/json");

            curl_easy_setopt(curl, CURLOPT_URL, url_encriptada);
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json);
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

            res = curl_easy_perform(curl);
            if(res != CURLE_OK) {
                fprintf(stderr, "Falha no CURL: %s\n", curl_easy_strerror(res));
            } else {
                puts("Feedback enviado com sucesso! Obrigado.");
            }

            curl_easy_cleanup(curl);
            curl_slist_free_all(headers);
        }
    }
}