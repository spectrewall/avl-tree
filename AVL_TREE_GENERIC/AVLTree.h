/*************************************************************************************
* Arquivo AVLtree.h para trabalhar com arvores AVL de tipo genérico                  *
* Aluno: Wallace Luiz Carvalho de Andrade                                            *
*************************************************************************************/
#ifndef AVLTREE_H
#define AVLTREE_H

#include <stdio.h>
#include <stdlib.h>

/*Estrutura para a Árvore AVL.*/
typedef struct ArvoreAVL
{
    void *info;
    int altura;
    struct ArvoreAVL *dir;
    struct ArvoreAVL *esq;
} noAVL;

/****************** Funções ******************/

noAVL *insereNo(noAVL *ArvoreAVL, void *info, int (*compara)(void *, void *)); /*Insere um nó na árvore.*/
noAVL *removeNo(noAVL *ArvoreAVL, void *info, int (*compara)(void *, void *)); /*Remove um nó da árvore.*/
noAVL *criaNo(void *info);                                                     /*Cria um novo nó.*/

/*Funções auxiliares*/
void imprimeArvore(noAVL *arvore, int cont, void (*printInfo)(void *)); /*Imprime a arvore na tela.*/
noAVL *achaMenor(noAVL *ArvoreAVL);                                     /*Retorna o menor filho de um nó.*/
int retornaAltura(noAVL *ArvoreAVL);                                    /*Retorna a altura do nó ou 0 caso não exista o nó.*/
int retornaFatorBalanceamento(noAVL *ArvoreAVL);                        /*Retorna o fator de balanceamento do nó ou 0 caso não exista o nó.*/
int retornaMaior(int a, int b);                                         /*Retorna o maior valor.*/

/*Funções de rotações*/
noAVL *rotacaoSimplesEsq(noAVL *no_A); /*Faz a rotação simples a esquerda. RR*/
noAVL *rotacaoSimplesDir(noAVL *no_A); /*Faz a rotação simples a direita. LL*/

#endif
