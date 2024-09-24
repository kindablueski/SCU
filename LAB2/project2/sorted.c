#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "set.h"

typedef struct set {
	int length;
	int count;
	char **data ; 
}SET;


static int search(SET *sp, char *elt, bool *tf);
// O (log n)
static int search(SET *sp, char *elt, bool *tf){
	assert(sp != NULL);
	int left =0;
	int mid;
	int right = sp->count -1;
	
	while(left <= right)
	{
		mid = (left+right)/2;
		
		if (strcmp(sp->data[mid],elt) < 0)
			left = mid +1 ;
		if (strcmp(sp->data[mid],elt) > 0)
			right = mid -1;
		if (strcmp(sp->data[mid],elt) == 0)
		{
			*tf = true;
			return mid;
		}
	}
	*tf = false;
	return left;
}

// Time : O(1)
SET *createSet(int maxElts) {

	SET *sp;
	sp = malloc(sizeof(SET));
	assert(sp != NULL);
	sp-> count = 0;
	sp -> length = maxElts;
	sp-> data = malloc(sizeof(char*)*maxElts);
	assert(sp->data != NULL);
	return sp;

}
 
// Time : O(n)
void destroySet(SET *sp)
 
{
	int i;
	assert(sp != NULL);
	for (i = 0; i < sp->count; i++)
		free(sp->data[i]);
	free(sp->data);
	free(sp);



}
// Time O(1)
int numElements(SET *sp){

	assert(sp != NULL);
	return sp->count;

} 

//Time O(n)
void addElement(SET *sp, char *elt){
	
	assert(sp!=NULL);
	int found;
	bool tf = false;
	found = search(sp, elt, &tf);
	if (tf == true)
		return;
	if(sp->count == sp->length)
    	{
        	printf("The array is full\n");
        	return;
    	}
    
    	for(int i = sp->count; i > found; i--)
    	{
        	sp->data[i] = sp->data[i - 1];
    	}
    	sp->data[found] = strdup(elt);
    	sp->count += 1;
    	return;

} 

//TIme O(n)
void removeElement(SET *sp, char *elt){
	bool tf ;
	int found;
	assert(sp!=NULL);
	found = search(sp, elt, &tf);
	if (tf == true)
	{
		free(sp->data[found]);
		for (int i = found+1; i<sp->count; i++)
		{
			sp->data[i-1] = sp->data[i];
		}
		sp->count-=1;
	}
	return;
}
 // Time : O(log n)
char *findElement(SET *sp, char *elt){
	bool tf = false;
	search(sp,elt,&tf);
	if (tf == true)
	{
		return elt;
	}
	return NULL;

}
// Time O(n)
char **getElements(SET *sp){
	int i;
	char **array = malloc(sizeof(char*)* sp->count);
	for (i = 0; i < sp->count; i++)
	{
		array[i] = sp->data[i];
	}
	return array;	
	
}
