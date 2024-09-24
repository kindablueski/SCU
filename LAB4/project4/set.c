//	Xavier Zacklin   
//	Project 4 
//	COEN 12 SPRING 2024
//	TUESDAY 9:15 Am
//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include "set.h"
#include "list.h"

// Node structure for the doubly linked list
typedef struct node {
    void *data;
    struct node *next;
    struct node *prev;
} NODE;

// List structure
typedef struct list {
    int count;
    struct node *head;
    int (*compare)();
} LIST;

// Set structure
typedef struct set {
    int length;
    int count;
    int (*compare)();
    unsigned (*hash)();
    LIST **lists;
} SET;

// Create a new set - O(n) complexity
SET *createSet(int maxElts, int (*compare)(), unsigned (*hash)()) {
    SET *sp;
    int i;
    
    assert(compare != NULL && hash != NULL);
    sp = (SET *)malloc(sizeof(SET));
    assert(sp != NULL);
    
    sp->count = 0;
    sp->compare = compare;
    sp->hash = hash;
    sp->length = maxElts / 20;
    sp->lists = (LIST **)malloc(sizeof(LIST *) * sp->length);
    assert(sp->lists != NULL);
    
    for (i = 0; i < sp->length; i++) {
        sp->lists[i] = createList(compare);
    }
    return sp;
}

// Destroy the set - O(n) complexity
void destroySet(SET *sp) {
    
    assert(sp != NULL);
    int i = 0;
    for (i = 0; i < sp->length; i++) {
        destroyList(sp->lists[i]);
    }
    
    free(sp);
}

// Get the number of elements in the set - O(1) complexity
int numElements(SET *sp) {
    
    assert(sp != NULL);
    return sp->count;

}

// Add an element to the set - O(1) average complexity
void addElement(SET *sp, void *elt) {
    
    assert(sp != NULL && elt != NULL);
    int index = sp->hash(elt) % sp->length;
    
    if (findItem(sp->lists[index], elt) == NULL) {
        addFirst(sp->lists[index], elt);
        sp->count++;
    }
}

// Remove an element from the set - O(n) complexity
void removeElement(SET *sp, void *elt) {
    
    assert(sp != NULL && elt != NULL);
    int index = sp->hash(elt) % sp->length;
    
    if (findItem(sp->lists[index], elt) == NULL) {
      return;
    }
    
    removeItem(sp->lists[index], elt);
    sp->count--;
    
}

// Find an element in the set - O(n) complexity
void *findElement(SET *sp, void *elt) {

    assert(sp != NULL && elt != NULL);
    int index = sp->hash(elt) % sp->length;
    return findItem(sp->lists[index], elt);

}

// Get all elements in the set - O(n) complexity
void *getElements(SET *sp) {

    assert(sp != NULL);
    void **elements = (void **)malloc(sizeof(void *) * sp->count);
    assert(elements != NULL);
    
    int i = 0;
    int j =0;
    
    for (i = 0; i < sp->length; i++) {
        NODE *np = sp->lists[i]->head->next;
        while (np != sp->lists[i]->head) {
            elements[j++] = np->data;
            np = np->next;
        }
    }
    return elements;
}

