#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
 char id[4];
 char nome[31];
 char sexo;
 int idade;
 char areaEsp[31];
 char telefone[15];
}Professor;


/*---------------------------------------------------------------------------- //
                     1 - Registros de Tamanho Fixo
//---------------------------------------------------------------------------- */

void escreverRegistrosTamanhoFixo(FILE* arqE, Professor *p, int linhas){

  int aux1, aux2;

  for (int i = 0 ; i < linhas-1; i++) {
    fprintf(arqE,"%s|%s", p[i].id, p[i].nome);
      aux1 = 30 - strlen(p[i].nome) ;
        for (int j = 0 ; j < aux1; j++) {
          fprintf(arqE," ");
        }//for

    fprintf(arqE,"|%c|%d|%s", p[i].sexo, p[i].idade, p[i].areaEsp);
      aux2 = 30 - strlen(p[i].areaEsp) ;
        for (int k = 0 ; k < aux2; k++) {
          fprintf(arqE," ");
        }//for

    fprintf(arqE,"|%s|\n", p[i].telefone);
  }//for

}//escreverRegistrosTamanhoFixo

void lerRegistrosTamanhoFixo(FILE* arqS, Professor *p, int linhas){

  fseek(arqS, 0, SEEK_SET);

  for (int i = 0; i < linhas-1; i++) {
    fscanf(arqS,"%[^|]s|%30[^|]|%c|%d|%30[^|]|%14[^|]|", &p[i].id, &p[i].nome, &p[i].sexo, &p[i].idade, &p[i].areaEsp, &p[i].telefone);
  }//while

}//lerRegistrosTamanhoFixo


/*---------------------------------------------------------------------------- //
                    2 - Registros com Indicadores de Tamanho
//---------------------------------------------------------------------------- */
void escreverRegistrosIndicadoresTamanho(FILE* arqE, Professor *p, int linhas){

  int tam;

  for (int i = 0; i < linhas-1; i++) {
    tam = strlen(p[i].id) + strlen(p[i].nome) + strlen(p[i].areaEsp) + strlen(p[i].telefone) + 9;
    fprintf(arqE,"%d %s|%s|%c|%d|%s|%14s|", tam, p[i].id, p[i].nome, p[i].sexo, p[i].idade, p[i].areaEsp, p[i].telefone);
  }//for

}//escreverRegistrosIndicadoresTamanho

void lerRegistrosIndicadoresTamanho(FILE* arqS, Professor *p, int linhas){

  int aux;

  for (int i = 0; i < linhas-1; i++) {
    fscanf(arqS,"%d %3[^|]|%30[^|]|%c|%d|%30[^|]|%14[^|]|", aux, &p[i].id, &p[i].nome, &p[i].sexo, &p[i].idade, &p[i].areaEsp, &p[i].telefone);
  }//for

}//lerRegistrosIndicadoresTamanho


/*---------------------------------------------------------------------------- //
                        3 - Registros de Delimitadores
//---------------------------------------------------------------------------- */
void escreverRegistrosDelimitadores(FILE* arqE, Professor *p, int linhas){

  fprintf(arqE,"%s", p[0].id);

  for (int i = 0; i < linhas-1; i++) {
    if(i > 0){
      fprintf(arqE,"#%s", p[i].id);
    }
    fprintf(arqE,"|%s|%c|%d|%s|%s|", p[i].nome, p[i].sexo, p[i].idade, p[i].areaEsp, p[i].telefone);
  }//for

}//escreverRegistrosDelimitadores

void lerRegistrosDelimitadores(FILE* arqS, Professor *p, int linhas){

  fseek(arqS, 0, SEEK_SET);

  for (int i = 0; i < linhas - 1; i++) {
    if (i != 0 ) {
      fscanf(arqS,"#");
    }
    fscanf(arqS,"%3[^|]|%30[^|]|%c|%d|%30[^|]|%14[^|]|", &p[i].id, &p[i].nome, &p[i].sexo, &p[i].idade, &p[i].areaEsp, &p[i].telefone);
  }//for
}//lerRegistrosDelimitadores


/*---------------------------------------------------------------------------- //
                 Função para printar no arquivo de persistencia
//---------------------------------------------------------------------------- */

void printArq(FILE* arqP, Professor *p, int linhas){
  for (int i = 0; i < linhas-1; i++) {
    fprintf(arqP,"{%3s,%s,%c,%d,%s,%s}\n", p[i].id, p[i].nome, p[i].sexo, p[i].idade, p[i].areaEsp, p[i].telefone);
  }//for
}


/*---------------------------------------------------------------------------- //
                                    Main
//---------------------------------------------------------------------------- */

int main(int argc, char const *argv[]) {

  if(argc!=4){
    printf(" Sao necessarios 4 argumentos por parametro\n" );
    exit(1);
  }

  FILE *arqE, *arqS, *arqP;
  Professor *p;
  int n = 0, linhas = 0, metodo, arquivo, auxID;
  char caracter;

  arqE = fopen(argv[1],"r");// abre um arquivo para leitura
  arqS = fopen(argv[2],"w+");// abre um arquivo para escrita
  arqP = fopen(argv[3],"w");// abre o arquivoP.txt para escrita
  /*arqE = fopen("arquivoE.txt","r");// abre o arquivoE.txt para leitura
  arqS = fopen("arquivoS.txt","w+");// abre o arquivoS.txt para escrita
  arqP = fopen("arquivoP.txt","w");// abre o arquivoP.txt para escrita
*/
  if(arqE == NULL || arqS == NULL || arqP == NULL){ // Verifica se não ocorreu um erro ao tentar abrir os arquivos
    printf(" Erro ao executar o arquivo / ou arquivo inexistente\n");
    exit(1);
  }//if

  while( (caracter = fgetc(arqE)) != EOF ){
    if (caracter == '\n'){//conta quantas linhas o arquivoE possui
      linhas++;
    }//if
  }

  arquivo = ftell(arqE);//pega o tamanho do arquivoE
    fseek(arqE, 0, SEEK_SET);

  if (arquivo == 0) {//se o tamanho do arquivoE for igual a 0 o programa é encerrado
    fprintf(arqS, " Arquivo de entrada vazio!\n");
    exit(1);
  }

  p = (Professor*)malloc(linhas * sizeof(Professor));

  while( n < linhas-1){

    if (!fscanf(arqE,"{%3[^,],%30[^,],%c,%d,%30[^,],%14[^,]}\n", &p[n].id, &p[n].nome, &p[n].sexo, &p[n].idade, &p[n].areaEsp, &p[n].telefone)) {
      fprintf(arqS," Arquivo fora do formato!\n");
      exit(1);
    }

    auxID = atoi(p[n].id);
    // Controle para que o codigo tenha no maximo 3 digitos
    if(auxID < 0 || auxID > 999){
      fprintf(arqS," ID invalida!\n");
      exit(1);

      // Controle de erro para o sexo ser dado como F, M ou N
    }else if(p[n].sexo != 'F' && p[n].sexo != 'f' && p[n].sexo != 'M' && p[n].sexo != 'm' && p[n].sexo != 'N' && p[n].sexo != 'n'){
      fprintf(arqS," Sexo invalido!\n");
      exit(1);

    // Controle de erro para a idade possuir 2 digitos
    }else if(p[n].idade < 10 || p[n].idade > 99){
      fprintf(arqS," Idade invalida!\n");
      exit(1);
    }

    // Pega o metodo a ser usado
    fscanf(arqE,"%d", &metodo);
    n++;
  }

  // envia para as funcoes de registro
  if (metodo == 1) {
    escreverRegistrosTamanhoFixo(arqS, p, linhas);
    lerRegistrosTamanhoFixo(arqS, p, linhas);
    printArq(arqP, p, linhas);

  }else if(metodo == 2){
    escreverRegistrosIndicadoresTamanho(arqS, p, linhas);
    lerRegistrosIndicadoresTamanho(arqS, p, linhas);
    printArq(arqP, p, linhas);

  }else if(metodo == 3){
    escreverRegistrosDelimitadores(arqS, p, linhas);
    lerRegistrosDelimitadores(arqS, p, linhas);
    printArq(arqP, p, linhas);

  }else{
    printf(" Metodo invalido\n");
    fprintf(arqS," Metodo invalido\n");
    exit(1);
  }

  //Libera a memória
  free(p);

 //Fecha os arquivos
  fclose(arqE);
  fclose(arqS);
  fclose(arqP);

  return 0;
}//main
