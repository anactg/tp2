#include "racionais.h"
#include <stdlib.h>
#include <stdio.h>

/* Funcoes privadas restritas a este modulo.
 * Voce deve implementa-las pois serao necessarias,
 * embora elas nao precisem estar no .h */

/* Função auxiliar para calcular o máximo divisor comum */
int mdc(int a, int b) {
    if (b == 0)
        return a;
    return mdc(b, a % b);
}

/* Função auxiliar para calcular o mínimo múltiplo comum */
int mmc(int a, int b) {
    return (a * b) / mdc(a, b);
}


void simplifica_r(struct racional *r) {
    int divisor;

    /* Calcula o máximo divisor comum (mdc) entre o numerador e o denominador */
    divisor = mdc(r->num, r->den);

    /* Simplifica o racional dividindo o numerador e o denominador pelo mdc */
    r->num /= divisor;
    r->den /= divisor;

    /* Se ambos numerador e denominador forem negativos, transforma para positivo */
    if (r->num < 0 && r->den < 0) {
        r->num = -r->num;
        r->den = -r->den;
    }

    /* Se o denominador for negativo, move o sinal para o numerador */
    if (r->den < 0) {
        r->num = -r->num;
        r->den = -r->den;
    }
}

/* Cria um número racional com base nas informações dos parâmetros */
struct racional cria_r(int numerador, int denominador) {
    struct racional r;

    r.num = numerador;
    r.den = denominador;
    if (denominador == 0)
        r.valido = 0;
    else
        r.valido = 1;

    simplifica_r(&r);

    return r;
}

/* Retorna um número racional gerado aleatoriamente */
struct racional sorteia_r(int n) {
    int numerador, denominador;

    numerador = rand() % (2 * n + 1) - n;
    denominador = rand() % (2 * n + 1) - n;
    if (denominador == 0)
        return cria_r(0, 0);
    else
        return cria_r(numerador, denominador);
}

/* Retorna o numerador do racional */
int numerador_r(struct racional r) {
    return r.num;
}

/* Retorna o denominador do racional */
int denominador_r(struct racional r) {
    return r.den;
}

/* Retorna 1 se o racional é válido ou 0 caso contrário */
int valido_r(struct racional r) {
    return r.valido;
}

/* Retorna a soma (simplificada) dos racionais r1 e r2 */
void soma_r(struct racional r1, struct racional r2, struct racional *r3) {
    r3->num = r1.num * r2.den + r2.num * r1.den;
    r3->den = r1.den * r2.den;
    r3->valido = r1.valido && r2.valido;
    simplifica_r(r3);
}

/* Retorna a subtração dos racionais r1 e r2 */
void subtrai_r(struct racional r1, struct racional r2, struct racional *r3) {
    r2.num *= -1; /* invertendo o sinal para realizar a subtração */
    soma_r(r1, r2, r3);
}

/* Retorna a multiplicação dos racionais r1 e r2 */
void multiplica_r(struct racional r1, struct racional r2, struct racional *r3) {
    r3->num = r1.num * r2.num;
    r3->den = r1.den * r2.den;
    r3->valido = r1.valido && r2.valido;
    simplifica_r(r3);
}

/* Retorna 1 se a divisão dos racionais r1 e r2 é válida, caso contrário retorna 0 */
int divide_r(struct racional r1, struct racional r2, struct racional *r3) {
    if (r2.num == 0) {
        r3->valido = 0;
        return 0;
    }

    r2.num = r2.num < 0 ? -r2.num : r2.num;
    r2.den = r2.den < 0 ? -r2.den : r2.den;

    r3->num = r1.num * r2.den;
    r3->den = r1.den * r2.num;
    r3->valido = r1.valido && r2.valido;
    simplifica_r(r3);

    return 1;
}

/* Retorna -1 se r1 < r2; 0 se r1 == r2; 1 se r1 > r2 */
int compara_r(struct racional r1, struct racional r2) {
    int num1, num2;

    if (!r1.valido || !r2.valido)
        return -2; /* indeterminado */

    num1 = r1.num * r2.den;
    num2 = r2.num * r1.den;

    if (num1 < num2)
        return -1;
    else if (num1 > num2)
        return 1;
    else
        return 0;
}

/* Imprime um racional */
void imprime_r(struct racional r) {
    if (!r.valido) {
        printf("INVALIDO");
        return;
    }

    if (r.num == 0) {
        printf("0");
        return;
    }

    if (r.den == 1) {
        printf("%d", r.num);
        return;
    }

    if (r.num == r.den) {
        printf("1");
        return;
    }

    if (r.num < 0 && r.den < 0) {
        r.num *= -1;
        r.den *= -1;
    }

    if (r.num < 0 || r.den < 0)
        printf("-");

    printf("%d/%d", abs(r.num), abs(r.den));
}

