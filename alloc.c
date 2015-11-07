#include <stddef.h>
#include <stdio.h>
#include "alloc.h"

/* Pointeur sur le premier block free */
/* Vaut NULL si il n'y en a pas */
FreeBlock* first_FB = NULL;

/**
 * mem_init
 * Initialise la liste des zones libres avec une seule zone correspondant à l'ensemble du tableau
 * mem_heap.
 *
 * Lorsqu’on appelle mem_init alors que des allocations et libérations ont déjà été
 * effectuées, l’ensemble des structures de données est réinitialisé.
 */
void mem_init(){
    /* Définit le heap complet comme une block libre */
    first_FB = (FreeBlock*) mem_heap;
    first_FB->size = HEAP_SIZE;
    first_FB->next = NULL;
}


/*

*/
/**
 * mem_alloc
 * Retourne un pointeur sur une zone mémoire alloué de la taille ``size`` dans mem_heap. La taille
 * est arrondie au plus petit multiple de la taille du descripteur de zone supérieur ou égal à
 * size
 * @param size : taille de la zone à allouer
 * return : pointeur sur la zone alloué. NULL si allocation impossible
 */
void *mem_alloc(size_t size){
    FreeBlock *wCurrentFB = first_FB;
    /* Pointeur de pointeur du FreeBlock précédent */
    /* Ce pointeur est utilisé pour remplacer la valeur next du FreeBLock précédent */
    FreeBlock **wOldFBNext = &first_FB;

    /* Retourne NULL si Le heap est complet */
    if (first_FB == NULL){
        return NULL;
    }

    /* Calcul de la vrai taille du bloc à allouer */
    int wFreeBlockSize = sizeof(FreeBlock);
    int wDiff = size % wFreeBlockSize;
    if (wDiff != 0){
        size += wFreeBlockSize - wDiff;
    }

    /* Avance dans la liste des FreeBlock pour trouver un bloc sufisamment grand */
    while(wCurrentFB->size < size){
        /* La fin de la liste a été atteinte */
        if(wCurrentFB->next == NULL){
            return NULL;
        }
        /* Sauvegarde l'adresse du pointeur next de courant puis avance dans la liste */
        else{
            wOldFBNext = &(wCurrentFB->next);
            wCurrentFB = wCurrentFB->next;
        }
    }

    /* wCurrentFB pointe vers un FreeBlock de taille sufissante */
    /* Le block fait exactement la taille nécessaire */
    if(wCurrentFB->size == size){
        *wOldFBNext = wCurrentFB->next;
    }
    /* Le bloc est plus grand que necessaire */
    else{
        FreeBlock *wNewFreeBlock = (FreeBlock*) ((char*)wCurrentFB + size);
        wNewFreeBlock->size = wCurrentFB->size - size;
        wNewFreeBlock->next = wCurrentFB->next;
        *wOldFBNext = wNewFreeBlock;
    }

    return wCurrentFB;
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
 * mem_show
 * Utilise la fonction passé en paramètre pour afficher les spécifications de toutes les zones *
 * libres du heap.
 * @param print : procedure affichant le bloc mémoire à une adresse et taille passé en paramètre
 */
void mem_show(void (*print)(void *zone, size_t size)){
    FreeBlock *wCurrentBlock = first_FB;

    while(wCurrentBlock != NULL){
        print(wCurrentBlock, wCurrentBlock->size);
        wCurrentBlock = wCurrentBlock->next;
    }
}
