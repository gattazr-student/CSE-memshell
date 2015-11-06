#include <stddef.h>
#include <stdio.h>
#include "alloc.h"

/**
 * mem_init
 * Initialise la liste des zones libres avec une seule zone correspondant à l'ensemble du tableau
 * mem_heap.
 *
 * Lorsqu’on appelle mem_init alors que des allocations et libérations ont déjà été
 * effectuées, l’ensemble des structures de données est réinitialisé.
 */
void mem_init(){
    /* TODO: test function */
    int wTailleStructFb;
    /* Création de la liste gestion mémoire en tête du heap */
    wTailleStructFb = sizeof(FreeBlock);

    FreeBlock *wFirstBlock = (FreeBlock*) mem_heap;
    FreeBlock *wFreeBlock = (FreeBlock*)mem_heap + wTailleStructFb;

    wFirstBlock->size = 0;
    wFirstBlock->next = wFreeBlock;

    /* Création de l'élément vide en mémoire */
    wFreeBlock->size = HEAP_SIZE - wTailleStructFb;
    wFreeBlock->next = NULL;
}

/**
 * mem_alloc
 * @param size
 */
void *mem_alloc(size_t size){
    /* TODO: write function */
    return NULL;
}

/**
 * mem_free
 * @param zone :
 * @param size :
 */
void mem_free(void *zone, size_t size){
    /* TODO: write function */
}

/**
 * mem_free
 * Utilise la fonction passé en paramètre pour afficher les spécifications de toutes les zones libres du heap.
 * @param print : procedure affichant le bloc mémoire à une adresse et taille passé en paramètre
 */
void mem_show(void (*print)(void *zone, size_t size)){
    /* TODO: write function */
    FreeBlock *wCurrentBlock = (FreeBlock*) mem_heap;
    int wI = 0;
    while(wCurrentBlock != NULL){
        printf("%d : ", wI);
        print(wCurrentBlock, wCurrentBlock->size);
        wCurrentBlock = wCurrentBlock->next;
        wI++;
    }
}
