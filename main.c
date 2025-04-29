#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Usuario.h"

enum Options {
    PRINT_VECTOR,
    ADD_NEW_USER,
    TRANSFERENCE,
    DELETE_USER,
    CLOSE_PROGRAM
};

/*  TODO
    assert em funcoes que aceitam ponteiro como vectorInit pra checar se um
    ponteiro não é NULL; assert vector capacity >= size; manter found = -1 se no
    final do for não ter encontrado o ID;
*/

void clearConsole() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void awaitResponse() {
    printf("\n\nPressione ENTER para continuar...");
    getchar();
}

void clearBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

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

int main() {
    UserVector Users;
    initVector(&Users);

    while (1) {
        printf("Insira uma opção: \n");
        printf(
            "[0] Listar usuários\n[1] Inserir novos usuários\n[2] Transferência de "
            "Saldo\n[3] Excluir um usuário\n[4] para fechar o programa\n");

        int option;
        scanf("%d", &option);
        clearBuffer();

        clearConsole();

        switch (option) {
            case PRINT_VECTOR:
                printVector(&Users);
                awaitResponse();
                break;

            case ADD_NEW_USER:
                addNewUser(&Users);
                break;

            case TRANSFERENCE:
                makeTransference(&Users);
                awaitResponse();
                break;

            case DELETE_USER:
                int id;
                printf("Insira o ID que deseja remover: ");
                scanf("%d", &id);

                deleteUser(&Users, id);

                printf("Usuario Removido!");
                awaitResponse();
                break;

            case CLOSE_PROGRAM:
                clearVectorMem(&Users);

                printf("Fechando programa...");
                awaitResponse();
                exit(0);

            default:
                printf("Comando Invalido!");
                awaitResponse();
                break;
        }

        clearConsole();
    }

    return 0;
}
