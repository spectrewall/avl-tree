#include "AVLTree.h"

int main()
{
    noAVL *ArvoreAVL = NULL;

    ArvoreAVL = insereNO(ArvoreAVL, 5);
    ArvoreAVL = insereNO(ArvoreAVL, 10);
    ArvoreAVL = insereNO(ArvoreAVL, 15);
    ArvoreAVL = insereNO(ArvoreAVL, 25);
    ArvoreAVL = insereNO(ArvoreAVL, 30);
    ArvoreAVL = insereNO(ArvoreAVL, 14);
    ArvoreAVL = insereNO(ArvoreAVL, 23);
    ArvoreAVL = insereNO(ArvoreAVL, 6);
    ArvoreAVL = insereNO(ArvoreAVL, 24);
    ArvoreAVL = insereNO(ArvoreAVL, 30);
    ArvoreAVL = insereNO(ArvoreAVL, 3);

    imprimeArvore(ArvoreAVL, 0);

    return 0;
}
