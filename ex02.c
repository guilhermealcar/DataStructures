/*Exercício 2. [Arquivos] Faça um programa que receba do usuário um arquivo texto. Crie outro arquivo
texto de saída contendo o texto do arquivo de entrada original, porém substituindo todas as vogais pelo
caractere ‘*’. Além disso, mostre na tela quantas linhas esse arquivo possui. Dentro do programa faça
o controle de erros, isto é, insira comandos que mostre se os arquivos foram abertos com sucesso, e caso
contrário, imprima uma mensagem de erro encerrando o programa*/

#include <stdio.h>

int main(){
    FILE *arq1, *arq2;
    arq1 = fopen("old.txt", 'r');
    arq2 = fopen("new.txt", 'w');

    // Se houver erro na abertura do arquivo
    if(arq1 == NULL || arq2 == NULL){ 
        printf("Erro ao abrir o arquivo!\n");
        exit(1);
    }

    int linhas=0;
    char letra;

    

    return 0;
}