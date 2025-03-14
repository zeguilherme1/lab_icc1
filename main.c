#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	int id;
	char nome[100];
	int idade;
	float saldoAtual;
} Usuario;

typedef struct{
	Usuario *DB;
	int size;
	int capacity;
} vector;

void VectorInit(vector *arr){
	arr->DB = (Usuario *)malloc(10 * sizeof(Usuario));
	if(!arr->DB){
		printf("Error in malloc\n");
		exit(1);
	}
	arr->size = 0;
	arr->capacity = 10;
}

void resizeVector(vector *arr){
	int updateCapacity = (int)(arr->capacity * 1.5);
	Usuario *updateDB = (Usuario *)realloc(arr->DB, updateCapacity * sizeof(Usuario));
	if(!updateDB){
		printf("Error in malloc\n");
		exit(1);
	}
	arr->DB = updateDB;
	arr->capacity = updateCapacity;
}

void addUser(vector *arr, int id, char *nome, int idade, float saldoAtual){
	if(arr->size >= arr->capacity){
		resizeVector(arr);
	}

	arr->DB[arr->size].id = id;
	strncpy(arr->DB[arr->size].nome, nome, sizeof(arr->DB[arr->size].nome) - 1);
	arr->DB[arr->size].nome[sizeof(arr->DB[arr->size].nome) - 1] = '\0';
	arr->DB[arr->size].idade = idade;
	arr->DB[arr->size].saldoAtual = saldoAtual;

	arr->size++;
}

void printVector(vector *arr){
	if(arr->size == 0){
		printf("O Banco de dados está vazio\n");
		return;
	}

	printf("\nLista de pessoas no banco de dados: \n");
	for(int i = 0; i < arr->size; i++){
		printf("ID: %d, Nome: %s, Idade: %d, Saldo Atual: %.2f\n",
			arr->DB[i].id, arr->DB[i].nome, arr->DB[i].idade, arr->DB[i].saldoAtual);
	}
}

void cleanVector(vector *arr){
	free(arr->DB);
}

void InsertUser(vector *Usuarios, int n){
	for(int i = 0; i < n; i++){
		char nome[100];
		int idade;
		float saldoAtual;

		printf("\nDigite o nome do usuário: ");
		scanf(" %[^\n]", nome);

		nome[strcspn(nome, "\n")] = '\0';

		printf("Digite a idade: ");
		scanf("%d", &idade);
		getchar();

		printf("Digite o saldo atual: ");
		scanf("%f", &saldoAtual);
		
		if(saldoAtual <= 0){
			printf("Não é possível inserir um saldo negativo\n");
			exit(1);
		}
		addUser(Usuarios, Usuarios->size + 1, nome, idade, saldoAtual);
		}
}


int main(){
	vector Usuarios;
	VectorInit(&Usuarios);

	printf("Insira uma opção: \n");
	printf("[0] Listar usuários, [1] Inserir novos usuários, [2] Transferência de Saldo, [3] Excluir um usuário\n");
	int option;
	scanf("%d", &option);

	if(option == 0){
		printVector(&Usuarios);
	}

	else if(option == 1){
		int n;
		printf("Insira quantos usuários quer inserir no DB: \n");
		scanf("%d", &n);
		InsertUser(&Usuarios, n);
		printVector(&Usuarios);
	}

	return 0;
}
