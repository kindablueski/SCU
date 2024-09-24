//	Xavier Zacklin Lab 4 
//	COEN 12 SPRING 2024
//	TUESDAY 9:15 AM
//
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

// Definition of a node in the doubly linked list
void destroyList(LIST *lp);
int numItems(LIST *lp);
void addFirst(LIST *lp, void *item);
void addLast(LIST *lp, void *item);
void *removeFirst(LIST *lp);
void *removeLast(LIST *lp);
void *getFirst(LIST *lp);
void *getLast(LIST* lp);
void removeItem(LIST *lp, void *item);
void *findItem(LIST *lp, void *item);
void *getItems(LIST *lp);
typedef struct node NODE;


struct node {
    void *data;
    NODE *prev;
    NODE *next;
};

// Definition of the list structure
struct list {
    int count;
    NODE *head;
    NODE *tail;
    int (*compare)();
} ;

// Creates and initializes a new list - O(1) complexity
LIST *createList(int (*compare) ()) {
    
	LIST *listPtr = malloc(sizeof(LIST));
    assert(listPtr != NULL);
    listPtr->count = 0;
    listPtr->compare = compare;
    listPtr->head = malloc(sizeof(NODE));
    assert(listPtr->head != NULL);
    listPtr->head->next = listPtr->head;
    listPtr->head->prev = listPtr->head;

    return listPtr;
}

// Frees all memory associated with the list - O(n) complexity
void destroyList(LIST *listPtr) {
    
	assert(listPtr != NULL);
    NODE *currentNode = listPtr->head->next;
    NODE *nextNode;
    while (currentNode != listPtr->head)
	{
        nextNode = currentNode;
        currentNode = currentNode->next;
        free(nextNode);
    }
	free(listPtr->head);
    free(listPtr);
}

// Returns the number of items in the list - O(1) complexity
int numItems(LIST *listPtr) {

    assert(listPtr != NULL);
    return listPtr->count;

}

// Adds an item to the front of the list - O(1) complexity
void addFirst(LIST *listPtr, void *item) {
    
	assert(listPtr != NULL && item != NULL);
    NODE *newNode = malloc(sizeof(NODE));
    newNode->data = item;
    newNode->prev = listPtr->head;
    newNode->next = listPtr->head->next;
    listPtr->head->next = newNode;
    newNode->next->prev = newNode;
    listPtr->count++;

}

// Adds an item to the end of the list - O(1) complexity
void addLast(LIST *listPtr, void *item) {

    assert(listPtr != NULL && item != NULL);
    NODE *newNode = malloc(sizeof(NODE));
    newNode->data = item;
    newNode->next = listPtr->head;
    newNode->prev = listPtr->head->prev;
    listPtr->head->prev = newNode;
    newNode->prev->next = newNode;
    listPtr->count++;

}

// Removes and returns the first item from the list - O(1) complexity
void *removeFirst(LIST *listPtr) {

    assert(listPtr != NULL);
    NODE *nodeToRemove = listPtr->head->next;
    void *firstItem = nodeToRemove->data;
    listPtr->head->next = nodeToRemove->next;
    nodeToRemove->next->prev = listPtr->head;
    free(nodeToRemove);
    listPtr->count--;
    return firstItem;

}

// Removes and returns the last item from the list - O(1) complexity
void *removeLast(LIST *listPtr) {

    assert(listPtr != NULL);
    NODE *nodeToRemove = listPtr->head->prev;
    void *lastItem = nodeToRemove->data;
    nodeToRemove->prev->next = listPtr->head;
    listPtr->head->prev = nodeToRemove->prev;
    free(nodeToRemove);
    listPtr->count--;
    return lastItem;

}

// Returns the data of the first item in the list - O(1) complexity
void *getFirst(LIST *listPtr) {

    assert(listPtr != NULL);
    return listPtr->head->next->data;

}

// Returns the data of the last item in the list - O(1) complexity
void *getLast(LIST *listPtr) {

    assert(listPtr != NULL);
    return listPtr->head->prev->data;

}

// Removes a specific item from the list - O(n) complexity
void removeItem(LIST *listPtr, void *item) {

    assert(listPtr != NULL && item != NULL);
    NODE *currentNode = listPtr->head->next;

    while (currentNode != listPtr->head) {
        if (listPtr->compare(item, currentNode->data) == 0) {
            currentNode->next->prev = currentNode->prev;
            currentNode->prev->next = currentNode->next;
            free(currentNode);
            listPtr->count--;
            return;
        }
        currentNode = currentNode->next;
    }

}

// Finds and returns a specific item in the list - O(n) complexity
void *findItem(LIST *listPtr, void *item) {

    assert(listPtr != NULL && item != NULL);
    NODE *currentNode = listPtr->head->next;

    while (currentNode != listPtr->head) {
        if (listPtr->compare(item, currentNode->data) == 0) {
            return currentNode->data;
        }
        currentNode = currentNode->next;
    }

    return NULL;

}

// Returns an array of all items in the list - O(n) complexity
void *getItems(LIST *listPtr) {
	
    int i;
    assert(listPtr != NULL);
    void **arrcpy = malloc(sizeof(void *) * listPtr->count);
    assert(arrcpy != NULL);
    NODE *currentNode = listPtr->head->next;

    while(currentNode != listPtr->head)
	{
        arrcpy[i] = currentNode->data;
        currentNode = currentNode->next;
    	i++;
	}

    return arrcpy;

}
