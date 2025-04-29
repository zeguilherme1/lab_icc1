#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Usuario.h"

// arrow function >
// (pointer_name) -> (variable_name);
// foo->bar == (*foo).bar;

/* To do
        organizar melhor usando header;
        assert em funcoes que aceitam ponteiro como vectorInit pra checar se um
   ponteiro não é NULL; assert vector capacity >= size; manter found = -1 se no
   final do for não ter encontrado o ID;
*/

int main() {
  UserVector Usuarios;
  initVector(&Usuarios);

  while (1) {
    printf("Insira uma opção: \n");
    printf(
        "[0] Listar usuários, [1] Inserir novos usuários, [2] Transferência de "
        "Saldo, [3] Excluir um usuário ou [4] para fechar o programa\n");

    int option;
    scanf("%d", &option);
    clearBuffer();

    if (option == 0) {
      printVector(&Usuarios);
    } else if (option == 1) {
      int n;
      printf("Insira quantos usuários quer inserir no DB: \n");
      scanf("%d", &n);
      insertUser(&Usuarios, n);
      printVector(&Usuarios);
    } else if (option == 2) {
      int id1, id2;
      printf("Insira o primeiro ID: \n");
      scanf("%d", &id1);
      printf("Insira o segundo ID: \n");
      scanf("%d", &id2);

      float valor;
      printf("Insira o valor a ser transferido: \n");
      scanf("%f", &valor);

      transferBalance(&Usuarios, id1, id2, valor);
    } else if (option == 3) {
      int id1;
      printf("Insira o ID que deseja remover:\n");
      scanf("%d", &id1);

      deleteUser(&Usuarios, id1);
      printf("Usuário removido\n");
    } else if (option == 4) {
      clearVectorMem(&Usuarios);
      printf("Fechando programa...\n");
      break;
    } else {
      printf("Opção inválida, tente novamente!\n");
    }
  }

  return 0;
}
