#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REGISTROS_MAXIMOS 100

// os dados bin sao usados pra armazenar as informacoes como se fosse um arquivo
// txt so que criptografado para que os arquivos nao sejam perdidos apos a
// finalizaçao do programa

struct Registro {
  char nome[50];
  char email[50];
  char senha[20];
  float horario[20];
};

void Cadastrar(struct Registro *registros, int *numeroRegistros) {
  if (*numeroRegistros < REGISTROS_MAXIMOS) {
    printf("Digite o nome: ");
    scanf(" %[^\n]", registros[*numeroRegistros].nome);

    printf("Digite o email: ");
    scanf(" %[^\n]", registros[*numeroRegistros].email);

    printf("Digite a senha: ");
    scanf(" %[^\n]", registros[*numeroRegistros].senha);

    printf("Digiite o horario: ");
    scanf("%f", registros[*numeroRegistros].horario);

    (*numeroRegistros)++;
    printf("Registro cadastrado com sucesso.\n");
  } else {
    printf("Limite de registros atingido.\n");
  }
}

void MostrarRegistros(struct Registro *registros, int numeroRegistros) {
  if (numeroRegistros > 0) {
    printf("\nRegistros:\n");
    for (int i = 0; i < numeroRegistros; i++) {
      printf("Nome: %s\n", registros[i].nome);
      printf("Email: %s\n", registros[i].email);
      printf("Horário: %.f\n", *registros[i].horario);
      printf("------------------------\n");
    }
  } else {
    printf("Nenhum registro encontrado.\n");
  }
}

void deletarRegistro(struct Registro *registros, int *qtdRegistros) {
  char email[50];
  printf("Digite o email do registro a ser excluído: ");
  scanf(" %[^\n]", email);

  for (int i = 0; i < *qtdRegistros; i++) {
    if (strcmp(registros[i].email, email) == 0) {
      // Substituir o registro a ser excluído pelo último registro
      registros[i] = registros[*qtdRegistros - 1];
      (*qtdRegistros)--;
      printf("Registro excluído com sucesso.\n");
      return;
    }
  }
  printf("Registro não encontrado.\n");
}

void alterarHorario(struct Registro *registros, int qtdRegistros) {
  char email[50];
  printf("Digite o email do registro a qual voce cadastrou seu horario: ");
  scanf(" %[^\n]", email);

  for (int i = 0; i < qtdRegistros; i++) {
    if (strcmp(registros[i].email, email) == 0) {

      printf("Digite seu novo horario: ");
      scanf("%f", registros[i].horario);

      printf("Registro alterado com sucesso.\n");
      return;
    }
  }

  printf("Registro não encontrado.\n");
}

// salvando o arquivo

void salvarEmArquivo(struct Registro *registros, int qtdRegistros) {
  FILE *arquivo;

  if ((arquivo = fopen("dados.bin", "wb")) == NULL) {
    printf("Erro ao abrir o arquivo para escrita.\n");
    exit(1);
  }

  fwrite(registros, sizeof(struct Registro), qtdRegistros, arquivo);

  fclose(arquivo);
}

// carregando o arquivo apos a saida no dados.bin
void Arquivo(struct Registro *registros, int *qtdRegistros) {
  FILE *arquivo;

  if ((arquivo = fopen("dados.bin", "rb")) != NULL) {
    *qtdRegistros =
        fread(registros, sizeof(struct Registro), REGISTROS_MAXIMOS, arquivo);
  }
}

int main() {
  struct Registro registros[REGISTROS_MAXIMOS];
  int numeroRegistros = 0;

  Arquivo(registros, &numeroRegistros);
  int opcao;
  do {
    printf("\nAgende seu horario conosco:\n");
    printf("1. Cadastrar\n");
    printf("2. Mostrar Cadastros\n");
    printf("3. Escluir Cadastros\n");
    printf("4. Alterar horario\n");
    printf("5. Sair\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);

    switch (opcao) {
    case 1:
      Cadastrar(registros, &numeroRegistros);
      break;
    case 2:
      MostrarRegistros(registros, numeroRegistros);
      break;
    case 3:
      deletarRegistro(registros, &numeroRegistros);
      break;
    case 4:
      alterarHorario(registros, numeroRegistros);
      break;
    case 5:
      printf("Saindo...\n");
      salvarEmArquivo(registros, numeroRegistros);
      break;
    default:
      printf("Opção inválida.\n");
    }
  } while (opcao != 5);

  return 0;
}