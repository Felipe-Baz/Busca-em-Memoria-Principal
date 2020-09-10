/* Programa: Arvore AVL
Autor: Felipe Baz Mitsuishi
Versao: 1.0 - 08/09/2020
*/
// ##################### Bibliotecas Externas ##############################

#include <stdio.h>

// ########################## TAD X.h ######################################

typedef int TChave;

typedef struct
{
    TChave Chave;
    /* outros compomentes */
} TItem;

typedef struct SNo *TArvBin;

typedef struct SNo
{
    TItem Item;
    TArvBin Esq, Dir;
} TNo;

TArvBin Carrega()
{
    char c;
    TArvBin No;
    scanf("%c", &c);
    if (c == '(')
    {
        scanf("%c", &c);
        if (c == 'C')
        {
            No = (TArvBin)malloc(sizeof(TNo));
            scanf("%d", &No->Item.Chave);
            No->Esq = Carrega();
            No->Dir = Carrega();
            scanf("%c", &c);
        }
        else if (c == ')')
            No = NULL;
    }
    return No;
}

void Imprime(TArvBin No)
{
    if (No != NULL)
    {
        printf("(C%d", No->Item.Chave);
        Imprime(No->Esq);
        Imprime(No->Dir);
        printf(")");
    }
    else
        printf("()");
}

int alturaABB(TArvBin raiz)
{
    int He = 0, Hd = 0;
    if (raiz == NULL)
    {
        return 0;
    }
    else
    {
        He = alturaABB(raiz->Esq);
        Hd = alturaABB(raiz->Dir);
        if (He < Hd)
        {
            return Hd + 1;
        }
        else
        {
            return He + 1;
        }
    }
}

// ###################### Funcoes e Procedimentos do programa ##############

int fatorBalanceamento(TArvBin Raiz)
{
    int FB = 0;
    FB = alturaABB(Raiz->Esq) - alturaABB(Raiz->Dir);
    return FB;
}

TArvBin LL(TArvBin raiz)
{
    //configura as variaveis a serem usadas na rotação
    TArvBin pB, pA;
    pA = raiz;
    pB = raiz->Esq;

    //aplica as trocas a fim de tornar pB o novo no raiz
    pA->Esq = pB->Dir;
    pB->Dir = pA;

    //retorna pB como nova raiz
    return pB;
}

TArvBin RR(TArvBin raiz)
{
    //configura as variaveis a serem usadas na rotação
    TArvBin pB, pA;
    pA = raiz;
    pB = raiz->Dir;

    //aplica as trocas a fim de tornar pB o novo no raiz
    pA->Dir = pB->Esq;
    pB->Esq = pA;

    //retorna pB como nova raiz
    return pB;
}

TArvBin LR(TArvBin raiz)
{
    //configura as variaveis a serem usadas na rotação
    TArvBin pC, pB, pA;
    pA = raiz;
    pB = raiz->Esq;
    pC = raiz->Esq->Dir;

    //aplica as trocas a fim de tornar pC o novo no raiz
    pB->Dir = pC->Esq;
    pC->Esq = pB;

    pA->Esq = pC->Dir;
    pC->Dir = pA;

    //retorna pC como nova raiz
    return pC;
}

TArvBin RL(TArvBin raiz)
{
    //configura as variaveis a serem usadas na rotação
    TArvBin pC, pB, pA;
    pA = raiz;
    pB = raiz->Dir;
    pC = raiz->Dir->Esq;

    //aplica as trocas a fim de tornar pC o novo no raiz
    pB->Esq = pC->Dir;
    pC->Dir = pB;

    pA->Dir = pC->Esq;
    pC->Esq = pA;

    //retorna pC como nova raiz
    return pC;
}

TArvBin Balanceamento(TArvBin Raiz)
{
    TArvBin raiz2 = NULL;
    int FbRaiz = 0;
    FbRaiz = fatorBalanceamento(Raiz);
    //chama procedimentos para balanceamento
    if (FbRaiz > 1)
    {
        int Fb = fatorBalanceamento(Raiz->Esq);
        if (Fb > 0)
        {
            //necessario fazer uma rotação simples a direita
            raiz2 = LL(Raiz);
            printf("LL\n");
            return raiz2;
        }else if (Fb < 0)
        {
            //necessario fazer uma rotação dulpa a direita
            raiz2 = LR(Raiz);
            printf("LR\n");
            return raiz2;
        }
    }
    else if (FbRaiz < -1)
    {
        int Fb = fatorBalanceamento(Raiz->Dir);
        if (Fb < 0)
        {
            //necessario fazer uma rotação simples a esquerda
            raiz2 = RR(Raiz);
            printf("RR\n");
            return raiz2;
        }else if (Fb > 0)
        {
            //necessario fazer uma rotação dulpa a esquerda
            raiz2 = RL(Raiz);
            printf("RL\n");
            return raiz2;
        }
    }
}
// ############################ Principal ###################################

int main()
{
    TArvBin Raiz;
    TItem x;

    Raiz = Carrega(); //le arvore binaria inicial com parenteses aninhados

    //calcula e imprime na tela a altura da arvore recebida
    int alturaEntrada = alturaABB(Raiz) - 1;
    printf("%d\n", alturaEntrada);

    Imprime(Raiz); //imprime arvore recebida
    printf("\n");
    //faz o balanceamento da arvore, tornando ela uma arvore AVL
    Raiz = Balanceamento(Raiz);

    //calcula e imprime na tela a altura da arvore final balanceada
    int alturaSaida = alturaABB(Raiz) - 1;
    printf("%d\n", alturaSaida);

    Imprime(Raiz); //imprime arvore final balanceada
    printf("\n");
    return 0;
}
