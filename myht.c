// Codigo principal para arvore Red-Black segundo especificacoes para o trabalho I de Algoritmos e Estruturas de Dados III
// Leonardo Kreusch GRR20245579 - Bacharelado em Ciencia da Computacao - UFPR
// Ultima modificacao em 20/04/2025

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rb_tree.h"

int main() {
    struct rb_node *T_nil = init_T_nil();
    struct rb_node *root = T_nil;

    char op;
    int chave;

    while (scanf(" %c %d", &op, &chave) == 2) {
        if (op == 'i') {
            add_node(&root, NULL, chave, T_nil);
        } else if (op == 'r') {
            remove_node(&root, chave, T_nil);
        } else {
            fprintf(stderr, "Operação inválida: %c\n", op);
        }
    }

    print_output_tree(root, T_nil);

    destroy_tree(root, T_nil);
    free(T_nil);
    return 0;
}



