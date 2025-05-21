#include<stdlib.h>
#include<stdio.h>
#include "Utils.h"

void awaitResponse() {
    printf("\n\nPressione ENTER para continuar...");
    getchar();
}

void clearConsole() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}