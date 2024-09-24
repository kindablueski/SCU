//
//	Xavier Zacklin COEN 12 2024 
//	THURSDAY 9:15 SECTION
//	LAB 5 HUFFMAN - COMPRESSES .txt TO .z FILE
//
//
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include "pqueue.h"
#include "pack.h"

// Time Complexity : O(1) , Compares frequencies of nodes
int freqComp(struct node* p, struct node* q){
	return (p->count - q->count);
}

// Time Complexity : O(n), calculates the depth from a node to its parent
int depth(struct node* node) {
	if (node->parent == NULL) {
		return 0;
	}//BASE CASE	
	return depth(node->parent) + 1;

}

struct node* makeNode(int count, struct node*left, struct node* right){
	struct node* newNode = (struct node*) malloc(sizeof(struct node));
	assert(newNode != NULL);
	newNode->parent = NULL;
	newNode->count = count;
	if(left != NULL) left->parent = newNode;
	if(right != NULL) right->parent = newNode;
	return newNode;
}


int main(int argc, char* argv[]) {
	FILE *inputF = fopen(argv[1], "r");
	int counts[256 + 1] = {0};
	struct node *huffnodes[257] = {NULL};
	int c;
	int i = 0;
	int j = 0;
	PQ *priorityQueue = createQueue(freqComp);	
	//count frequency of each character in input file
	while((c = fgetc(inputF)) != EOF) {
		 counts[c]++;
	}
	fclose(inputF);
	//creates a leaf node for each character with non zero frequency
	while(i <257) {
		if(counts[i] > 0) {
			huffnodes[i] = makeNode(counts[i], NULL, NULL);
			addEntry(priorityQueue, huffnodes[i]);
		}
		i++;
	}

	huffnodes[256] = makeNode(0, NULL, NULL);
	addEntry(priorityQueue, huffnodes[256]);
	//constructs the huffman tree removes 2 nodes with smallest frequency and creates a new internal node with the two smallest ones as its children
	while(numEntries(priorityQueue) > 1) {
		struct node *node1 = removeEntry(priorityQueue);
		struct node *node2 = removeEntry(priorityQueue);
		int total = node1->count + node2->count;
		addEntry(priorityQueue, makeNode(total, node1, node2));
	}
	//prints the tree and their bit lengths
	while ( j <257) {
		if (huffnodes[j] != NULL) {
			if(isprint(j)) {
				printf("%c", j);
			} else {
				printf("%03o", j);
			}
			
			printf(": %d * %d bits = %d\n", counts[j], depth(huffnodes[j]), counts[j] * depth(huffnodes[j]));
		}
		j++;
	}

	pack(argv[1], argv[2], huffnodes);
	return 0;
}
