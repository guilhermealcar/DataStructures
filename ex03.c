/*Exercício 3. [Recursão] Escreva uma função recursiva para calcular o valor de um número inteiro de base
x elevada a um expoente inteiro y.*/

int potencia(int X, int Y){
    if(Y == 0)
        return 1;
    else if(Y>0)
        return X*potencia(X, Y-1);
}

int main(){
    int x, y, pot;

    printf("Digite o numero base da operacao: ");
    scanf("%d", &x);
    printf("Digite o expoente da operacao: ");
    scanf("%d", &y);

    pot = potencia(x, y);

    printf("%d elevado a %d e': %d\n", x, y, pot);

    return 0;
}