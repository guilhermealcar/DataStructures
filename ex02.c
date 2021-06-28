/*Exercício 2. [Arquivos] Faça um programa que receba do usuário um arquivo texto. Crie outro arquivo
texto de saída contendo o texto do arquivo de entrada original, porém substituindo todas as vogais pelo
caractere ‘*’. Além disso, mostre na tela quantas linhas esse arquivo possui. Dentro do programa faça
o controle de erros, isto é, insira comandos que mostre se os arquivos foram abertos com sucesso, e caso
contrário, imprima uma mensagem de erro encerrando o programa*/

#include <stdlib.h>
#include <stdio.h>


int main() {
    FILE *arq, *arq2;
    arq = fopen("ex02old.txt","r");
    arq2 = fopen("ex02new.txt","w");

    // Se houver erro na abertura do arquivo
    if(arq == NULL || arq2 == NULL ){
        printf("Erro ao abrir o arquivo!");
        exit(1);
    }
    
    int linhas = 1;
    char letra;

    while((letra = fgetc(arq)) != EOF ){
        if(letra == 'A' || letra == 'a' || letra == 'E' || letra == 'e' || letra == 'I' || letra == 'i' || letra == 'O' || letra == 'o' || letra == 'U' || letra == 'u'){
            letra = '*';
        }
        fprintf(arq2, "%c", letra);

        if(letra == '\n'){
            linhas++;
        }
    }

    printf("O arquivo possui %d linhas.\n", linhas);

    fclose(arq);
    fclose(arq2);

    return 0;
}