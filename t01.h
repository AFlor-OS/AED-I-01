
#ifndef T01_H
#define T01_H

#define SKIPLIST_MAX_LEVEL 7

typedef struct contato {
    char* num;
    char nome[11];
    struct contato** prox;
} contato;

typedef struct lista {
    int nivel;
    int tam;
    contato* cabeca;
} lista;

void inicializar(lista* l);
void inserir(lista* l, char* nom, char* numr);
void remover(lista* l, char* nom);
int existe(lista* l, char* nom);
contato* pesquisar(lista* l, char* n);

#endif
