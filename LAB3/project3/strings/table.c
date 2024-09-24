//
//
//		LAB 3 Part 1 : STRINGS
//		Xavier Zacklin
//		COEN 12 2024 SPRING
//		THURSDAY 9:15 AM SECION
//
//
//
//
//#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "set.h"
#include <stdbool.h>

#define EMPTY 0
#define DELETED 1
#define FILLED 2

typedef struct set {
    char **data; // holds an array of elements
    int length; // holds the maximum number of elements
    int count; // holds currenot count of elements
    char *flags; // flags to indicate the state of hash table
} SET;

unsigned strhash(char *s);

//Creates a Set and allocates memory, O(n)
SET *createSet(int maxElts) {
    int i;
    SET *sp = malloc(sizeof(SET));
    assert(sp != NULL);
    sp->data = malloc(sizeof(char*) * maxElts);
    assert(sp->data != NULL);
    sp->length = maxElts;
    sp->count = 0;
    sp->flags = malloc(sizeof(char) * maxElts);
    assert(sp->flags != NULL);

    for (i = 0; i < sp->length; i++) {
        sp->flags[i] = EMPTY;
    }
    return sp;
}

// Searches for an element in the hash table and either returns its location or the location it will be inserted in 
// O(n) 
static int search(SET *sp, char *elt, bool *found) {
    assert(sp != NULL || elt != NULL);

    int location = -1;
    int index;
    unsigned hash = strhash(elt);

    for (int i = 0; i < sp->length; i++) {
        index = (hash + i) % sp->length;

        if (sp->flags[index] == FILLED) {
            if (strcmp(sp->data[index], elt) == 0) {
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
            }
            return index;
        }
    }

    *found = false;
    return location;
}
// Function to add an element to the set, O(n) due to search
void addElement(SET *sp, char *elt) {
    assert(sp != NULL && elt != NULL);
    if (sp->count == sp->length) {
        return;
    }

    bool found = false;
    int index = search(sp, elt, &found);
    if (index == -1 || found) {
        return;
    }

    sp->data[index] = strdup(elt);
    sp->flags[index] = FILLED;
    sp->count++;
}

//Function to get rid of a set and free all the memory allocated to it O(n)
void destroySet(SET *sp) {
    int i = 0;
    for (i =0; i < sp->length ; i++){ 
        if (sp->flags[i] == FILLED) {
            free(sp->data[i]);
        }
    }
    free(sp->data);
    free(sp->flags);
    free(sp);
}

// Function to return the number of elements inthe set O(1)
int numElements(SET *sp) {
    return sp->count;
}

//Function to remove an element from the set O(n)
void removeElement(SET *sp, char *elt) {
    assert(sp != NULL && elt != NULL);
    bool found = false;
    int index = search(sp, elt, &found);
    if (found) {
        free(sp->data[index]);
        sp->flags[index] = DELETED;
        sp->count--;
    }
}

//Function to find a specific element in the set, O(n) 
char *findElement(SET *sp, char *elt) {
    assert(sp != NULL && elt != NULL);
    bool found = false;
    int index = search(sp, elt, &found);
    if (found) {
        return sp->data[index];
    }
    return NULL;
}

//Function to copy all elements to a seperate array O(n)
char **getElements(SET *sp) {
    assert(sp != NULL);
    char **array = malloc(sizeof(char*) * sp->count);
    assert(array != NULL);

    int i, j = 0;
    for (i = 0; i < sp->length; i++) {
        if (sp->flags[i] == FILLED) {
            array[j++] = sp->data[i];
        }
    }

    return array;
}

//Function to hash a string O(1)
unsigned strhash(char *s) {
    unsigned hash = 0;
    while (*s != '\0') {
        hash = 31 * hash + *s++;
    }
    return hash;
}
