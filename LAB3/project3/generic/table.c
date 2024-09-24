//
//
//	Xavier Zacklin
//	Lab 3 GENERIC 
//	COEN 12 2024
//	THURSDAY 9:15 SECTION
//
//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "set.h"

#define EMPTY 0
#define DELETED 1
#define FILLED 2

typedef struct set {
    int count; // holds an array of elements
    int length; // holds the maximum number of elements
    void **data; //holds the current count of the elements
    char *flags; // flags to indicate the state of the hash table
    int (*compare)(); // compares the two pointers
    unsigned (*hash)(); // pointer for hash function
} SET;

// Searches for an element in teh hash table and either returns its location or the location it will be inserted in (O(n))
static int searchElement(SET *sp, void *elt, bool *found) {
    assert(sp != NULL && elt != NULL);
    int location = -1;
    unsigned hash = (*sp->hash)(elt) % sp->length;

    for (int i = 0; i < sp->length; i++) {
        int index = (hash + i) % sp->length;

        if (sp->flags[index] == FILLED) {
            if ((*sp->compare)(sp->data[index], elt) == 0) {
                *found = true;
                return index;
            }
        } else if (sp->flags[index] == DELETED) {
            if (location == -1) {
                location = index;
            }
        } else if (sp->flags[index] == EMPTY) {
            *found = false;
            if (location != -1) {
                return location;
            } else {
                return index;
            }
        }
    }

    *found = false;
    return location;
}
// Creates a set and allocates memory O (n)
SET *createSet(int maxElts, int (*compare)(), unsigned (*hash)()) {
    SET *sp = malloc(sizeof(SET));
    assert(sp != NULL);
    sp->length = maxElts;
    sp->count = 0;
    sp->data = malloc(sizeof(void*) * maxElts);
    sp->flags = malloc(sizeof(char) * maxElts);
    assert(sp->data != NULL && sp->flags != NULL);

    for (int i = 0; i < sp->length; i++) {
        sp->flags[i] = EMPTY;
    }

    sp->compare = compare;
    sp->hash = hash;
    return sp;
}

// Function to add an element to the set (O(n))
void addElement(SET *sp, void *elt) {
    assert(sp != NULL && elt != NULL);
    if (sp->count == sp->length) return;

    bool found = false;
    int index = searchElement(sp, elt, &found);

    if (!found && index != -1) {
        sp->data[index] = elt;
        sp->flags[index] = FILLED;
        sp->count++;
    }
}

// Function to get rid of the set and free all the memory allocated for it (O(n))
void destroySet(SET *sp) {
    assert(sp != NULL);
    free(sp->data);
    free(sp->flags);
    free(sp);
}

// Function to return the number of elements in the Set (O(1))
int numElements(SET *sp) {
    return sp->count;
}

// Function to find an element in the set (o(n))
void *findElement(SET *sp, void *elt) {
    assert(sp != NULL && elt != NULL);
    bool found = false;
    int index = searchElement(sp, elt, &found);
    if (found) {
        return sp->data[index];
    } else {
        return NULL;
    }
}

// Function to remove an element from the set (O(n))
void removeElement(SET *sp, void *elt) {
    assert(sp != NULL && elt != NULL);
    bool found = false;
    int index = searchElement(sp, elt, &found);
    if (found) {
        sp->flags[index] = DELETED;
        sp->count--;
    }
}

// Function to create a seperate array containing all the elements from the set (O(n))
void *getElements(SET *sp) {
    assert(sp != NULL);
    void **array = malloc(sizeof(void*) * sp->count);
    assert(array != NULL);
    
    int j = 0;
    for (int i = 0; i < sp->length; i++) {
        if (sp->flags[i] == FILLED) {
            array[j++] = sp->data[i];
        }
    }

    return array;
}
    
    
 
