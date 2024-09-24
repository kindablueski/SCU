//
//	Xavier Zacklin COEN 12 2024
//	THURSDAY 9:15 SECTION
//	LAB 5 PQUEUE
//
//
#include "pqueue.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define P(x) ((x-1)/2)
#define L(x) ((x*2) + 1)
#define R(x) ((x*2) + 2)

struct pqueue {
    int count;
    int length;
    void **data;
    int (*compare)();
};

// BigO - O(1) creates and initialize a new priority queue
PQ *createQueue(int (*compare)()) {
    PQ *pq = malloc(sizeof(PQ));
    pq->length = 10;
    pq->data = malloc(sizeof(void*) * pq->length);
    pq->compare = compare;
    pq->count = 0;
    return pq;
}

// BigO - O(1) deallocates memory associated with the priority queue
void destroyQueue(PQ *pq) {
    free(pq->data);
    free(pq);
}

// O(1) returns the number of entries in the queue
int numEntries(PQ *pq) {
    return pq->count;
}

// O(log n) adds an entry to the priority queue
void addEntry(PQ *pq, void *entry) {
    if (pq->count == pq->length) {
        pq->length *= 2;
        void **temp = realloc(pq->data, sizeof(void*) * pq->length);
        assert(temp != NULL);
        pq->data = temp;
    }

    pq->data[pq->count] = entry;
    int idx = pq->count++;
    while (idx > 0 && pq->compare(pq->data[P(idx)], pq->data[idx]) > 0) { // parent is larger
        void *temp = pq->data[P(idx)];
        pq->data[P(idx)] = pq->data[idx];
        pq->data[idx] = temp;
        idx = P(idx);
    }
}

// O(log n) returns and remove the smallest entry in the priority queue
void *removeEntry(PQ *pq) {
    void *root = pq->data[0]; // save root to return later
    pq->data[0] = pq->data[--pq->count];
    int idx = 0;
    int smaller;

    while (L(idx) < pq->count) {
        if (R(idx) < pq->count) {
            if (pq->compare(pq->data[L(idx)], pq->data[R(idx)]) < 0)
                smaller = L(idx);
            else
                smaller = R(idx);
        } else {
            smaller = L(idx);
        }
        if (pq->compare(pq->data[smaller], pq->data[idx]) < 0) { // checking smaller child with parent
            void *temp = pq->data[idx];
            pq->data[idx] = pq->data[smaller];
            pq->data[smaller] = temp;
            idx = smaller;
        } else {
            break;
        }
    }
    return root;
}
