// Codigo principal para semi Cuckoo Hash segundo especificacoes para o trabalho II de Algoritmos e Estruturas de Dados III
// Leonardo Kreusch GRR20245579 - Bacharelado em Ciencia da Computacao - UFPR
// Ultima modificacao em 19/06/2025

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_table.h"

#define M 11

int main(int argc, char *argv[]) {
    struct cuckoo_ht_t *cuckoo_ht;
    char op;
    int chave;

    if (argc > 1) {
        if (strcmp(argv[1], "-h") == 0) {
            printf("Nome: Leonardo Kreusch\nGRR: GRR20245579\nlogin: lk24\n");
        }
        return 0;
    }

    cuckoo_ht = create_cuckoo_ht(M);

    while (scanf(" %c %d", &op, &chave) == 2) {
        if (op == 'i') {
            add_content(cuckoo_ht, chave, NULL);
        } else if (op == 'r') {
            remove_content(cuckoo_ht, chave);
        } else {
            fprintf(stderr, "Operação inválida: %c\n", op);
        }
        //print_tables(cuckoo_ht);
        //printf("\n");
    }

    print_tables(cuckoo_ht);

    destroy_cuckoo_ht(cuckoo_ht);
    
    return 0;
}



