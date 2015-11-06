#include <stddef.h>

/**
 * mem_init
 */
void mem_init(){
    /* TODO: write function */
}


/*

*/
/**
 * mem_alloc
 * @param size
 */
void *mem_alloc(size_t size){
    /* TODO: write function */
    FreeBlock* currentPtr = mem_heap;
    FreeBlock* oldPtr = mem_heap;
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
    fb* returnPtr = currentPtr;
    if (returnPtr->size == size)
    {
      oldPtr->next = currentPtr->next;
    } else
    {
      currentPtr = returnPtr+size;
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
 * @param print :
 */
void mem_show(void (*print)(void *zone, size_t size)){
    /* TODO: write function */
}
