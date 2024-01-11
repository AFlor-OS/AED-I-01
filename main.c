
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

#include "t01.h"

int main() {
    char op;
    lista l;
    inicializar(&l);
    char nome[11];
    char numero[11];
    while(1) {
        scanf(" %c", &op);

        if (op == '0') {
            break;
        }

        switch (op) {
            case 'I':
                scanf("%s %s", nome, numero);
                if (existe(&l, nome)) {
                    printf("Contatinho ja inserido\n");
                    break;
                }
                inserir(&l, nome, numero);
            break;
            case 'P':
                scanf("%s", nome);
                contato* c = pesquisar(&l, nome);
                if (c == NULL) {
                    printf("Contatinho nao encontrado\n");
                } else {
                    printf("Contatinho encontrado: telefone %s\n", c->num);
                }
            break;
            case 'A':
                scanf("%s %s", nome, numero);
                if (!existe(&l, nome)) {
                    printf("Operacao invalida: contatinho nao encontrado\n");
                    break;
                }
                inserir(&l, nome, numero);            
            break;
            case 'R':
                scanf("%s", nome);
                if (!existe(&l, nome)) {
                    printf("Operacao invalida: contatinho nao encontrado\n");
                    break;
                } 
                remover(&l, nome);
            break;
            default:
            break;
        }
    }
    //free_lista(&l);
    return 0;
}
