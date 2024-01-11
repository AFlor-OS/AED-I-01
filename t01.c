
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "t01.h"

#define SKIPLIST_MAX_LEVEL 7



static float randomize() {
    return ((float)rand()) / (float)(RAND_MAX);
}

static void imprimir_contato(contato* c) {
    printf("Contatinho encontrado: telefone %s\n", c->num);
}

void inicializar(lista* l) {
    contato* cabeca = (contato*)malloc(sizeof(contato));
    l->cabeca = cabeca;
    strcpy(l->cabeca->nome, "");
    cabeca->prox = (contato**)malloc((SKIPLIST_MAX_LEVEL + 1) * sizeof(contato*));
    for (int i = 0; i <= SKIPLIST_MAX_LEVEL; i++) {
        cabeca->prox[i] = l->cabeca;
    }
    l->nivel = 1;
    l->tam = 0;
}

static int rand_level() {
    int nivel = 1;
    while (rand() < RAND_MAX/2 && nivel < SKIPLIST_MAX_LEVEL) {
        nivel++;
    }
    return nivel;
}

void inserir(lista* l, char* nom, char* numr) {
    contato* novo[SKIPLIST_MAX_LEVEL + 1];
    contato* c = l->cabeca;
    int nivel;
    int i = l->nivel;

    while (i >= 1) {
        while (c->prox[i] != l->cabeca && strcmp(c->prox[i]->nome, nom) < 0) {
            c = c->prox[i];
        }
        novo[i] = c;
        i--;
    }

    if (c->prox[1] != l->cabeca) {
        c = c->prox[1];
    }

    if (c != l->cabeca && strcmp(nom, c->nome) == 0) {
        free(c->num);
        c->num = strdup(numr);
        return;
    } else {
        nivel = rand_level();
        if (nivel > l->nivel) {
            int i = l->nivel + 1;
            while (i <= nivel) {
                novo[i] = l->cabeca;
                i++;
            }
            l->nivel = nivel;
        }
        c = (contato*)malloc(sizeof(contato));
        strcpy(c->nome, nom);
        c->num = strdup(numr);
        c->prox = (contato**)malloc(sizeof(contato*) * (nivel + 1));
        for (int i = 1; i <= nivel; i++) {
            c->prox[i] = novo[i]->prox[i];
            novo[i]->prox[i] = c;
        }
        l->tam = l->tam+1;
    }
}

contato* pesquisar(lista* l, char* n) {
    int i = l->nivel;
    contato* c = l->cabeca;
    while (i >= 1) {
        while (c->prox[i] != l->cabeca && strcmp(c->prox[i]->nome, n) < 0) {
            c = c->prox[i];
        }
        i--;
    }
    if (c->prox[1] != l->cabeca && strcmp(c->prox[1]->nome, n) == 0) {
        return c->prox[1];
    } else {
        return (NULL);
    }
}

int existe(lista* l, char* nom) {
    contato* c = pesquisar(l, nom);
    return (c != NULL);
}

static void free_cont(contato* c) {
    if(c){
        free(c->prox);
        free(c);
    }
}

/*static void free_lista(lista* l) {
    contato* c = l->cabeca->prox[1];
    while (c != l->cabeca) {
        contato* prox_c = c->prox[1];
        free_cont(c);
        c = prox_c;
    }
    free(l->cabeca->prox);
    free(l->cabeca);
}
*/

void remover(lista* l, char* nom) {
    contato* novo[SKIPLIST_MAX_LEVEL + 1];
    contato* c = l->cabeca;

    for (int i = l->nivel; i >= 1; i--) {
        while (c->prox[i] != l->cabeca && strcmp(c->prox[i]->nome, nom) < 0) {
            c = c->prox[i];
        }
        novo[i] = c;
    }

    if (c->prox[1] != l->cabeca) {
        c = c->prox[1];
    }

    if (c != l->cabeca && strcmp(c->nome, nom) == 0) {
        for (int i = 1; i <= l->nivel; i++) {
            if (novo[i]->prox[i] != c) {
                break;
            }
            novo[i]->prox[i] = c->prox[i];
        }
        free(c->num);
        free_cont(c);

        while (l->nivel > 1 && l->cabeca->prox[l->nivel] == l->cabeca) {
            l->nivel--;
        }
        l->tam = l->tam - 1;
    }
}


