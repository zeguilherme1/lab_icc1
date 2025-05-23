#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "User.h"
#include "UserActions.h"
#include "Utils.h"

enum Options {
    PRINT_VECTOR,
    ADD_NEW_USER,
    TRANSFERENCE,
    DELETE_USER,
    EXPORT_USERS,
    CLOSE_PROGRAM
};

int main() {
    UserVector Users;
    Users = importUsers();

    while (1) {
        printf("Insira uma opção: \n");
        printf(
            "[0] Listar usuários\n[1] Inserir novos usuários\n[2] Transferência de "
            "Saldo\n[3] Excluir um usuário\n[4] Exportar usuários\n[5] Fechar o programa\n> ");

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
                awaitResponse();
                break;

            case TRANSFERENCE:
                makeTransference(&Users);
                awaitResponse();
                break;

            case DELETE_USER:
                removeUser(&Users);
                awaitResponse();
                break;

            case EXPORT_USERS:
                exportUsersToTxt(&Users);
                awaitResponse();
                break;

            case CLOSE_PROGRAM:
                clearVectorMem(&Users);
                printf("Fechando programa...");
                awaitResponse();
                exit(0);
                break;
            	
	    default:
                printf("Comando Invalido!");
                awaitResponse();
                break;
        }

        clearConsole();
    }

    return 0;
}
