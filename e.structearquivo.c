#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
//Vinicius Horacio Marques Povoa
typedef struct horario Horario;
typedef struct registro Registro;
char fputs
struct horario{
    int ano;
    int mes;
    int dia;
    int hora;
    int min;
};

struct registro{
    char placa[8];
    char modelo[10];
    char cor[10];
    char status;
    Horario entrada, saida;
};

void imprimehorario(Horario h){
  printf("Ano: %d / Mes: %d / Dia: %d / H: %d / M: %d\n", h.ano, h.mes, h.dia, h.hora, h.min);

  return;
}

void imprimir_registro(Registro r){
  printf("Placa: %s\n", r.placa);
  printf("Modelo: %s\n", r.modelo);
  printf("Cor: %s\n", r.cor);
  printf("Status: %c\n", r.status);
  printf("Entrada: "); imprimehorario(r.entrada);
  printf("Saida: "); imprimehorario(r.saida);

  return;
}

//FUNCAO VALIDA HORARIO
int validarhorario(Horario hora){
  if(hora.mes < 1 || hora.mes > 12)
    return -1;
  if(hora.dia < 1)
    return -1;
  int bissexto = 0;
  if ((hora.ano % 400 == 0) || ((hora.ano % 4 == 0) && (hora.ano % 100 != 0)))
    bissexto = 1;
  if(bissexto && hora.mes == 2 && hora.dia > 29) return -1;
  if((hora.mes == 1 || hora.mes == 3 || hora.mes == 5 || hora.mes == 7 || hora.mes == 8 || hora.mes == 10 || hora.mes == 12) && hora.dia > 31)
    return -1;
  if((hora.mes == 4 || hora.mes == 6 || hora.mes == 9 || hora.mes == 11) && hora.dia > 30)
    return -1;
  if(hora.hora < 0 || hora.hora > 23)
    return -1;
  if(hora.min < 0 || hora.min > 59)
    return -1;

  return 0;
}




int inserir(FILE *f) {
    if(f == NULL) return -1;
    Registro registronovo;
    //CADASTRO PLACA, MODELO, COR
    registronovo.status = 'P';
    printf("Digite a placa: ");
    scanf("%s", registronovo.placa);
    printf("Digite o modelo: ");
    scanf("%s", registronovo.modelo);
    printf("Digite a cor: ");
    scanf("%s", registronovo.cor);
    //HORARIO DE ENTRADA
    printf("Digite o horario de entrada (ano, mes, dia, hora e minuto, abaixo): \n");
    printf("Digite o ano:\n");
    scanf("%d",&registronovo.entrada.ano);
    printf("Digite o mes:\n");
    scanf("%d",&registronovo.entrada.mes);
    printf("Digite o dia:\n");
    scanf("%d",&registronovo.entrada.dia);
    printf("Digite a hora:\n");
    scanf("%d",&registronovo.entrada.hora);
    printf("Digite o minuto:\n");
    scanf("%d",&registronovo.entrada.min);
    //HORARIO DE SAIDA
    printf("Digite o horario de saida (ano, mes, dia, hora e min, abaixo): \n");
    printf("Digite o ano:\n");
    scanf("%d",&registronovo.saida.ano);
    printf("Digite o mes:\n");
    scanf("%d",&registronovo.saida.mes);
    printf("Digite o dia:\n");
    scanf("%d",&registronovo.saida.dia);
    printf("Digite a hora:\n");
    scanf("%d",&registronovo.saida.hora);
    printf("Digite o minuto:\n");
    scanf("%d",&registronovo.saida.min);

    if(validarhorario(registronovo.entrada) || validarhorario(registronovo.saida)){
      printf("Data(s)/Horario(s) fornecidos são inválidos.\n");
      return -1;
    }

    fwrite(&registronovo, sizeof(Registro), 1, f);

    return 0;
}

void Horario contatempo(int hEntrada, int hSaida){
    Horario tempoEstacionado;
    tempoEstacionado.ano = hSaida.ano - hEntrada.ano;
    tempoEstacionado.mes = hSaida.mes - hEntrada.mes;
    if(hSaida.dia < hEntrada.dia){
      if(hEntrada.mes == 2 && (hEntrada.ano)%400==0) ((hEntrada. ano)%4==0)&& ((hEntrada.ano)%100!=0);{
        tempoEstacionado.dia = 29 - hEntrada.dia + hSaida.dia;
      }
      else if(hEntrada.mes==2){
        tempoEstacionado.dia = 28 - hEntrada.dia + hSaida.dia;
      }
      else if (horarioEntradames == 1 || hEntrada.mes == 3 || hEntrada.mes == 5 || hEntrada.mes == 7|| hEntrada. mes == 8 || hEntrada. mes == 10 || hEntrada. mes == 12){
      tempoEstacionado.dia = 31 - hEntrada.dia + hSaida.dia;
      }
      tempoEstacionado. dia = 30 - hEntrada. dia + hSaida. dia;
        }
      else {
      tempoEstacionado. dia = hSaida. dia - hEntrada. dia;
    }
    tempoEstacionado.hora = hSaida.hora - hEntrada.hora;
    tempoEstacionado.min = hSaida.min - hEntrada.min;
      if(tempoEstacionado.min < 0){
        tempoEstacionado.min += 60;
        tempoEstacionado.hora -= 1;
      }
      if(tempoEstacionado.hora < 0){
        tempoEstacionado.hora += 24;
        tempoEstacionado.dia -= 1;
      }
      if(tempoEstacionado.mes < 0){
        tempoEstacionado. mes += 12;
        tempoEstacionado.ano -= 1;
      }
}


void alterar(FILE *f) {
  int i = 1;
  int escolha;
  char buscar[8];
  printf("Qual a placa do registro que deseja alterar :  \n");
  scanf("%s", buscar); printf("\n");

  Registro rgi;

  rewind(f);
  while(fread(&rgi, sizeof(rgi), 1, f)> 0){
    if(strcmp(rgi.placa, buscar) == 0 && rgi.status == 'P'){
      printf("\nRegistro %d: \n",i);

      imprimir_registro(rgi);


      printf("Digite a opcao desejada : \n");
      printf("1 - Alterar registro \n");
      printf("2 - Nao alterar registro\n");
      scanf("%d", &escolha);

      if(escolha == 1){
        int opcao;
        while(1){
           printf("Qual das opçoes vai ser alterada: \n");
                    printf("1 - Placa\n");
                    printf("2 - Modelo\n");
                    printf("3 - Cor\n");
                    scanf("%d", &opcao);

                    if(opcao < 1 || opcao > 5){
                      printf("Nao existe essa opcao!");
                    }
                    else if(opcao == 1){
                      printf("Placa: ");
                      scanf("%s", rgi.placa);

                      fseek(f, -sizeof(Registro), SEEK_CUR);
                      fwrite(&rgi, sizeof(Registro), 1, f);
                    }
                    else if(opcao == 2){
                      printf("Modelo: ");
                      scanf("%s", rgi.modelo);

                      fseek(f, -sizeof(Registro), SEEK_CUR);
                      fwrite(&rgi, sizeof(Registro), 1, f);
                    }
                    else if(opcao == 3){
                      printf("Cor: ");
                      scanf("%s", rgi.cor);
                    }

                    else if (opcao == 4){
                        printf("Digite o horario de entrada (ano, mes, dia, hora e minuto, abaixo): \n");
                        printf("Digite o ano:\n");
                        scanf("%d",&rgi.entrada.ano);
                        printf("Digite o mes:\n");
                        scanf("%d",&rgi.entrada.mes);
                        printf("Digite o dia:\n");
                        scanf("%d",&rgi.entrada.dia);
                        printf("Digite a hora:\n");
                        scanf("%d",&rgi.entrada.hora);
                        printf("Digite o minuto:\n");
                        scanf("%d",&rgi.entrada.min);
                        validarhorario(rgi.entrada);
                        fseek(f, -sizeof(Registro), SEEK_CUR);
                        fwrite(&rgi, sizeof(Registro), 1, f);
                    }

                    else if (opcao == 4){
                        printf("Digite o horario de saida (ano, mes, dia, hora e min, abaixo): \n");
                        printf("Digite o ano:\n");
                        scanf("%d",&rgi.saida.ano);
                        printf("Digite o mes:\n");
                        scanf("%d",&rgi.saida.mes);
                        printf("Digite o dia:\n");
                        scanf("%d",&rgi.saida.dia);
                        printf("Digite a hora:\n");
                        scanf("%d",&rgi.saida.hora);
                        printf("Digite o minuto:\n");
                        scanf("%d",&rgi.saida.min);
                        validarhorario(rgi.saida);
                        fseek(f, -sizeof(Registro), SEEK_CUR);
                        fwrite(&rgi, sizeof(Registro), 1, f);
                    }


                    printf("Confirme : \n");
                    printf("1 - Alterar registro \n");
                    printf("2 - Nao alterar registro\n");
                    scanf("%d", &opcao);
              if(opcao == 2){
                break;
              }
        }
      }
      i++;
    }
  }
}
void remover(FILE *f) {

  Registro remove;
  int i = 1;
  int escolha;
  char placaBusc[8];
  printf("Digite a placa para ser removida: ");
  scanf("%s", placaBusc);
  printf("\n");

  rewind(f);
  while(fread(&remove, sizeof(remove),1,f)> 0){
    if(strcmp(remove.placa, placaBusc) == 0 && remove.status == 'P'){
      printf("Registro: %d: \n", i);

      imprimir_registro(remove);

      printf("Digite a opcao desejada : \n");
      printf("1 - Apagar registro \n");
      printf("2 - Nao apagar registro\n");
      scanf("%d", &escolha);

      if(escolha == 1){
         printf("O registro foi apagado!");
         fseek(f, -sizeof(Registro), SEEK_CUR);
                remove.status = 'R';
                fwrite(&remove, sizeof(Registro), 1, f);
                    }
                i++;
            }
        }
    }

void buscar(FILE *f){
    Registro rg;
    char placabusc[8];
    printf("Digite a placa para ser buscada: ");
    scanf("%s", placabusc);
    printf("\n");

    rewind(f);
    while(fread(&rg, sizeof(rg), 1,f)> 0){
      if(strcmp(rg.placa, buscar) == 0 && rg.status == 'P'){
        imprimir_registro(rg);
        }
    }
}

int listar(FILE *f) {
    if(f == NULL)
    return -1;
    rewind(f);
    Registro re;
    while(fread(&re, sizeof(re), 1, f)> 0){
      if(re.status == 'P' || re.status == ''){
      imprimir_registro(re);
        }
    }
}

int main() {
    FILE *f = fopen("arqipce.txt", "rb+");
    if(f == NULL)
      f = fopen("arqipce.txt", "wb+");
    if(f == NULL){
      printf("Não foi possivel abrir o arquivo.\n");
      return -1;
    }

    int opcao = -1;
    while (opcao != 0) {

        printf("\n========ESTACIONAMENTO IPC - Digite a opcao desejada!========");
        printf("\n\n 0 - Sair do programa\n 1 - Inserir Cadastro\n 2 - Alterar Cadastro \n 3 - Remover Cadastro\n 4 - Buscar Cadastro\n 5 - Listar Cadastros\n");
        printf("\n Opcao: ");
        scanf(" %d",&opcao);
        switch(opcao) {
            case 1: inserir(f); break;
            case 2: alterar(f); break;
            case 3: remover(f); break;
            case 4: buscar(f); break;
            case 5: listar(f); break;
            printf("\n\n\n");
        }
    }

    fclose(f);
    return 0;
}
