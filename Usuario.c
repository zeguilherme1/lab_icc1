#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Usuario.h"

void initVector(UserVector* array) {
    array->users    = malloc(10 * sizeof(User));

    if (array->users == NULL) {
        printf("MALLOC ERROR\n");
        exit(1);
    }

    array->size     = 0;
    array->capacity = 10;
}

void clearVectorMem(UserVector* array) { 
    free(array->users); 
}

void resizeVector(UserVector* array) {
    int newCapacity = (int) (array->capacity * 1.5);
    User* newUsers  = realloc(array->users, newCapacity * sizeof(User));

    if (newUsers == NULL) {
        printf("REALLOC ERROR\n");
        exit(1);
    }

    array->users    = newUsers;
    array->capacity = newCapacity;
}

void clearBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void printVector(UserVector* array) {
    if (array->size == 0) {
      printf("O Banco de dados está vazio \n");
      return;
    }
  
    printf("\nLista de pessoas no banco de dados: \n");
    for (int index = 0; index < array->size; index++) {
        printf(
            "ID: %d, Nome: %s, Idade: %d, Saldo Atual: %.2f\n", 
            array->users[index].id,
            array->users[index].name, 
            array->users[index].age, 
            array->users[index].balance
        );
    }
}

int contains(UserVector* array, int userId) {
    for (int index = 0; index < array->size; index++) {
      if (array->users[index].id == userId) {
        return index;
      }
    }

    return -1;
}

void addNewUser(UserVector* array, int id, int age, char* name, float balance) {
    if (array->size >= array->capacity) resizeVector(array);
  
    // foo->bar == (*foo).bar;
    array->users[array->size].id = id;
    strncpy(array->users[array->size].name, name, sizeof(array->users[array->size].name) - 1);
    array->users[array->size].name[sizeof(array->users[array->size].name) - 1] = '\0';
    array->users[array->size].age = age;
    array->users[array->size].balance = balance;
  
    array->size++;
  }

void insertUser(UserVector* Usuarios, int n) {
    for (int i = 0; i < n; i++) {
      char nome[100];
      int idade;
      float saldoAtual;
  
      printf("\nDigite o nome do usuário: ");
      scanf(" %[^\n]", nome);
  
      nome[strcspn(nome, "\n")] = '\0';
  
      printf("Digite a idade: ");
      scanf("%d", &idade);
  
      clearBuffer();
  
      printf("Digite o saldo atual: ");
      scanf("%f", &saldoAtual);
  
      clearBuffer();
  
      if (saldoAtual <= 0) {
        printf("Não é possível inserir um saldo negativo\n");
        exit(1);
      }
      addNewUser(Usuarios, Usuarios->size + 1, idade, nome, saldoAtual);
    }
  }

void deleteUser(UserVector* array, int userId) {
    int found = contains(array, userId);
    if (found == -1) {
        printf("Usuario nao encontrado, impossivel excluir.");
        return;
    }

    for (int index = found; index < array->size; index++) {
        array->users[index] = array->users[index + 1];
    }
    array->size--;
}

void transferBalance(UserVector* Usuarios, int id1, int id2, float valor) {
    if (id1 == id2) {
      printf("Os ID's devem ser diferentes");
      return;
    }
    if (valor <= 0) {
      printf("O valor a ser transferido deve ser positivo: ");
      return;
    }
  
    User *remetente = NULL, *destinatario = NULL;
    for (int i = 0; i < Usuarios->size; i++) {
      if (Usuarios->users[i].id == id1) {
        remetente = &Usuarios->users[i];
      }
      if (Usuarios->users[i].id == id2) {
        destinatario = &Usuarios->users[i];
      }
    }
    if (remetente == NULL || destinatario == NULL) {
      printf("ID's inválidos\n");
      return;
    }
  
    if (remetente->balance < valor) {
      printf("Saldo insuficiente para transferência");
      return;
    }
  
    remetente->balance -= valor;
    destinatario->balance += valor;
  
    printf("Transferência de %.2f realizada com sucesso\n\n", valor);
  }