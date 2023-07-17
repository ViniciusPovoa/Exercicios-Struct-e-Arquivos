#include <stdio.h>
#include <stdlib.h>



int main (){

 struct pessoa_estatica {int cpf; char nome[20]; };
 struct pessoa_estatica p1 = {1213131, "Maria"}, p2;
 p2=p1;

 printf("P1 = %d %s\n", p1.cpf, p1.nome);
 printf("P2= %d %s\n", p2.cpf, p2.nome);

 struct pessoa_dinamica {int cpf; char *nome};
 struct pessoa_dinamica p3 = {921219291, NULL}, p4;

 p3.nome = (char*)malloc(20);
 strcpy(p3.nome, "Ana");

 p4=p3;

 printf("P3 = %d %s\n", p3.cpf, p3.nome );
 printf("P4 = %d %s\n", p4.cpf, p4.nome);
}