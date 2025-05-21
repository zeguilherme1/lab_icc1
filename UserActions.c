#include<stdio.h>
#include<string.h>
#include "Utils.h"
#include "User.h"
#include "UserActions.h"

void addNewUser(UserVector* array) {
    int numberOfUsers;
    printf("Insira quantos usuários gostaria de inserir: ");
    scanf("%d", &numberOfUsers);

    char name[100];
    int age;
    float balance;
    for (int i = 0; i < numberOfUsers; i++) {
        memset(name, '\0', sizeof(name));

        printf("\nDigite o nome do usuário: ");
        scanf(" %[^\n]", name);
    
        name[strcspn(name, "\n")] = '\0';
    
        printf("Digite a idade: ");
        scanf("%d", &age);
    
        clearBuffer();
    
        printf("Digite o saldo atual: ");
        scanf("%f", &balance);
    
        clearBuffer();
    
        if (balance <= 0) {
            printf("Nao é possivel inserir um saldo negativo!\n");
            awaitResponse();
            return;
        }

        insertUser(array, array->size + 1, age, name, balance);
    }
}

void removeUser(UserVector *array) {
    int id;
    printf("Insira o ID que deseja remover: ");
    scanf("%d", &id);

    deleteUser(array, id);

    printf("Usuario Removido!");
}

void makeTransference(UserVector* array) {
    int id1, id2;
    printf("Insira o primeiro ID: ");
    scanf("%d", &id1);
    printf("Insira o segundo ID: ");
    scanf("%d", &id2);

    float value;
    printf("Insira o valor a ser transferido: ");
    scanf("%f", &value);

    transferBalance(array, id1, id2, value);
}

void printVector(UserVector* array) {
    if (array->size == 0) {
      printf("O Banco de dados está vazio \n");
      return;
    }
  
    printf("Lista de pessoas no banco de dados: \n");
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

void exportUsersToTxt(UserVector *array) {
    char file[100];
    printf("Digite o nome do arquivo (sem .txt): ");
    scanf("%s", file);
    strcat(file, ".txt");

    printf("Exportando usuários...");
    exportUsers(file, array);
}

