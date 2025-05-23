#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Utils.h"
#include "User.h"
#include "UserActions.h"
#define TXT_PATH "userDB.txt"

void addNewUser(UserVector* array) {
    unsigned int numberOfUsers;
    printf("Insira quantos usuários gostaria de inserir: ");
    scanf("%u", &numberOfUsers);

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
            return;
        }

        insertUser(array, array->size + 1, age, name, balance);
    }
}

void removeUser(UserVector *array) {
    unsigned int id;
    printf("Insira o ID que deseja remover: ");
    scanf("%u", &id);

    deleteUser(array, id);
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
    printf("Exportando usuários...");
    exportUsers(TXT_PATH, array);
}

UserVector importUsers() {
    FILE* fp = fopen(TXT_PATH, "r");

    UserVector newUsers;
    initVector(&newUsers);

    if (!fp) {
        perror("Error trying to open file");

        fp = fopen(TXT_PATH, "w+");
        if (!fp) {
            perror("Error trying to create file");
            clearBuffer();
            exit(0);
        }

        fprintf(fp, "id|idade|nome|saldo\n");
    }
    else {
        char line[1000];
        memset(line, '\0', sizeof(line));

        fgets(line, sizeof(line), fp);
        while (fgets(line, sizeof(line), fp) != NULL) {
            char strCopy[1000];
            strcpy(strCopy, line);

            char *attr = strtok(strCopy, "|");
            int id = atoi(attr);

            attr = strtok(NULL, "|");
            int age = atoi(attr);

            attr = strtok(NULL, "|");
            char *name = attr;

            attr = strtok(NULL, "|");
            attr[strcspn(attr, "\n")] = '\0';
            float balance = atof(attr);
            
            insertUser(&newUsers, id, age, name, balance);
        }

        fclose(fp);
    }

    return newUsers;
}
