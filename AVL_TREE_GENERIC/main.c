/*************************************************************************************
* Arquivo main.c para testar arvores AVL de tipo genérico.                           *
* Aluno: Wallace Luiz Carvalho de Andrade                                            *
*************************************************************************************/

#include "AVLTree.h"

typedef struct itemInfo
{
	char nome[50];
	float preco;
	float peso;
} item;

void printInfo(void *info)
{
	item *x = (item *)info;
	printf("%s", x->nome);
}

void printFullInfo(void *info)
{
	item *x = (item *)info;
	printf("\nnome: %s", x->nome);
	printf("\npreco R$: %.2f", x->preco);
	printf("\npeso: %.4f", x->peso);
}

int compara(void *info_1, void *info_2)
{
	item *x = (item *)info_1;
	item *y = (item *)info_2;

	int res;
	res = strcmp(x->nome, y->nome);

	if (res > 0)
		return 1;
	else if (res < 0)
		return -1;
	else
		return 0;
}

int main()
{
	noAVL *ArvoreAVL = NULL;
	noAVL *aux = NULL;
	int op = 0;

	while (op != 5)
	{
		item *produto;

		printf("\n\n--- MENU ---\n\n1 - Inserir item\n2 - Remover item\n3 - Buscar item\n4 - Imprimir a arvore\n5 - Sair\nDigite sua opcao: ");
		scanf("%d", &op);
		fflush(stdin);

		switch (op)
		{
		case 1:
			produto = (item *)malloc(sizeof(item));
			printf("\nDigite o nome do produto: ");
			scanf("%s", produto->nome);
			fflush(stdin);
			printf("Digite o valor (em R$) do produto: ");
			scanf("%f", &produto->preco);
			fflush(stdin);
			printf("Digite o peso do produto: ");
			scanf("%f", &produto->peso);
			fflush(stdin);

			ArvoreAVL = insereNo(ArvoreAVL, produto, compara);

			aux = buscaNo(ArvoreAVL, produto, compara);
			printFullInfo(aux->info);
			break;

		case 2:
			produto = (item *)malloc(sizeof(item));
			printf("\nDigite o nome do produto que deseja remover: ");
			scanf("%s", produto->nome);
			fflush(stdin);

			aux = buscaNo(ArvoreAVL, produto, compara);
			printFullInfo(aux->info);

			ArvoreAVL = removeNo(ArvoreAVL, produto, compara);
			break;

		case 3:
			produto = (item *)malloc(sizeof(item));
			printf("\nDigite o nome do produto que deseja buscar: ");
			scanf("%s", produto->nome);
			fflush(stdin);

			aux = buscaNo(ArvoreAVL, produto, compara);
			printFullInfo(aux->info);
			break;

		case 4:
			printf("\n\n---------------------------------\n\n");
			imprimeArvore(ArvoreAVL, 0, printInfo);
			printf("\n\n---------------------------------\n\n");
			break;

		case 5:
			printf("\n\n ATE A PROXIMA... \n\n");
			break;

		default:
			printf("\n\n *** ENTRE COM UMA OPCAO VALIDA *** \n\n");
			break;
		}
	}

	return 0;
}
