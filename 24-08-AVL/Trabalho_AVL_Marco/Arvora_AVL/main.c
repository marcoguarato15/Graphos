#include <stdio.h>
#include <stdlib.h>

//Árvore ABB - PROFESSOR GUILHERME MELO
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

void mostrar_preOrdem(no* raiz) {//R E D
    if(raiz != NULL) {
        printf("%d ", raiz->n);
        mostrar_preOrdem(raiz->esq);
        mostrar_preOrdem(raiz->dir);
    }
}

no* encontrarMinimo(no* raiz) {
    if(raiz != NULL) {
        while (raiz->esq != NULL) {
            raiz = raiz->esq;
        }
        return raiz;
    } else {
        return NULL;
    }
}

no* encontrarMaximo(no* raiz) {
     if(raiz != NULL) {
        while (raiz->dir != NULL) {
            raiz = raiz->dir;
        }
        return raiz;
     } else {
        return NULL;
     }
}

no* encontrarNo(no* raiz, int n) {
    if (raiz == NULL) {
        //Não Encontrado
        return NULL;
    } else if (raiz->n == n) {
        return raiz;
    } else if (n < raiz->n) {
        return encontrarNo(raiz->esq, n);
    } else if (n > raiz->n) {
        return encontrarNo(raiz->dir, n);
    }
}

int verificaIgualdade(no* arv1, no* arv2){
    if (arv1 == NULL && arv2 == NULL){
        return 1;
    }

    if (arv1 == NULL || arv2 == NULL) {
        return 0;
    }

    if (arv1->n != arv2->n){
        return 0;
    }

    return verificaIgualdade(arv1->esq, arv2->esq) && verificaIgualdade(arv1->dir, arv2->dir);
}

int verificaEstrita(no* raiz){
    if (raiz == NULL){
        return 1;
    }

    if ((raiz->esq == NULL && raiz->dir != NULL) || (raiz->esq != NULL && raiz->dir == NULL)){
        return 0;
    }

    return verificaEstrita(raiz->esq) && verificaEstrita(raiz->dir);
}

int altura(no* raiz) {
    if(raiz == NULL){
        return 0;
    }
    int alturaEsquerda = altura(raiz->esq);
    int alturaDireita = altura(raiz->dir);

    if(alturaEsquerda > alturaDireita) {
        return alturaEsquerda + 1;
    } else {
        return alturaDireita + 1;
    }
}

int fatorBalanceamento(no* no) {
    //FB = hesq - hdir
    int fb = 0;
    if (no != NULL){
        fb = altura(no->esq) - altura(no->dir);
    }
    return fb;
}

no* rotacaoDireita(no* desbal) {
    no* filho = desbal->esq;
    desbal->esq = filho->dir;
    filho->dir = desbal;

    return filho;
}

no* rotDireita(no* desbal){
    no* filho = desbal->esq;
    desbal->esq = filho->dir;
    filho->dir = desbal;

    return filho;
}


no* rotacaoEsquerda(no* desbal) {
    no* filho = desbal->dir;
    desbal->dir = filho->esq;
    filho->esq = desbal;

    return filho;
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

        //CALCULAR O FATOR DE BALANCIAMENTO
        int fb = fatorBalanceamento(raiz);

        //VERIFICAR NECESSIDADE DE ROTACAO

        //ROTACAO SIMPLES A DIREITA (TEMOS UMA ÁRVORE ESQUERDA ESQUERDA)
        // INSERINDO o 3 -
        //     5         4
        //   4     ->  3   5
        // 3
        if(fb > 1 && n < raiz->esq->n) {
            return rotacaoDireita(raiz);
        }

        //ROTACAO SIMPLES A ESQUERDA (TEMOS UMA ÁRVORE DIREITA DIREITA)
        // INSERINDO o 5
        // 3             4
        //   4     ->  3   5
        //     5
        if(fb < -1 && n > raiz->dir->n) {
            return rotacaoEsquerda(raiz);
        }

        //ROTACAO DUPLA ESQUERDA DIREITA
        // INSERINDO o 6
        //    7            7        6
        //  5      ->    6    ->  7   9
        //    6        5
        if(fb > 1 && n > raiz->esq->n) {
            raiz->esq = rotacaoEsquerda(raiz->esq);
            return rotacaoDireita(raiz);
        }

        //ROTACAO DUPLA DIREITA ESQUERDA
        // INSERINDO o 6
        //    5         5             6
        //      7   ->    6     ->  5   7
        //    6              7
        if(fb < -1 && n < raiz->dir->n) {
            raiz->dir = rotacaoDireita(raiz->dir);
            return rotacaoEsquerda(raiz);
        }

        return raiz;
    }
}

no* removerNo(no* raiz, int n) {
    if (raiz == NULL) {
        return raiz; // valor não encontrado
    }

    // 1. Busca do nó
    if (n < raiz->n) {
        raiz->esq = removerNo(raiz->esq, n);
    } else if (n > raiz->n) {
        raiz->dir = removerNo(raiz->dir, n);
    } else {
        // 2. Remoção
        if (raiz->esq == NULL || raiz->dir == NULL) {
            no* temp = NULL;
            if (raiz->esq != NULL) {
                temp = raiz->esq;
            } else {
                temp = raiz->dir;
            }

            if (temp == NULL) { // sem filhos
                temp = raiz;
                raiz = NULL;
            } else { // um filho
                *raiz = *temp; // copia conteúdo do filho
            }
            free(temp);
        } else {
            // dois filhos → pega o menor da subárvore direita
            no* temp = encontrarMinimo(raiz->dir);
            raiz->n = temp->n;
            raiz->dir = removerNo(raiz->dir, temp->n);
        }
    }

    // Se a árvore ficou vazia
    if (raiz == NULL) return raiz;

    // 3. Rebalanceamento
    int fb = fatorBalanceamento(raiz);

    // Caso esquerda-esquerda
    if (fb > 1 && fatorBalanceamento(raiz->esq) >= 0) {
        return rotacaoDireita(raiz);
    }

    // Caso esquerda-direita
    if (fb > 1 && fatorBalanceamento(raiz->esq) < 0) {
        raiz->esq = rotacaoEsquerda(raiz->esq);
        return rotacaoDireita(raiz);
    }

    // Caso direita-direita
    if (fb < -1 && fatorBalanceamento(raiz->dir) <= 0) {
        return rotacaoEsquerda(raiz);
    }

    // Caso direita-esquerda
    if (fb < -1 && fatorBalanceamento(raiz->dir) > 0) {
        raiz->dir = rotacaoDireita(raiz->dir);
        return rotacaoEsquerda(raiz);
    }

    return raiz;
}

no* rNo(no* raiz, int n){
    if (raiz == NULL){
        return raiz;
    }
    if (n > raiz->n){
        raiz->dir = rNo(raiz->dir, n);
    } else if (n < raiz->n){
        raiz->esq = rNo(raiz->esq, n);
    } else {
        if (raiz->esq == NULL || raiz->dir == NULL){
            no* temp;
            if (raiz->esq != NULL){
                temp = raiz->esq;
            } else if (raiz->dir != NULL){
                temp = raiz->dir;
            }
            if(temp == NULL){
                temp = raiz;
                raiz = NULL;
            } else {
                *raiz = *temp;
            }
            free(temp);
        } else {
            no* temp = encontrarMinimo(raiz->dir);
            raiz->n = temp->n;
            raiz->dir = rNo(raiz->dir, temp->n);
        }
    }

    if (raiz == NULL){
        return raiz;
    }

    int fb = fatorBalanceamento(raiz);

    if (fb > 1 && fatorBalanceamento(raiz->esq) >= 0){
        return rotacaoDireita(raiz);
    }

    if (fb > 1 && fatorBalanceamento(raiz->esq) < 0){
        raiz->esq = rotacaoEsquerda(raiz->esq);
        return rotacaoDireita(raiz);
    }

    if (fb < -1 && fatorBalanceamento(raiz->dir) <= 0){
        return rotacaoEsquerda(raiz);
    }

    if (fb < -1 && fatorBalanceamento(raiz->dir) > 0){
        raiz->dir = rotacaoDireita(raiz->dir);
        return rotacaoEsquerda(raiz);
    }

    return raiz;
}

no* remNo(no* raiz, int n){
    if (raiz == NULL){
        return raiz;
    }

    if (n > raiz->n){
        raiz->dir = remNo(raiz->dir, n);
    } else if (n < raiz->n) {
        raiz->esq = remNo(raiz->esq, n);
    } else {
        if (raiz->esq == NULL || raiz->dir == NULL){
            no* temp = NULL;
            if (raiz->esq != NULL){
                temp = raiz->esq;
            } else if (raiz->dir != NULL) {
                temp = raiz->dir;
            }
            if (temp == NULL){
                temp = raiz;
                raiz = NULL;
            } else {
                *raiz = *temp;
            }
            free(temp);

        } else {
            no* temp = encontrarMinimo(raiz->dir);
            raiz->n = temp->n;
            raiz->dir = remNo(raiz->dir, temp->n);
        }
    }

    if (raiz == NULL){
        return raiz;
    }

    int fb = fatorBalanceamento(raiz);

    if (fb > 1 && fatorBalanceamento(raiz->esq) > 0) {
        return rotacaoDireita(raiz);
    }

    if (fb > 1 && fatorBalanceamento(raiz->esq) <= 0) {
        raiz->esq = rotacaoEsquerda(raiz->esq);
        return rotacaoDireita(raiz);
    }

    if (fb < -1 && fatorBalanceamento(raiz->dir) < 0) {
        return rotacaoEsquerda(raiz);
    }

    if (fb < -1 && fatorBalanceamento(raiz->dir) >= 0) {
        raiz->dir = rotacaoDireita(raiz->dir);
        return rotacaoEsquerda(raiz);
    }

    return raiz;
}

no* rNo(no* raiz, int n){
    if (raiz == NULL){
        return raiz;
    }
    if (n > raiz->n){
        raiz->dir = rNo(raiz->dir, n);
    }else if(n < raiz->n){
        raiz->esq = rNo(raiz->esq, n);
    } else {
        if (raiz->esq == NULL || raiz->dir == NULL){
            no* temp = NULL;
            if (raiz->esq != NULL){
                temp = raiz->esq;
            }else{
                temp = raiz->dir;
            }
            if (temp == NULL){
                temp = raiz;
                raiz = NULL;
            } else {
                *raiz = *temp;
            }
            free(temp);

        } else {
            no* temp = encontrarMinimo(raiz->dir);
            raiz->n = temp->n;
            raiz->dir = rNo(raiz->dir, temp->n);
        }
    }
    if (raiz == NULL){
        return raiz;
    }

    int fb = fatorBalanceamento(raiz);
    // caso esquerda

    if (fb > 1 && fatorBalanceamento(raiz->esq) >= 0){
        return rotacaoDireita(raiz);
    }

    if (fb > 1 && fatorBalanceamento(raiz->esq) < 0){
        raiz->esq = rotacaoEsquerda(raiz);
        return rotacaoDireita(raiz);
    }

    if (fb < -1 && fatorBalanceamento(raiz->dir) <= 0){
        return rotacaoEsquerda(raiz);
    }

    if (fb < -1 && fatorBalanceamento(raiz->dir) > 0){
        raiz->dir = rotacaoDireita(raiz->dir);
        return rotacaoEsquerda(raiz);
    }

    return raiz;
}

int main() {
    printf("Arvore Binaria de Busca!\n\n");
    no* raiz = NULL;
    no* raiz2 = NULL;
    no* raiz3 = NULL;
    int i=0;
    int valores[11] = {50, 30, 20, 60, 65, 55, 70, 68, 15, 35, 79};
    int valores2[12] = {50, 30, 20, 60, 65, 55, 70, 68, 15, 35, 79, 80};
    int valores3[5] = {10, 5, 20, 15, 25};
    for(i=0; i<11; i++) {
        raiz = inserirNo(valores[i], raiz);
    }
    for(i=0; i<12; i++) {
        raiz2 = inserirNo(valores2[i], raiz2);
    }

    for(i=0; i<5; i++) {
        raiz3 = inserirNo(valores3[i], raiz3);
    }
    printf("\n\nAQUI\n\n");
    int aux = verificaIgualdade(raiz, raiz2);
    printf("AUX: %d", aux);
    if(aux == 1){
        printf("Arvores iguais");
    } else {
        printf("Arvores diferentes");
    }
    printf("\n\nAQUI2\n");

    printf("\n\nEstrita? %d", verificaEstrita(raiz3));
//    mostrar_preOrdem(raiz);

    no* min = encontrarMinimo(raiz);
    printf("\n\nMinimo valor: %d\n", min->n);

    mostrar_preOrdem(raiz3);
    raiz3 = remNo(raiz3, 10);
    raiz3 = remNo(raiz3, 5);
    mostrar_preOrdem(raiz3);
//
//    no* max = encontrarMaximo(raiz);
//    printf("\nMaximo valor: %d\n", max->n);
//
//    no* encontrado = encontrarNo(raiz, 20);
//    if(encontrado == NULL) {
//        printf("\nValor nao foi encontrado\n");
//    } else {
//        printf("\nEncontrado: %d\n", encontrado->n);
//    }

    printf("\n\nFim!\n\n");
    return 0;
}
