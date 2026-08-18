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

int altura(no* raiz) {
    if (raiz == NULL) {
        return -1; // árvore vazia tem altura -1, assim raiz começa em 0
    } else {
        int alturaEsq = altura(raiz->esq);
        int alturaDir = altura(raiz->dir);
        if (alturaEsq > alturaDir) {
            return alturaEsq + 1;
        } else {
            return alturaDir + 1;
        }
    }
}

int maiorValor(no* raiz) {
    if (raiz == NULL){
        return -1;
    } else {
        if (raiz->dir == NULL) {
            return raiz->n;
        } else {
            maiorValor(raiz->dir);
        }
    }
}

// Função auxiliar que percorre a árvore e verifica se é cheia
int verificaCheia(no* raiz, int nivel, int *alturaFolha) {
    if (raiz == NULL) {
        return 1; // Nó vazio não atrapalha
    }

    // Caso 1: Nó folha
    if (raiz->esq == NULL && raiz->dir == NULL) {
        if (*alturaFolha == -1) {
            *alturaFolha = nivel; // Guardamos a altura da primeira folha
        } else if (nivel != *alturaFolha) {
            return 0; // Folha em altura diferente → não é cheia
        }
        return 1;
    }

    // Caso 2: Nó interno mas incompleto
    if (raiz->esq == NULL || raiz->dir == NULL) {
        return 0;
    }

    // Caso 3: Nó interno completo → verificamos recursivamente
    return verificaCheia(raiz->esq, nivel + 1, alturaFolha) &&
           verificaCheia(raiz->dir, nivel + 1, alturaFolha);
}

// Função principal
int arvoreCheia(no* raiz) {
    int alturaFolha = -1; // variável compartilhada
    return verificaCheia(raiz, 0, &alturaFolha);
}

// Receba um valor e faça a remoção do nó que contém esse valor na árvore ABB.

// Função auxiliar para encontrar o menor valor em uma subárvore
no* menorNo(no* raiz) {
    no* atual = raiz;
    while (atual != NULL && atual->esq != NULL) {
        atual = atual->esq;
    }
    return atual;
}

// Função para remover um nó da árvore
no* removerNo(no* raiz, int valor) {
    if (raiz == NULL) {
        return NULL; // Caso 1: árvore vazia ou valor não encontrado
    }

    if (valor < raiz->n) {
        // Procurar na subárvore esquerda
        raiz->esq = removerNo(raiz->esq, valor);
    } else if (valor > raiz->n) {
        // Procurar na subárvore direita
        raiz->dir = removerNo(raiz->dir, valor);
    } else {
        // Caso encontrado

        // Caso 3: Nó folha
        if (raiz->esq == NULL && raiz->dir == NULL) {
            free(raiz);
            return NULL;
        }

        // Caso 4: Nó com apenas um filho
        else if (raiz->esq == NULL) {
            no* temp = raiz->dir;
            free(raiz);
            return temp;
        } else if (raiz->dir == NULL) {
            no* temp = raiz->esq;
            free(raiz);
            return temp;
        }

        // Caso 5: Nó com dois filhos
        else {
            no* temp = menorNo(raiz->dir); // sucessor in-order
            raiz->n = temp->n; // substitui valor
            raiz->dir = removerNo(raiz->dir, temp->n); // remove sucessor
        }
    }
    return raiz;
}


int main() {
    printf("Arvore Binaria de Busca!\n\n");
    no* raiz = NULL;
    int i=0;
    int valores[11] = {50, 30, 70, 20, 40, 60, 80, 35, 45, 65, 85};
    //
    for(i=0; i<11; i++) {
        raiz = inserirNo(valores[i], raiz);
    }
    mostrar_preOrdem(raiz);
    printf("\nMaior valor da arvore e: %d\n", maiorValor(raiz));
    printf("\nAltura da arvore: %d\n", altura(raiz));

    if (arvoreCheia(raiz)) {
        printf("\nA arvore eh cheia!\n");
    } else {
        printf("\nA arvore NAO eh cheia!\n");
    }

        printf("Pre-ordem antes da remocao:\n");
    mostrar_preOrdem(raiz);

    raiz = removerNo(raiz, 30); // remove nó 30
    printf("\nPre-ordem apos remover 30:\n");
    mostrar_preOrdem(raiz);

    raiz = removerNo(raiz, 50); // remove raiz
    printf("\nPre-ordem apos remover 50:\n");
    mostrar_preOrdem(raiz);

    return 0;
}
