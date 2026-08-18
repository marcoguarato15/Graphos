#include <stdio.h>
#include <stdlib.h>
//Árvore ABB
struct no {
    int n;
    struct no *esq;
    struct no *dir;
};
typedef struct no no;

no* criaNo(int n) {
    no* novoNo = (no*)malloc(sizeof(no));
    novoNo->n = n;
    novoNo->esq = NULL;
    novoNo->dir = NULL;
    return novoNo;
}

no* inserirNo(int n, no* raiz) {
    //1 - raiz é nula
    //2 - raiz não é nula
        //n > raiz -> adiciona a direita
        //n < raiz -> adiciona a esquerda
        //n === raiz -> printf "valor já existente"
    if(raiz == NULL) {
        no* novoNo = criaNo(n);
        return novoNo;
    } else {
        if (n > raiz->n) {
            raiz->dir = inserirNo(n, raiz->dir);
        } else if (n < raiz->n){
            raiz->esq = inserirNo(n, raiz->esq);
        } else {
            printf("o valor %d ja existe na arvore", n);
        }
        return raiz;
    }
}

void mostrar_preOrdem(no* raiz) {//R E D
    if(raiz != NULL) {
        printf("%d ", raiz->n);
        mostrar_preOrdem(raiz->esq);
        mostrar_preOrdem(raiz->dir);
    }
}

int main() {
    printf("Arvore Binaria de Busca!\n\n");
    no* raiz = NULL;
    int i=0;
    int valores[11] = {50, 30, 70, 20, 40, 60, 80, 35, 45, 65, 85};
    for(i=0; i<11; i++) {
        raiz = inserirNo(valores[i], raiz);
    }
    mostrar_preOrdem(raiz);
    return 0;
}
