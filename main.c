#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
void inicio(void);
void jogo(char jg1[], char jg2[]);

int main(void) {
    srand(time(NULL));

    puts("Hello!");
    puts("-----------------------");
    puts("Bem vindo ao jogo das condenações!");
    
    char resposta[10];
    puts("Deseja começar o jogo? (Sim/Nao)");
    scanf("%s", resposta);

    if (strcasecmp(resposta, "Sim") == 0) { 
        puts("Ok, começando os jogos!");
        inicio();
    } else {
        puts("Talvez na próxima!");
        sleep(2.5);
        exit(1);
    }

    return 0;
}

void inicio(void) {
    char jg1[50], jg2[50];

    printf("Jogador 1, por favor digite seu nome: ");
    scanf("%s", jg1);
    printf("Jogador 2, digite seu nome: ");
    scanf("%s", jg2);

    puts("Redirecionando para o jogo...");
    jogo(jg1, jg2);
}

void jogo(char jg1[], char jg2[]) {
    int jg1vivo = 1;
    int jg2vivo = 1;
    int turno = 1;

    while (jg1vivo && jg2vivo) {
        printf("\n--- Vez de %s ---\n", (turno == 1) ? jg1 : jg2);
        puts("Escolha: 1. Condenar | 2. Passar o martelo");
        
        int choice;
        scanf("%d", &choice);

        if (choice == 1) {
            int sorteio = rand() % 4; 
            
            if (sorteio == 0) {
                printf("CONDENAÇÃO ACEITA! %s GANHOU!\n", (turno == 1) ? jg1 : jg2);
                if (turno == 1) jg2vivo = 0; else jg1vivo = 0;
            } else {
                printf("O martelo falhou... A vez passou.\n");
                turno = (turno == 1) ? 2 : 1;
            }
        } else {
            puts("Passando o martelo...");
            turno = (turno == 1) ? 2 : 1;
        }
    }
}
void avaliacao(){
    char avaliacao[500];
    while (getchar()!="\n")
    printf("O que achou do jogo? ");
    scanf(" %[^\n]", avaliacao); 
    disparar_webhook(avaliacao);
}
char disparar_webhook(char avaliacao){

}