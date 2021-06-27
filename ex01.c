/*Exercício 1. [Ponteiros] Um ponteiro pode ser usado para dizer a uma função onde ela deve depositar
o resultado de seus cálculos. Escreva uma função que converta uma quantidade de minutos na notação
horas/minutos. A função recebe como parâmetro:
• um número inteiro (totalMinutos); e
• os endereços de duas variáveis inteiras, horas e minutos.
A função deve então atribuir valores às variáveis passadas por referência, de modo que os valores atribuídos
respeitem as seguintes condições:
minutos < 60
60 ∗ horas + minutos = totalMinutos
Escreva também a função principal (main) que use a função desenvolvida.*/

#include <stdio.h>

void conversor(int *totalMin, int *h, int *min){
    if(*totalMin < 60){
        *h = 0;
        *min = *totalMin % 60;
    } else {
        *h = *totalMin / 60;
        *min = *totalMin % 60;
    }
}

int main(){
    int totalMinutos, horas, minutos;

    printf("Digite a quantidade de minutos a serem convertidos: ");
    scanf("%d", &totalMinutos);

    conversor(&totalMinutos, &horas, &minutos);

    printf("Horas: %d\nMinutos: %d\n", horas, minutos);

    return 0;
}