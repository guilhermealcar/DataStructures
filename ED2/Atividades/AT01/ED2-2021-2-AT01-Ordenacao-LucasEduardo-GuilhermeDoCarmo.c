#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

typedef struct{
  int compara;
}Conta;

/******************************************************************************
                Função de troca de ordem de elementos do vetor
/******************************************************************************/

void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

/******************************************************************************
                              Insertion Sort
/******************************************************************************/
void insertionSort(int *v, int n, Conta *cont) {

  int i, j, chosen;

  for(i = 1; i < n; i++) {

    chosen = v[i];
    j = i-1;

    while(j>=0 & chosen < v[j]) {
      v[j+1] = v[j];
      j = j-1;
      cont->compara++;
    }//while
    cont->compara++;

    v[j+1] = chosen;
  }//for

}//insertionSort

/******************************************************************************
                                Selection Sort
/******************************************************************************/

void selectionSort(int *v, int n, Conta *cont) {

  int i, j, min;
  for(i = 0; i < n-1; i++) {
    cont->compara++;
    min = i;

    for(j = i+1; j < n; j++) {
      cont->compara++;
      if(v[j] < v[min]) {
        min = j;
      }//if
    }//for

    if(i != min) {
      swap(&v[i], &v[min]);
    }//if

  }//for

}//selectionSort

/******************************************************************************
                                Bubble Sort
/******************************************************************************/

void bubbleSort(int *v, int n, Conta *cont) {

  bool changed = true;

  while(changed) {
    changed = false;

    for(int i = 0; i < n-1; i++) {
      if(v[i] > v[i+1]) {
        swap(&v[i], &v[i+1]);
        changed = true;
      }//if
      cont->compara++;
    }//for
    //cont->compara++;

  }//while

}//bubbleSort

/******************************************************************************
                                Merge Sort
/******************************************************************************/

void merge(int *v, int start, int middle, int end, Conta *cont) {

  int vecSize = (end - start) + 1;

  int *temp = (int*) malloc(vecSize * sizeof(int));

  int i, j, k, p1, p2;

  bool finished1, finished2;
  finished1 = 0;
  finished2 = 0;

  p1 = start;
  p2 = middle + 1;

  if(temp != NULL) {

    for(i = 0; i < vecSize; i++) {
      cont->compara++;
      if(!finished1 && !finished2) {
        if(v[p1] < v[p2]) {
          temp[i] = v[p1];
          p1++;
        } else {
          temp[i] = v[p2];
          p2++;
        }//else

        if(p1 > middle) finished1 = 1;
        if(p2 > end)    finished2 = 1;

      } else {

        if(!finished1){
          temp[i] = v[p1];
          p1++;
        }else{
          temp[i] = v[p2];
          p2++;
        }//else

      }//else

    }//for

  }//if

    for( j=0,k=start; j<vecSize; j++, k++) {
      cont->compara++;
      v[k] = temp[j];
    }//for

  free(temp);
}//merde

void mergeSort(int *v, int start, int end, Conta *cont) {

  int middle;

  if(start < end) {
    cont->compara++;
    middle = (int)floor((start + end)/2);
    mergeSort(v, start, middle, cont);
    mergeSort(v, middle+1, end, cont);
    merge(v, start, middle, end, cont);
  }//if

}//mergeSort

/******************************************************************************
                                  Quick Sort
/******************************************************************************/

int particiona(int *V, int inicio, int fim, Conta *cont){

  int esq = inicio;
  int dir = fim;
  int pivo = V[inicio];
  int aux;

  while(esq < dir){
    cont->compara++;
    while(V[esq] <= pivo && esq <= fim){
      cont->compara++;
      esq++;
    }//while
    while(V[dir] > pivo && dir >= inicio){
      cont->compara++;
      dir--;
    }//while

    if (esq < dir) {
      aux = V[esq];
      V[esq] = V[dir];
      V[dir] = aux;
    }//if
  }//while

  aux = V[dir];
  V[dir] = V[inicio];
  V[inicio] = aux;

  return dir;
}//particiona

void quickSort(int *V, int inicio, int fim, Conta *cont){
  int pivo;

  if(inicio < fim){
    cont->compara++;
    pivo = particiona(V, inicio, fim, cont);
    quickSort(V, inicio, pivo-1, cont);
    quickSort(V, pivo+1, fim, cont);
  }//if
}//quickSort

/******************************************************************************/
/******************************************************************************/

void printArray(int *v, int tam, FILE *arqS) {

  for(int i = 0; i < tam; i++) {
    fprintf(arqS, "%d ", v[i]);
  }//for
}//printArray

/******************************************************************************/
/******************************************************************************/


int main(int argc, char const *argv[]) {

/*
  if(argc!=3){
    printf(" Apenas 3 argumentos sao aceitos\n" );
    exit(1);
  }
*/
  FILE *arqE, *arqS;
  Conta cont;
  int n, start, ms, arquivo, *V, *Vi, *Vs, *Vb, *Vm, *Vq;
  char caracter;

  //arqE = fopen(argv[1],"r");// abre um arquivo para leitura
  //arqS = fopen(argv[2],"w");// abre um arquivo para escrita
  arqE = fopen("arquivoE.txt","r");// abre o arquivoEntrada.txt para leitura
  arqS = fopen("arquivoS.txt","w");// abre o arquivoSaida.txt para escrita

  if(arqE == NULL || arqS == NULL ){ // Verifica se não ocorreu um erro ao tentar abrir os arquivos
    printf(" Erro ao executar o arquivo / ou arquivo inexistente\n");
    exit(1);
  }//if

  fseek(arqE, 0, SEEK_END);
    arquivo = ftell(arqE);//pega o tamanho do arquivoE
  fseek(arqE, 0, SEEK_SET);

  if (arquivo == 0) {//se o tamanho do arquivoE for igual a 0 o programa é encerrado
    printf(" O arquivo esta vazio\n");
    exit(1);
  }

// ler o tamanho do vetor a ser gerado e o caractere que define se o vetor será em ordem crescente ou decrescente
  fscanf(arqE,"%d\n%c\n", &n, &caracter);

// verifica se o caractere é alguma das opções disponiveis
  if(caracter != 'c' && caracter != 'C' && caracter != 'd' && caracter != 'D' && caracter != 'r' && caracter != 'R'){
    fprintf(arqS, " Arquivo de entrada invalido!\n");
    exit(1);
  }

  V = (int *) malloc(n * sizeof(int));
  Vi = (int *) malloc(n * sizeof(int));
  Vs = (int *) malloc(n * sizeof(int));
  Vb = (int *) malloc(n * sizeof(int));
  Vm = (int *) malloc(n * sizeof(int));
  Vq = (int *) malloc(n * sizeof(int));

  srand(time(NULL));

  //Gerando o vetor original de forma crescente e Fazendo as cópias do vetor original
  if (caracter == 'c' || caracter == 'C') {

    for (int i = 0; i < n; i++){
      V[i] = i+1;
      printf(" %d ", V[i]);
      Vi[i] = V[i];
      Vs[i] = V[i];
      Vb[i] = V[i];
      Vm[i] = V[i];
      Vq[i] = V[i];
    }
      printf("\n %c \n", caracter);

  //Gerando o vetor original de forma decrescente e Fazendo as cópias do vetor original
  }else if(caracter == 'd' || caracter == 'D'){

    for (int i = n-1; i >= 0; i--){
      V[i] = i+1;
      printf(" %d ", V[i]);
      Vi[i] = V[i];
      Vs[i] = V[i];
      Vb[i] = V[i];
      Vm[i] = V[i];
      Vq[i] = V[i];
    }
      printf("\n %c \n", caracter);

  //Gerando o vetor original com valores random e Fazendo as cópias do vetor original
  }else{

    for (int i = 0; i < n; i++){
      V[i] = (rand() % 32000);
      printf(" %d ", V[i]);
      Vi[i] = V[i];
      Vs[i] = V[i];
      Vb[i] = V[i];
      Vm[i] = V[i];
      Vq[i] = V[i];
    }
    printf("\n %c \n", caracter);
  }

  //Chamando os métodos de ordenação e printando no arquivo os vetores ordenados

  cont.compara = 0;
  start = clock();
    insertionSort(Vi, n, &cont);
      ms = (int)((clock()-start)*1000/CLOCKS_PER_SEC);
        fprintf(arqS," insertionSort: ");
          printArray(Vi, n, arqS);
            fprintf(arqS,", %d comp, %d ms", cont.compara, ms);

  start = clock();
  cont.compara = 0;
    selectionSort(Vs, n, &cont);
      ms = (int)((clock()-start)*1000/CLOCKS_PER_SEC);
        fprintf(arqS,"\n selectionSort ");
          printArray(Vs, n, arqS);
            fprintf(arqS,", %d comp, %d ms", cont.compara, ms);

  cont.compara = 0;
  start = clock();
    bubbleSort(Vb, n, &cont);
      ms = (int)((clock()-start)*1000/CLOCKS_PER_SEC);
        fprintf(arqS,"\n bubbleSort: ");
          printArray(Vb, n, arqS);
            fprintf(arqS,", %d comp, %d ms", cont.compara, ms);

  cont.compara = 0;
  start = clock();
    mergeSort(Vm, 0, n-1, &cont);
      ms = (int)((clock()-start)*1000/CLOCKS_PER_SEC);
        fprintf(arqS,"\n mergeSort: ");
          printArray(Vm, n, arqS);
            fprintf(arqS,", %d comp, %d ms", cont.compara, ms);

  cont.compara = 0;
  start = clock();
    quickSort(Vq, 0, n-1, &cont);
      ms = (int)((clock()-start)*1000/CLOCKS_PER_SEC);
        fprintf(arqS,"\n quickSort: ");
          printArray(Vq, n, arqS);
            fprintf(arqS,", %d comp, %d ms", cont.compara, ms);

 //libera a memória alocada para os vetores
    free(V);
    free(Vi);
    free(Vs);
    free(Vb);
    free(Vm);
    free(Vq);
 //fecha os arquivos
   fclose(arqE);
   fclose(arqS);

  return 0;
}//main