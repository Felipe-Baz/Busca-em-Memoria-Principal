/*
Programa: Arvore binaria de busca
Autor: Felipe Baz Mitsuishi
Versao: 1.0 - 01/09/2020
*/

// ##################### Bibliotecas Externas ##############################

#include <stdio.h>
#include <stdlib.h>

// ########################## TAD X.h ######################################

struct noABB
{
    int chave;
    struct noABB *esq;
    struct noABB *dir;
};
typedef struct noABB arvore;

void inicia(int chave, arvore *teste)
{
    //cria o nó raiz da arvore
    teste->chave = chave;
    teste->dir = NULL;
    teste->esq = NULL;
}

arvore *insereNo(int chave)
{
    arvore *novo = (arvore *)malloc(sizeof(arvore));
    novo->chave = chave;
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}

void insereOrdem(int chave, arvore *teste)
{
    if (chave <= teste->chave)
    {
        if (teste->esq == NULL)
        {
            teste->esq = insereNo(chave);
        }
        else
        {
            insereOrdem(chave, teste->esq);
        }
    }
    else
    {
        if (teste->dir == NULL)
        {
            teste->dir = insereNo(chave);
        }
        else
        {
            insereOrdem(chave, teste->dir);
        }
    }
}

void limpaTudo(arvore *teste)
{
    int i;
    teste->dir = NULL;
    teste->esq = NULL;
    teste->chave = 0;
}

arvore *removeNo(arvore *r)
{
    arvore *p, *q;
    if (r->esq == NULL)
    {
        q = r->dir;
        free(r);
        return q;
    }
    p = r;
    q = r->esq;
    while (q->dir != NULL)
    {
        p = q;
        q = q->dir;
    }
    // q é nó anterior a r na ordem e-r-d
    // p é pai de q
    if (p != r)
    {
        p->dir = q->esq;
        q->esq = r->esq;
    }
    q->dir = r->dir;
    free(r);
    return q;
}



void busca(int chave, arvore *raiz, int *tamanho, int *cond)
{
    arvore *anterior = raiz;
    int count = 0;
    //chave = raiz
    if (raiz->chave == chave)
    {
        raiz = removeNo(raiz);
    }
    else
    {
        //encontra o pai
        //caso filho a direita
        if (raiz->esq != NULL && raiz->esq->chave == chave)
        {
            //remove filho
            raiz->esq = removeNo(raiz->esq);
            //faz a busca para ver se não a outra chave
            busca(chave, raiz, tamanho, cond);
            count++;
            *cond = 1;
        }
        else if (raiz->dir != NULL && raiz->dir->chave == chave)
        {
            //remove filho
            raiz->dir = removeNo(raiz->esq);
            busca(chave, raiz, tamanho, cond);
            count++;
            *cond = 1;
        }
        else
        {
            //desce a arvore em busca do nó buscado
            if (raiz->esq != NULL && raiz->chave > chave)
            {
                busca(chave, raiz->esq, tamanho, cond);
            }
            else if (raiz->dir != NULL && raiz->chave < chave)
            {
                busca(chave, raiz->dir, tamanho, cond);
            }
        }
    }
    *tamanho = *tamanho - count;
}

// ###################### Funcoes e Procedimentos do programa ##############

int alturaABB(arvore *raiz)
{
    if (raiz == NULL)
    {
        return 0;
    }
    else
    {
        int He = alturaABB(raiz->esq);
        int Hd = alturaABB(raiz->dir);
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

// ############################ Principal ###################################

int main()
{
    int i, chave = 0, tamanho = 0, altura, newTamanho, newAltura, buscado, cond = 0, condicional = 0;

    arvore raiz;

    scanf("%d", &chave);
    if (chave >= 0)
    {
        inicia(chave, &raiz);
        tamanho++;
        condicional = 1;
    }
    
    while (chave >= 0)
    {
        scanf("%d", &chave);
        if (chave >= 0)
        {
            insereOrdem(chave, &raiz);
            tamanho++;
        }
    }
    scanf("%d", &buscado);

    if (tamanho == 1)
    {
        if (buscado == raiz.chave)
        {
            printf("1 1\n");
            printf("0 0\n");
            return 0;
        }else
        {
            printf("1 1\n");
            insereOrdem(buscado, &raiz);
            newTamanho = tamanho + 1;
            newAltura = alturaABB(&raiz);
            printf("%d %d\n", newTamanho, newAltura);
            return 0;
        }
        
    }


    newTamanho = tamanho;
        
    if (condicional == 0)
    {
        printf("0 0\n");
        inicia(buscado, &raiz);
        newTamanho++;
    }else
    {

        altura = alturaABB(&raiz);
        printf("%d %d\n", tamanho, altura);
        busca(buscado, &raiz, &newTamanho, &cond);
    }
    if (cond == 0 && condicional == 1)
    {
        insereOrdem(buscado, &raiz);
        newTamanho = tamanho + 1;
    }
    
    newAltura = alturaABB(&raiz);
    
    printf("%d %d\n", newTamanho, newAltura);
    return 0;
}
