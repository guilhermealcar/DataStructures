#include <stdio.h>
#include <ctype.h> //isalpha
#include <stdbool.h> //bool
#include <stdlib.h> //exit

typedef struct{
    int key;
    float weight;
    float height;
    char name[50];
    char sex;
} Register;

typedef struct listNode *ptrListNode;

typedef struct listNode{
    Register element;
    ptrListNode next;
    ptrListNode last;
} listNode;

typedef struct{
    ptrListNode start;
    int size;
} OrderedList;

// Booleano para a lista vazia
bool isempty(OrderedList *ol){
    return(ol->start == 0);
}

// Inicia a Lista Ordenada
void startList(OrderedList *ol){
    ol->start = NULL;
    ol->size = 0;
}

// Insere novo elemento a lista
void pushList(OrderedList *ol, Register reg){
    ptrListNode new = (ptrListNode)malloc(sizeof(listNode));
    new->element = reg;

    // Lista vazia ou elemento na cabeca
    if(isempty(ol) || reg.key < ol->start->element.key){
        new->next = ol->start;
        new->last = NULL;
        if(!isempty(ol))
            ol->start->last = new;

        ol->start = new;
    }

    // Lista nao esta vazia
    else{
        ptrListNode tmp = ol->start;

        while((tmp->next != NULL) && (reg.key > tmp->next->element.key))
            tmp = tmp->next;

        new->next = tmp->next;
        new->last = tmp;

        if(new->next != NULL)
            new->next->last = new;

        tmp->next = new;
    }

    ol->size++;
}

// Pesquisa elemento na lista
bool searchList(OrderedList *ol, int key){
    if(isempty(ol))
        return false;
    else{
        ptrListNode goThrough = ol->start;
        while(goThrough != NULL && key >= goThrough->element.key){
            if(goThrough->element.key == key)
                return true;

            goThrough = goThrough->next;
        }
        return false;
    }
}

// Tamanho da lista
int sizeofList(OrderedList *ol){
    return(ol->size);
}

// Remove o primeiro
ptrListNode peekFirst(OrderedList *ol, Register *reg){
    ptrListNode tmp;

    if(ol->start != NULL && ol->start->next == NULL){
        tmp = ol->start;
        ol->start->last == NULL;
        ol->start = NULL;
        ol->size--;
    } else if(!isempty(ol)){
        tmp = ol->start;
        ol->start = tmp->next;
        ol->start->last = tmp->last;
        ol->size--;
    }

    return tmp;
}

// Remove o ultimo
ptrListNode peekLast(OrderedList *ol, Register *reg){
    ptrListNode goThrough = ol->start;
    ptrListNode tmp, result;

    if(ol->start != NULL && ol->start->next == NULL){
        ol->start = NULL;
        ol->size--;
    } else if(!isempty(ol)){
        while(goThrough->next != NULL){
            tmp = goThrough;
            goThrough = goThrough->next;
            result = goThrough;
        }

        tmp->next = NULL;
        goThrough->next = tmp;
        ol->size--;
    }

    return result;
}

// Remove elemento
ptrListNode peek(OrderedList *ol, int key, Register *reg){
    ptrListNode goThrough = ol->start;
    ptrListNode result;

    if(isempty(ol) || key < ol->start->element.key || !searchList(ol, key)){
        printf("Lista vazia ou elemento nao encontrado\n");
        return false;
    } else if(key == ol->start->element.key){
        result = peekFirst(ol, reg);
        return result;
    } else {
        while(goThrough->next != NULL && key > goThrough->next->element.key)
            goThrough = goThrough->next;

        result = goThrough->next;
        goThrough->next = goThrough->next->next;
        ol->size--;
        return result;
    }
}

//////// Main
int main(int argc, char **argv){
    OrderedList ol;
    ptrListNode tmp;
    Register reg;

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

    // Abrindo arquivo de entrada
    FILE *file1;
    file1 = fopen(argv[1], "r");
    if(file1 == NULL){
        printf("Erro ao abrir o arquivo de entrada\n");
        system("pause");
        exit(1);
    }

    // Abrindo o arquivo de saida
    FILE *file2;
    file2 = fopen(argv[2], "w");
    if(file2 == NULL){
        printf("Erro ao abrir o arquivo de saida\n");
        system("pause");
        exit(1);
    }

    // Tamanho e verificacao do arquivo
    fseek(file1, 0, SEEK_END);
    int fileSize = ftell(file1);
    if(fileSize == 0){
        printf("Nao ha nada no arquivo de entrada\n");
        system("pause");
        exit(1);
    }

    // Condicoes para o decorrer do problema
    fseek(file1, 0, SEEK_SET);
    char characters;
    int lines=0;
    int occurences=0;
    int option;
    int specific;

    while((characters = fgetc(file1)) != EOF){
        // Conta as linhas
        if(characters == '\n')
            lines++;

        // Conta as ocorrencias de registro
        if(characters == '}')
            occurences++;

        fscanf(file1, "%d\n", &option);
        fscanf(file1, "%d\n", &specific);
    }

    fseek(file1, 0, SEEK_SET);

    startList(&ol);

    while(fscanf(file1, "{%d,%50[^,],%c,%f,%f}\n", &reg.key, &reg.name, &reg.sex, &reg.weight, &reg.height) != EOF && occurences > 0){
        if(!isalpha(reg.sex)){
            printf("O sexo do paciente deve ser um unico caracter\n");
            system("pause");
            exit(1);
        } else if(searchList(&ol, reg.key)){
            printf("Esse codigo ja existe\n");
            system("pause");
            exit(1);
        }
        pushList(&ol, reg);
        occurences--;
    }

    // Opcao 1 para ordem crescente
    if(option == 1){
        printf("\nRegistro em ordem crescente\n");
        for(int i=0; i<sizeofList(&ol); i){
            tmp = peekFirst(&ol, &reg);
            fprintf(file2, "{%d,%s,%c,%.1f,%.1f}\n", tmp->element.key, tmp->element.name, tmp->element.sex, tmp->element.weight, tmp->element.height);
        }
    }

    // Opcao 2 para ordem decrescente
    else if(option == 2){
        printf("\nRegistro em ordem decrescente\n");
        for(int i=0; i<sizeofList(&ol); i){
            if(sizeofList(&ol) == 1)
                tmp = peekFirst(&ol, &reg);
            else
                tmp = peekLast(&ol, &reg);

            fprintf(file2, "{%d,%s,%c,%.1f,%.1f}\n", tmp->element.key, tmp->element.name, tmp->element.sex, tmp->element.weight, tmp->element.height);
        }
    }

    else if(option == 3){
        printf("\nRegistro especifico\n");
        tmp = peek(&ol, specific, &reg);
        if(tmp != false)
            fprintf(file2, "{%d,%s,%c,%.1f,%.1f}\n", tmp->element.key, tmp->element.name, tmp->element.sex, tmp->element.weight, tmp->element.height);
        else
            fprintf(file2, "Codigo nao existente na lista\n");
    }

    fclose(file1);
    fclose(file2);

    return 0;
}
