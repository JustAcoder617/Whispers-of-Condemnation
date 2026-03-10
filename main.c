#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <curl/curl.h>
#include "modularization/cweb.h"
#include "modularization/simplemath.h"

/* * Copyright (C) 2024 - Jogo das Condenações 
 * Licença: GPLv2
 */

void inicio(char *user_login);
void jogo(char jg1[], char jg2[], char *user_login);
void avaliacao(char *user_login);

int main(void) {
    srand(time(NULL));
    char user_login[50];

    puts("-----------------------\nBem vindo ao jogo das condenações!");
    printf("Digite seu username de desenvolvedor/jogador: ");
    scanf("%49s", user_login);

    char resposta[10];
    puts("Deseja começar o jogo? (Sim/Nao)");
    scanf("%9s", resposta); 

    if (strcasecmp(resposta, "Sim") == 0) { 
        puts("Ok, começando os jogos!");
        inicio(user_login);
    } else {
        puts("Talvez na próxima!");
    }

    avaliacao(user_login);
    return 0;
}

void inicio(char *user_login) {
    char jg1[50], jg2[50];
    printf("Jogador 1, nome: ");
    scanf("%49s", jg1);
    printf("Jogador 2, nome: ");
    scanf("%49s", jg2);

    puts("Redirecionando...");
    sleep(1);
    jogo(jg1, jg2, user_login);
}

void jogo(char jg1[], char jg2[], char *user_login) {
    int jg1vivo = 1, jg2vivo = 1, turno = 1;

    const char *frases_falha[] = {
        "O martelo falhou... O réu escapou por pouco!",
        "Sentença anulada por falta de provas.",
        "O juiz se distrai e o martelo erra o alvo!",
        "O martelo quebrou no meio do caminho..."
    };

    while (jg1vivo && jg2vivo) {
        char *atual = (turno == 1) ? jg1 : jg2;
        char *alvo = (turno == 1) ? jg2 : jg1;

        printf("\n--- Vez de %s ---\n1. Condenar | 2. Passar\n", atual);
        int choice;
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n'); 
            continue;
        }

        if (choice == 1) {
            printf("O martelo esta caindo");
            for(int i = 0; i < 3; i++) { 
                printf("."); 
                fflush(stdout); 
                usleep(500000); 
            }

            int sorteio = rand() % 5; 

            if (sorteio == 4) { 
                char possibilidades[] = {'s','s','s','s'}; 
                char escolha = char_aleatorio(possibilidades, 1);
                if (escolha == 's') {
                    printf("\n%s foi condenado sumariamente! %s vence!\n", alvo, atual);
                    if (turno == 1) jg2vivo = 0; else jg1vivo = 0;
                }
            } 
            else if (sorteio == 3) {
                char possibilidades[] = {'s','s','s','n'};
                sleep(1);
                char escolha = char_aleatorio(possibilidades, 1);
                if (escolha == 's') {
                    printf("\n%s CONDENOU %s no detalhe!!!!\n", atual, alvo);
                    if (turno == 1) jg2vivo = 0; else jg1vivo = 0;
                } else {
                    printf("\n%s\n", frases_falha[rand() % 4]);
                }
            }
            else if (sorteio == 2) {
                char possibilidades[] = {'s','s','n','n'}; 
                char escolha = char_aleatorio(possibilidades, 1);
                if (escolha == 's') {
                    printf("\n%s CONDENOU %s no detalhe!!!!\n", atual, alvo);
                    if (turno == 1) jg2vivo = 0; else jg1vivo = 0;
                } else {
                    printf("\n%s\n", frases_falha[rand() % 4]);
                }
            }
            else if (sorteio == 1) {
                char possibilidades[] = {'s','n','n','n'}; 
                char escolha = char_aleatorio(possibilidades, 1);
                if (escolha == 's') {
                    printf("\n%s CONDENOU %s no detalhe!!!!\n", atual, alvo);
                    if (turno == 1) jg2vivo = 0; else jg1vivo = 0;
                } else {
                    printf("\n%s\n", frases_falha[rand() % 4]);
                }
            }

            turno = (turno == 1) ? 2 : 1;
        } else {
            puts("Passando a vez...");
            turno = (turno == 1) ? 2 : 1;
        }
    }
    printf("\n--- FIM DE JOGO ---\nVoltando para avaliação...\n");
}

void avaliacao(char *user_login) {
    char pergunta[10];
    printf("\nGostaria de deixar o seu feedback, %s? (sim/nao): ", user_login);
    scanf("%9s", pergunta); 

    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    if (strcasecmp(pergunta, "sim") == 0) {
        char feedback[500];
        printf("\nO que achou do jogo? ");
        fgets(feedback, sizeof(feedback), stdin);
        feedback[strcspn(feedback, "\n")] = 0;

        int stars;
        puts("De 0 a 10, qual sua nota?");
        scanf("%d", &stars);

        int check_webhook = disparar_webhook(feedback, user_login, stars);
        if (check_webhook==1)
        {
            puts("Não foi possível enviar seu feedback, mas agradecemos por jogar!");
            exit(1);
        }
        puts("\nObrigado pelo feedback! Ele foi enviado com sucesso!");
        
    } else {
        puts("Até a próxima!");
    }
}