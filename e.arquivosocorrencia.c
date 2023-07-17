#include <stdio.h>
#include <stdlib.h>

int main (){

 char arquivo [100] = "main.c";
 char busca[100] = "a";

 FILE *f = fopen (arquivo, "r");
 if (f==NULL) { printf("Sorry"); return 0;}



 int cont = 0;
 char str[1000];
 while (!feof(f)){
    fgets(str, 1000, f);
    char *ocorrencia = str;

 do {
    ocorrencia = strstr(ocorrencia, busca);
    if(ocorrencia != NULL){
        cont++;
        ocorrencia++;
        }
    }while (ocorrencia != NULL);
 }
 printf("encontrou %s %d vezes! ", busca, cont);
 }