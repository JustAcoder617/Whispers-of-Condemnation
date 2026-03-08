#ifndef SIMPLE_MATH_H
#define SIMPLE_MATH_H

#include <string.h>
#include <stdio.h>

static inline int Expressao(int n1, int n2, char operacao[]) {
    
    if (strcmp(operacao, "su") == 0) return n1 - n2;
    if (strcmp(operacao, "ad") == 0) return n1 + n2;
    if (strcmp(operacao, "mult") == 0) return n1 * n2;

    if (strcmp(operacao, "div") == 0) {
        if (n2 == 0) {
            fprintf(stderr, "Erro: Divisao por zero em simple_math.h\n");
            return 0;
        }
        return n1 / n2;
    }

    if (strcmp(operacao, "pot") == 0) {
        int resultado = 1;
        for (int i = 0; i < n2; i++) {
            resultado *= n1;
        }
        return resultado;
    }

    if (strcmp(operacao, "frdm") == 0) {
        return (n2 != 0) ? (n1 / n2) : 0;
    }

    fprintf(stderr, "Erro: Operacao '%s' invalida.\n", operacao);
    return -1;
}



static inline int tamanho_check(int var_check, int tamanho_max) {
    if (var_check > tamanho_max) return 2;
    if (var_check < tamanho_max) return 0;
    return 1;
}

#endif