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
    FreeBlock *wFreeBlock = (FreeBlock*)((char *) mem_heap + wTailleStructFb);

    wFirstBlock->size = 0;
    wFirstBlock->next = wFreeBlock;

    /* Création de l'élément vide en mémoire */
    wFreeBlock->size = HEAP_SIZE - wTailleStructFb;
    wFreeBlock->next = NULL;
}


/*

*/
/**
 * mem_alloc
 * @param size
 */
void *mem_alloc(size_t size){
    /* TODO: write function */
    FreeBlock* currentPtr = (FreeBlock*)mem_heap;
    FreeBlock* oldPtr = (FreeBlock*)mem_heap;
    if (size < sizeof(FreeBlock))
    {
      size = sizeof(FreeBlock);
    }
    while (currentPtr->size < size) {
      if(currentPtr->next == NULL) //Pas de zone memoire libre. On renvoie NULL
      {
        return NULL;
      } else
      { // On garde en mémoire le block courant et l'ancien.
        oldPtr = currentPtr;
        currentPtr = currentPtr->next;
      }
    }

    //On a trouve un espace memoire disponible et assez grand.
    // L'espace mémoire disponible est plus grand que requis.
    FreeBlock* returnPtr = currentPtr;
    if (returnPtr->size == size)
    {
      oldPtr->next = currentPtr->next;
    } else
    {
      currentPtr = (FreeBlock*) ((char*)returnPtr + size);
      currentPtr->size = returnPtr->size - size;
      currentPtr->next = returnPtr->next;
      oldPtr->next = currentPtr;
    }

    // On renvoie l'adresse de ptr
    return returnPtr;
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
