#include <stdio.h>
#include <ctype.h> //isalpha
#include <stdbool.h> //bool
#include <stdlib.h> //exit

#define MAXSIZE 5

/////// Pilha Estática
typedef struct{
    int value;
}Object;

typedef struct{
    Object array[MAXSIZE];
    int top;
}staticStack;

Object top(staticStack *ss){
    return(ss->array[ss->top-1]);
}

// Booleano para pilha estatica vazia
bool isempty(staticStack *ss){
    return(ss->top == 0);
}

// Booleano para pilha estatica cheia
bool isfull(staticStack *ss){
    return(ss->top == MAXSIZE);
}

// Inicia a pilha Estatica
void startStaticStack(staticStack *ss){
    ss->top = 0;
}

// Empilha a pilha Estatica
void push(Object data, staticStack *ss){
    if(!isfull(ss)){
        ss->array[ss->top] = data;
        ss->top++;
    } else {
        printf("Warning: nao foi possivel inserir - pilha cheia\n");
    }
}

// Desempilha a pilha estatica
int peek(Object *data, staticStack *ss){
    if(!isempty(ss)){
        *data = ss->array[ss->top-1];
        ss->top--;
    } else {
        printf("Warning: nao foi possivel remover - pilha vazia\n");
    }
    return(ss->top);
}

// Tamanho da pilha estatica
int sizeofStaticStack(staticStack *ss){
    return(ss->top);
}

void printStaticStack(staticStack *ss){
    printf("\n Pilha = {");
    for(int i=0; i<ss->top; i++){
        printf("%d ", ss->array[i]);
    }
    printf("}\n");
}

/////// Pilha Dinâmica
typedef struct node *ptrNode;

typedef struct node{
    int valueD;
    ptrNode next;
}node;

typedef struct{
    ptrNode topD;
    int sizeofD;
}dynamicStack;

// Booleano para pilha dinamica vazia
bool isEmptyD(dynamicStack *ds){
    return(ds->sizeofD == 0);
}

// Inicia a pilha dinamica
void startDynamicStack(dynamicStack *ds){
    ds->topD = NULL;
    ds->sizeofD = 0;
}

// Empilha a pilha dinamica
void pushD(dynamicStack *ds, int value){
    // Aloca dinamicamente
    ptrNode aux = malloc(sizeof(ptrNode));

    aux->valueD = value;
    aux->next = ds->topD;
    ds->topD = aux;
    ds->sizeofD++;
}

// Desempilha a pilha dinamica
int peekD(dynamicStack *ds){
    int v = -999;
    if(!isEmptyD(ds)){
        ptrNode aux;
        aux = ds->topD;
        v = aux->valueD;
        ds->topD = aux->next;
        free(aux);
        ds->sizeofD--;
    } else {
        printf("Warning: nao foi possivel remover - pilha vazia\n");
    }
    return (v);
}

// Tamanho da pilha dinamica
int sizeofDynamicStack(dynamicStack *ds){
    return(ds->sizeofD);
}

void printDynamicStack(dynamicStack *ds){
    ptrNode ptr;
    printf("\n Pilha = {");
    for(ptr=ds->topD; ptr != NULL; ptr = ptr->next){
        printf("%d ", ptr->valueD);
    }
    printf("}\n");
}

/////// Main
int main(int argc, char **argv){
    staticStack ss;
    Object obj;

    // Caso nao tenha parametros no argc
    if(argc < 2){
        printf("Nenhum parametro fornecido\n");
        system("pause");
        exit(1);
    }

    // Caso tenha apenas um arquivo fornecido no argv
    if(argc == 2){
        printf("Nao foram fornecidos parametros suficientes\n");
        system("pause");
        exit(1);
    }

    // Abrindo primeiro arquivo
    FILE *file1;
    file1 = fopen(argv[1], "r");
    if(file1 == NULL){
        printf("Erro ao abrir o arquivo de entrada!\n");
        system("pause");
        exit(1);
    }

    // Abrindo o segundo arquivo
    FILE *file2;
    file2 = fopen(argv[2], "w");
    if(file2 == NULL){
        printf("Erro ao abrir o arquivo de saida!\n");
        system("pause");
        exit(1);
    }

    // Tamanho e verificacao do arquivo de entrada
    fseek(file1, 0, SEEK_END);
    int fileSize = ftell(file1);
    if(fileSize == 0){
        printf("Nao ha nada no arquivo\n");
        system("pause");
        exit(1);
    }

    // Condicoes para o decorrer do problema
    fseek(file1, 0, SEEK_SET);
    char characters;
    int letter=0;
    int lines=0;
    while((characters = fgetc(file1)) != EOF){
        // Se nao forem inteiros
        if(characters == '.'){
            printf("Ha numeros que nao sao inteiros no arquivo\n");
            system("pause");
            exit(2);
        }

        // Apenas o primeiro caracter do arquivo deve ser uma letra
        if(isalpha(characters)){
            letter++;
        }
        if(letter > 1){
            printf("Apenas o primeiro caracter do arquivo deve ser uma letra\n");
            system("pause");
            exit(2);
        }

        // Conta as linhas
        if(characters == '\n'){
            lines++;
        }
    }

    // 'e' para pilha estática e 'd' para pilha dinâmica
    fseek(file1, 0, SEEK_SET);
    while((characters = fgetc(file1)) != EOF){
        if(characters != 'e' && characters != 'd'){
            printf("A primeira letra do arquivo deve ser 'e' ou 'd'\n");
            system("pause");
            exit(3);
        } else if (characters == 'e'){
            // Pilha Estatica
            startStaticStack(&ss);

            while(!feof(file1)){
                fscanf(file1, "%d", &obj.value);
                push(obj, &ss);
            }

            printStaticStack(&ss);
            printf("Tamanho da pilha estatica: %d\n", sizeofStaticStack(&ss));

            int result;
            while(lines <= sizeofStaticStack(&ss)){
                result = peek(&obj, &ss);
            }

            printStaticStack(&ss);
            printf("Tamanho da pilha estatica: %d\n", sizeofStaticStack(&ss));

            for(int i=0; i<sizeofStaticStack(&ss);){
                // Recebe os valores em ordem contraria
                result = peek(&obj, &ss);

                char binary[50];
                int a=0;

                if(result==0){
                    binary[a] = 0;
                    fprintf(file2, "%d", binary[a]);
                } else if(result==1){
                    binary[a] = 1;
                    fprintf(file2, "%d", binary[a]);
                } else {
                    while(result > 0){
                        binary[a] = result % 2;
                        a++;
                        result /= 2;
                    }
                }

                for(int i=a-1; i>=0; i--){
                    fprintf(file2, "%d", binary[i]);
                }
                fprintf(file2, "\n");
            }

            printStaticStack(&ss);
            printf("Tamanho da pilha estatica: %d\n", sizeofStaticStack(&ss));
            break;
        } else if(characters == 'd'){
            // Pilha Dinamica
            dynamicStack dStack1, dStack2;
            int aux;

            startDynamicStack(&dStack1);
            startDynamicStack(&dStack2);

            while(!feof(file1)){
                fscanf(file1, "%d", &aux);
                pushD(&dStack1, aux);
            }

            int result;
            while(lines <= sizeofDynamicStack(&dStack1)){
                result = peekD(&dStack1);
            }

            printDynamicStack(&dStack1);
            printf("Tamanho da pilha dinamica: %d\n", sizeofDynamicStack(&dStack1));

            for(int i=0; i<sizeofDynamicStack(&dStack1);){
                // Recebe os valores em ordem contraria
                result = peekD(&dStack1);

                if(result==0){
                    fprintf(file2, "%d", result);
                } else {
                    while(result > 0){
                        aux = result % 2;
                        result /= 2;
                        pushD(&dStack2, aux);
                    }
                }

                while(!isEmptyD(&dStack2)){
                    aux = peekD(&dStack2);
                    fprintf(file2, "%d", aux);
                }
                fprintf(file2, "\n");
            }

            printDynamicStack(&dStack1);
            printf("Tamanho da pilha dinamica 1: %d\n", sizeofDynamicStack(&dStack1));

            printDynamicStack(&dStack2);
            printf("Tamanho da pilha dinamica 2: %d\n", sizeofDynamicStack(&dStack2));
            break;
        }
    }
    
    fclose(file1);
    fclose(file2);
    
    return 0;
}