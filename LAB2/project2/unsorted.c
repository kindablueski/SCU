//
//	Xavier Zacklin
//	COEN 12 SPRING 2024
//
//#include <stdio.h>
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
//  Time : O(n)
static int search(SET *sp, char *elt, bool *tf){
	assert(sp != NULL);
	int i;
	*tf = false;
	for (i = 0; i < sp->count; i++)
	{
		if(strcmp(elt, sp->data[i]) == 0)
		{
			*tf = true;
			return i;
		}
	}
	return -1;


}
// TIME : O(1)
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
//Time : O(n)
void destroySet(SET *sp)
 
{
	int i;
	assert(sp != NULL);
	for (i = 0; i < sp->count; i++)
		free(sp->data[i]);
	free(sp->data);
	free(sp);



}
// Time : O(1)
int numElements(SET *sp){

	assert(sp != NULL);
	return sp->count;

} 
// Time : O(n)
void addElement(SET *sp, char *elt){
	
	bool tf = NULL;
	if (search(sp, elt,&tf) ==-1)
	{
		assert (sp!= NULL);
		if (sp->count == sp-> length){
		
			printf("The set is full\n");
			return;	
		}	
		sp->data[sp->count] = strdup(elt); 
		sp->count +=1;
	}
	return;
} 

//Time O(n)
void removeElement(SET *sp, char *elt){
	bool tf ;
	int i;
	assert(sp!=NULL);
	i = search(sp, elt, &tf);
	if (i == -1)
	{
		return;
	}
		sp->data[i] = sp->data[sp->count-1];
		sp->data[sp->count-1] = NULL;
		sp->count -=1;
	
	return;
}
//Time O(n)
char *findElement(SET *sp, char *elt){
	
	bool tf ;	
	int found;
	found = search(sp, elt , &tf);
	if (found != -1)
	{
		return(sp->data[found]);
	}
	return NULL;

}
// Time O(n)
char **getElements(SET *sp){
	int i;
	char **array = malloc(sizeof(char*)* sp->count);
	for (i =0; i < sp->count; i++)
	{
		array[i] = sp->data[i];
	}
	return array;	
	
}
