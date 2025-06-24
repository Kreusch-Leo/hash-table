// Implementacao do Cuckoo Hash segundo especificacoes para o trabalho II de Algoritmos e Estruturas de Dados III
// Leonardo Kreusch GRR20245579 - Bacharelado em Ciencia da Computacao - UFPR
// Ultima modificacao em 19/06/2025

// Algoritmos um tanto baseados em: Introduction to Algorithms, Cormen, Leiserson, Rivest. MIT Press, Cambridge, Massachusetts, 1996.

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "hash_table.h"

// First table hash function
int h1(int k, int m) {
    return (k % m);
}

// Second table hash function
int h2(int k, int m) {
    return(floor(m * (k * 0.9 - floor(k * 0.9))));
}

// Creates a cuckoo hash structure with a given size
struct cuckoo_ht_t *create_cuckoo_ht(int size) {
    struct cuckoo_ht_t *ht;

    ht = malloc(sizeof(struct cuckoo_ht_t));

    if (!ht)
        return NULL;

    ht->content_t1 = malloc(size * sizeof(void *));
    
    if (!(ht->content_t1)) {
        free(ht);
        return NULL;
    }
    
    ht->content_t2 = malloc(size * sizeof(void *));

    if (!(ht->content_t2)) {
        free(ht->content_t1);
        free(ht);
        return NULL;
    }

    ht->size = size;

    return ht;
}

// Destroy a given cuckoo ht and frees memory
int destroy_cuckoo_ht(struct cuckoo_ht_t *t) {
    if (!t) 
        return -1;

    if (!(t->content_t1 && t->content_t2))
        return -1;

    for (int c = 0; c < t->size; c++) {
        if(t->content_t1[c])
            free(t->content_t1[c]);
        
        if(t->content_t2[c])
            free(t->content_t2[c]);
    }

    free(t->content_t1);
    free(t->content_t2);

    free(t);

    return 0;
}

int add_content(struct cuckoo_ht_t *t, int k, void *c) {
    if (!t || !(t->content_t1 && t->content_t2))
        return -1;

    // se não for fornecido, aloca espaço para a chave
    if (!c) {
        c = malloc(sizeof(int));
        if (!c)
            return -1;
        *((int *)c) = k;
    }

    int pos1 = h1(k, t->size);

    // slot livre em T1
    if (!t->content_t1[pos1]) {
        t->content_t1[pos1] = c;
        return 0;
    }

    // colisão: mover antiga para T2
    int *old = t->content_t1[pos1];
    int old_key = *old;
    int pos2 = h2(old_key, t->size);

    if (!t->content_t2[pos2]) {
        // mover old para T2
        t->content_t2[pos2] = old;

        // colocar nova em T1
        t->content_t1[pos1] = c;
        return 0;
    }

    // T2 ocupado (não deveria ocorrer, mas trata)
    return -1;
}

// Searchs for data in the ht
void *search_content(struct cuckoo_ht_t *t, int k, int *table, int *p) {
    if (!t) 
        return NULL;

    if (!(t->content_t1 && t->content_t2))
        return NULL;

    int pos = h1(k, t->size);

    if (t->content_t1[pos] && t->content_t1[pos] != (void *)-1 && *((int *)t->content_t1[pos]) == k) {
        *table = 1;
        *p = pos;
        return t->content_t1[pos];
    }

    pos = h2(k, t->size);

    if (t->content_t2[pos] && *((int *)t->content_t2[pos]) == k) {
        *table = 2;
        *p = pos;
        return t->content_t2[pos];
    }

    return NULL;
}

// Removes data from the ht
int remove_content(struct cuckoo_ht_t *t, int k) {
    int *content;
    int v, table, pos;

    if (!t) 
        return -1;

    if (!(t->content_t1 && t->content_t2))
        return -1;

    content = search_content(t, k, &table, &pos);

    if (!content) 
        return(-1);

    v = *content;

    free(content);

    if (table == 1) {
        t->content_t1[pos] = NULL;
    }   else {
        t->content_t2[pos] = NULL;
    } 

    return v;
    
}
// Comparison function to sort print output
int compare_entries(const void *a, const void *b) {
    const struct table_entry *entry_a = a;
    const struct table_entry *entry_b = b;

    if (entry_a->key != entry_b->key)
        return entry_a->key - entry_b->key;
        
    if (entry_a->table != entry_b->table)
        return entry_a->table - entry_b->table;
    
    return entry_a->index - entry_b->index;
}

// Prints content from the structure according to the assigment prompt
void print_tables(struct cuckoo_ht_t *t) {

    if (!t) 
        return;

    if (!(t->content_t1 && t->content_t2))
        return;

    struct table_entry *entries = malloc(sizeof(struct table_entry) * 2 * t->size);

    if (!entries)
        return;

    int count = 0;

    for (int i = 0; i < t->size; i++) {
        if (t->content_t1[i]) {
            entries[count].key = *((int *)t->content_t1[i]);
            entries[count].table = 1;
            entries[count].index = i;
            count++;
        }
    }

    for (int i = 0; i < t->size; i++) {
        if (t->content_t2[i]) {
            entries[count].key = *((int *)t->content_t2[i]);
            entries[count].table = 2;
            entries[count].index = i;
            count++;
        }
    }

    qsort(entries, count, sizeof(struct table_entry), compare_entries);

    for (int i = 0; i < count; i++) {
        printf("%d,%s,%d\n",
               entries[i].key,
               entries[i].table == 1 ? "T1" : "T2",
               entries[i].index);
    }

    free(entries);
}
