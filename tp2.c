#include "racionais.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    srand(0); // Inicializa a semente randômica

    int n, max;
    printf("Digite um valor para n (0 < n < 100): ");
    scanf("%d", &n);
    printf("Digite um valor para max (0 < max < 30): ");
    scanf("%d", &max);

    for (int i = 1; i <= n; i++) {
        printf("%d: ", i);

        struct racional r1 = sorteia_r(max);
        struct racional r2 = sorteia_r(max);

        printf("%d/%d %d/%d ", numerador_r(r1), denominador_r(r1), numerador_r(r2), denominador_r(r2));

        if (!valido_r(r1) || !valido_r(r2)) {
            printf("NUMERO INVALIDO\n");
            return 1;
        }

        struct racional soma, subtracao, multiplicacao, divisao;
        soma_r(r1, r2, &soma);
        subtrai_r(r1, r2, &subtracao);
        multiplica_r(r1, r2, &multiplicacao);
        if (!divide_r(r1, r2, &divisao)) {
            printf("DIVISAO INVALIDA\n");
            return 1;
        }

        printf("%d/%d %d/%d %d/%d %d/%d\n", numerador_r(soma), denominador_r(soma),
               numerador_r(subtracao), denominador_r(subtracao),
               numerador_r(multiplicacao), denominador_r(multiplicacao),
               numerador_r(divisao), denominador_r(divisao));
    }

    return 0;
}
