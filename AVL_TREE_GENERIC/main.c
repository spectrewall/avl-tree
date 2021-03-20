#include "AVLTree.h"

void printInfo(void *info)
{
	int *x = (int *)info;
	printf("%d", *x);
}

int compara(void *info1, void *info2)
{
	int *x = (int *)info1;
	int *y = (int *)info2;

	if (*x > *y)
		return 1;

	else if (*x < *y)
		return -1;

	else
		return 0;
}

int main()
{
	noAVL *ArvoreAVL = NULL;

	int *a1 = (int *)malloc(sizeof(int));
	int *a2 = (int *)malloc(sizeof(int));
	int *a3 = (int *)malloc(sizeof(int));
	int *a4 = (int *)malloc(sizeof(int));
	int *a5 = (int *)malloc(sizeof(int));
	int *a6 = (int *)malloc(sizeof(int));
	int *a7 = (int *)malloc(sizeof(int));
	int *a8 = (int *)malloc(sizeof(int));
	int *a9 = (int *)malloc(sizeof(int));
	int *a10 = (int *)malloc(sizeof(int));
	int *a11 = (int *)malloc(sizeof(int));
	int *a12 = (int *)malloc(sizeof(int));
	int *a13 = (int *)malloc(sizeof(int));

	*a1 = 10;
	*a2 = 9;
	*a3 = 3;
	*a4 = 7;
	*a5 = 6;
	*a6 = 5;
	*a7 = 4;
	*a8 = 3;
	*a9 = 2;
	*a10 = 1;
	*a11 = 11;
	*a12 = 12;
	*a13 = 13;

	ArvoreAVL = insereNo(ArvoreAVL, a13, compara);
	ArvoreAVL = insereNo(ArvoreAVL, a1, compara);
	ArvoreAVL = insereNo(ArvoreAVL, a2, compara);
	ArvoreAVL = insereNo(ArvoreAVL, a3, compara);
	ArvoreAVL = insereNo(ArvoreAVL, a4, compara);
	ArvoreAVL = insereNo(ArvoreAVL, a5, compara);
	ArvoreAVL = insereNo(ArvoreAVL, a6, compara);
	ArvoreAVL = insereNo(ArvoreAVL, a7, compara);
	ArvoreAVL = insereNo(ArvoreAVL, a8, compara);
	ArvoreAVL = insereNo(ArvoreAVL, a9, compara);
	ArvoreAVL = insereNo(ArvoreAVL, a10, compara);
	ArvoreAVL = insereNo(ArvoreAVL, a11, compara);
	ArvoreAVL = insereNo(ArvoreAVL, a12, compara);

	printf("\n\n");
	imprimeArvore(ArvoreAVL, 0, printInfo);

	ArvoreAVL = removeNo(ArvoreAVL, a4, compara);
	ArvoreAVL = removeNo(ArvoreAVL, a13, compara);
	ArvoreAVL = removeNo(ArvoreAVL, a9, compara);
	ArvoreAVL = removeNo(ArvoreAVL, a10, compara);
	ArvoreAVL = removeNo(ArvoreAVL, a3, compara);

	printf("\n\n");
	imprimeArvore(ArvoreAVL, 0, printInfo);

	return 0;
}
