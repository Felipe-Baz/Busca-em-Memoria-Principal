/* Programa: Arvore Rubro Negra
Autor: Felipe Baz Mitsuishi
Versao: 1.0 - 22/09/2020
*/
// ##################### Bibliotecas Externas ##############################

#include <stdio.h>
#include <stdlib.h>

// ########################## TAD X.h ######################################

typedef struct SNo *TArvBin;

typedef int TChave;

typedef struct
{
    TChave Chave;
    /* outros compomentes */
} TItem;

typedef struct SNo
{
    TItem Item;
    int cor;
    TArvBin pai;
    TArvBin esq, dir;
} TNo;

TArvBin insereNovo(int k, TArvBin esq, TArvBin dir, TArvBin pai)
{
    //algoritmo de criação de um novo elemento com chave K.
    TArvBin p;
    p = (TArvBin)malloc(sizeof(TNo));
    p->Item.Chave = k;
    p->esq = esq;
    p->dir = dir;
    p->pai = pai;
    return p;
}

TArvBin inicializa(TArvBin nodonull)
{
    //algoritmo de inicialização da arvore Rubro-Negra
    nodonull = insereNovo(0, NULL, NULL, NULL);
    nodonull->cor = 1;
    return nodonull;
}

TArvBin rotacaoEsq(TArvBin r, TArvBin p, TArvBin nodonull)
{
    //algoritmo de rotação a esquerda
    TArvBin y = p->dir;
    p->dir = y->esq;
    if (y->esq != nodonull)
        y->esq->pai = p;
    y->pai = p->pai;
    if (p->pai == nodonull)
        r = y;
    else if (p == p->pai->esq)
        p->pai->esq = y;
    else
        p->pai->dir = y;
    y->esq = p;
    p->pai = y;
    return r;
}

TArvBin rotacaoDir(TArvBin r, TArvBin p, TArvBin nodonull)
{
    //algoritmo de rotação a direita
    TArvBin y = p->esq;
    p->esq = y->dir;
    if (y->dir != nodonull)
        y->dir->pai = p;
    y->pai = p->pai;
    if (p->pai == nodonull)
        r = y;
    else if (p == p->pai->esq)
        p->pai->esq = y;
    else
        p->pai->dir = y;
    y->dir = p;
    p->pai = y;
    return r;
}

TArvBin arrumaInsere(TArvBin r, TArvBin p, TArvBin nodonull)
{
    //arruma a arvore r recebida usando de transformações de cores e rotações, sendo aplicada apos a inserção de um elemento na arvore
    TArvBin tio;
    
    while (p->pai->cor == 0)
    {
        if (p->pai == p->pai->pai->esq)
        { 
            tio = p->pai->pai->dir;
            if (tio->cor == 0)
            {                        
                p->pai->cor = 1; 
                tio->cor = 1;
                p->pai->pai->cor = 0;
                p = p->pai->pai;
            }
            else
            { 
                if (p == p->pai->dir)
                {               
                    p = p->pai; 
                    r = rotacaoEsq(r, p, nodonull);
                }
                else
                {
                    p->pai->cor = 1; 
                    p->pai->pai->cor = 0;
                    r = rotacaoDir(r, p->pai->pai, nodonull);
                }
            }
        }
        else
        {
            tio = p->pai->pai->esq;
            if (tio->cor == 0)
            {                        
                p->pai->cor = 1; 
                tio->cor = 1;
                p->pai->pai->cor = 0;
                p = p->pai->pai;
            }
            else
            { 
                if (p == p->pai->esq)
                {               
                    p = p->pai; 
                    r = rotacaoDir(r, p, nodonull);
                }
                else
                {
                    p->pai->cor = 1; 
                    p->pai->pai->cor = 0;
                    r = rotacaoEsq(r, p->pai->pai, nodonull);
                }
            }
        }
    }
    r->cor = 1;
    
    return r;
}

TArvBin Insere(TArvBin p, int k, TArvBin nodonull)
{
    //insere o elemento k na posição correta da arvore P recebida seguindo as regras da arvore binaria de busca
    TArvBin novo = insereNovo(k, nodonull, nodonull, nodonull);

    TArvBin x = p;
    TArvBin paix = nodonull;

    while (x != nodonull)
    { //busca o pai do nodo novo
        paix = x;
        if (k < x->Item.Chave)
            x = x->esq;
        else
            x = x->dir;
    }
    novo->pai = paix;
    if (paix == nodonull) //arvore vazia
        p = novo;
    else if (k < paix->Item.Chave)
        paix->esq = novo;
    else
        paix->dir = novo;
    novo->cor = 0;
    p = arrumaInsere(p, novo, nodonull);
    
    return p;
}

TArvBin sucessor(TArvBin p,TArvBin nodonull)
{
    //verifica qual o sucessor do elemento p
    TArvBin aux;
    if (p->dir == nodonull)
        return nodonull;
    aux = p->dir;
    while (aux->esq != nodonull)
    {
        aux = aux->esq;
    }
    return aux;
}

void arrumaRem(TArvBin T, TArvBin x, TArvBin nodonull)
{
    //arruma a arvore fazendo transformações de cores e de rotações apos a remoção de um elemento
    TArvBin w;
    while (x != T && x->cor == 1)
    {
        if (x == x->pai->esq)
        {
            w = x->pai->dir;
            if (w->cor == 0)
            {
                w->cor = 1;
                x->pai->cor = 0;
                rotacaoEsq(T, x->pai, nodonull);
                w = x->pai->dir;
            }
            if (w->esq->cor == 1 && w->dir->cor == 1)
            {
                w->cor = 0;
                x = x->pai;
            }
            else if (w->dir->cor == 1)
            {
                w->esq->cor = 1;
                w->cor = 0;
                rotacaoDir(T, w, nodonull);
                w = x->pai->dir;
            }
            w->cor = x->pai->cor;
            x->pai->cor = 1;
            w->dir->cor = 1;
            rotacaoEsq(T, x->pai, nodonull);
            x = T;
        }
        else
        {
            w = x->pai->esq;
            if (w->cor == 0)
            {
                w->cor = 1;
                x->pai->cor = 0;
                rotacaoDir(T, x->pai, nodonull);
                w = x->pai->esq;
            }
            if (w->dir->cor == 1 && w->esq->cor == 1)
            {
                w->cor = 0;
                x = x->pai;
            }
            else if (w->esq->cor == 1)
            {
                w->dir->cor = 1;
                w->cor = 0;
                rotacaoEsq(T, w, nodonull);
                w = x->pai->esq;
            }
            w->cor = x->pai->cor;
            x->pai->cor = 1;
            w->esq->cor = 1;
            rotacaoDir(T, x->pai, nodonull);
            x = T;
        }
    }
    x->cor = 1;
}

TArvBin arvRN_remove(TArvBin r, TArvBin nodok, TArvBin nodonull, TArvBin raiz)
{
    //algoritmo de remoção do elemento presente no no auxiliar nodok da arvore r
    TArvBin nodoRem, filho;
    if (nodok == nodonull)
        return r;
    if (nodoRem == raiz)
    {
        if (nodok->esq == nodonull || nodok->dir == nodonull)
        {
            return nodonull;
        }
    }
    if (nodok->esq == nodonull || nodok->dir == nodonull)
        /* se nodok tem 0 ou 1 filho, remove nodok */
        nodoRem = nodok;
    else                           /* senão remove o Sucessor */
        nodoRem = sucessor(nodok, nodonull); /* neste caso o nodoRem não tem filho esq */
    if (nodoRem->esq != nodonull)
        filho = nodoRem->esq;
    else
        filho = nodoRem->dir;
    filho->pai = nodoRem->pai;
    if (nodoRem->pai == nodonull)
        r = filho;
    else if (nodoRem == nodoRem->pai->esq)
        nodoRem->pai->esq = filho;
    else
        nodoRem->pai->dir = filho;
    if (nodok != nodoRem) /* copia Item.Chave e dados do nodoRem para nodok */
        nodok->Item.Chave = nodoRem->Item.Chave;
    
    free(nodoRem);
    if (nodoRem->cor == 1)
        arrumaRem(r, filho, nodonull);
    return r;
}

TArvBin busca(TArvBin p, int k,TArvBin nodonull)
{
    //faz a busca do elemento K na arvore p recebida (incialmente sendo a raiz)
    if (p == nodonull)
        return nodonull;
    if (p->Item.Chave == k)
        return p;
    else if (k < p->Item.Chave)
        return busca(p->esq, k, nodonull);
    else
        return busca(p->dir, k, nodonull);
}

// ###################### Funcoes e Procedimentos do programa ##############

int EhNegro(TArvBin No)
{
    //verifica se o nó é negro
    return (No == NULL) || (No->cor == 1);
}

int EhRubro(TArvBin No)
{
    //verifica se o nó é rubro
    return (No != NULL) && (No->cor == 0);
}

void Imprime(TArvBin No, TArvBin nodonull)
{
    //imprime a arvore rubro negra
    if (No != nodonull)
    {
        if (EhNegro(No))
            printf("(N%d", No->Item.Chave);
        else
            printf("(R%d", No->Item.Chave);
        Imprime(No->esq, nodonull);
        Imprime(No->dir, nodonull);
        printf(")");
    }
    else
        printf("()");
}

int noNegros(TArvBin raiz, TArvBin nodonull)
{
    //como para as arvores RB a quantidade de nos negros deve ser igual para qualquer caminho percorrido, basta seguir um e vc sabera quantos nos negros a arvore possui
    int He = 0;
    if (raiz == nodonull)
    {
        return 0;
    }
    else
    {
        He = noNegros(raiz->esq, nodonull);
        if (raiz->cor == 1)
        {
            return He + 1;
        }
        else
        {
            return He;
        }
    }
}

// ############################ Principal ###################################

int main()
{
    int chave, tam, i, removido, alt;
    //cria uma arvore Auxiliar que sera utilizada para a busca e remoção
    TArvBin aux;
    TArvBin raiz, nodonull;

    //inicializa a arvore na memoria
    nodonull = inicializa(nodonull);
    raiz = nodonull;
    //recebe o tamanho

    scanf("%d", &tam);
    for (i = 0; i < tam; i++)
    {
        //Insere os n elementos na arvore
        scanf("%d", &chave);
        aux = busca(raiz, chave, nodonull);
        if (aux == nodonull)
        {
            raiz = Insere(raiz, chave, nodonull);
        }
    }
    //recebe o elemento que vai ser removido
    scanf("%d", &removido);

    //calcula a altura da arvore
    alt = noNegros(raiz, nodonull);
    printf("%d\n", alt);
    //imprime a arvore antes das remoções
    Imprime(raiz, nodonull);
    printf("\n");

    //Remover
    aux = busca(raiz, removido, nodonull);
    if (aux == nodonull)
    {
        raiz = Insere(raiz, removido, nodonull);
    }else
    {
        raiz = arvRN_remove(raiz, aux, nodonull, raiz);
    }

    //calcula a altura da arvore
    alt = noNegros(raiz, nodonull);
    printf("%d\n", alt);
    //imprime a arvore antes das remoções
    Imprime(raiz, nodonull);
    printf("\n");
    return 0;
}
