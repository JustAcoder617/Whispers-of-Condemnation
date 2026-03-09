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
        if (n1==0)
        {
            return 0;
        }
        if (n2==0)
        {
            return 1;
        }
        if (n1==1)
        {
            return 1;
        }
        //para fins de preservação de memória, usamos os if's acima para não ter que usar memória atoa.
        
        
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
static inline dist2d(double x1, double y1, double x2, double y2){
    return sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
}
static inline double quadrado(double x){
    return x * x;
}
static inline double cubo(double x){
    return x * x * x;
}
static inline double clamp(double v, double min, double max){
    if(v < min) return min;
    if(v > max) return max;
    return v;
}
static inline double min_max(double a,double b){
    return (a < b) ? a : b;
}
#endif