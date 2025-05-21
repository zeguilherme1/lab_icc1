#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "User.h"

//
// Memory functions
//

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

//
// Utils
// 

int contains(UserVector* array, int userId) {
    for (int index = 0; index < array->size; index++) {
      if (array->users[index].id == userId) {
        return index;
      }
    }

    return -1;
}

//
// CRUD Functions
//

void insertUser(UserVector* array, int id, int age, char* name, float balance) {
    if (array->size >= array->capacity) resizeVector(array);
  
    // foo->bar == (*foo).bar;
    array->users[array->size].id = id;
    strncpy(array->users[array->size].name, name, sizeof(array->users[array->size].name) - 1);
    array->users[array->size].name[sizeof(array->users[array->size].name) - 1] = '\0';
    array->users[array->size].age = age;
    array->users[array->size].balance = balance;
  
    array->size++;
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

void transferBalance(UserVector* array, int id1, int id2, float value) {
    if (id1 == id2) {
        printf("Os ID's devem ser diferentes");
        return;
    }
    int found1 = contains(array, id1), found2 = contains(array, id2);
    if (found1 == -1 || found2 == -1) {
        printf("Usuario(s) nao encontrado(s), impossivel excluir.");
        return;
    }

    if (value <= 0) {
        printf("O valor a ser transferido deve ser positivo: ");
        return;
    }
  
    User *remetente = NULL, *destinatario = NULL;
    for (int i = 0; i < array->size; i++) {
        if (array->users[i].id == id1) {
            remetente = &array->users[i];
        }
        if (array->users[i].id == id2) {
            destinatario = &array->users[i];
        }
    }
    if (remetente == NULL || destinatario == NULL) {
        printf("ID's inválidos\n");
        return;
    }
  
    if (remetente->balance < value) {
        printf("Saldo insuficiente para transferência");
        return;
    }
  
    remetente->balance -= value;
    destinatario->balance += value;
  
    printf("Transferência de %.2f realizada com sucesso\n\n", value);
}

void exportUsers(const char* file, UserVector* array) {
	FILE* fp = fopen(file, "w+");
	if(!fp){
		perror("Error trying to write in file");
		return;
	}
	for(int i = 0; i < array->size; i++){
		User u = array->users[i];
		fprintf(fp, "%d|%d|%s|%.2f\n", u.id, u.age, u.name, u.balance);
	}
	fclose(fp);
}
