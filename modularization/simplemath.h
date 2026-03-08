#ifndef simple_math_H
#define simple_math_H
#include <string.h>
#include <errno.h>
#include <stdio.h>
static inline int Expressao(int n1, int n2, char operaçao[]){
    
    if (strcmp(operaçao, "su")==0){
        int resposta=n1-n2;
        return resposta;
    }
    if (strcmp(operaçao, "ad")==0)
    {
        int resposta=n1+n2;
        return resposta;
    }
    if (strcmp(operaçao, "div")==0)
    {
        if (n1==0 || n2==0){
            perror("Não é possivel dividir um número por 0. origem do erro: simplemath.h");
            return 1;
        }
        int resposta=n1/n2;
        return resposta;
    }
    
    if (strcmp(operaçao, "mult")==0){
        int resposta=n1*n2;
        return resposta;
    }
    if (strcmp(operaçao, "pot")==0){
        for (int i; i<n2; i++){
            n1=n1*n1;
        }
        int resultado=n1;
        return resultado;
    }
    if(strcmp(operaçao, "frdm")){//fração para decimal
        float resultado=n1/n2;
        return resultado;
    }
    else{
        perror("Operação inválida.")
    }
}
#endif