// Header para Cuckoo Hash segundo especificacoes para o trabalho II de Algoritmos e Estruturas de Dados III
// Leonardo Kreusch GRR20245579 - Bacharelado em Ciencia da Computacao - UFPR
// Ultima modificacao em 19/06/2025

#ifndef __HASH_TABLE__
#define __HASH_TABLE__


struct cuckoo_ht_t {
    int size;                  // table size (m)
    void **content_t1;         // pointer a vector of pointers t1
    void **content_t2;         // pointer a vector of pointers t2
};

struct table_entry {
    int key;
    int table; // 1 for T1, 2 for T2
    int index;
};

/* First table hash function
    
    In  : key, size
    Out : position
*/
int h1(int k, int m);

/* Second table hash function
    
    In  : key, size
    Out : position
*/
int h2(int k, int m);


/* Creates a cuckoo hash structure with a given size

    In  : size (m)
    Out : pointer to struct
*/
struct cuckoo_ht_t *create_cuckoo_ht(int size);


/* Destroy a given cuckoo ht and frees memory
    
    In  : pointer to struct
    Out : successful operation (0), error (1)
*/
int destroy_cuckoo_ht(struct cuckoo_ht_t *t);

/* Adds new data to the ht, 
    if possible to t1
    else if possible to t2
    else error
    
    In  : pointer to struct, key value
    Out : successful operation (0), error (1)
*/
int add_content(struct cuckoo_ht_t *t, int k, void *c);

/* Searchs for data in the ht, 
    
    In  : pointer to struct, key value
    Out : if exists: pointer to content
          else: NULL
*/
void *search_content(struct cuckoo_ht_t *t, int k, int *table, int *pk);

/* Removes data from the ht, 
    
    In  : pointer to struct, key value
    Out : if exists: value of content
          else: -1
*/
int remove_content(struct cuckoo_ht_t *t, int k);

/* Prints content from the structure according to the assigment prompt, 
    
    In  : pointer to struct
    Out : void
*/
void print_tables(struct cuckoo_ht_t *t);

#endif