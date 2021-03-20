#include "AVLTree.h"

/*Retorna o maior valor entre dois inteiros*/
int retornaMaior(int a, int b)
{
    return (a > b) ? a : b;
}

/*Retorna a altura de um nó ou 0 caso seja NULL*/
int retornaAltura(noAVL *ArvoreAVL)
{
    if (ArvoreAVL == NULL)
        return 0;

    return ArvoreAVL->altura;
}

/*Retorna o fator de balanceamento de um nó ou 0 caso seja NULL*/
int retornaFatorBalanceamento(noAVL *ArvoreAVL)
{
    if (ArvoreAVL == NULL)
        return 0;

    return retornaAltura(ArvoreAVL->esq) - retornaAltura(ArvoreAVL->dir);
}

/*Percorre recursivamente a arvore imprimindo os valores
da direita para a esquerda respeitando a altura de cada nó*/
void imprimeArvore(noAVL *arvore, int cont, void (*printInfo)(void *))
{
    int i;

    if (arvore != NULL)
    {
        imprimeArvore(arvore->dir, cont + 1, printInfo);
        for (i = 0; i < cont; i++)
            printf("\t");
        printInfo(arvore->info);
        printf("\n");
        imprimeArvore(arvore->esq, cont + 1, printInfo);
    }
}

/*Retorna o filho com o menor valor, ou seja
o filho mais a esquerda*/
noAVL *achaMenor(noAVL *ArvoreAVL)
{
    while (ArvoreAVL->esq != NULL)
        ArvoreAVL = ArvoreAVL->esq;

    return ArvoreAVL;
}

/*Cria um novo nó pronto para ser inserido na árvore*/
noAVL *criaNo(void *info)
{
    noAVL *novo = (noAVL *)malloc(sizeof(noAVL));
    novo->info = info;
    novo->esq = NULL;
    novo->dir = NULL;
    novo->altura = 1;
    return novo;
}

/*Remove um nó da árvore e efetua o balanceamento*/
noAVL *removeNo(noAVL *ArvoreAVL, void *info, int (*compara)(void *, void *))
{
    int FatorBalanceamento;

    if (ArvoreAVL == NULL) /*caso base, se a árvore for vazia ou se o valor a ser removido não estiver na árvore.*/
        return ArvoreAVL;

    if (compara(info, ArvoreAVL->info) == -1)                     /*verifica se o valor a ser removido é menor que o da posição atual.*/
        ArvoreAVL->esq = removeNo(ArvoreAVL->esq, info, compara); /*caso seja percorre para a esquerda.*/

    else if (compara(info, ArvoreAVL->info) == 1)                 /*verifica se o valor a ser removido é maior que o da posição atual.*/
        ArvoreAVL->dir = removeNo(ArvoreAVL->dir, info, compara); /*caso seja percorre para a direita.*/

    else /*Valor encontrado na árvore.*/
    {
        if (ArvoreAVL->dir == NULL && ArvoreAVL->esq == NULL) /*Verifica se é um nó folha.*/
        {
            free(ArvoreAVL);  /*Libera o nó.*/
            ArvoreAVL = NULL; /*Evita o lixo de memória, para não atrapalhar a recursão.*/
        }

        else if (ArvoreAVL->esq != NULL && ArvoreAVL->dir == NULL) /*Verifica se possui um filho a esquerda.*/
        {
            ArvoreAVL = ArvoreAVL->esq; /*Faz o nó atual receber as informações do filho.*/
        }

        else if (ArvoreAVL->dir != NULL && ArvoreAVL->esq == NULL) /*Verifica se possui um filho a direita.*/
        {
            ArvoreAVL = ArvoreAVL->dir; /*Faz o nó atual receber as informações do filho.*/
        }

        else /*Caso o nó a ser removido possua filhos de ambos os lados.*/
        {
            noAVL *novo = achaMenor(ArvoreAVL->dir);                        /*Procura o sucessor (menor filho na sub arvore a direita).*/
            ArvoreAVL->info = novo->info;                                   /*Faz o nó a ser removido receber a info do sucessor.*/
            ArvoreAVL->dir = removeNo(ArvoreAVL->dir, novo->info, compara); /*Percorre a sub arvore a direita e remove o sucessor.*/
        }
    }
    if (ArvoreAVL == NULL) /*Verifica se a arvore está vazia após a remoção.*/
        return ArvoreAVL;

    ArvoreAVL->altura = 1 + retornaMaior(retornaAltura(ArvoreAVL->esq), retornaAltura(ArvoreAVL->dir)); /*Atualiza as alturas dos nós.*/

    FatorBalanceamento = retornaFatorBalanceamento(ArvoreAVL); /*Recebe o fator de balanceamento do nó.*/

    if (FatorBalanceamento >= 2 && retornaFatorBalanceamento(ArvoreAVL->esq) >= 0) /*Se o fator de balanceamento do nó for 2 ou maior e o do filho a esquerda for positivo.*/
        return rotacaoSimplesDir(ArvoreAVL);                                       /*Faz a rotação simples a direita (ROTAÇÃO LL).*/

    if (FatorBalanceamento <= -2 && retornaFatorBalanceamento(ArvoreAVL->dir) <= 0) /*Se o fator de balanceamento do nó for -2 ou menor e o do filho a direita for negativo.*/
        return rotacaoSimplesEsq(ArvoreAVL);                                        /*Faz a rotação simples a esquerda (ROTAÇÃO RR).*/

    if (FatorBalanceamento >= 2 && retornaFatorBalanceamento(ArvoreAVL->esq) < 0) /*Se o fator de balanceamento do nó for 2 ou maior e o do filho a esquerda for negativo.*/
    {                                                                             /* ROTAÇÃO DUPLA A DIREITA (ROTAÇÃO LR).*/
        ArvoreAVL->esq = rotacaoSimplesEsq(ArvoreAVL->esq);                       /*1- Faz uma rotação simples a esquerda no filho a esquerda.*/
        return rotacaoSimplesDir(ArvoreAVL);                                      /*2- Faz uma rotação simples a direita no nó atual.*/
    }

    if (FatorBalanceamento <= -2 && retornaFatorBalanceamento(ArvoreAVL->dir) > 0) /*Se o fator de balanceamento do nó for -2 ou menor e o do filho a direita for positivo.*/
    {                                                                              /* ROTAÇÃO DUPLA A ESQUERDA (ROTAÇÃO RL).*/
        ArvoreAVL->dir = rotacaoSimplesDir(ArvoreAVL->dir);                        /*1- Faz uma rotação simples a direita no filho a direita.*/
        return rotacaoSimplesEsq(ArvoreAVL);                                       /*2- Faz uma rotação simples a esquerda no nó atual.*/
    }
    return ArvoreAVL; /*Retorna o nó atual e no final da recursão a raiz da árvore.*/
}

/*Insere um nó na árvore e efetua o balanceamento*/
noAVL *insereNo(noAVL *ArvoreAVL, void *info, int (*compara)(void *, void *))
{
    int FatorBalanceamento;

    if (ArvoreAVL == NULL)   /*caso base, verifica se a árvore está vazia ou se a recursão chegou na posição em que deve ser inserido.*/
        return criaNo(info); /*Cria o nó com a informação passada.*/

    if (compara(info, ArvoreAVL->info) == -1)                     /*Verifica se a informação a ser inserida é menor que a do nó atual.*/
        ArvoreAVL->esq = insereNo(ArvoreAVL->esq, info, compara); /*Percorre a árvore para a esquerda.*/

    else if (compara(info, ArvoreAVL->info) == 1)                 /*Verifica se a informação a ser inserida é maior que a do nó atual.*/
        ArvoreAVL->dir = insereNo(ArvoreAVL->dir, info, compara); /*Percorre a árvore para a direita.*/

    else                  /*Caso seja já exista essa informação na árvore.*/
        return ArvoreAVL; /*Retorna o nó*/

    ArvoreAVL->altura = retornaMaior(retornaAltura(ArvoreAVL->esq), retornaAltura(ArvoreAVL->dir)) + 1; /*Atualiza as alturas dos nós.*/

    FatorBalanceamento = retornaFatorBalanceamento(ArvoreAVL); /*Recebe o fator de balanceamento do nó.*/

    if (FatorBalanceamento >= 2 && compara(info, ArvoreAVL->esq->info) == -1) /*Verifica se o fator de balanceamento do nó é 2 ou maior e se o novo nó está na esquerda do filho a esquerda.*/
        return rotacaoSimplesDir(ArvoreAVL);                                  /*Faz uma rotação simples a direita (ROTAÇÃO LL).*/

    if (FatorBalanceamento <= -2 && compara(info, ArvoreAVL->dir->info) == 1) /*Verifica se o fator de balanceamento do nó é -2 ou menor e se o novo nó está na direita do filho a direita.*/
        return rotacaoSimplesEsq(ArvoreAVL);                                  /*Faz uma rotação simples a direita (ROTAÇÃO RR).*/

    if (FatorBalanceamento >= 2 && compara(info, ArvoreAVL->esq->info) == 1) /*Verifica se o fator de balanceamento do nó é 2 ou maior e se o novo nó está na direita do filho a esquerda.*/
    {                                                                        /* ROTAÇÃO DUPLA A DIREITA (ROTAÇÃO LR).*/
        ArvoreAVL->esq = rotacaoSimplesEsq(ArvoreAVL->esq);                  /*1- Faz uma rotação simples a esquerda no filho a esquerda.*/
        return rotacaoSimplesDir(ArvoreAVL);                                 /*2- Faz uma rotação simples a direita no nó atual.*/
    }

    if (FatorBalanceamento <= -2 && compara(info, ArvoreAVL->dir->info) == -1) /*Verifica se o fator de balanceamento do nó é -2 ou menor e se o novo nó está na esquerda do filho a direita.*/
    {                                                                          /* ROTAÇÃO DUPLA A ESQUERDA (ROTAÇÃO LR).*/
        ArvoreAVL->dir = rotacaoSimplesDir(ArvoreAVL->dir);                    /*1- Faz uma rotação simples a direita no filho a direita.*/
        return rotacaoSimplesEsq(ArvoreAVL);                                   /*2- Faz uma rotação simples a esquerda no nó atual.*/
    }

    return ArvoreAVL; /*Retorna o nó atual e no final da recursão a raiz da árvore.*/
}

/*Faz uma rotação simples a esquerda (rotação RR)*/
noAVL *rotacaoSimplesEsq(noAVL *no_A)
{
    noAVL *no_B = no_A->dir; /*Cria um nó auxiliar B que recebe o filho a direita de A.*/
    noAVL *aux = no_B->esq;  /*Cria um nó auxiliar que recebe o filho a esquerda do nó B.*/

    no_B->esq = no_A; /*Faz o filho a esquerda de B apontar para o nó A.*/
    no_A->dir = aux;  /*Faz o filho a direita de A apontar para o antigo filho a esquerda de B.*/

    no_A->altura = retornaMaior(retornaAltura(no_A->esq), retornaAltura(no_A->dir)) + 1; /*Atualiza a altura do nó A.*/
    no_B->altura = retornaMaior(retornaAltura(no_B->esq), retornaAltura(no_B->dir)) + 1; /*Atualiza a altura do nó B (nova raiz da sub arvore).*/

    return no_B; /*Retorna a nova raiz.*/
}

/*Faz uma rotação simples a direita (rotação LL)*/
noAVL *rotacaoSimplesDir(noAVL *no_A)
{
    noAVL *no_B = no_A->esq; /*Cria um nó auxiliar B que recebe o filho a esquerda de A.*/
    noAVL *aux = no_B->dir;  /*Cria um nó auxiliar que recebe o filho a direita do nó B.*/

    no_B->dir = no_A; /*Faz o filho a direita de B apontar para o nó A.*/
    no_A->esq = aux;  /*Faz o filho a esquerda de A apontar para o antigo filho a direita de B.*/

    no_A->altura = retornaMaior(retornaAltura(no_A->esq), retornaAltura(no_A->dir)) + 1; /*Atualiza a altura do nó A.*/
    no_B->altura = retornaMaior(retornaAltura(no_B->esq), retornaAltura(no_B->dir)) + 1; /*Atualiza a altura do nó B (nova raiz da sub arvore).*/

    return no_B; /*Retorna a nova raiz.*/
}
