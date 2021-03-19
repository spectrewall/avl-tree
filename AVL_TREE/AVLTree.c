#include "AVLTree.h"

int retornaMaior(int a, int b)
{
    return (a > b) ? a : b;
}

int retornaAltura(noAVL *ArvoreAVL)
{
    if (ArvoreAVL == NULL)
        return 0;

    return ArvoreAVL->altura;
}

int retornaFatorBalanceamento(noAVL *ArvoreAVL)
{
    if (ArvoreAVL == NULL)
        return 0;

    return retornaAltura(ArvoreAVL->esq) - retornaAltura(ArvoreAVL->dir);
}

void imprimeArvore(noAVL *arvore, int cont)
{
    int i;

    if (arvore != NULL)
    {
        imprimeArvore(arvore->dir, cont + 1);
        for (i = 0; i < cont; i++)
            printf("\t");
        printf("%d", arvore->info);
        printf("\n");
        imprimeArvore(arvore->esq, cont + 1);
    }
}

noAVL *achaMenor(noAVL *ArvoreAVL)
{
    while (ArvoreAVL->esq != NULL)
        ArvoreAVL = ArvoreAVL->esq;

    return ArvoreAVL;
}

noAVL *criaNo(int info)
{
    noAVL *novo = (noAVL *)malloc(sizeof(noAVL));
    novo->info = info;
    novo->esq = NULL;
    novo->dir = NULL;
    novo->altura = 1;
    return novo;
}

noAVL *removeNo(noAVL *ArvoreAVL, int info)
{
    if (ArvoreAVL == NULL)
        return ArvoreAVL;

    if (info < ArvoreAVL->info)
        ArvoreAVL->esq = removeNo(ArvoreAVL->esq, info);

    else if (info > ArvoreAVL->info)
        ArvoreAVL->dir = removeNo(ArvoreAVL->dir, info);

    else
    {
        if (ArvoreAVL->dir == NULL && ArvoreAVL->esq == NULL)
        {
            free(ArvoreAVL);
            ArvoreAVL = NULL;
        }

        else if (ArvoreAVL->esq != NULL && ArvoreAVL->dir == NULL)
        {
            noAVL *novo = ArvoreAVL->esq;
            ArvoreAVL = ArvoreAVL->esq;
            free(novo);
        }

        else if (ArvoreAVL->dir != NULL && ArvoreAVL->esq == NULL)
        {
            noAVL *novo = ArvoreAVL->dir;
            ArvoreAVL = ArvoreAVL->dir;
            free(novo);
        }

        else
        {
            noAVL *novo = achaMenor(ArvoreAVL->dir);
            ArvoreAVL->info = novo->info;
            ArvoreAVL->dir = removeNo(ArvoreAVL->dir, novo->info);
        }
    }
    if (ArvoreAVL == NULL)
        return ArvoreAVL;

    ArvoreAVL->altura = 1 + retornaMaior(retornaAltura(ArvoreAVL->esq), retornaAltura(ArvoreAVL->dir));

    int FatorBalanceamento = retornaFatorBalanceamento(ArvoreAVL);

    //esq esq Case
    if (FatorBalanceamento > 1 && retornaFatorBalanceamento(ArvoreAVL->esq) >= 0)
        return rotacaoSimplesDir(ArvoreAVL);

    // dir dir Case
    if (FatorBalanceamento < -1 && retornaFatorBalanceamento(ArvoreAVL->dir) <= 0)
        return rotacaoSimplesEsq(ArvoreAVL);

    // esq dir Case
    if (FatorBalanceamento > 1 && retornaFatorBalanceamento(ArvoreAVL->esq) < 0)
    {
        ArvoreAVL->esq = rotacaoSimplesEsq(ArvoreAVL->esq);
        return rotacaoSimplesDir(ArvoreAVL);
    }

    //dir esq Case
    if (FatorBalanceamento < -1 && retornaFatorBalanceamento(ArvoreAVL->dir) > 0)
    {
        ArvoreAVL->dir = rotacaoSimplesDir(ArvoreAVL->dir);
        return rotacaoSimplesEsq(ArvoreAVL);
    }
    return ArvoreAVL;
}

noAVL *insereNO(noAVL *ArvoreAVL, int info)
{
    if (ArvoreAVL == NULL)
        return criaNo(info);

    if (info < ArvoreAVL->info)
        ArvoreAVL->esq = insereNO(ArvoreAVL->esq, info);

    else if (info > ArvoreAVL->info)
        ArvoreAVL->dir = insereNO(ArvoreAVL->dir, info);

    else
        return ArvoreAVL;

    ArvoreAVL->altura = retornaMaior(retornaAltura(ArvoreAVL->esq), retornaAltura(ArvoreAVL->dir)) + 1;

    int FatorBalanceamento = retornaFatorBalanceamento(ArvoreAVL);

    // esq esq Case
    if (FatorBalanceamento > 1 && info < ArvoreAVL->esq->info)
        return rotacaoSimplesDir(ArvoreAVL);

    // dir dir Case
    if (FatorBalanceamento < -1 && info > ArvoreAVL->dir->info)
        return rotacaoSimplesEsq(ArvoreAVL);

    //esq dir Case
    if (FatorBalanceamento > 1 && info > ArvoreAVL->esq->info)
    {
        ArvoreAVL->esq = rotacaoSimplesEsq(ArvoreAVL->esq);
        return rotacaoSimplesDir(ArvoreAVL);
    }

    // dir esq Case
    if (FatorBalanceamento < -1 && info < ArvoreAVL->dir->info)
    {
        ArvoreAVL->dir = rotacaoSimplesDir(ArvoreAVL->dir);
        return rotacaoSimplesEsq(ArvoreAVL);
    }

    return ArvoreAVL;
}

noAVL *rotacaoSimplesEsq(noAVL *no_A)
{
    noAVL *no_B = no_A->dir;
    noAVL *aux = no_B->esq;

    no_B->esq = no_A;
    no_A->dir = aux;

    no_A->altura = retornaMaior(retornaAltura(no_A->esq), retornaAltura(no_A->dir)) + 1;
    no_B->altura = retornaMaior(retornaAltura(no_B->esq), retornaAltura(no_B->dir)) + 1;

    return no_B;
}

noAVL *rotacaoSimplesDir(noAVL *no_A)
{
    noAVL *no_B = no_A->esq;
    noAVL *aux = no_B->dir;

    no_B->dir = no_A;
    no_A->esq = aux;

    no_A->altura = retornaMaior(retornaAltura(no_A->esq), retornaAltura(no_A->dir)) + 1;
    no_B->altura = retornaMaior(retornaAltura(no_B->esq), retornaAltura(no_B->dir)) + 1;

    return no_B;
}
