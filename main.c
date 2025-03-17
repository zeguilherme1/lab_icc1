#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int id;
  char nome[100];
  int idade;
  float saldoAtual;
}
Usuario;

typedef struct {
  Usuario * DB;
  int size;
  int capacity;
}
vector;

// arrow function > 
// (pointer_name) -> (variable_name);
// foo->bar == (*foo).bar;

/* To do
	organizar melhor usando header;
	assert em funcoes que aceitam ponteiro como vectorInit pra checar se um ponteiro não é NULL;
	assert vector capacity >= size;
	manter found = -1 se no final do for não ter encontrado o ID;
*/
void vectorInit(vector * array) {
  array -> DB = malloc(10 * sizeof(Usuario));
  if (!array -> DB) {
    printf("MALLOC ERROR\n");
    exit(1);
  }
  array -> size = 0;
  array -> capacity = 10;
}

void resizeVector(vector * array) {
  int updateCapacity = (int)(array -> capacity * 1.5);
  Usuario * updateDB = realloc(array -> DB, updateCapacity * sizeof(Usuario));
  if (!updateDB) {
    printf("MALLOC ERROR\n");
    exit(1);
  }
  array -> DB = updateDB;
  array -> capacity = updateCapacity;
}

void addUser(vector * array, int id, char * nome, int idade, float saldoAtual) {
  if (array -> size >= array -> capacity) {
    resizeVector(array);
  }

  //foo->bar == (*foo).bar;
  array -> DB[array -> size].id = id;
  strncpy(array -> DB[array -> size].nome, nome, sizeof(array -> DB[array -> size].nome) - 1);
  array -> DB[array -> size].nome[sizeof(array -> DB[array -> size].nome) - 1] = '\0';
  array -> DB[array -> size].idade = idade;
  array -> DB[array -> size].saldoAtual = saldoAtual;

  array -> size++;
}

void removeUser(vector * array, int id) {
  int found = -1;
  for (int i = 0; i < array -> size; i++) {
    if (array -> DB[i].id == id) {
      found = i;
      break;
    }
  }
  for (int i = found; i < array -> size; i++) {
    array -> DB[i] = array -> DB[i + 1];
  }
  array -> size--;
}

void printVector(vector * array) {
  if (array -> size == 0) {
    printf("O Banco de dados está vazio \n");
    return;
  }

  printf("\nLista de pessoas no banco de dados: \n");
  for (int i = 0; i < array -> size; i++) {
    printf("ID: %d, Nome: %s, Idade: %d, Saldo Atual: %.2f\n",
      array -> DB[i].id, array -> DB[i].nome, array -> DB[i].idade, array -> DB[i].saldoAtual);
  }
}

void cleanVector(vector * array) {
  free(array -> DB);
}

void clearBuffer(void) {
  int c;
  while ((c = getchar()) != '\n' && c != EOF);
}

void insertUser(vector * Usuarios, int n) {
  for (int i = 0; i < n; i++) {
    char nome[100];
    int idade;
    float saldoAtual;

    printf("\nDigite o nome do usuário: ");
    scanf(" %[^\n]", nome);

    nome[strcspn(nome, "\n")] = '\0';

    printf("Digite a idade: ");
    scanf("%d", & idade);

    clearBuffer();

    printf("Digite o saldo atual: ");
    scanf("%f", & saldoAtual);

	clearBuffer();

    if (saldoAtual <= 0) {
      printf("Não é possível inserir um saldo negativo\n");
      exit(1);
    }
    addUser(Usuarios, Usuarios -> size + 1, nome, idade, saldoAtual);
  }
}

void transfSaldo(vector * Usuarios, int id1, int id2, float valor) {
  if (id1 == id2) {
    printf("Os ID's devem ser diferentes");
    return;
  }
  if (valor <= 0) {
    printf("O valor a ser transferido deve ser positivo: ");
    return;
  }

  Usuario * remetente = NULL, * destinatario = NULL;
  for (int i = 0; i < Usuarios -> size; i++) {
    if (Usuarios -> DB[i].id == id1) {
      remetente = & Usuarios -> DB[i];
    }
    if (Usuarios -> DB[i].id == id2) {
      destinatario = & Usuarios -> DB[i];
    }
  }
  if (remetente == NULL || destinatario == NULL) {
    printf("ID's inválidos\n");
    return;
  }

  if (remetente -> saldoAtual < valor) {
    printf("Saldo insuficiente para transferência");
    return;
  }

  remetente -> saldoAtual -= valor;
  destinatario -> saldoAtual += valor;

  printf("Transferência de %.2f realizada com sucesso\n\n", valor);

}

int main() {
  vector Usuarios;
  vectorInit( & Usuarios);

  while (1) {
    printf("Insira uma opção: \n");
    printf("[0] Listar usuários, [1] Inserir novos usuários, [2] Transferência de Saldo, [3] Excluir um usuário ou [4] para fechar o programa\n");

    int option;
    scanf("%d", & option);
    clearBuffer();

    if (option == 0) {
      printVector( & Usuarios);
    } else if (option == 1) {
      int n;
      printf("Insira quantos usuários quer inserir no DB: \n");
      scanf("%d", & n);
      insertUser( & Usuarios, n);
      printVector( & Usuarios);
    } else if (option == 2) {
      int id1, id2;
      printf("Insira o primeiro ID: \n");
      scanf("%d", & id1);
      printf("Insira o segundo ID: \n");
      scanf("%d", & id2);

      float valor;
      printf("Insira o valor a ser transferido: \n");
      scanf("%f", & valor);

      transfSaldo( & Usuarios, id1, id2, valor);
    } else if (option == 3) {
      int id1;
      printf("Insira o ID que deseja remover:\n");
      scanf("%d", & id1);

      removeUser( & Usuarios, id1);
      printf("Usuário removido\n");
    } else if (option == 4) {
      cleanVector( & Usuarios);
      printf("Fechando programa...\n");
      break;
    } else {
      printf("Opção inválida, tente novamente!\n");
    }
  }

  return 0;
}
